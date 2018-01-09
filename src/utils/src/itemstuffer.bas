' ItemStuffer v0.1 [MK2 0.90+]
' Copyleft 2015 by The Mojon Twins

Sub usage
	Print "usage"
	Print
	Print "$ itemstuffer.exe items.txt items.bin"
	Print
	Print "items.txt is the input file name. It contains three lines of text per object."
	Print "- Line 1 will be procrusted to 24 chars and used as ITEM NAME."
	Print "- Lines 2, 3 will be procrusted to 28 chars and used as ITEM DESCRIPTION."
	Print
	Print "Output will be items.bin, 80*number of items in items.txt"
	Print
End Sub

Function procrust (s As String, length As Integer) As String
	Dim As String res
	If Len (s) = length Then 
		res = s
	ElseIf Len (s) < length Then
		res = s & Space (length - Len (s))
	Else 
		res = Left (s, length)
	End If
	procrust = res
End Function

Sub writeStringAsBytesToFile (fHandle As Integer, s As String)
	Dim As Integer i
	Dim As uByte d
	For i = 1 To Len (s)
		d = Asc (Mid (s, i, 1))
		Put #fHandle, , d
	Next i
End Sub

' Variables

Dim As Integer fIn, fOut, ctr
Dim As String myline
Dim As uByte d

' GO!

Print "item stuffer v0.1"
Print "Items stuffer for MK2 0.90+"
Print ""

If Command (2) = "" Then
	usage
	End
End If

fIn = FreeFile
Open Command (1) For Input As #fIn
Kill Command (2)
fOut = FreeFile
Open Command (2) For Binary As #fOut

ctr = 0
While Not Eof (fIn)
	Line Input #fIn, myline
	writeStringAsBytesToFile fOut, procrust (myline, 24)
	Line Input #fIn, myline
	writeStringAsBytesToFile fOut, procrust (myline, 28)
	Line Input #fIn, myline
	writeStringAsBytesToFile fOut, procrust (myline, 28)	
	ctr = ctr + 1 
Wend

Close fIn, fOut

Print "" & ctr & " items stuffed into " & Command (2) & "."
Print
