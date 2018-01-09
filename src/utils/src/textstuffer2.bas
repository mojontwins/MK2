' TextStuffer2 v0.1 [MK2 0.90+]
' Copyleft 2015 by The Mojon Twins

' Compile with fbc textstuffer2.bas cmdlineparser.bas

' Esto está programado muy rápido haciendo enmiendas muy rápidas
' y no tengo ganas de limpiarlo. ¿Funciona? Sí. Po te hoe.

#include "cmdlineparser.bi"

' Textstuffer 

Sub usage
	Print "usage:"
	Print 
	Print "$ textstuffer2.exe output.bin key1=value1 key2=value2 ... "
	Print
	Print "output.bin     Output file name."
	Print ""
	Print "Parameters to textstuffer2.exe are specified as key=value, where keys are "
	Print "as follow:"
	Print ""
	Print "textfile       Input texts, one per line, marked or not."
	Print "mode           Can be 'simple' (like textstuffer), 'character' [*]. If omitted"
	Print "               'simple' is asumed."
	Print "wordwrap       # of chars before a line break (% char)"
	Print "wordwrap_c     # of chars before a line break, for characters talk."
	Print "offset         An offset to be added to every value in the index. Optional."
	Print "ramiro         Special for screen names in ramiro. Don't use. "
	Print "               ramiro=N makes first N lines be preceded by a X coordinate"
	Print "               rather than # of lines, used for text centering. Custom"
	Print
	Print "Outputs 5-bit compressed strings w/scapes."
	Print
	Print "[*] character mode has every line prepended by a two digits hex number"
	Print "    followed by a space. The two digits hex number dictates who is talking"
	Print "    or if it is a general text (when this number is FF). "
	Print 
	Print "    In character mode, wordwrap is used when number = FF, wordwrap_c is"
	Print "    used otherwise."
	Print
	Print "    simple mode doesn't need the wordwrap_c parameter thus it can be "
	Print "    omitted."
	Print
End Sub

Dim as Integer fin, fout
Dim as Integer addresses (1024)
Dim as Integer address, errors
Dim as uByte textBin (16384)
Dim as uByte textBinTemp (1024)
Dim as Integer index, memIndex, memIndexTemp, tlength, memIndexStart
Dim as String textLine, o, m, binaryString
Dim as integer i, j
Dim as Integer offset
Dim as uByte lsb, msb, nlines
Dim as uByte wordWrap, wordWrapC, ww
Dim as uByte x
Dim as Byte mode
Dim as uByte code
Dim as Integer charSubCounter, charCounter, lineCounter, byteCounter
Dim as Integer lineThreshold

'' DO 

Print "textstuffer2 v0.1"
Print "Stuffs 5-bit text for MK2 0.90+"
Print ""

' Get command line parameters parsed.
sclpParseAttrs

' Check If all we need is in.
If Len (Command (1)) = 0 Then 
	usage
	End
End If

errors = 0

' This is lame, but better than nothing:
If Instr (Command (1), "=") Then 
	Print "1st Parameter must be output file name!"
	errors = -1
End If

If sclpGetValue ("textfile") = "" Then
	Print "How could you forget to specify the input file?"
	errors = -1
End If

' Mode = 0 (simple) or -1 (character)
mode = (sclpGetValue ("mode") = "character")

If sclpGetValue ("wordwrap") = "" Then
	Print "wordwrap must be specified."
	errors = -1
End If

If mode And sclpGetValue ("wordwrap_c") = "" Then
	Print "In character mode, wordwrap_c must be specified."
	errors = -1
End If

wordWrap = Val (sclpGetValue ("wordwrap"))
If wordWrap = 0 Then
	Print "wordwrap must be > 0."
	errors = -1
End If

lineThreshold = Val (sclpGetValue ("ramiro"))
Print "    Threshold for screen names @ " & lineThreshold

If mode Then
	wordWrapC = Val (sclpGetValue ("wordwrap_c"))
	If wordWrapC = 0 Then
		Print "wordwrap_c must be > 0."
		errors = -1
	Else
		Print "    Character mode on, width (characters) = " & wordWrapC & ", width (general) = " & wordWrap
	End If
Else
	Print "    Simple mode on, width = " & wordWrap
End If

If errors Then
	Print
	Print "Failed. Run buildlevel.exe with no params to get help."
	End
End If

kill (Command (1))

memIndex = 0
index = 0
address = 0

fin = freefile
Open sclpGetValue ("textfile") For Input as #fin

charCounter = 0
lineCounter = 0
byteCounter = 0

