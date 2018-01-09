' Enems to bin
#include "file.bi"
#include once "crt.bi"


Sub usage
	puts ("ene2bin 0.1")
	puts ("usage")
	puts ("")
	puts ("$ ene2bin map_w map_h enems_life enems.ene enems.bin hotspots.bin")
	Puts ("")
	Puts ("where:")
	Puts ("   * map_w, map_h are map dimmensions in screens")
	Puts ("   * enems_life is the enemies max life gauge")
	Puts ("   * enems.ene enems/hotspots directly from colocador.exe")
	Puts ("   * enems.bin output binary file")
	Puts ("   * hotspots.bin output binary file")
End Sub

Type EnemyIn
	t As uByte
	x As uByte
	y As uByte
	xx As uByte
	yy As uByte
	n As uByte
	s1 As uByte
	s2 As uByte
End Type

Dim As Byte flag, is_packed
Dim As integer i, j, x, y, xx, yy, f, fout, idx, byteswritten, totalsize
Dim As uByte d, life, numlocks
Dim As Byte sd
Dim As integer map_w, map_h, tile_lock, max
ReDim As uByte map_data (0, 0)
Dim As uByte whole_screen (149)
Dim As String levelBin
Dim As Any Ptr img
Dim As uByte tileset (2303)
Dim As String dummy
Dim As EnemyIn e


' DO

If Len (Command (1)) = 0 Or Len (Command (2)) = 0 Or Len (Command (3)) = 0 Or Len (Command (4)) = 0 Or Len (Command (5)) = 0  Or Len (Command (6)) = 0Then
	usage
	End
End If

map_w = Val (Command (1))
map_h = Val (Command (2))
life = Val (Command (3))

'' ********************
'' ** ENEMS/HOTSPOTS **
'' ********************

fout = FreeFile
Open Command (5) for Binary as #fout

byteswritten = 0
Puts ("reading enems file")
Puts ("    enems filename = " & Command (4))
f = freefile
Open Command (4) For Binary as #f
' Skip header
dummy = Input (261, f)
' Read enems
max = map_w * map_h * 3 
Puts ("    reading " & max & " enemies")
For idx = 1 To max
	' Read
	Get #f, , e.t
	Get #f, , e.x
	Get #f, , e.y
	Get #f, , e.xx
	Get #f, , e.yy
	Get #f, , e.n
	Get #f, , e.s1
	Get #f, , e.s2
	
	' Write		
	' int16 x, y; lsb msb
	x = e.x * 16
	d = x And &hff: Put #fout, , d
	d = (x Shr 8) And &hff: Put #fout, , d
	
	y = e.y * 16
	d = y And &hff: Put #fout, , d
	d = (y Shr 8) And &hff: Put #fout, , d
	
	' ubyte x1, y1, x2, y2
	d = 16 * e.x: Put #fout, , d
	d = 16 * e.y: Put #fout, , d
	d = 16 * e.xx: Put #fout, , d
	d = 16 * e.yy: Put #fout, , d
	
	' ubyte mx, my
	sd = e.n * sgn (e.xx - e.x): Put #fout, , sd
	sd = e.n * sgn (e.yy - e.y): Put #fout, , sd
	
	' ubyte t
	d = e.t: Put #fout, , d
	
	' ubyte life
	d = life: Put #fout, , d
	
	'puts ("->" & x & ", " & y & ", " & e.x & ", " & e.y & ", " & e.xx & ", " & e.yy & ", " & 
	byteswritten = byteswritten + 12	
Next idx
Puts ("    written " & max & " enemies")
Puts ("    " & byteswritten & " bytes written.")
totalsize = totalsize + byteswritten
byteswritten = 0
Close #fout
fout = FreeFile
Open Command (6) for Binary as #fout

max = map_w * map_h
Puts ("    reading " & max & " hotspots")
For idx = 1 To max
	' Read
	get #f, , e.x
	get #f, , e.t
	
	' Write
	' unsigned char xy
	d = e.x: put #fout, , d
	' unsigned char t
	d = e.t: put #fout, , d
	' unsigned char act
	d = 1: put #fout, , d
	
	byteswritten = byteswritten + 3
Next idx
Close #f
Puts ("    " & byteswritten & " bytes written.")
Puts ("")
