' test tont

Dim As Integer f, f2, fo, i
Dim As String tline
Dim As uByte b

f = Freefile
open "texts.txt" for input as #f
Kill "outp.bin"
fo = Freefile
open "outp.bin" for output as #fo

While Not Eof (f)
	Line Input #f, tline
	f2 = Freefile
	Open "wip.bin" for binary as #f2
	For i = 1 To Len (tline)
		b = Asc (Mid (tline, i, 1))
		Put #f2, , b
	Next i
	Close #f2
	Shell "..\utils\apack.exe wip.bin wipc.bin"
	f2 = Freefile
	Open "wipc.bin" for binary as #f2
	While Not Eof (f2)
		Get #f2, , b
		Put #fo, , b
	Wend
	Close #f2
	Kill "wip.bin"
	Kill "wipc.bin"
Wend
