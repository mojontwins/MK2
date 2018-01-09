' Portraits bas
' Takes a lots of portraits in PNG and generates a BIN with all of them

#include "file.bi"
#include "fbpng.bi"
#include "fbgfx.bi"
#include once "crt.bi"

#define RGBA_R( c ) ( CUInt( c ) Shr 16 And 255 )
#define RGBA_G( c ) ( CUInt( c ) Shr  8 And 255 )
#define RGBA_B( c ) ( CUInt( c )        And 255 )
#define RGBA_A( c ) ( CUInt( c ) Shr 24         )

Sub usage
	Print "usage"
	Print ""
	Print "$ portraits.exe output.bin img1.png img2.png ..."
	Print
	Print "Where..."
	Print "   * output.bin is the output binary image."
	Print "   * img?.png are 32x48 monochrome PNG files with the portraits."
	Print	
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

Function getBitPattern (img As Any Ptr, x0 As Integer, y0 As Integer) as uByte
	Dim as uByte x, c, res
	res = 0
	For x = 0 To 7
		If speccyColour(Point (x0 + x, y0, img)) <> 0 Then res = res + 2 ^ (7 - x)
	Next x
	getBitPattern = res
End Function

Sub processAndWrite (img As Any Ptr, fOut As Integer)
	Dim As Integer pixelLine, charLine, column
	Dim As uByte d
	
	' Order is:
	' pixel line > char line > char column
	Puts ("   Writing pixel line > char line > char column")
	For pixelLine = 0 To 7
		For charLine = 0 To 5
			For column = 0 To 3
				d = getBitPattern (img, column * 8, pixelLine + charLine * 8)
				Put #fOut, , d
			Next column
		Next charLine
	Next pixelLine
	Puts ("   Done! 192 bytes written")
End Sub

'' Vars

Dim As Integer fOut
Dim As Integer ptCount, cmdIdx, w, h
Dim As Any Ptr img


'' DO

Print "protraits v0.1"
Print "Packs up a binary with 32x48 pixel portraits for Key To Time (MK2 0.90+)"
Print

If Len (Command (2)) = 0 Then 
	usage
	End
End If

screenres 640, 480, 32, , -1
Kill Command (1)
fOut = FreeFile
Open Command (1) For Binary As #fOut

ptCount = 0
cmdIdx = 2

While Len (Command (cmdIdx))
	Puts ("Processing " & Command (cmdIdx))
	img = png_load (Command (cmdIdx))
	If ImageInfo (img, w, h, , , , ) Then
		' Error!
	End If
	If w <> 32 Or h <> 48 Then 
		Puts ("   All images must be 32x48 pixel PNGs. Aborting")
		End
	End If
	
	processAndWrite img, fOut
	
	cmdIdx = cmdIdx + 1
	ptCount = ptCount + 192
Wend

Close #fOut
Puts ("" & ptCount & " bytes written.")
Puts ("Done!")
