' Map to bin

' Spriteset to bin

' Tileset to bin

#include "file.bi"
#include once "crt.bi"



Sub usage
	puts ("map2bin 1.1 - Hanna edition")
	puts ("usage")
	puts ("")
	puts ("$ map2bin mapa.map map_w map_h lock map.bin bolts.bin [connections.txt] [force|twots]")
	Puts ("")
	Puts ("where:")
	Puts ("   * mapa.map is your map from mappy .map")
	Puts ("   * map_w, map_h are map dimmensions in screens")
	Puts ("   * lock is 15 to autodetect lock, 99 otherwise")
	Puts ("   * map.bin is the output map, bin file.")
	Puts ("   * bolts.bin is the output bolts, bin file.")
	Puts ("   * connections.txt - include custom connections.")
	Puts ("   * force - forces packed, extra tiles are output to map.bin.spt.")
	Puts ("   * twots - forces packed + 2ts, tiles 16-31 are writen to map.bin.spt.")
	Puts ("")
	Puts ("packed/unpacked auto-detected")
End Sub

Type LockType
	np as uByte
	x as uByte
	y as uByte
	st as uByte
End Type

' VARS.

Dim As Byte flag, is_packed
Dim As integer i, j, x, y, xx, yy, f, fout, fextra, idx, byteswritten, totalsize
Dim As String levelBin, amalgamer(255), wholeme
Dim As Any Ptr img
Dim As integer map_w, map_h, tile_lock, max
ReDim As uByte map_data (0, 0)
Dim As uByte whole_screen (149)
Dim As Byte somethingOn (255)
Dim As LockType l (32)
Dim As uByte d, life, numlocks
Dim as uByte x_pant, y_pant, n_pant
Dim As Integer doConnections
Dim As Integer doForce, doTwoTs, forceDone, doYawn
Dim As uByte whichTs (255)

' DO

If Len (Command (1)) = 0 Or Len (Command (2)) = 0 Or Len (Command (3)) = 0 Or Len (Command (4)) = 0 Or Len (Command (5)) = 0 Or Len (Command (6)) = 0 Then
	usage
	End
End If

For i = 0 To 255: whichTs (i) = 0: Next i

Kill levelBin

fout = FreeFile
Open Command (5) for Binary as #fout

map_w = Val (Command (2))
map_h = Val (Command (3))
tile_lock = Val (Command (4))

if Command(7) <> "" And Command (7) <> "force" Then doConnections = -1 Else doConnections = 0
if Command(7) = "force" Or Command (8) = "force" Then doForce = -1 Else doForce = 0
if Command(7) = "twots" Or Command (8) = "towts" Then doTwoTs = -1 Else doTwoTs = 0

'' *********
'' ** MAP **
'' *********

Puts ("reading map...")
Puts ("    map filename = " & Command (1))
Puts ("    width in tiles = " & (map_w * 15))
Puts ("    height in tiles = " & (map_h * 10))
is_packed = -1
ReDim As uByte map_data (map_h * 10, map_w * 15)
numlocks = 0: forceDone = 0
f = FreeFile
Open Command(1) For Binary as #f
For y = 0 To (10 * map_h) - 1
	For x = 0 To (15 * map_w) - 1
		Get #f, , d
		map_data (y, x) = d
		' Autodetect unpacked:
		If d > 15 Then
			If doForce Then
				If Not forceDone Then 
					Puts ("    Tile(s) > 15 found, but you said 'force'")
					forceDone = -1
				End If
			ElseIf doTwoTs Then
				If Not forceDone Then 
					Puts ("    Tile(s) > 15 found, but you said 'twots'")
					forceDone = -1
				End If
			Else
				is_packed = 0 
			End If
		End If
		' Autodetect lock
		If d = tile_lock Then
			If numlocks = 32 Then Puts ("ERROR! No more than 32 locks allowed!!"): End
			x_pant = x \ 15: y_pant = y \ 10
			Puts "    lock @ (" & x & ", " & y & ") => (" & x_pant & ", " & y_pant & ")=" & (x_pant + y_pant * map_w) & "."
			l (numlocks).np = x_pant + y_pant * map_w
			l (numlocks).x = x Mod 15
			l (numlocks).y = y Mod 10
			l (numlocks).st = 1
			numlocks = numlocks + 1
		End If
	Next x
Next y
Close #f
Puts ("    total bytes read = " & ((map_w * 15) * (map_h * 10)))

If is_packed Then Puts ("    packed map detected (16 tiles).") else puts ("    unpacked map detected (48 tiles)")
Puts ("    " & numlocks & " bolts found.")

