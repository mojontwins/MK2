' makepadded
? "Leyendo credits.txt y generando credits.bin"
? "Script mierder 100%"

Dim As String linea
Dim As Integer i
Dim As uByte d

open "credits.txt" for input as #1
open "credits.bin" for binary as #2

while not eof (1)
	line input #1, linea
	linea = trim (linea)
	'linea = Space (16 - len (linea) / 2) & linea
	linea = space ((32 - len (linea)) \ 2) & linea
	linea = linea & Space (32 - len (linea))

	for i = 1 to len (linea)
		d = Asc (Mid (linea, i, 1))
		put #2, , d
	next i
wend

close