While Not Eof (fin)
	Line Input #fin, textLine
	textLine = Ucase (Trim (textLine))
	lineCounter = lineCounter + 1
	
	' Character mode: store code, trim line
	If mode Then
		code = val ("&H" & Left (textLine, 2))
		textLine = Right (textLine, Len (textLine) - 3)
		If code = &HFF Then 
			ww = wordWrap 
		Else 
			ww = wordWrapC
		End If
		Print "Talks " & code & " - WW used is " & ww
	Else
		ww = wordWrap
	End If
	
	addresses (index) = address
	
	x = 0: o = "": textLine = textLine + " "
	nlines = 1
	tlength = 0
	
	memIndexTemp = 1
	charSubCounter = 0
	For i = 1 To Len (textLine)
		m = mid (textLine, i , 1)
		charCounter = charCounter + 1
		charSubCounter = charSubCounter + 1
		If m = " " then
			If lineCounter > lineThreshold Then
				If x + len (o) >= ww then
					textBinTemp (memIndexTemp - 1) = Asc ("%")
					x = 0
					nlines = nlines + 1	
				End If
			End If
			For j = 1 to len (o)
				textBinTemp (memIndexTemp) = asc (Mid (o, j, 1))
				memIndexTemp = memIndexTemp + 1
			Next j
			x = x + len (o)
			if x = ww And lineCounter > lineThreshold then
				x = 0
				nlines = nlines + 1	
			else
				if i <> len(textLine) then
					textBinTemp (memIndexTemp) = 32
					memIndexTemp = memIndexTemp + 1 					
					x = x + 1
				end if
			end if
			o = ""
		elseif m ="%" then
			For j = 1 to len (o)
				textBinTemp (memIndexTemp) = asc (Mid (o, j, 1))
				memIndexTemp = memIndexTemp + 1
			Next j
			textBinTemp (memIndexTemp) = Asc ("%")
			x = 0
			nlines = nlines + 1	
			memIndexTemp = memIndexTemp + 1 
			o = ""
		else 
			o = o + m
		end if
	next i
	textBinTemp (memIndexTemp) = 0
	
	If lineCounter <= lineThreshold Then
		If charSubCounter > 30 Then textBinTemp (0) = 1 Else textBinTemp (0) = 16 - (charSubCounter \ 2)
	Else
		textBinTemp (0) = nlines
	End If
	
	' pack bits
	binaryString = Bin (textBinTemp (0), 5)
	'? binaryString
	For i = 1 to memIndexTemp
		j = textBinTemp (i)
		if j <> 0 And (j < 32 Or j > 95) Then j = Asc ("[")
		
		If j = 0 Then
			binaryString = binaryString + "00000"
		ElseIf j = 32 Then
			binaryString = binaryString + Bin (30, 5)
		ElseIf j < 64 Then
			' add 31 & j - 32
			binaryString = binaryString + "11111" + Bin (j - 32, 5)
		Else
			' add j - 64
			binaryString = binaryString + Bin (j - 64, 5)
		End If
	Next i
	
	If len (binaryString) Mod 8 <> 0 Then
		binaryString = binaryString + String (8 - (len (binaryString) Mod 8), "0")
	End If
	
	' Store code
	If mode Then
		textBin (memIndex) = code
		memIndex = memIndex + 1
		address = address + 1
		byteCounter = byteCounter + 1
	End If
	
	For i = 1 to len (binaryString) Step 8
		textBin (memIndex) = Val ("&B" & mid (binaryString, i, 8))
		'? mid (binaryString, i, 8) & "=" & Hex (textBin (memIndex), 2);" ";
		memIndex = memIndex + 1
		address = address + 1
		byteCounter = byteCounter + 1
	Next i
'?:?	
	index = index + 1	
Wend

Close #fin

' Fix addresses
''offset = 49152 + index * 2
if sclpGetValue ("offset") <> "" Then 
	offset = Val (sclpGetValue ("offset")) + index * 2 
Else 
	offset = index * 2
End If

For i = 0 to index - 1
	addresses (i) = addresses (i) + offset
next i

fout = freefile
Open Command (1) For Binary as #fout

' Write addresses
For i = 0 to index - 1
	lsb = addresses (i) Mod 256
	msb = addresses (i) Shr 8
	put #fout,,lsb
	put #fout,,msb
	byteCounter = byteCounter + 2
next i

' Write binary
For i = 0 To memIndex - 1
	put #fout,,textBin(i)
Next i

Close fout

Print "    Processing done."
Print "    " & lineCounter & " lines; " & charCounter & " chars packed into " & byteCounter & " bytes."
