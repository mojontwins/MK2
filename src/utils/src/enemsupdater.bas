' Enems updater (old format -> new format)
' If you like, you can use the old colocador and then feed the .ene to this proggie

sub usage
	print "usage"
	print
	print "$ enemsupdate enemsold.ene enemsnew.ene [verbose]"
	print
	print "Transforms old enems (limited) to the new format. In fact, this is what the"
	print "program does:"
	print
	print "t0   t1"
	print "1    00001000 (8)"
	print "2    00001001 (9)"
	print "3    00001010 (10)"
	print "4    01000011 (67)"
	print "6    00010010 (18)"
	print "7    00011000 (24)"
end sub

Dim As Integer fi, fo, i, map_w, map_h, nenems
Dim As uByte d
Dim As String header

print "enemsupdater 0.1a"

If Command (2) = "" Then usage: End
	
Kill Command (2)
Print "Reading " & Command (1) &"; writing " & Command (2)
fi = Freefile
Open Command (1) For Binary As #fi
fo = Freefile
Open Command (2) For Binary As #fo

' Copy header
header = Input (261, fi)
Put #fo, , header

'For i = 257 To 261: ? i & " = " & Hex (Asc (Mid (header, i, 1)), 2): Next i
map_w = Asc (Mid (header, 257, 1))
map_h = Asc (Mid (header, 258, 1))
nenems = Asc (Mid (header, 261, 1))

For i = 0 To (map_w * map_h * nenems) - 1
	' Read/write register
	
	' Type: change
	Get #fi, , d
	If Command (3) = "verbose" Then
		Print "Type " & d & " found; result = ";
		Select Case d
			Case 1: d = 8
			Case 2: d = 9
			Case 3: d = 10
			Case 4: d = 67
			Case 5: d = 18
			Case 6: d = 18
			Case 7: d = 24
			Case 8: d = 12
		End Select
		Print d
	End If
	Put #fo, , d
	
	Get #fi, , d: Put #fo, , d		' x
	Get #fi, , d: Put #fo, , d		' y
	Get #fi, , d: Put #fo, , d		' xx
	Get #fi, , d: Put #fo, , d		' yy
	Get #fi, , d: Put #fo, , d		' n
	Get #fi, , d: Put #fo, , d		' s1
	Get #fi, , d: Put #fo, , d		' s2
Next i

' Write rest
While Not Eof (fi)
	Get #fi, , d: Put #fo, , d
Wend

Close
? "Done!"
