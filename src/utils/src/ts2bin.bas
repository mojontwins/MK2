' Tileset to bin

#include "file.bi"
#include "fbpng.bi"
#include "fbgfx.bi"
#include once "crt.bi"

#define RGBA_R( c ) ( CUInt( c ) Shr 16 And 255 )
#define RGBA_G( c ) ( CUInt( c ) Shr  8 And 255 )
#define RGBA_B( c ) ( CUInt( c )        And 255 )
#define RGBA_A( c ) ( CUInt( c ) Shr 24         )

Dim Shared As Integer forceZero

Function speccyColour (colour As Unsigned Long) As uByte
	Dim res as uByte
	If RGBA_R (colour) >= 128 Then 
		res = res Or 2
		If RGBA_R (colour) >= 240 Then
			res = res Or 128
		End If
	End If
	If RGBA_G (colour) >= 128 Then 
		res = res Or 4
		If RGBA_G (colour) >= 240 Then
			res = res Or 128
		End If
	End If
	If RGBA_B (colour) >= 128 Then 
		res = res Or 1
		If RGBA_B (colour) >= 240 Then
			res = res Or 128
		End If
	End If
	speccyColour = res
End Function

Sub getUDGIntoCharset (img As Any Ptr, x0 As integer, y0 As Integer, tileset () As uByte, idx As Integer)
	Dim As Integer x, y
	Dim As uByte c1, c2, b, c, attr
	Dim As String o
	
	' First: detect colours
	c1 = speccyColour (Point (x0, y0, img))
	c2 = c1
	For y = 0 To 7
		For x = 0 To 7
			c = speccyColour (Point (x0 + x, y0 + y, img))
			If c <> c1 Then c2 = c
		Next x
	Next y
	' Detect bright:
	b = 0
	If c1 And 128 Then b = 64: c1 = c1 And 127
	If c2 And 128 Then b = 64: c2 = c2 And 127
	If c1 = c2 Then 
		If forcezero Then
			If c1 = 0 Then c1 = 7 Else c1 = 0
		Else 
			If c2 < 4 Then
				c1 = 7
			Else 
				c1 = 0
			End If
		End If
	end if
	' Darker colour = PAPER (c2)
	If c2 > c1 Then Swap c1, c2
	' Build attribute
	attr = b + 8 * c2 + c1
	' Write to array
	tileset (2048 + idx) = attr

	o = Hex (idx, 2) & " [" & Hex(attr, 2) & "] -->"
	
	' Now build	& write bitmap
	For y = 0 To 7
		b = 0
		For x = 0 To 7
			c = speccyColour (Point (x0 + x, y0 + y, img)) And 127
			If c = c1 Then b = b + 2 ^ (7- x)
		Next x
		tileset (8 * idx + y) = b
		o = o & Hex (b, 2) & " "
	Next y
	' Puts (o)
End Sub

Function getBitPattern (img As Any Ptr, x0 As Integer, y0 As Integer) as uByte
	Dim as uByte x, c, res
	res = 0
	For x = 0 To 7
		If speccyColour(Point (x0 + x, y0, img)) <> 0 Then res = res + 2 ^ (7 - x)
	Next x
	getBitPattern = res
End Function

Sub usage
	puts ("ts2bin 0.2")
	puts ("usage")
	puts ("")
	puts ("$ ts2bin work.png/nofont work.png ts.bin [forcezero]")
	Puts ("")
	Puts ("where:")
	Puts ("   * font.png is a 256x16 file with 64 chars ascii 32-95")
	Puts ("     (use 'nofont' if you don't want to include a font & gen. 192 tiles)")
	Puts ("   * work.png is a 256x48 file with your 16x16 tiles")
	Puts ("   * ts.bin is the output, 2304 bytes bin file.")
	Puts ("   * forcezero: adds 0 as 2nd colour when there's only one per 8x8 cell")
End Sub

' VARS.

Dim As Byte flag, is_packed
Dim As integer i, j, x, y, xx, yy, f, fout, idx, byteswritten, totalsize
Dim As uByte d
Dim As String levelBin
Dim As Any Ptr img
Dim As uByte tileset (2303)

' DO

If Len (Command (3)) = 0 Then
	usage
	End
End If

If Command (4) = "forcezero" Then forcezero = -1 Else forcezero = 0

levelBin = Command (3)

screenres 640, 480, 32, , -1
Kill levelBin

fout = FreeFile
Open levelBin for Binary as #fout

'' *************
'' ** TILESET **
'' *************

' Puts ("building tileset")
idx = 0
If command (1) <> "nofont" then
	Puts ("reading font")
	img = png_load (Command (1))
	Puts ("    font filename = " & Command (1))
	idx = 0
	For y = 0 To 1
		For x = 0 To 31
			getUDGIntoCharset img, x * 8, y * 8, tileset (), idx
			idx = idx + 1	
		Next x
	Next y
	Puts ("    converted 64 chars")
	Puts ("reading 16x16 tiles")
	img = png_load (Command (2))
	Puts ("    tileset filename = " & Command (2))
	x = 0
	y = 0
	For idx = 0 to 47
		getUDGIntoCharset img, x, y, tileset (), idx * 4 + 64
		getUDGIntoCharset img, x + 8, y, tileset (), idx * 4 + 65
		getUDGIntoCharset img, x, y + 8, tileset (), idx * 4 + 66
		getUDGIntoCharset img, x + 8, y + 8, tileset (), idx * 4 + 67
		x = x + 16: If x = 256 Then x = 0: y = y + 16
	Next idx
	Puts ("    converted 192 chars")
	Puts ("writing tileset")
	
	For idx = 0 To 2303
		d = tileset (idx)
		put #fout, , d
	Next idx
	Puts ("    2304 bytes written")
	Puts ("")
Else
	Puts ("reading 16x16 tiles")
	img = png_load (Command (2))
	Puts ("    tileset filename = " & Command (2))
	x = 0
	y = 0
	For idx = 0 to 47
		getUDGIntoCharset img, x, y, tileset (), idx * 4 + 64
		getUDGIntoCharset img, x + 8, y, tileset (), idx * 4 + 65
		getUDGIntoCharset img, x, y + 8, tileset (), idx * 4 + 66
		getUDGIntoCharset img, x + 8, y + 8, tileset (), idx * 4 + 67
		x = x + 16: If x = 256 Then x = 0: y = y + 16
	Next idx
	Puts ("    converted 192 chars")
	Puts ("writing tileset")
	
	For idx = 512 To 2303
		d = tileset (idx)
		put #fout, , d
	Next idx
	Puts ("    1792 bytes written")
	Puts ("")	
End If
Close