Puts ("writing map...")
byteswritten = 0
If doForce Or doTwoTs Then 
	fExtra = freefile
	Open Command (5) & ".spt" For Output as #fExtra
End If
For y = 0 To map_h - 1
	For x = 0 To map_w - 1
		If is_packed Then
			idx = 0
			n_pant = map_w * y + x
			
			doYawn = 0
			If doForce Or doTwoTs Then
				' Is this needed? YES. Only useful code should be output so msc3 behaves.
				For yy = 0 To 9
					For xx = 0 To 14
						' If map_data (10 * y + yy, 15 * x + xx) Then doYawn = -1: Exit For
						If doForce Then
							If map_data (10 * y + yy, 15 * x + xx) > 15 Then doYawn = -1: Exit For
						ElseIf doTwoTs Then
							If map_data (10 * y + yy, 15 * x + xx) > 15 And map_data (10 * y + yy, 15 * x + xx) < 32 Then doYawn = -1: Exit For
						End If
					Next xx
					If doYawn Then Exit For
				Next yy		
			End If
			
			If doYawn Then 
				Print #fExtra, "ENTERING SCREEN " & Trim (Str (n_pant))
				Print #fExtra, "	IF TRUE"
				Print #fExtra, "	THEN"
				Print #fExtra, "		DECORATIONS"
				
				somethingOn (n_pant) = 0
				amalgamer (n_pant) = "const unsigned char ep_scr_" + hex (n_pant, 2) + " [] = { "
			End If
	
			For yy = 0 To 9
				For xx = 0 To 14
					d = map_data (10 * y + yy, 15 * x + xx)
					
					If d > 15 Then
						If doForce Or (doTwoTs And d < 32) Then
							Print #fExtra, "			" & Trim (Str (xx)) & ", " & Trim (Str (yy)) & ", " & Trim (Str (d))
							If somethingOn (n_pant) Then
								amalgamer (n_pant) = amalgamer (n_pant) & ", "
							Else
								somethingOn (n_pant) = -1
							End If
							amalgamer (n_pant) = amalgamer (n_pant) & "0x" & hex (xx * 16 + yy) & ", " & trim (Str (d))
							d = 0
						End If					
						
						If doTwoTs And d > 31 Then
							d = d - 32
							' Penco
							whichTs (n_pant) = 1
						End If
					End If
					
					whole_screen (idx) = d
					idx = idx + 1
				Next xx
			Next yy
			If doYawn Then 
				amalgamer (n_pant) = amalgamer (n_pant) & " };"
				Print #fExtra, "		END"
				Print #fExtra, "	END"
				Print #fExtra, "END"
				Print #fExtra, " "
			End If
			For i = 0 To 74
				d = (whole_screen (i + i) Shl 4) + (whole_screen (1 + i + i) And 15)
				Put #fout, , d
				byteswritten = byteswritten + 1
			Next i
		Else
			For yy = 0 To 9
				For xx = 0 To 14
					d = map_data (10 * y + yy, 15 * x + xx)
					Put #fout, , d
					byteswritten = byteswritten + 1
				Next xx
			Next yy
		End If
	Next x
Next y

' Write twots map
If doTwoTs Then
	For i = 0 To (map_h * map_w) - 1
		d = whichTs (i)
		Put #fout, , d
		byteswritten = byteswritten + 1
	Next i
End If

If doForce Or doTwoTs Then
	Print #fExtra, " "
	Print #fExtra, "// If you use extraprints.h, trim this bit and use it!"
	wholeme = "const unsigned char *prints [] = { "
	For i = 0 To (map_w * map_h) - 1
		if i > 0 Then wholeme = wholeme & ", "
		If somethingOn (i) Then
			Print #fExtra, amalgamer (i)
			wholeme = wholeme & "ep_scr_" + hex (i, 2)
		else
			wholeme = wholeme & "0"
		End If
	Next i
	wholeme = wholeme & " };"
	Print #fExtra, wholeme
End If
Puts ("    " & byteswritten & " bytes written.")
If doForce Or doTwoTs Then
	Puts ("    Out of range tiles written to " & Command (5) &".spt")
End If
byteswritten = 0

Close
Open Command (6) for Binary as #fout

Puts ("writing bolts...")
For i = 0 To 31
	d = l (i).np: Put #fout, , d
	d = l (i).x: Put #fout, , d
	d = l (i).y: Put #fout, , d
	d = l (i).st: Put #fout, , d
	byteswritten = byteswritten + 4
Next i

Puts ("    " & byteswritten & " bytes written.")
Puts ("")

Close
