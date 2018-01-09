' Spriteset to bin

' Tileset to bin

#include "file.bi"
#include "fbpng.bi"
#include "fbgfx.bi"
#include once "crt.bi"

#define RGBA_R( c ) ( CUInt( c ) Shr 16 And 255 )
#define RGBA_G( c ) ( CUInt( c ) Shr  8 And 255 )
#define RGBA_B( c ) ( CUInt( c )        And 255 )
#define RGBA_A( c ) ( CUInt( c ) Shr 24         )

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
		if c2 < 4 then
			c1 = 7
		else 
			c1 = 0
		end if
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
	puts ("spg2bin 0.1")
	puts ("converts a PNG file with intertwined sprites/masks to a binary file")
	puts ("width must be multiple of 32, height multiple of 16 (of course...)")
	puts ("usage")
	puts ("")
	puts ("$ spg2bin sprites.png sprites.bin")
	Puts ("")
	Puts ("where:")
	Puts ("   * spriteset.png is a PNG file with your spriteset")
	Puts ("   * sprites.bin is the output, 144*frames bytes")
End Sub

' VARS.

Dim As Byte flag, is_packed
Dim As integer i, j, x, y, xx, yy, f, fout, idx, byteswritten, totalsize, nsprites, w, h
Dim As uByte d
Dim As String levelBin
Dim As Any Ptr img

' DO

If Len (Command (1)) = 0 Or Len (Command (2)) = 0 Then
	usage
	End
End If

levelBin = Command (2)

screenres 640, 480, 32, , -1
Kill levelBin

fout = FreeFile
Open levelBin for Binary as #fout

'' ***************
'' ** SPRITESET **
'' ***************

' Puts ("converting spriteset")

Puts ("reading spriteset")
img = png_load (Command (1))
Puts ("    spriteset filename = " & Command (1))

Puts ("converting & writing spriteset")

x = 0
y = 0
byteswritten = 0
'For idx = 0 To 7
'	d = 0: Put #fout, , d
'	d = 255: Put #fout, , d
'	byteswritten = byteswritten + 2
'Next idx

if ImageInfo (img, w, h, , , , ) then
   'Error!
End If

nsprites = (h \ 16) * (w \ 32)
For idx = 1 To nsprites
	' First & second columns
	For xx = 0 To 8 Step 8
		For yy = 0 To 15
			d = getBitPattern (img, x + xx, y + yy)
			Put #fout, , d
			d = getBitPattern (img, x + xx + 16, y + yy)
			Put #fout, , d
			byteswritten = byteswritten + 2
		Next yy
		For yy = 0 To 7
			d = 0
			Put #fout, , d
			d = 255
			Put #fout, , d
			byteswritten = byteswritten + 2
		Next yy
	Next xx	
	' Third column
	For yy = 0 to 23
		d = 0
		Put #fout, , d
		d = 255
		Put #fout, , d
		byteswritten = byteswritten + 2
	Next yy
	x = x + 32: If x >= w Then x = 0: y = y + 16
Next idx
Puts ("    " & byteswritten & " bytes written in " & nsprites & " frames")
Puts ("")

Close