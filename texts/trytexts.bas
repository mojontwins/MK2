'
dim as uByte textsBinary (16384)
dim as uByte textBuff (256)
dim as String packedBuff
dim as integer index, tindex
dim as integer address, n, i
dim as uByte d

index = 0
open "texts.bin" for binary as #1
while not eof (1)
	get #1,,textsBinary (index)
	index = index + 1
wend

do
	print:print
	input "texto"; n
	if n = 99 then system
	
	' get address
	address = textsBinary (n * 2) + 256 * textsBinary (1 + n * 2)
	?address
	address = address - 49152
	? address
	
	' Depack
	packedBuff = ""
	for i = 0 to 255
		packedBuff = packedBuff + Bin (textsBinary (address	+ i), 8)
	next i
	
	index = 0: tindex = 1
	Do
		d = val ("&B" & mid (packedBuff, tindex, 5))
		tindex = tindex + 5
		if d = 0 then
			textBuff (index) = 0
		elseif d = 31 then
			d = val ("&B" & mid (packedBuff, tindex, 5))
			tindex = tindex + 5
			textBuff (index) = d + 32
		else 
			textBuff (index) = d + 64
		end if
		
		index = index + 1
		
	Loop While (d <> 0)
	
	index = 0
	locate csrlin,1:Print string(24,"*");
	locate csrlin,1
	d = textBuff (index) - 64: index = index + 1
	?"LINEAS: " & d
	do
		d = textBuff (index)
		index = index + 1
		if d = 0 then exit do
		if d = asc ("%") then 
			print: locate csrlin,1:Print string(24,"*");: locate csrlin,1
		else
			print chr(d);
		end if
	loop
loop
