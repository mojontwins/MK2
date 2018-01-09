' mksubts.bas for MK2 v0.1

#include "file.bi"
#include "fbpng.bi"
#include "fbgfx.bi"
#include once "crt.bi"

#define RGBA_R( c ) ( CUInt( c ) Shr 16 And 255 )
#define RGBA_G( c ) ( CUInt( c ) Shr  8 And 255 )
#define RGBA_B( c ) ( CUInt( c )        And 255 )
#define RGBA_A( c ) ( CUInt( c ) Shr 24         )

#define MSB( x ) ( x Shr 8 )
#define LSB( x ) ( x And 255 )

Dim Shared As uByte mainBin (4095)
Dim Shared As uByte patternData (511)
Dim Shared As uByte attributeData (63)
Dim Shared As uByte behsData (15)
Dim Shared As Integer binPtr, patternPtr, attributePtr, behsPtr
Dim As Integer l1, l2, l3, fFin, i

Sub usage
	Print "usage"
	Print ""
	Print "$ mktsubts work.png set behs.txt output.bin"
	Print ""
	Print "Where..."
	Print "   * work.png is the 48 tiles work.png you use elsewhere."
	Print "   * set is 0, 1 or 2 (which tile line you want in the subts?)"
	Print "   * behs.txt has 16 values (comma separated) with the new behs."
	Print "   * output.bin is... well, I'm sure you've guessed."
	Print ""
	Print "This program needs apack.exe somewhere near."
End Sub

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

Sub writeByte (b As uByte)
	mainBin (binPtr) = b
	binPtr = binPtr + 1
End Sub

Sub writeWord (w As Integer)
	w = w And &HFFFF
	'Puts "writeWord " & Hex(w,4) & "(" & Hex(LSB (w),2) & ", " & Hex(MSB (w),2) & ")" & " @ " & binPtr
	writeByte LSB (w)
	writeByte MSB (w)
End Sub

Sub writeFile (fileName As String)
	Dim As Integer fH
	Dim As uByte d
	fH = FreeFile
	Open fileName For Binary As fH
	While Not Eof (fH)
		Get #fH, , d
		writeByte d
	Wend
	Close fH
End Sub

Sub writeWordAt (address As Integer, w As Integer)
	Dim As Integer backup
	backup = binPtr
	binPtr = address
	writeWord w
	binPtr = backup
End Sub

Sub writePatternAt (img As Any Ptr, x0 As Integer, y0 As Integer)
	Dim As Integer x, y
	Dim As uByte c1, c2, b, c

	' Detect colours...
	c1 = speccyColour (Point (x0, y0, img))
	c2 = c1
	For y = 0 To 7
		For x = 0 To 7
			c = speccyColour (Point (x0 + x, y0 + y, img))
			If c <> c1 Then c2 = c
		Next x
	Next y

	' Detect bright
	b = 0
	If c1 And 128 Then b = 64: c1 = c1 And 127
	If c2 And 128 Then b = 64: c2 = c2 And 127

	' Calculate ink when paper = ink
	If c1 = c2 Then 
		If c2 < 4 Then c1 = 7 Else c1 = 0
	End If

	' Darker colour always paper
	If c2 > c1 Then Swap c1, c2

	' Build attribute
	attributeData (attributePtr) = b + 8 * c2 + c1
	attributePtr = attributePtr + 1

	' Write patterns
	For y = 0 To 7
		b = 0
		For x = 0 To 7
			c = speccyColour (Point (x0 + x, y0 + y, img)) And 127
			If c = c1 Then b = b + 2 ^ (7 - x)
		Next x
		patternData (patternPtr) = b
		patternPtr = patternPtr + 1
	Next y
End Sub

Sub makeTileset (fileName As String, x As Integer, y As Integer, n As Integer)
	Dim As Integer i
	Dim As Any Ptr img

	img = png_load (fileName)
	
	patternPtr = 0
	attributePtr = 0

	For i = 1 To n
		writePatternAt img, x, y
		writePatternAt img, x + 8, y
		writePatternAt img, x, y + 8
		writePatternAt img, x + 8, y + 8
		x = x + 16
	Next i
End Sub

Sub readBehs (fileName As String)
	Dim As Integer fIn, beh, i

	behsPtr = 0
	fIn = FreeFile
	Open fileName For Input as fIn
	For i = 0 To 15
		If Eof (fIn) Then Exit For
		Input #fIn, beh
		behsData (behsPtr) = beh
		behsPtr = behsPtr + 1
	Next i
	Close #fIn
End Sub

Function myFileLen (fileName As String) As Integer
	Dim As Integer fTemp, length
	fTemp = FreeFile
	Open fileName For Binary As fTemp
	length = Lof (fTemp)
	Close fTemp
	myFileLen = length
End Function

Sub writeBin (array () As uByte, nBytes As Integer, fileName As String)
	Dim As Integer fH, i

	fH = FreeFile
	Open fileName For Binary As #fH
	For i = 0 To nBytes - 1
		Put #fH, , array (i)
	Next i
	Close #fH
End Sub

'' DO 

Print "mksubts v0.1"
Print "Extracts and packs a subtileset for MK2 0.90+"
Print ""

If Command (4) = "" Then usage: End

screenres 640, 480, 32, , -1
Kill Command (4)

' First we leave space for offset values
binPtr = 4

' Extract tileset
Puts ("reading 16x16 tiles")
makeTileset Command (1), 0, 16 * Val (Command (2)), 16

' Read behs
Puts ("reading behs")
readBehs Command (3)

Puts ("writing temp binary files")
' Now create a temp file with the binary pattern data
writeBin patternData (), patternPtr, "pat.bin"

' And with attribute data
writeBin attributeData (), attributePtr, "att.bin"

' And with behs
writeBin behsData (), behsPtr, "beh.bin"

' Compress everything
Puts ("Compressing...")
Shell """" & ExePath & "\apack.exe"" pat.bin patc.bin > nul"
Shell """" & ExePath & "\apack.exe"" att.bin attc.bin > nul"
Shell """" & ExePath & "\apack.exe"" beh.bin behc.bin > nul"

' Add to binary
Puts ("Adding compressed binaries to output")
writeFile "patc.bin"
writeFile "attc.bin"
writeFile "behc.bin"

' Calculate offsets
l1 = FileLen ("patc.bin")
l2 = FileLen ("attc.bin")
l3 = FileLen ("behc.bin")
Puts ("   Pattern data   = 512 -> " & l1 & " bytes")
Puts ("   Attribute data = 64  -> " & l2 & " bytes")
Puts ("   Behs. data     = 16  -> " & l3 & " bytes")
Puts ("   Total 592 -> " & (l1 + l2 + l3) & " bytes & (~" & Int (100*(l1+l2+l3)/592) & "%)")

' Write offsets
Puts ("Writing index offset")
writeWordAt 0, l1 + 4
writeWordAt 2, l2 + l1 + 4

' Write binary
fFin = FreeFile
Open Command (4) For Binary as fFin
For i = 0 To binPtr - 1
	Put #fFin, , mainBin (i)
Next i
Close #fFin
Puts ("Total " & binPtr & " bytes writen.")

' And clean up temps
kill "pat.bin"
kill "att.bin"
kill "beh.bin"
kill "patc.bin"
kill "attc.bin"
kill "behc.bin"

Puts "Done!"
