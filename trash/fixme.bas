'' fixme
dim as integer i
dim as ubyte d
open "mal.ene" for binary as #1
open "enems0.ene" for binary as #2
' Headers
for i = 1 to 256
	get #1,,d:put #2,,d
next i
get #1,,d:put #2,,d
get #1,,d:put #2,,d
get #1,,d:put #2,,d
get #1,,d:put #2,,d
get #1,,d:d = 3:put #2,,d ''fix

for i = 1 to 12
	get #1,,d:put #2,,d
	get #1,,d:put #2,,d
	get #1,,d:put #2,,d
	get #1,,d:put #2,,d
	get #1,,d:put #2,,d
	get #1,,d:put #2,,d
	get #1,,d:put #2,,d
	get #1,,d:put #2,,d
	get #1,,d:put #2,,d
	get #1,,d:put #2,,d
	get #1,,d:put #2,,d
	get #1,,d:put #2,,d
	get #1,,d:put #2,,d
	get #1,,d:put #2,,d
	get #1,,d:put #2,,d
	get #1,,d:put #2,,d
	
	d = 0
	put #2,, d
	put #2,, d
	put #2,, d
	put #2,, d
	
	put #2,, d
	put #2,, d
	put #2,, d
	put #2,, d
next i

for i=1 to 24
d=0:put #2,,d
next i

close