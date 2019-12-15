;* * * * *  Small-C/Plus z88dk * * * * *
;  Version: 20100416.1
;
;	Reconstructed for z80 Module Assembler
;
;	Module compile time: Sun Dec 15 11:09:17 2019



	MODULE	mk2.c


	INCLUDE "z80_crt0.hdr"


	LIB SPMoveSprAbs
	LIB SPPrintAtInv
	LIB SPTileArray
	LIB SPInvalidate
	LIB SPCompDListAddr
;	SECTION	text

._keyscancodes
	defw	2175,765,509,1277,1151,0,507,509,735,479
	defw	383,0
;	SECTION	code



._my_malloc
	ld	hl,0 % 256	;const
	push	hl
	call	sp_BlockAlloc
	pop	bc
	ret


;	SECTION	text

._u_malloc
	defw	_my_malloc

;	SECTION	code

;	SECTION	text

._u_free
	defw	sp_FreeBlock

;	SECTION	code

	.vpClipStruct defb 2, 2 + 20, 1, 1 + 30
	.fsClipStruct defb 0, 24, 0, 32
;	SECTION	text

._half_life
	defm	""
	defb	0

;	SECTION	code


;	SECTION	text

._level
	defm	""
	defb	0

;	SECTION	code


;	SECTION	text

._breaking_idx
	defm	""
	defb	0

;	SECTION	code


;	SECTION	text

._do_process_breakable
	defm	""
	defb	0

;	SECTION	code


;	SECTION	text

._do_gravity
	defm	""
	defb	1

;	SECTION	code


;	SECTION	text

._script_result
	defm	""
	defb	0

;	SECTION	code


;	SECTION	text

._sc_terminado
	defm	""
	defb	0

;	SECTION	code


;	SECTION	text

._sc_continuar
	defm	""
	defb	0

;	SECTION	code


	._script defw 0

._SetRAMBank
	.SetRAMBank
	ld a, b
	or a
	jp z, restISR
	xor a
	ld i, a
	jp keepGoing
	.restISR
	ld a, $f0
	ld i, a
	.keepGoing
	ld a, 16
	or b
	ld bc, $7ffd
	out (C), a
	ret


	; aPPack decompressor
	; original source by dwedit
	; very slightly adapted by utopian
	; optimized by Metalbrain
	;hl = source
	;de = dest
	.depack ld ixl,128
	.apbranch1 ldi
	.aploop0 ld ixh,1 ;LWM = 0
	.aploop call ap_getbit
	jr nc,apbranch1
	call ap_getbit
	jr nc,apbranch2
	ld b,0
	call ap_getbit
	jr nc,apbranch3
	ld c,16 ;get an offset
	.apget4bits call ap_getbit
	rl c
	jr nc,apget4bits
	jr nz,apbranch4
	ld a,b
	.apwritebyte ld (de),a ;write a 0
	inc de
	jr aploop0
	.apbranch4 and a
	ex de,hl ;write a previous byte (1-15 away from dest)
	sbc hl,bc
	ld a,(hl)
	add hl,bc
	ex de,hl
	jr apwritebyte
	.apbranch3 ld c,(hl) ;use 7 bit offset, length = 2 or 3
	inc hl
	rr c
	ret z ;if a zero is encountered here, it is EOF
	ld a,2
	adc a,b
	push hl
	ld iyh,b
	ld iyl,c
	ld h,d
	ld l,e
	sbc hl,bc
	ld c,a
	jr ap_finishup2
	.apbranch2 call ap_getgamma ;use a gamma code * 256 for offset, another gamma code for length
	dec c
	ld a,c
	sub ixh
	jr z,ap_r0_gamma ;if gamma code is 2, use old r0 offset,
	dec a
	;do I even need this code?
	;bc=bc*256+(hl), lazy 16bit way
	ld b,a
	ld c,(hl)
	inc hl
	ld iyh,b
	ld iyl,c
	push bc
	call ap_getgamma
	ex (sp),hl ;bc = len, hl=offs
	push de
	ex de,hl
	ld a,4
	cp d
	jr nc,apskip2
	inc bc
	or a
	.apskip2 ld hl,127
	sbc hl,de
	jr c,apskip3
	inc bc
	inc bc
	.apskip3 pop hl ;bc = len, de = offs, hl=junk
	push hl
	or a
	.ap_finishup sbc hl,de
	pop de ;hl=dest-offs, bc=len, de = dest
	.ap_finishup2 ldir
	pop hl
	ld ixh,b
	jr aploop
	.ap_r0_gamma call ap_getgamma ;and a new gamma code for length
	push hl
	push de
	ex de,hl
	ld d,iyh
	ld e,iyl
	jr ap_finishup
	.ap_getbit ld a,ixl
	add a,a
	ld ixl,a
	ret nz
	ld a,(hl)
	inc hl
	rla
	ld ixl,a
	ret
	.ap_getgamma ld bc,1
	.ap_getgammaloop call ap_getbit
	rl c
	rl b
	call ap_getbit
	jr c,ap_getgammaloop
	ret
	._ram_address
	defw 0
	._ram_destination
	defw 0
	._ram_page
	defb 0

._unpack_RAMn
	ld	de,_ram_address
	ld	hl,6-2	;const
	add	hl,sp
	call	l_gint	;
	call	l_pint
	ld	hl,_ram_page
	push	hl
	ld	hl,8	;const
	add	hl,sp
	ld	a,(hl)
	pop	de
	ld	(de),a
	ld	de,_ram_destination
	ld	hl,4-2	;const
	add	hl,sp
	call	l_gint	;
	call	l_pint
	di
	ld a, (_ram_page)
	ld b, a
	call SetRAMBank
	ld hl, (_ram_address)
	ld de, (_ram_destination)
	call depack
	ld b, 0
	call SetRAMBank
	ei
	ret


;	SECTION	text

._resources
	defb	3
	defw	49152
	defb	3
	defw	51623
	defb	3
	defw	51951
	defb	3
	defw	52008
	defb	3
	defw	52527
	defb	3
	defw	52527
	defb	3
	defw	53148
	defb	3
	defw	53717
	defb	3
	defw	53874
	defb	3
	defw	53884
	defb	3
	defw	53902
	defb	3
	defw	54383
	defb	3
	defw	54383
	defb	3
	defw	55506
	defb	3
	defw	56127
	defb	3
	defw	56285
	defb	3
	defw	56301
	defb	3
	defw	56326
	defb	3
	defw	56800
	defb	3
	defw	56800
	defb	3
	defw	57626
	defb	3
	defw	58177
	defb	3
	defw	58306
	defb	3
	defw	58322
	defb	3
	defw	58340
	defb	3
	defw	59092
	defb	3
	defw	59092
	defb	3
	defw	59655
	defb	3
	defw	59844
	defb	3
	defw	59854
	defb	3
	defw	59873
	defb	3
	defw	60315
	defb	3
	defw	60315
	defb	3
	defw	61251
	defb	3
	defw	61849
	defb	3
	defw	61993
	defb	3
	defw	62010
	defb	3
	defw	62030
	defb	3
	defw	62697
	defb	3
	defw	62697
	defb	3
	defw	63907
	defb	3
	defw	64100
	defb	3
	defw	64113
	defb	3
	defw	64137
	defb	3
	defw	64137
	defb	3
	defw	64376
	defb	3
	defw	64390
	defb	3
	defw	64417
	defb	3
	defw	64648
	defb	3
	defw	64658
	defb	3
	defw	64658
	defb	3
	defw	64658
	defb	3
	defw	64658
	defb	3
	defw	64658
	defb	3
	defw	64658
	defb	3
	defw	64658
	defb	3
	defw	64658
	defb	3
	defw	64658
	defb	3
	defw	64830
	defb	3
	defw	64842
	defb	3
	defw	64872
	defb	3
	defw	64890
	defb	3
	defw	64897
	defb	3
	defw	64918
	defb	3
	defw	65167
	defb	3
	defw	65189
	defb	3
	defw	65418
	defb	3
	defw	65435
	defb	4
	defw	49152
	defb	4
	defw	50394
	defb	4
	defw	51144
	defb	4
	defw	51714
	defb	4
	defw	52223
	defb	4
	defw	53334
	defb	4
	defw	53701
	defb	4
	defw	54818
	defb	4
	defw	55525
	defb	4
	defw	56166
	defb	4
	defw	57137
	defb	4
	defw	57522
	defb	4
	defw	57629
	defb	4
	defw	57640
	defb	4
	defw	57955
	defb	4
	defw	58658
	defb	4
	defw	58766
	defb	4
	defw	58775
	defb	4
	defw	58797
	defb	4
	defw	59343
	defb	4
	defw	59622
	defb	4
	defw	59643
	defb	4
	defw	60226
	defb	4
	defw	60392
	defb	4
	defw	60407
	defb	4
	defw	60407
	defb	4
	defw	61056
	defb	4
	defw	61056
	defb	4
	defw	62324
	defb	4
	defw	62536
	defb	4
	defw	62550
	defb	4
	defw	62581
	defb	4
	defw	63241
	defb	4
	defw	63241
	defb	4
	defw	63853
	defb	4
	defw	64142
	defb	4
	defw	64165
	defb	4
	defw	64183
	defb	4
	defw	64248
	defb	4
	defw	64248
	defb	4
	defw	64578
	defb	4
	defw	64588
	defb	4
	defw	64596
	defb	4
	defw	64610
	defb	6
	defw	61213
	defb	6
	defw	62377
	defb	6
	defw	65229
	defb	7
	defw	59265
	defb	7
	defw	60453
	defb	7
	defw	61684

;	SECTION	code


._get_resource
	ld	hl,_resources
	push	hl
	ld	hl,6	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	pop	de
	add	hl,de
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,_resources
	push	hl
	ld	hl,8	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	pop	de
	add	hl,de
	inc	hl
	ld	e,(hl)
	inc	hl
	ld	d,(hl)
	push	de
	ld	hl,6	;const
	add	hl,sp
	call	l_gint	;
	push	hl
	call	_unpack_RAMn
	pop	bc
	pop	bc
	pop	bc
	ret


	._level_data defs 16
	._map defs 3 * 7 * 75
	._tileset
	._font
	BINARY "../bin/font.bin"
	._metatileset
	defs 192*8+256
	._spriteset
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	._sprite_1_a
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	._sprite_1_b
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	._sprite_1_c
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	._sprite_2_a
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	._sprite_2_b
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	._sprite_2_c
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	._sprite_3_a
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	._sprite_3_b
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	._sprite_3_c
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	._sprite_4_a
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	._sprite_4_b
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	._sprite_4_c
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	._sprite_5_a
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	._sprite_5_b
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	._sprite_5_c
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	._sprite_6_a
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	._sprite_6_b
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	._sprite_6_c
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	._sprite_7_a
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	._sprite_7_b
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	._sprite_7_c
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	._sprite_8_a
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	._sprite_8_b
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	._sprite_8_c
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	._sprite_9_a
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	._sprite_9_b
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	._sprite_9_c
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	._sprite_10_a
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	._sprite_10_b
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	._sprite_10_c
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	._sprite_11_a
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	._sprite_11_b
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	._sprite_11_c
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	._sprite_12_a
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	._sprite_12_b
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	._sprite_12_c
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	._sprite_13_a
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	._sprite_13_b
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	._sprite_13_c
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	._sprite_14_a
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	._sprite_14_b
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	._sprite_14_c
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	._sprite_15_a
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	._sprite_15_b
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	._sprite_15_c
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	._sprite_16_a
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	._sprite_16_b
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	._sprite_16_c
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	defb 85, 170
	._baddies defs 3 * 7 * 3 * 12
	._hotspots defs 3 * 7 * 3
	._behs defs 48
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	._sprite_17_a
	defb 0, 128, 56, 0, 117, 0, 123, 0, 127, 0, 57, 0, 0, 0, 96, 0, 238, 0, 95, 0, 31, 0, 62, 0, 53, 128, 42, 128, 20, 128, 0, 192, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255
	._sprite_17_b
	defb 0, 3, 240, 1, 248, 0, 236, 0, 212, 0, 248, 0, 224, 1, 24, 0, 124, 0, 120, 0, 244, 0, 168, 0, 0, 1, 0, 3, 0, 63, 0, 127, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255
	._sprite_17_c
	defb 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255
	._sprite_18_a
	defb 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255
	._sprite_18_b
	defb 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255
	._sprite_18_c
	defb 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255
	._sprite_19_a
	defb 0, 255
	defb 0, 195
	defb 24, 129
	defb 60, 0
	defb 60, 0
	defb 24, 129
	defb 0, 195
	defb 0, 255
	defb 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255
	._sprite_19_b
	defb 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255
	defb 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255
	._sprite_20_a
	defb 0, 255
	defb 0, 0
	defb @10111110, 0
	defb @10110111, 0
	defb @10101011, 0
	defb @10101111, 0
	defb @00001110, 0
	defb 0, @11100000
	defb 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255
	defb 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255
	defb 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255
	._sprite_21_a
	defb 0, 255
	defb 0, 0
	defb @01111101, 0
	defb @11101101, 0
	defb @11010101, 0
	defb @11110101, 0
	defb @01110000, 0
	defb 0, @00000111
	defb 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255
	defb 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255
	defb 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255
;	SECTION	text

._levels
	defb	37
	defb	39
	defb	6
	defb	40
	defb	41
	defb	42
	defb	0
	defb	8
	defb	7
	defb	7
	defb	99
	defb	7
	defb	3
	defb	99
	defb	1
	defb	2
	defb	0
	defb	0
	defb	1
	defw	49152
	defb	3
	defb	5
	defb	6
	defb	7
	defb	8
	defb	9
	defb	17
	defb	0
	defb	2
	defb	2
	defb	99
	defb	1
	defb	12
	defb	1
	defb	1
	defb	0
	defb	0
	defb	1
	defb	0
	defw	0
	defb	17
	defb	19
	defb	20
	defb	21
	defb	22
	defb	23
	defb	1
	defb	9
	defb	12
	defb	2
	defb	99
	defb	10
	defb	1
	defb	1
	defb	1
	defb	0
	defb	1
	defb	0
	defb	0
	defw	0
	defb	30
	defb	32
	defb	33
	defb	34
	defb	35
	defb	36
	defb	2
	defb	0
	defb	3
	defb	2
	defb	99
	defb	12
	defb	1
	defb	1
	defb	1
	defb	0
	defb	0
	defb	1
	defb	1
	defw	59095
	defb	70
	defb	19
	defb	20
	defb	47
	defb	48
	defb	23
	defb	1
	defb	0
	defb	1
	defb	1
	defb	99
	defb	4
	defb	3
	defb	1
	defb	1
	defb	0
	defb	1
	defb	1
	defb	0
	defw	0
	defb	69
	defb	68
	defb	33
	defb	44
	defb	45
	defb	46
	defb	0
	defb	13
	defb	10
	defb	6
	defb	99
	defb	7
	defb	3
	defb	99
	defb	1
	defb	2
	defb	0
	defb	0
	defb	1
	defw	50301
	defb	75
	defb	32
	defb	33
	defb	63
	defb	64
	defb	36
	defb	2
	defb	0
	defb	2
	defb	2
	defb	99
	defb	10
	defb	2
	defb	1
	defb	1
	defb	0
	defb	0
	defb	1
	defb	0
	defw	0
	defb	24
	defb	26
	defb	13
	defb	27
	defb	28
	defb	29
	defb	2
	defb	0
	defb	3
	defb	2
	defb	99
	defb	10
	defb	2
	defb	1
	defb	1
	defb	0
	defb	0
	defb	1
	defb	0
	defw	0
	defb	10
	defb	12
	defb	13
	defb	14
	defb	15
	defb	16
	defb	0
	defb	0
	defb	2
	defb	2
	defb	99
	defb	12
	defb	1
	defb	1
	defb	1
	defb	0
	defb	0
	defb	1
	defb	0
	defw	0
	defb	76
	defb	77
	defb	20
	defb	65
	defb	66
	defb	67
	defb	11
	defb	0
	defb	1
	defb	1
	defb	99
	defb	7
	defb	2
	defb	99
	defb	1
	defb	2
	defb	1
	defb	1
	defb	1
	defw	53915
	defb	71
	defb	72
	defb	13
	defb	57
	defb	58
	defb	59
	defb	3
	defb	9
	defb	1
	defb	6
	defb	99
	defb	4
	defb	4
	defb	1
	defb	1
	defb	2
	defb	0
	defb	1
	defb	1
	defw	51212
	defb	73
	defb	74
	defb	6
	defb	60
	defb	61
	defb	62
	defb	6
	defb	0
	defb	1
	defb	3
	defb	99
	defb	2
	defb	6
	defb	1
	defb	1
	defb	2
	defb	0
	defb	1
	defb	1
	defw	52250
	defb	78
	defb	12
	defb	13
	defb	79
	defb	80
	defb	16
	defb	19
	defb	0
	defb	4
	defb	2
	defb	99
	defb	12
	defb	1
	defb	1
	defb	1
	defb	0
	defb	0
	defb	1
	defb	1
	defw	54759
	defb	81
	defb	82
	defb	6
	defb	83
	defb	84
	defb	85
	defb	2
	defb	9
	defb	12
	defb	5
	defb	99
	defb	1
	defb	10
	defb	1
	defb	1
	defb	0
	defb	0
	defb	0
	defb	1
	defw	55387
	defb	86
	defb	26
	defb	13
	defb	87
	defb	88
	defb	29
	defb	2
	defb	0
	defb	1
	defb	1
	defb	99
	defb	8
	defb	2
	defb	1
	defb	1
	defb	0
	defb	0
	defb	1
	defb	0
	defw	0
	defb	89
	defb	5
	defb	6
	defb	90
	defb	91
	defb	9
	defb	0
	defb	0
	defb	7
	defb	1
	defb	99
	defb	1
	defb	12
	defb	1
	defb	1
	defb	0
	defb	0
	defb	1
	defb	0
	defw	0
	defb	93
	defb	112
	defb	13
	defb	96
	defb	97
	defb	98
	defb	3
	defb	15
	defb	7
	defb	7
	defb	99
	defb	4
	defb	5
	defb	99
	defb	1
	defb	2
	defb	0
	defb	0
	defb	1
	defw	55689
	defb	99
	defb	101
	defb	6
	defb	102
	defb	103
	defb	104
	defb	17
	defb	0
	defb	1
	defb	1
	defb	99
	defb	20
	defb	1
	defb	1
	defb	1
	defb	0
	defb	0
	defb	1
	defb	1
	defw	58378
	defb	105
	defb	117
	defb	6
	defb	108
	defb	109
	defb	110
	defb	3
	defb	0
	defb	12
	defb	8
	defb	99
	defb	3
	defb	1
	defb	99
	defb	1
	defb	2
	defb	0
	defb	0
	defb	1
	defw	58499

;	SECTION	code

;	SECTION	text

._level_sequence
	defm	""
	defb	12

	defm	""
	defb	0

	defm	""
	defb	1

	defm	""
	defb	2

	defm	""
	defb	11

	defm	""
	defb	3

	defm	""
	defb	4

	defm	""
	defb	5

	defm	""
	defb	11

	defm	""
	defb	6

	defm	""
	defb	7

	defm	""
	defb	8

	defm	""
	defb	11

	defm	""
	defb	9

	defm	""
	defb	10

	defm	""
	defb	11

	defm	""
	defb	15

	defm	""
	defb	14

	defm	""
	defb	13

	defm	""
	defb	11

	defm	""
	defb	11

	defm	""
	defb	17

	defm	""
	defb	16

	defm	""
	defb	18

;	SECTION	code


	defw 0

._ISR
	ld b, 1
	call SetRAMBank
	call 0xC000
	ld b, 0
	call SetRAMBank
	ld	hl,(_isrc)
	ld	h,0
	inc	hl
	ld	a,l
	ld	(_isrc),a
	ret



._wyz_init
	ld b,1
	call SetRAMBank
	call 0xC018
	ld b,0
	call SetRAMBank
	ret



._wyz_play_sound
	push	hl
	di
	ld b, 1
	call SetRAMBank
	; __FASTCALL__ -> fx_number is in l!
	ld b, l
	call 0xC47E
	ld b, 0
	call SetRAMBank
	ei
	pop	bc
	ret



._wyz_play_music
	push	hl
	di
	ld b, 1
	call SetRAMBank
	; __FASTCALL__ -> song_number is in l!
	ld a, l
	call 0xC087
	ld b, 0
	call SetRAMBank
	ei
	pop	bc
	ret



._wyz_stop_sound
	di
	ld b,1
	call SetRAMBank
	call 0xC062
	ld b,0
	call SetRAMBank
	ei
	ret



._wyz_play_sample
	di
	ld b, 1
	call SetRAMBank
	; __FASTCALL__ -> sample_number is in l!
	ld a, l
	call 0xC5E5
	ld b, 0
	call SetRAMBank
	ei
	ret


;	SECTION	text

._spacer
	defw	i_1+0
;	SECTION	code


._draw_coloured_tile
	ld a, (__x)
	ld c, a
	ld a, (__y)
	call SPCompDListAddr
	ex de, hl
	ld a, (__t)
	sla a
	sla a
	add 64
	ld hl, _tileset + 2048
	ld b, 0
	ld c, a
	add hl, bc
	ld c, a
	ld a, (hl)
	ld (de), a
	inc de
	inc hl
	ld a, c
	ld (de), a
	inc de
	inc a
	ld c, a
	inc de
	inc de
	ld a, (hl)
	ld (de), a
	inc de
	inc hl
	ld a, c
	ld (de), a
	inc a
	ex de, hl
	ld bc, 123
	add hl, bc
	ex de, hl
	ld c, a
	ld a, (hl)
	ld (de), a
	inc de
	inc hl
	ld a, c
	ld (de), a
	inc de
	inc a
	ld c, a
	inc de
	inc de
	ld a, (hl)
	ld (de), a
	inc de
	ld a, c
	ld (de), a
	ret



._invalidate_tile
	; Invalidate Rectangle
	;
	; enter: B = row coord top left corner
	; C = col coord top left corner
	; D = row coord bottom right corner
	; E = col coord bottom right corner
	; IY = clipping rectangle, set it to "ClipStruct" for full screen
	ld a, (__x)
	inc a
	ld e, a
	ld a, (__y)
	inc a
	ld d, a
	ld a, (__x)
	ld c, a
	ld a, (__y)
	ld b, a
	ld iy, fsClipStruct
	call SPInvalidate
	ret



._invalidate_viewport
	; Invalidate Rectangle
	;
	; enter: B = row coord top left corner
	; C = col coord top left corner
	; D = row coord bottom right corner
	; E = col coord bottom right corner
	; IY = clipping rectangle, set it to "ClipStruct" for full screen
	ld b, 2
	ld c, 1
	ld d, 2+19
	ld e, 1+29
	ld iy, vpClipStruct
	call SPInvalidate
	ret



._draw_invalidate_coloured_tile_g
	call	_draw_coloured_tile_gamearea
	call	_invalidate_tile
	ret



._draw_coloured_tile_gamearea
	ld	a,(__x)
	ld	e,a
	ld	d,0
	ld	l,#(1 % 256)
	call	l_asl
	ld	de,1
	add	hl,de
	ld	h,0
	ld	a,l
	ld	(__x),a
	ld	a,(__y)
	ld	e,a
	ld	d,0
	ld	l,#(1 % 256)
	call	l_asl
	ld	de,2
	add	hl,de
	ld	h,0
	ld	a,l
	ld	(__y),a
	call	_draw_coloured_tile
	ret



._print_number2
	ld	a,(__t)
	ld	e,a
	ld	d,0
	ld	hl,10	;const
	call	l_div_u
	ld	de,16
	add	hl,de
	ld	h,0
	ld	a,l
	ld	(_rda),a
	ld	a,(__t)
	ld	e,a
	ld	d,0
	ld	hl,10	;const
	call	l_div_u
	ex	de,hl
	ld	de,16
	add	hl,de
	ld	h,0
	ld	a,l
	ld	(_rdb),a
	; enter: A = row position (0..23)
	; C = col position (0..31/63)
	; D = pallette #
	; E = graphic #
	ld a, (_rda)
	ld e, a
	ld d, 7
	ld a, (__x)
	ld c, a
	ld a, (__y)
	call SPPrintAtInv
	ld a, (_rdb)
	ld e, a
	ld d, 7
	ld a, (__x)
	inc a
	ld c, a
	ld a, (__y)
	call SPPrintAtInv
	ret



._draw_objs
	ret



._print_str
	ld hl, (_gp_gen)
	.print_str_loop
	ld a, (hl)
	or a
	ret z
	inc hl
	sub 32
	ld e, a
	ld a, (__t)
	ld d, a
	ld a, (__x)
	ld c, a
	inc a
	ld (__x), a
	ld a, (__y)
	push hl
	call SPPrintAtInv
	pop hl
	jr print_str_loop
	ret



._blackout_area
	ld	hl,22593	;const
	ld	(_asm_int),hl
	ld de, (_asm_int)
	ld b, 20
	.bal1
	push bc
	ld h, d
	ld l, e
	ld (hl), 0
	inc de
	ld bc, 29
	ldir
	inc de
	inc de
	pop bc
	djnz bal1
	ret


;	SECTION	text

._utaux
	defm	""
	defb	0

;	SECTION	code



._update_tile
	ld a, (__x)
	ld c, a
	ld a, (__y)
	ld b, a
	sla a
	sla a
	sla a
	sla a
	sub b
	add c
	ld b, 0
	ld c, a
	ld hl, _map_attr
	add hl, bc
	ld a, (__n)
	ld (hl), a
	ld hl, _map_buff
	add hl, bc
	ld a, (__t)
	ld (hl), a
	call _draw_coloured_tile_gamearea
	ld a, (_is_rendering)
	or a
	ret nz
	call _invalidate_tile
	ret



._print_message
	ld	a,#(10 % 256 % 256)
	ld	(__x),a
	ld	a,#(12 % 256 % 256)
	ld	(__y),a
	ld	hl,87 % 256	;const
	ld	a,l
	ld	(__t),a
	call	_print_str
	ld	a,#(10 % 256 % 256)
	ld	(__x),a
	ld	a,#(11 % 256 % 256)
	ld	(__y),a
	ld	a,#(87 % 256 % 256)
	ld	(__t),a
	ld	hl,(_spacer)
	ld	(_gp_gen),hl
	call	_print_str
	ld	a,#(10 % 256 % 256)
	ld	(__x),a
	ld	a,#(13 % 256 % 256)
	ld	(__y),a
	ld	a,#(87 % 256 % 256)
	ld	(__t),a
	ld	hl,(_spacer)
	ld	(_gp_gen),hl
	call	_print_str
	call	sp_UpdateNow
	call	sp_WaitForNoKey
	ret



._read_controller
	ld	hl,(_pad0)
	ld	h,0
	ld	a,l
	ld	(_pad_this_frame),a
	ld	hl,(_joyfunc)
	push	hl
	ld	hl,_keys
	pop	de
	ld	bc,i_19
	push	hl
	push	bc
	push	de
	ld	a,1
	ret
.i_19
	pop	bc
	ld	h,0
	ld	a,l
	ld	(_pad0),a
	ld	hl,(_pad_this_frame)
	ld	h,0
	ex	de,hl
	ld	hl,(_pad0)
	ld	h,0
	call	l_xor
	call	l_com
	ex	de,hl
	ld	hl,(_pad0)
	ld	h,0
	call	l_or
	ld	de,112	;const
	ex	de,hl
	call	l_or
	ld	h,0
	ld	a,l
	ld	(_pad_this_frame),a
	ret



._button_pressed
	call	_read_controller
	ld	a,(_pad_this_frame)
	ld	e,a
	ld	d,0
	ld	hl,255	;const
	call	l_ne
	ld	hl,0	;const
	rl	l
	ld	h,0
	ret



._cortina
	ld b, 7
	.fade_out_extern
	push bc
	ld e, 3 ; 3 tercios
	ld hl, 22528 ; aquí empiezan los atributos
	halt ; esperamos retrazo.
	.fade_out_bucle
	ld a, (hl ) ; nos traemos el atributo actual
	ld d, a ; tomar atributo
	and 7 ; aislar la tinta
	jr z, ink_done ; si vale 0, no se decrementa
	dec a ; decrementamos tinta
	.ink_done
	ld b, a ; en b tenemos ahora la tinta ya procesada.
	ld a, d ; tomar atributo
	and 56 ; aislar el papel, sin modificar su posiciÃ³n en el byte
	jr z, paper_done ; si vale 0, no se decrementa
	sub 8 ; decrementamos papel restando 8
	.paper_done
	ld c, a ; en c tenemos ahora el papel ya procesado.
	ld a, d
	and 192 ; nos quedamos con bits 6 y 7 (0x40 y 0x80)
	or c ; añadimos paper
	or b ; e ink, con lo que recompuesto el atributo
	ld (hl),a ; lo escribimos,
	inc l ; e incrementamos el puntero.
	jr nz, fade_out_bucle ; continuamos hasta acabar el tercio (cuando L valga 0)
	inc h ; siguiente tercio
	dec e
	jr nz, fade_out_bucle ; repetir las 3 veces
	pop bc
	djnz fade_out_extern
	ret



._addsign
	ld	hl,4	;const
	call	l_gintspsp	;
	ld	hl,0	;const
	pop	de
	call	l_eq
	jp	nc,i_20
	ld	hl,0	;const
	jp	i_21
.i_20
	ld	hl,4	;const
	call	l_gintspsp	;
	ld	hl,0	;const
	pop	de
	call	l_gt
	jp	nc,i_22
	pop	bc
	pop	hl
	push	hl
	push	bc
	jp	i_23
.i_22
	pop	bc
	pop	hl
	push	hl
	push	bc
	call	l_neg
.i_23
.i_21
	ret



._abs
	pop	bc
	pop	hl
	push	hl
	push	bc
	xor	a
	or	h
	jp	p,i_24
	pop	bc
	pop	hl
	push	hl
	push	bc
	call	l_neg
	ret


.i_24
	pop	bc
	pop	hl
	push	hl
	push	bc
	ret


.i_25
	ret



._active_sleep
.i_28
	halt
	ld	a,(_p_killme)
	ld	e,a
	ld	d,0
	ld	hl,0	;const
	call	l_eq
	jp	nc,i_30
	call	_button_pressed
	ld	a,h
	or	l
	jr	nz,i_31_i_30
.i_30
	jp	i_29
.i_31_i_30
	jp	i_27
.i_29
.i_26
	pop	de
	pop	hl
	dec	hl
	push	hl
	push	de
	ld	a,h
	or	l
	jp	nz,i_28
.i_27
	ld	hl,0 % 256	;const
	push	hl
	call	sp_Border
	pop	bc
	ret



._select_joyfunc
.i_32
	call	sp_GetKey
	ld	h,0
	ld	a,l
	ld	(_gpit),a
	cp	#(49 % 256)
	jp	z,i_35
	ld	a,(_gpit)
	cp	#(50 % 256)
	jp	nz,i_34
.i_35
	ld	hl,sp_JoyKeyboard
	ld	(_joyfunc),hl
	ld	hl,(_gpit)
	ld	h,0
	ld	bc,-49
	add	hl,bc
	ld	a,h
	or	l
	jp	z,i_37
	ld	hl,6	;const
	jp	i_38
.i_37
	ld	hl,0	;const
.i_38
	ld	h,0
	ld	a,l
	ld	(_gpjt),a
	ld	hl,_keys+8
	push	hl
	ld	hl,_keyscancodes
	push	hl
	ld	hl,_gpjt
	ld	a,(hl)
	inc	(hl)
	ld	l,a
	ld	h,0
	add	hl,hl
	pop	de
	add	hl,de
	call	l_gint	;
	pop	de
	call	l_pint
	ld	hl,_keys+6
	push	hl
	ld	hl,_keyscancodes
	push	hl
	ld	hl,_gpjt
	ld	a,(hl)
	inc	(hl)
	ld	l,a
	ld	h,0
	add	hl,hl
	pop	de
	add	hl,de
	call	l_gint	;
	pop	de
	call	l_pint
	ld	hl,_keys+4
	push	hl
	ld	hl,_keyscancodes
	push	hl
	ld	hl,_gpjt
	ld	a,(hl)
	inc	(hl)
	ld	l,a
	ld	h,0
	add	hl,hl
	pop	de
	add	hl,de
	call	l_gint	;
	pop	de
	call	l_pint
	ld	hl,_keys+1+1
	push	hl
	ld	hl,_keyscancodes
	push	hl
	ld	hl,_gpjt
	ld	a,(hl)
	inc	(hl)
	ld	l,a
	ld	h,0
	add	hl,hl
	pop	de
	add	hl,de
	call	l_gint	;
	pop	de
	call	l_pint
	ld	hl,_keys
	push	hl
	ld	hl,_keyscancodes
	push	hl
	ld	hl,_gpjt
	ld	a,(hl)
	inc	(hl)
	ld	l,a
	ld	h,0
	add	hl,hl
	pop	de
	add	hl,de
	call	l_gint	;
	pop	de
	call	l_pint
	jp	i_33
.i_34
	ld	a,(_gpit)
	cp	#(51 % 256)
	jp	nz,i_40
	ld	hl,sp_JoyKempston
	ld	(_joyfunc),hl
	jp	i_33
.i_40
	ld	a,(_gpit)
	cp	#(52 % 256)
	jp	nz,i_42
	ld	hl,sp_JoySinclair1
	ld	(_joyfunc),hl
	jp	i_33
.i_42
.i_41
.i_39
	jp	i_32
.i_33
	ld	hl,0 % 256	;const
	call	_wyz_play_sound
	call	sp_WaitForNoKey
	ret


;	SECTION	text

._is_cutscene
	defm	""
	defb	0

;	SECTION	code



._do_extern_action
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	a,l
	ld	(_gpt),a
	and	a
	jp	nz,i_44
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_exti),a
	jp	i_47
.i_45
	ld	hl,_exti
	ld	a,(hl)
	inc	(hl)
.i_47
	ld	a,(_exti)
	cp	#(10 % 256)
	jp	z,i_46
	jp	nc,i_46
	ld	hl,(_exti)
	ld	h,0
	ld	a,l
	ld	(_extx),a
	jp	i_50
.i_48
	ld	hl,_extx
	ld	a,(hl)
	inc	(hl)
.i_50
	ld	hl,(_extx)
	ld	h,0
	push	hl
	ld	hl,(_exti)
	ld	h,0
	ld	de,30
	ex	de,hl
	and	a
	sbc	hl,de
	pop	de
	call	l_ult
	jp	nc,i_49
	ld de, 0x4700
	ld a, (_extx)
	add 1
	ld c, a
	ld a, (_exti)
	add 2
	call SPPrintAtInv
	ld de, 0x4700
	ld a, (_extx)
	add 1
	ld c, a
	ld a, (_exti)
	ld b, a
	ld a, 2 + 19
	sub b
	call SPPrintAtInv
	ld	hl,(_extx)
	ld	h,0
	push	hl
	ld	hl,(_exti)
	ld	h,0
	ld	de,19
	ex	de,hl
	and	a
	sbc	hl,de
	pop	de
	call	l_ult
	jp	nc,i_51
	ld de, 0x4700
	ld a, (_exti)
	add 1
	ld c, a
	ld a, (_extx)
	add 2
	call SPPrintAtInv
	ld de, 0x4700
	ld a, (_exti)
	ld b, a
	ld a, 1 + 29
	sub b
	ld c, a
	ld a, (_extx)
	add 2
	call SPPrintAtInv
.i_51
	jp	i_48
.i_49
	halt
	ld	hl,0 % 256	;const
	push	hl
	call	sp_UpdateNowEx
	pop	bc
	jp	i_45
.i_46
	ret


.i_44
	ld	a,#(1 % 256 % 256)
	ld	(_stepbystep),a
	ld	hl,(_gpt)
	ld	h,0
	dec	hl
	add	hl,hl
	ld	(_asm_int),hl
	._extern_depack_text
	di
	ld b, 6
	call SetRAMBank
	; First we get where to look for the packed string
	ld hl, (_asm_int)
	ld de, $c000
	add hl, de
	ld a, (hl)
	inc hl
	ld h, (hl)
	ld l, a
	add hl, de
	ld de, _textbuff
	; 5-bit scaped depacker by na_th_an
	; Contains code by Antonio Villena
	ld a, $80
	.fbsd_mainb
	call fbsd_unpackc
	ld c, a
	ld a, b
	and a
	jr z, fbsd_fin
	call fbsd_stor
	ld a, c
	jr fbsd_mainb
	.fbsd_stor
	cp 31
	jr z, fbsd_escaped
	add a, 64
	jr fbsd_stor2
	.fbsd_escaped
	ld a, c
	call fbsd_unpackc
	ld c, a
	ld a, b
	add a, 32
	.fbsd_stor2
	ld (de), a
	inc de
	ret
	.fbsd_unpackc
	ld b, 0x08
	.fbsd_bucle
	call fbsd_getbit
	rl b
	jr nc, fbsd_bucle
	ret
	.fbsd_getbit
	add a, a
	ret nz
	ld a, (hl)
	inc hl
	rla
	ret
	.fbsd_fin
	ld (de), a
	;
	;
	ld b, 0
	call SetRAMBank
	ei
	ld	a,(_is_cutscene)
	and	a
	jp	nz,i_52
	ld	hl,(_textbuff)
	ld	h,0
	ld	bc,-64
	add	hl,bc
	ld	h,0
	ld	a,l
	ld	(_exti),a
	ld	hl,(_exti)
	ld	h,0
	ld	de,3
	add	hl,de
	ex	de,hl
	ld	hl,(_exti)
	ld	h,0
	add	hl,de
	ld	h,0
	ld	a,l
	ld	(_extx),a
	ld	a,#(3 % 256 % 256)
	ld	(__x),a
	ld	a,#(3 % 256 % 256)
	ld	(__y),a
	ld	a,#(1 % 256 % 256)
	ld	(__t),a
	ld	hl,i_1+13
	ld	(_gp_gen),hl
	call	_print_str
	ld	a,#(3 % 256 % 256)
	ld	(__x),a
	ld	a,#(1 % 256 % 256)
	ld	(__t),a
	ld	hl,i_1+40
	ld	(_gp_gen),hl
	ld	hl,4 % 256	;const
	ld	a,l
	ld	(__y),a
	jp	i_55
.i_53
	ld	hl,(__y)
	ld	h,0
	inc	hl
	ld	a,l
	ld	(__y),a
.i_55
	ld	hl,(__y)
	ld	h,0
	ex	de,hl
	ld	hl,(_extx)
	ld	h,0
	call	l_ult
	jp	nc,i_54
	ld	hl,3 % 256	;const
	ld	a,l
	ld	(__x),a
	call	_print_str
	jp	i_53
.i_54
	ld	a,#(3 % 256 % 256)
	ld	(__x),a
	ld	hl,(_extx)
	ld	h,0
	ld	a,l
	ld	(__y),a
	ld	a,#(1 % 256 % 256)
	ld	(__t),a
	ld	hl,i_1+67
	ld	(_gp_gen),hl
	call	_print_str
	ld	hl,4 % 256	;const
	ld	a,l
	ld	(_exty),a
	jp	i_56
.i_52
	ld	hl,13 % 256	;const
	ld	a,l
	ld	(_exty),a
.i_56
	ld	a,#(4 % 256 % 256)
	ld	(_extx),a
	ld	hl,_textbuff+1
	ld	(_gp_gen),hl
	ld	hl,1 % 256	;const
	ld	a,l
	ld	(_keyp),a
.i_57
	ld	hl,(_gp_gen)
	inc	hl
	ld	(_gp_gen),hl
	dec	hl
	ld	l,(hl)
	ld	h,0
	ld	a,l
	ld	(_exti),a
	ld	a,h
	or	l
	jp	z,i_58
	ld	a,(_exti)
	cp	#(37 % 256)
	jp	nz,i_59
	ld	a,#(4 % 256 % 256)
	ld	(_extx),a
	ld	hl,(_exty)
	ld	h,0
	inc	hl
	inc	hl
	ld	h,0
	ld	a,l
	ld	(_exty),a
	jp	i_60
.i_59
	ld a, (_exti)
	sub 32
	ld e, a
	ld a, (_extx)
	ld c, a
	ld a, (_exty)
	ld d, 71
	call SPPrintAtInv
	ld	hl,(_extx)
	ld	h,0
	inc	hl
	ld	a,l
	ld	(_extx),a
	cp	#(28 % 256)
	jp	nz,i_61
	ld	a,#(4 % 256 % 256)
	ld	(_extx),a
	ld	hl,(_exty)
	ld	h,0
	inc	hl
	inc	hl
	ld	h,0
	ld	a,l
	ld	(_exty),a
.i_61
.i_60
	ld	hl,(_stepbystep)
	ld	h,0
	ld	a,h
	or	l
	jp	z,i_62
	halt
	ld	a,(_exti)
	cp	#(32 % 256)
	jp	z,i_64
	ld	a,(_is_cutscene)
	cp	#(0 % 256)
	jr	z,i_65_i_64
.i_64
	jp	i_63
.i_65_i_64
	ld	hl,8 % 256	;const
	call	_wyz_play_sound
.i_63
	halt
	halt
	ld	hl,0 % 256	;const
	push	hl
	call	sp_UpdateNowEx
	pop	bc
.i_62
	call	_button_pressed
	ld	a,h
	or	l
	jp	z,i_66
	ld	a,(_keyp)
	and	a
	jp	nz,i_67
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_stepbystep),a
.i_67
	jp	i_68
.i_66
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_keyp),a
.i_68
	jp	i_57
.i_58
	ld	hl,0 % 256	;const
	push	hl
	call	sp_UpdateNowEx
	pop	bc
	call	sp_WaitForNoKey
.i_69
	call	_button_pressed
	ld	a,h
	or	l
	jp	nz,i_69
.i_70
	ld	hl,5000	;const
	push	hl
	call	_active_sleep
	pop	bc
	ret



._read_byte
	di
	ld b, 7
	call SetRAMBank
	ld hl, (_script)
	ld a, (hl)
	ld (_safe_byte), a
	inc hl
	ld (_script), hl
	ld b, 0
	call SetRAMBank
	ei
	ld	hl,(_safe_byte)
	ld	h,0
	ret



._read_vbyte
	call _read_byte
	ld a, l
	and 128
	ret z
	ld a, l
	and 127
	ld c, a
	ld b, 0
	ld hl, _flags
	add hl, bc
	ld l, (hl)
	ld h, 0
	ret
	ret



._readxy
	call	_read_vbyte
	ld	h,0
	ld	a,l
	ld	(_sc_x),a
	call	_read_vbyte
	ld	h,0
	ld	a,l
	ld	(_sc_y),a
	ret



._stop_player
	ld	hl,0	;const
	ld	a,l
	call	l_sxt
	ld	a,l
	ld	(_p_vy),a
	ld	a,l
	call	l_sxt
	ld	a,l
	ld	(_p_vx),a
	ret



._reloc_player
	call	_read_vbyte
	ld	h,l
	ld	l,0
	ld	(_p_x),hl
	call	_read_vbyte
	ld	h,l
	ld	l,0
	ld	(_p_y),hl
	call	_stop_player
	ret



._run_script
	ld	de,(_main_script_offset)
	ld	hl,4-2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	add	hl,de
	ex	de,hl
	ld	hl,4-2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	add	hl,de
	ld	(_asm_int),hl
	di
	ld b, 7
	call SetRAMBank
	ld hl, (_asm_int)
	ld a, (hl)
	inc hl
	ld h, (hl)
	ld l, a
	ld (_script), hl
	ld b, 0
	call SetRAMBank
	ei
	ld	hl,(_script)
	ld	a,h
	or	l
	jp	nz,i_71
	ret


.i_71
	ld	de,(_script)
	ld	hl,(_main_script_offset)
	add	hl,de
	ld	(_script),hl
.i_72
	call	_read_byte
	ld	h,0
	ld	a,l
	ld	(_sc_c),a
	ld	de,255	;const
	ex	de,hl
	call	l_ne
	jp	nc,i_73
	ld	de,(_script)
	ld	hl,(_sc_c)
	ld	h,0
	add	hl,de
	ld	(_next_script),hl
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_sc_continuar),a
	ld	h,0
	ld	a,l
	ld	(_sc_terminado),a
.i_74
	ld	hl,(_sc_terminado)
	ld	h,0
	call	l_lneg
	jp	nc,i_75
	call	_read_byte
.i_78
	ld	a,l
	cp	#(16% 256)
	jp	z,i_79
	cp	#(17% 256)
	jp	z,i_80
	cp	#(18% 256)
	jp	z,i_81
	cp	#(19% 256)
	jp	z,i_82
	cp	#(32% 256)
	jp	z,i_83
	cp	#(33% 256)
	jp	z,i_86
	cp	#(128% 256)
	jp	z,i_89
	cp	#(240% 256)
	jp	z,i_90
	cp	#(255% 256)
	jp	z,i_91
	jp	i_77
.i_79
	call	_readxy
	ld	de,_flags
	ld	hl,(_sc_x)
	ld	h,0
	add	hl,de
	ld	e,(hl)
	ld	d,0
	ld	hl,(_sc_y)
	ld	h,0
	call	l_ne
	ld	hl,0	;const
	rl	l
	ld	h,0
	ld	a,l
	ld	(_sc_terminado),a
	jp	i_77
.i_80
	call	_readxy
	ld	de,_flags
	ld	hl,(_sc_x)
	ld	h,0
	add	hl,de
	ld	e,(hl)
	ld	d,0
	ld	hl,(_sc_y)
	ld	h,0
	call	l_uge
	ld	hl,0	;const
	rl	l
	ld	h,0
	ld	a,l
	ld	(_sc_terminado),a
	jp	i_77
.i_81
	call	_readxy
	ld	de,_flags
	ld	hl,(_sc_x)
	ld	h,0
	add	hl,de
	ld	e,(hl)
	ld	d,0
	ld	hl,(_sc_y)
	ld	h,0
	call	l_ule
	ld	hl,0	;const
	rl	l
	ld	h,0
	ld	a,l
	ld	(_sc_terminado),a
	jp	i_77
.i_82
	call	_readxy
	ld	de,_flags
	ld	hl,(_sc_x)
	ld	h,0
	add	hl,de
	ld	e,(hl)
	ld	d,0
	ld	hl,(_sc_y)
	ld	h,0
	call	l_eq
	ld	hl,0	;const
	rl	l
	ld	h,0
	ld	a,l
	ld	(_sc_terminado),a
	jp	i_77
.i_83
	call	_readxy
	ld	a,(_sc_x)
	ld	e,a
	ld	d,0
	ld	l,#(4 % 256)
	call	l_asl
	ld	h,0
	ld	a,l
	ld	(_sc_x),a
	ld	a,(_sc_y)
	ld	e,a
	ld	d,0
	ld	l,#(4 % 256)
	call	l_asl
	ld	h,0
	ld	a,l
	ld	(_sc_y),a
	ld	hl,(_gpx)
	ld	h,0
	ld	bc,15
	add	hl,bc
	ex	de,hl
	ld	hl,(_sc_x)
	ld	h,0
	call	l_uge
	jp	nc,i_84
	ld	hl,(_gpx)
	ld	h,0
	push	hl
	ld	hl,(_sc_x)
	ld	h,0
	ld	bc,15
	add	hl,bc
	pop	de
	call	l_ule
	jp	nc,i_84
	ld	hl,(_gpy)
	ld	h,0
	ld	bc,15
	add	hl,bc
	ex	de,hl
	ld	hl,(_sc_y)
	ld	h,0
	call	l_uge
	jp	nc,i_84
	ld	hl,(_gpy)
	ld	h,0
	push	hl
	ld	hl,(_sc_y)
	ld	h,0
	ld	bc,15
	add	hl,bc
	pop	de
	call	l_ule
	jp	nc,i_84
	ld	hl,1	;const
	jr	i_85
.i_84
	ld	hl,0	;const
.i_85
	call	l_lneg
	ld	hl,0	;const
	rl	l
	ld	h,0
	ld	a,l
	ld	(_sc_terminado),a
	jp	i_77
.i_86
	call	_read_byte
	ld	h,0
	ld	a,l
	ld	(_sc_x),a
	call	_read_byte
	ld	h,0
	ld	a,l
	ld	(_sc_y),a
	ld	hl,(_p_x)
	ex	de,hl
	ld	l,#(4 % 256)
	call	l_asr
	ex	de,hl
	ld	hl,(_sc_x)
	ld	h,0
	call	l_ge
	jp	nc,i_87
	ld	hl,(_p_x)
	ex	de,hl
	ld	l,#(4 % 256)
	call	l_asr
	ex	de,hl
	ld	hl,(_sc_y)
	ld	h,0
	call	l_le
	jp	nc,i_87
	ld	hl,1	;const
	jr	i_88
.i_87
	ld	hl,0	;const
.i_88
	call	l_lneg
	ld	hl,0	;const
	rl	l
	ld	h,0
	ld	a,l
	ld	(_sc_terminado),a
	jp	i_77
.i_89
	call	_read_vbyte
	ex	de,hl
	ld	hl,(_level)
	ld	h,0
	call	l_ne
	ld	hl,0	;const
	rl	l
	ld	h,0
	ld	a,l
	ld	(_sc_terminado),a
.i_90
	jp	i_77
.i_91
	ld	a,#(1 % 256 % 256)
	ld	(_sc_terminado),a
	ld	hl,1 % 256	;const
	ld	a,l
	ld	(_sc_continuar),a
.i_77
	jp	i_74
.i_75
	ld	a,(_sc_continuar)
	and	a
	jp	z,i_92
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_sc_terminado),a
.i_93
	ld	hl,(_sc_terminado)
	ld	h,0
	call	l_lneg
	jp	nc,i_94
	call	_read_byte
.i_97
	ld	a,l
	cp	#(1% 256)
	jp	z,i_98
	cp	#(16% 256)
	jp	z,i_99
	cp	#(17% 256)
	jp	z,i_100
	cp	#(21% 256)
	jp	z,i_101
	cp	#(32% 256)
	jp	z,i_102
	cp	#(48% 256)
	jp	z,i_103
	cp	#(49% 256)
	jp	z,i_104
	cp	#(80% 256)
	jp	z,i_105
	cp	#(81% 256)
	jp	z,i_106
	cp	#(105% 256)
	jp	z,i_107
	cp	#(106% 256)
	jp	z,i_108
	cp	#(107% 256)
	jp	z,i_109
	cp	#(108% 256)
	jp	z,i_110
	cp	#(109% 256)
	jp	z,i_111
	cp	#(110% 256)
	jp	z,i_112
	cp	#(111% 256)
	jp	z,i_117
	cp	#(128% 256)
	jp	z,i_118
	cp	#(129% 256)
	jp	z,i_119
	cp	#(224% 256)
	jp	z,i_120
	cp	#(225% 256)
	jp	z,i_121
	cp	#(228% 256)
	jp	z,i_122
	cp	#(229% 256)
	jp	z,i_123
	cp	#(230% 256)
	jp	z,i_126
	cp	#(241% 256)
	jp	z,i_129
	cp	#(243% 256)
	jp	z,i_130
	cp	#(244% 256)
	jp	z,i_131
	cp	#(255% 256)
	jp	z,i_134
	jp	i_96
.i_98
	call	_readxy
	ld	de,_flags
	ld	hl,(_sc_x)
	ld	h,0
	add	hl,de
	push	hl
	ld	hl,_sc_y
	ld	a,(hl)
	pop	de
	ld	(de),a
	ld	l,a
	ld	h,0
	jp	i_96
.i_99
	call	_readxy
	ld	de,_flags
	ld	hl,(_sc_x)
	ld	h,0
	add	hl,de
	push	hl
	ld	e,(hl)
	ld	d,0
	ld	hl,(_sc_y)
	ld	h,0
	add	hl,de
	pop	de
	ld	a,l
	ld	(de),a
	jp	i_96
.i_100
	call	_readxy
	ld	de,_flags
	ld	hl,(_sc_x)
	ld	h,0
	add	hl,de
	push	hl
	ld	e,(hl)
	ld	d,0
	ld	hl,(_sc_y)
	ld	h,0
	ex	de,hl
	and	a
	sbc	hl,de
	pop	de
	ld	a,l
	ld	(de),a
	jp	i_96
.i_101
	call	_read_vbyte
	ld	h,0
	ld	a,l
	ld	(_sc_x),a
	ld	de,_flags
	ld	hl,(_sc_x)
	ld	h,0
	add	hl,de
	push	hl
	ld	de,_flags
	ld	hl,(_sc_x)
	ld	h,0
	add	hl,de
	ld	e,(hl)
	ld	d,0
	ld	hl,1
	and	a
	sbc	hl,de
	pop	de
	ld	a,l
	ld	(de),a
	jp	i_96
.i_102
	call	_readxy
	call	_read_vbyte
	ld	h,0
	ld	a,l
	ld	(_sc_n),a
	ld	hl,(_sc_x)
	ld	h,0
	ld	a,l
	ld	(__x),a
	ld	hl,(_sc_y)
	ld	h,0
	ld	a,l
	ld	(__y),a
	ld	de,_behs
	ld	hl,(_sc_n)
	ld	h,0
	add	hl,de
	ld	l,(hl)
	ld	h,0
	ld	a,l
	ld	(__n),a
	ld	hl,(_sc_n)
	ld	h,0
	ld	a,l
	ld	(__t),a
	call	_update_tile
	jp	i_96
.i_103
	ld	hl,(_p_life)
	ld	h,0
	push	hl
	call	_read_vbyte
	pop	de
	add	hl,de
	ld	h,0
	ld	a,l
	ld	(_p_life),a
	jp	i_96
.i_104
	ld	hl,(_p_life)
	ld	h,0
	push	hl
	call	_read_vbyte
	pop	de
	ex	de,hl
	and	a
	sbc	hl,de
	ld	h,0
	ld	a,l
	ld	(_p_life),a
	jp	i_96
.i_105
	call	_readxy
	ld	hl,(_sc_x)
	ld	h,0
	ld	a,l
	ld	(__x),a
	ld	hl,(_sc_y)
	ld	h,0
	ld	a,l
	ld	(__y),a
	call	_read_vbyte
	ld	h,0
	ld	a,l
	ld	(__t),a
	call	_draw_coloured_tile
	call	_invalidate_tile
	jp	i_96
.i_106
	call	_read_byte
	ld	h,0
	ld	a,l
	ld	(_fzx1),a
	call	_read_byte
	ld	h,0
	ld	a,l
	ld	(_fzy1),a
	call	_read_byte
	ld	h,0
	ld	a,l
	ld	(_fzx2),a
	call	_read_byte
	ld	h,0
	ld	a,l
	ld	(_fzy2),a
	ld	hl,1 % 256	;const
	ld	a,l
	ld	(_f_zone_ac),a
	jp	i_96
.i_107
	call	_read_vbyte
	ld	h,0
	ld	a,l
	ld	(_warp_to_level),a
	call	_read_vbyte
	ld	h,0
	ld	a,l
	ld	(_n_pant),a
	ld	hl,99 % 256	;const
	ld	a,l
	ld	(_o_pant),a
	call	_reloc_player
	call	_read_vbyte
	ld	h,0
	ld	a,l
	ld	(_silent_level),a
	ld	a,#(1 % 256 % 256)
	ld	(_sc_terminado),a
	ld	hl,3 % 256	;const
	ld	a,l
	ld	(_script_result),a
	ret


.i_108
	call	_read_vbyte
	ex	de,hl
	ld	l,#(4 % 256)
	call	l_asl
	ld	h,0
	ld	a,l
	ld	(_gpy),a
	ld	e,a
	ld	d,0
	ld	l,#(4 % 256)
	call	l_asl
	ld	(_p_y),hl
	call	_stop_player
	jp	i_96
.i_109
	call	_read_vbyte
	ex	de,hl
	ld	l,#(4 % 256)
	call	l_asl
	ld	h,0
	ld	a,l
	ld	(_gpx),a
	ld	e,a
	ld	d,0
	ld	l,#(4 % 256)
	call	l_asl
	ld	(_p_x),hl
	call	_stop_player
	jp	i_96
.i_110
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_do_respawn),a
	call	_reloc_player
	ld	a,#(99 % 256 % 256)
	ld	(_o_pant),a
	ld	hl,1 % 256	;const
	ld	a,l
	ld	(_sc_terminado),a
	jp	i_96
.i_111
	call	_read_vbyte
	ld	h,0
	ld	a,l
	ld	(_n_pant),a
	ld	hl,99 % 256	;const
	ld	a,l
	ld	(_o_pant),a
	call	_reloc_player
	ret


.i_112
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_sc_y),a
	ld	h,0
	ld	a,l
	ld	(_sc_x),a
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_sc_c),a
	jp	i_115
.i_113
	ld	hl,_sc_c
	ld	a,(hl)
	inc	(hl)
.i_115
	ld	a,(_sc_c)
	cp	#(150 % 256)
	jp	z,i_114
	jp	nc,i_114
	ld	hl,(_sc_x)
	ld	h,0
	ld	a,l
	ld	(__x),a
	ld	hl,(_sc_y)
	ld	h,0
	ld	a,l
	ld	(__y),a
	ld	de,_map_attr
	ld	hl,(_sc_c)
	ld	h,0
	add	hl,de
	ld	l,(hl)
	ld	h,0
	ld	a,l
	ld	(__n),a
	ld	de,_map_buff
	ld	hl,(_sc_c)
	ld	h,0
	add	hl,de
	ld	l,(hl)
	ld	h,0
	ld	a,l
	ld	(__t),a
	call	_update_tile
	ld	hl,_sc_x
	ld	a,(hl)
	inc	(hl)
	ld	a,(_sc_x)
	cp	#(15 % 256)
	jp	nz,i_116
	ld	a,#(0 % 256 % 256)
	ld	(_sc_x),a
	ld	hl,_sc_y
	ld	a,(hl)
	inc	(hl)
	ld	l,a
	ld	h,0
.i_116
	jp	i_113
.i_114
	jp	i_96
.i_117
	ld	a,#(0 % 256 % 256)
	ld	(_do_respawn),a
	ld	hl,99 % 256	;const
	ld	a,l
	ld	(_o_pant),a
	ret


.i_118
	ld	hl,_baddies
	push	hl
	ld	hl,(_enoffs)
	ld	h,0
	push	hl
	call	_read_vbyte
	pop	de
	add	hl,de
	ld	b,h
	ld	c,l
	add	hl,hl
	add	hl,hl
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	ld	bc,8
	add	hl,bc
	push	hl
	ld	a,(hl)
	and	#(127 % 256)
	pop	de
	ld	(de),a
	ld	l,a
	ld	h,0
	jp	i_96
.i_119
	ld	hl,_baddies
	push	hl
	ld	hl,(_enoffs)
	ld	h,0
	push	hl
	call	_read_vbyte
	pop	de
	add	hl,de
	ld	b,h
	ld	c,l
	add	hl,hl
	add	hl,hl
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	ld	bc,8
	add	hl,bc
	ld	a,(hl)
	or	#(128 % 256)
	ld	(hl),a
	ld	l,a
	ld	h,0
	jp	i_96
.i_120
	call	_read_vbyte
	ld	h,0
	call	_wyz_play_sound
	jp	i_96
.i_121
	call	sp_UpdateNow
	jp	i_96
.i_122
	call	_read_byte
	ld	h,0
	push	hl
	call	_do_extern_action
	pop	bc
	jp	i_96
.i_123
	call	_read_byte
	ld	h,0
	ld	a,l
	ld	(_sc_n),a
.i_124
	ld	hl,_sc_n
	ld	a,(hl)
	dec	(hl)
	ld	l,a
	ld	h,0
	ld	a,h
	or	l
	jp	z,i_125
	halt
	jp	i_124
.i_125
	jp	i_96
.i_126
	call	_read_vbyte
	ld	h,0
	ld	a,l
	ld	(_sc_n),a
	ld	e,a
	ld	d,0
	ld	hl,255	;const
	call	l_eq
	jp	nc,i_127
	call	_wyz_stop_sound
	jp	i_128
.i_127
	ld	hl,_level_data+10
	push	hl
	ld	hl,_sc_n
	ld	a,(hl)
	pop	de
	ld	(de),a
	ld	hl,(_level_data+10)
	ld	h,0
	call	_wyz_play_music
.i_128
	jp	i_96
.i_129
	ld	hl,1 % 256	;const
	ld	a,l
	ld	(_script_result),a
	ret


.i_130
	ld	hl,4 % 256	;const
	ld	a,l
	ld	(_script_result),a
	ret


	jp	i_96
.i_131
.i_132
	call	_read_byte
	ld	h,0
	ld	a,l
	ld	(_sc_x),a
	ld	de,255
	call	l_ne
	jp	nc,i_133
	call	_read_byte
	ld	h,0
	ld	a,l
	ld	(_sc_n),a
	ld	a,(_sc_x)
	ld	e,a
	ld	d,0
	ld	l,#(4 % 256)
	call	l_asr_u
	ld	h,0
	ld	a,l
	ld	(__x),a
	ld	a,(_sc_x)
	ld	e,a
	ld	d,0
	ld	hl,15	;const
	call	l_and
	ld	h,0
	ld	a,l
	ld	(__y),a
	ld	de,_behs
	ld	hl,(_sc_n)
	ld	h,0
	add	hl,de
	ld	l,(hl)
	ld	h,0
	ld	a,l
	ld	(__n),a
	ld	hl,(_sc_n)
	ld	h,0
	ld	a,l
	ld	(__t),a
	call	_update_tile
	jp	i_132
.i_133
	jp	i_96
.i_134
	ld	hl,1 % 256	;const
	ld	a,l
	ld	(_sc_terminado),a
.i_96
	jp	i_93
.i_94
.i_92
	ld	hl,(_next_script)
	ld	(_script),hl
	jp	i_72
.i_73
	ret



._run_entering_script
	ld	a,(_level_data+9)
	and	a
	jp	z,i_135
	ld	hl,43 % 256	;const
	push	hl
	call	_run_script
	pop	bc
	ld	hl,(_n_pant)
	ld	h,0
	ex	de,hl
	ld	hl,(_n_pant)
	ld	h,0
	add	hl,de
	push	hl
	call	_run_script
	pop	bc
.i_135
	ret



._run_fire_script
	ld	hl,44 % 256	;const
	push	hl
	call	_run_script
	pop	bc
	ld	hl,(_n_pant)
	ld	h,0
	ex	de,hl
	ld	hl,(_n_pant)
	ld	h,0
	add	hl,de
	inc	hl
	push	hl
	call	_run_script
	pop	bc
	ret



._do_ingame_scripting
	ld	a,(_level_data+9)
	and	a
	jp	z,i_137
	ld	hl,_pad0
	ld	a,(hl)
	and	#(2 % 256)
	cp	#(0 % 256)
	ld	hl,0
	jr	z,i_138_i_137
.i_137
	jp	i_136
.i_138_i_137
	ld	a,(_action_pressed)
	and	a
	jp	nz,i_139
	ld	hl,1 % 256	;const
	ld	a,l
	ld	(_action_pressed),a
	call	_run_fire_script
.i_139
	jp	i_140
.i_136
	ld	a,#(0 % 256 % 256)
	ld	(_action_pressed),a
	ld	a,(_level_data+9)
	and	a
	jp	z,i_142
	ld	a,(_f_zone_ac)
	and	a
	jr	nz,i_143_i_142
.i_142
	jp	i_141
.i_143_i_142
	ld	hl,(_gpx)
	ld	h,0
	ex	de,hl
	ld	hl,(_fzx1)
	ld	h,0
	call	l_uge
	jp	nc,i_145
	ld	hl,(_gpx)
	ld	h,0
	ex	de,hl
	ld	hl,(_fzx2)
	ld	h,0
	call	l_ule
	jp	nc,i_145
	ld	hl,(_gpy)
	ld	h,0
	ex	de,hl
	ld	hl,(_fzy1)
	ld	h,0
	call	l_uge
	jp	nc,i_145
	ld	hl,(_gpy)
	ld	h,0
	ex	de,hl
	ld	hl,(_fzy2)
	ld	h,0
	call	l_ule
	jr	c,i_146_i_145
.i_145
	jp	i_144
.i_146_i_145
	call	_run_fire_script
.i_144
.i_141
.i_140
	ret


;	SECTION	text

._player_frames
	defw	_sprite_5_a
	defw	_sprite_6_a
	defw	_sprite_7_a
	defw	_sprite_6_a
	defw	_sprite_1_a
	defw	_sprite_2_a
	defw	_sprite_3_a
	defw	_sprite_2_a
	defw	_sprite_8_a
	defw	_sprite_4_a

;	SECTION	code

;	SECTION	text

._enem_frames
	defw	_sprite_9_a
	defw	_sprite_10_a
	defw	_sprite_11_a
	defw	_sprite_12_a
	defw	_sprite_13_a
	defw	_sprite_14_a
	defw	_sprite_15_a
	defw	_sprite_16_a

;	SECTION	code


._prepare_level
	ld	de,_level_sequence
	ld	hl,(_level)
	ld	h,0
	add	hl,de
	ld	l,(hl)
	ld	h,0
	ld	a,l
	ld	(_level_ac),a
	ld	hl,_levels
	push	hl
	ld	hl,(_level_ac)
	ld	h,0
	push	de
	ld	de,21
	call	l_mult
	pop	de
	pop	de
	add	hl,de
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,_map
	push	hl
	call	_get_resource
	pop	bc
	pop	bc
	ld	hl,_levels
	push	hl
	ld	hl,(_level_ac)
	ld	h,0
	push	de
	ld	de,21
	call	l_mult
	pop	de
	pop	de
	add	hl,de
	inc	hl
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,_tileset+512
	push	hl
	call	_get_resource
	pop	bc
	pop	bc
	ld	hl,_levels
	push	hl
	ld	hl,(_level_ac)
	ld	h,0
	push	de
	ld	de,21
	call	l_mult
	pop	de
	pop	de
	add	hl,de
	inc	hl
	inc	hl
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,_spriteset
	push	hl
	call	_get_resource
	pop	bc
	pop	bc
	ld	hl,_levels
	push	hl
	ld	hl,(_level_ac)
	ld	h,0
	push	de
	ld	de,21
	call	l_mult
	pop	de
	pop	de
	add	hl,de
	inc	hl
	inc	hl
	inc	hl
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,_baddies
	push	hl
	call	_get_resource
	pop	bc
	pop	bc
	ld	hl,_levels
	push	hl
	ld	hl,(_level_ac)
	ld	h,0
	push	de
	ld	de,21
	call	l_mult
	pop	de
	pop	de
	add	hl,de
	ld	bc,4
	add	hl,bc
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,_hotspots
	push	hl
	call	_get_resource
	pop	bc
	pop	bc
	ld	hl,_levels
	push	hl
	ld	hl,(_level_ac)
	ld	h,0
	push	de
	ld	de,21
	call	l_mult
	pop	de
	pop	de
	add	hl,de
	ld	bc,5
	add	hl,bc
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,_behs
	push	hl
	call	_get_resource
	pop	bc
	pop	bc
	ld	a,(_script_result)
	cp	#(3 % 256)
	jp	z,i_149
	ld	hl,_levels
	push	hl
	ld	hl,(_level_ac)
	ld	h,0
	push	de
	ld	de,21
	call	l_mult
	pop	de
	pop	de
	add	hl,de
	ld	bc,7
	add	hl,bc
	ld	l,(hl)
	ld	h,0
	ld	a,l
	ld	(_n_pant),a
	ld	hl,_levels
	push	hl
	ld	hl,(_level_ac)
	ld	h,0
	push	de
	ld	de,21
	call	l_mult
	pop	de
	pop	de
	add	hl,de
	ld	bc,8
	add	hl,bc
	ld	e,(hl)
	ld	d,0
	ld	l,#(4 % 256)
	call	l_asl
	ld	h,0
	ld	a,l
	ld	(_gpx),a
	ld	hl,_levels
	push	hl
	ld	hl,(_level_ac)
	ld	h,0
	push	de
	ld	de,21
	call	l_mult
	pop	de
	pop	de
	add	hl,de
	ld	bc,9
	add	hl,bc
	ld	e,(hl)
	ld	d,0
	ld	l,#(4 % 256)
	call	l_asl
	ld	h,0
	ld	a,l
	ld	(_gpy),a
	ld	a,(_gpx)
	ld	e,a
	ld	d,0
	ld	l,#(4 % 256)
	call	l_asl
	ld	(_p_x),hl
	ld	a,(_gpy)
	ld	e,a
	ld	d,0
	ld	l,#(4 % 256)
	call	l_asl
	ld	(_p_y),hl
	ld	hl,_levels
	push	hl
	ld	hl,(_level_ac)
	ld	h,0
	push	de
	ld	de,21
	call	l_mult
	pop	de
	pop	de
	add	hl,de
	ld	bc,17
	add	hl,bc
	ld	l,(hl)
	ld	h,0
	ld	a,l
	ld	(_p_facing),a
.i_149
	ld	hl,_level_data
	push	hl
	ld	hl,_levels
	push	hl
	ld	hl,(_level_ac)
	ld	h,0
	push	de
	ld	de,21
	call	l_mult
	pop	de
	pop	de
	add	hl,de
	ld	bc,11
	add	hl,bc
	ld	a,(hl)
	pop	de
	ld	(de),a
	ld	hl,_level_data+1
	push	hl
	ld	hl,_levels
	push	hl
	ld	hl,(_level_ac)
	ld	h,0
	push	de
	ld	de,21
	call	l_mult
	pop	de
	pop	de
	add	hl,de
	ld	bc,12
	add	hl,bc
	ld	a,(hl)
	pop	de
	ld	(de),a
	ld	hl,_level_data+5
	push	hl
	ld	hl,_levels
	push	hl
	ld	hl,(_level_ac)
	ld	h,0
	push	de
	ld	de,21
	call	l_mult
	pop	de
	pop	de
	add	hl,de
	ld	bc,13
	add	hl,bc
	ld	a,(hl)
	pop	de
	ld	(de),a
	ld	hl,_level_data+6
	push	hl
	ld	hl,_levels
	push	hl
	ld	hl,(_level_ac)
	ld	h,0
	push	de
	ld	de,21
	call	l_mult
	pop	de
	pop	de
	add	hl,de
	ld	bc,14
	add	hl,bc
	ld	a,(hl)
	pop	de
	ld	(de),a
	ld	hl,_level_data+7
	push	hl
	ld	hl,_levels
	push	hl
	ld	hl,(_level_ac)
	ld	h,0
	push	de
	ld	de,21
	call	l_mult
	pop	de
	pop	de
	add	hl,de
	ld	bc,15
	add	hl,bc
	ld	a,(hl)
	pop	de
	ld	(de),a
	ld	hl,_level_data+8
	push	hl
	ld	hl,_levels
	push	hl
	ld	hl,(_level_ac)
	ld	h,0
	push	de
	ld	de,21
	call	l_mult
	pop	de
	pop	de
	add	hl,de
	ld	bc,10
	add	hl,bc
	ld	a,(hl)
	pop	de
	ld	(de),a
	ld	hl,_level_data+9
	push	hl
	ld	hl,_levels
	push	hl
	ld	hl,(_level_ac)
	ld	h,0
	push	de
	ld	de,21
	call	l_mult
	pop	de
	pop	de
	add	hl,de
	ld	bc,18
	add	hl,bc
	ld	a,(hl)
	pop	de
	ld	(de),a
	ld	hl,_level_data+10
	push	hl
	ld	hl,_levels
	push	hl
	ld	hl,(_level_ac)
	ld	h,0
	push	de
	ld	de,21
	call	l_mult
	pop	de
	pop	de
	add	hl,de
	ld	bc,6
	add	hl,bc
	ld	a,(hl)
	pop	de
	ld	(de),a
	ld	hl,_levels
	push	hl
	ld	hl,(_level_ac)
	ld	h,0
	push	de
	ld	de,21
	call	l_mult
	pop	de
	pop	de
	add	hl,de
	ld	bc,16
	add	hl,bc
	ld	l,(hl)
	ld	h,0
	ld	a,l
	ld	(_p_engine),a
	ld	e,a
	ld	d,0
	ld	hl,1	;const
	call	l_eq
	ccf
	ld	hl,0	;const
	rl	l
	ld	h,0
	ld	a,l
	ld	(_do_gravity),a
	ld	hl,_levels
	push	hl
	ld	hl,(_level_ac)
	ld	h,0
	push	de
	ld	de,21
	call	l_mult
	pop	de
	pop	de
	add	hl,de
	ld	bc,19
	add	hl,bc
	call	l_gint	;
	ld	(_main_script_offset),hl
	ret



._collide_pixel
	ld hl, 0
	ld a, (_cx2)
	inc a
	ld c, a
	ld a, (_cx1)
	cp c
	jr c, _collide_pixel_return
	ld a, (_cx1)
	ld c, a
	ld a, (_cx2)
	add 14
	cp c
	jr c, _collide_pixel_return
	ld a, (_cy2)
	inc a
	ld c, a
	ld a, (_cy1)
	cp c
	jr c, _collide_pixel_return
	ld a, (_cy1)
	ld c, a
	ld a, (_cy2)
	add 14
	cp c
	jr c, _collide_pixel_return
	ld l, 1
	._collide_pixel_return
	ret
	ret



._cm_two_points
	ld a, (_cx1)
	cp 15
	jr nc, _cm_two_points_at1_reset
	ld a, (_cy1)
	cp 10
	jr c, _cm_two_points_at1_do
	._cm_two_points_at1_reset
	xor a
	jr _cm_two_points_at1_done
	._cm_two_points_at1_do
	ld a, (_cy1)
	ld b, a
	sla a
	sla a
	sla a
	sla a
	sub b
	ld b, a
	ld a, (_cx1)
	add b
	ld e, a
	ld d, 0
	ld hl, _map_attr
	add hl, de
	ld a, (hl)
	._cm_two_points_at1_done
	ld (_at1), a
	ld a, (_cx2)
	cp 15
	jr nc, _cm_two_points_at2_reset
	ld a, (_cy2)
	cp 10
	jr c, _cm_two_points_at2_do
	._cm_two_points_at2_reset
	xor a
	jr _cm_two_points_at2_done
	._cm_two_points_at2_do
	ld a, (_cy2)
	ld b, a
	sla a
	sla a
	sla a
	sla a
	sub b
	ld b, a
	ld a, (_cx2)
	add b
	ld e, a
	ld d, 0
	ld hl, _map_attr
	add hl, de
	ld a, (hl)
	._cm_two_points_at2_done
	ld (_at2), a
	ret



._attr
	ld a, (_cx1)
	cp 15
	jr nc, _attr_reset
	ld a, (_cy1)
	cp 10
	jr c, _attr_do
	._attr_reset
	ld hl, 0
	ret
	._attr_do
	ld a, (_cy1)
	ld b, a
	sla a
	sla a
	sla a
	sla a
	sub b
	ld b, a
	ld a, (_cx1)
	add b
	ld e, a
	ld d, 0
	ld hl, _map_attr
	add hl, de
	ld a, (hl)
	ld h, 0
	ld l, a
	ret
	ret



._qtile
	ld a, (_cx1)
	cp 15
	jr nc, _qtile_reset
	ld a, (_cy1)
	cp 10
	jr c, _qtile_do
	._qtile_reset
	ld hl, 0
	ret
	._qtile_do
	ld a, (_cy1)
	ld b, a
	sla a
	sla a
	sla a
	sla a
	sub b
	ld b, a
	ld a, (_cx1)
	add b
	ld e, a
	ld d, 0
	ld hl, _map_buff
	add hl, de
	ld a, (hl)
	ld h, 0
	ld l, a
	ret
	ret


	._seed1 defw 0
	._seed2 defw 0
	._randres defb 0

._rand
	.rnd
	ld hl,0xA280
	ld de,0xC0DE
	ld a,h ; t = x ^ (x << 1)
	add a,a
	xor h
	ld h,l ; x = y
	ld l,d ; y = z
	ld d,e ; z = w
	ld e,a
	rra ; t = t ^ (t >> 1)
	xor e
	ld e,a
	ld a,d ; w = w ^ ( w << 3 ) ^ t
	add a,a
	add a,a
	add a,a
	xor d
	xor e
	ld e,a
	ld (rnd+1),hl
	ld (rnd+4),de
	ld (_randres), a
	ld	hl,(_randres)
	ld	h,0
	ret



._srand
	ld hl, (_seed1)
	ld (rnd+1),hl
	ld hl, (_seed2)
	ld (rnd+4),hl
	ret



._game_ending
	call	sp_UpdateNow
	ld	hl,2 % 256	;const
	push	hl
	ld	hl,16384	;const
	push	hl
	call	_get_resource
	pop	bc
	pop	bc
	ret



._game_over
	ld	a,#(3 % 256 % 256)
	ld	(__x),a
	ld	a,#(0 % 256 % 256)
	ld	(__y),a
	ld	hl,(_p_life)
	ld	h,0
	ld	a,l
	ld	(__t),a
	call	_print_number2
	ld	hl,i_1+94
	ld	(_gp_gen),hl
	call	_print_message
	ret



._wall_broken
	ld	a,#(0 % 256 % 256)
	ld	(_gpd),a
	ld	hl,2	;const
	add	hl,sp
	ld	e,(hl)
	ld	d,0
	ld	l,#(4 % 256)
	call	l_asl
	ex	de,hl
	ld	hl,4-2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ex	de,hl
	and	a
	sbc	hl,de
	ex	de,hl
	ld	hl,6-2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	add	hl,de
	ld	h,0
	ld	a,l
	ld	(_gpaux),a
	ld	de,_map_buff
	ld	hl,(_gpaux)
	ld	h,0
	add	hl,de
	ld	e,(hl)
	ld	d,0
	ld	hl,12	;const
	call	l_eq
	jp	nc,i_151
	call	_rand
	ld	de,3	;const
	ex	de,hl
	call	l_and
	ld	de,2	;const
	ex	de,hl
	call	l_le
	jr	c,i_152_i_151
.i_151
	jp	i_150
.i_152_i_151
	ld	hl,22 % 256	;const
	ld	a,l
	ld	(_gpd),a
.i_150
	ld	hl,4	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	a,l
	ld	(__x),a
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	a,l
	ld	(__y),a
	ld	a,#(0 % 256 % 256)
	ld	(__n),a
	ld	hl,(_gpd)
	ld	h,0
	ld	a,l
	ld	(__t),a
	call	_update_tile
	ld	hl,_map
	push	hl
	ld	hl,(_n_pant)
	ld	h,0
	ld	de,75
	call	l_mult
	pop	de
	add	hl,de
	push	hl
	ld	a,(_gpaux)
	ld	e,a
	ld	d,0
	ld	l,#(1 % 256)
	call	l_asr_u
	pop	de
	add	hl,de
	ld	(_map_pointer),hl
	push	hl
	ld	hl,_gpaux
	ld	a,(hl)
	rrca
	jp	nc,i_153
	ld	hl,(_map_pointer)
	ld	a,(hl)
	and	#(240 % 256)
	ld	l,a
	ld	h,0
	jp	i_154
.i_153
	ld	hl,(_map_pointer)
	ld	a,(hl)
	and	#(15 % 256)
	ld	l,a
	ld	h,0
.i_154
	pop	de
	ld	a,l
	ld	(de),a
	ret



._process_breakable
	dec	sp
	ld	a,#(0 % 256 % 256)
	ld	(_do_process_breakable),a
	ld	hl,0	;const
	add	hl,sp
	ld	(hl),#(0 % 256 % 256)
	ld	l,(hl)
	ld	h,0
	jp	i_157
.i_155
	ld	hl,0	;const
	add	hl,sp
	inc	(hl)
	ld	l,(hl)
	ld	h,0
	dec	l
.i_157
	ld	hl,0	;const
	add	hl,sp
	ld	a,(hl)
	cp	#(3 % 256)
	jp	z,i_156
	jp	nc,i_156
	ld	de,_breaking_f
	ld	hl,2-2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	add	hl,de
	ld	a,(hl)
	and	a
	jp	z,i_158
	ld	de,_breaking_f
	ld	hl,2-2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	add	hl,de
	dec	(hl)
	ld	l,(hl)
	ld	h,0
	call	l_lneg
	jp	nc,i_159
	ld	hl,3 % 256	;const
	call	_wyz_play_sound
	ld	de,_breaking_x
	ld	hl,2-2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	add	hl,de
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	de,_breaking_y
	ld	hl,4-2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	add	hl,de
	ld	l,(hl)
	ld	h,0
	push	hl
	call	_wall_broken
	pop	bc
	pop	bc
	jp	i_160
.i_159
	ld	hl,1 % 256	;const
	ld	a,l
	ld	(_do_process_breakable),a
.i_160
.i_158
	jp	i_155
.i_156
	inc	sp
	ret



._break_wall
	ld	hl,4	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	a,l
	ld	(_cx1),a
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	a,l
	ld	(_cy1),a
	call	_attr
	ld	de,16	;const
	ex	de,hl
	call	l_and
	ld	a,h
	or	l
	jp	z,i_161
	ld	hl,2	;const
	add	hl,sp
	ld	e,(hl)
	ld	d,0
	ld	l,#(4 % 256)
	call	l_asl
	ex	de,hl
	ld	hl,4-2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ex	de,hl
	and	a
	sbc	hl,de
	ex	de,hl
	ld	hl,6-2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	add	hl,de
	ld	h,0
	ld	a,l
	ld	(_gpaux),a
	ld	de,_map_attr
	ld	hl,(_gpaux)
	ld	h,0
	add	hl,de
	push	hl
	ld	a,(hl)
	and	#(239 % 256)
	pop	de
	ld	(de),a
	ld	de,_breaking_f
	ld	hl,(_breaking_idx)
	ld	h,0
	add	hl,de
	ld	(hl),#(4 % 256 % 256)
	ld	de,_breaking_x
	ld	hl,(_breaking_idx)
	ld	h,0
	add	hl,de
	push	hl
	ld	hl,6	;const
	add	hl,sp
	ld	a,(hl)
	pop	de
	ld	(de),a
	ld	de,_breaking_y
	ld	hl,(_breaking_idx)
	ld	h,0
	add	hl,de
	push	hl
	ld	hl,4	;const
	add	hl,sp
	ld	a,(hl)
	pop	de
	ld	(de),a
	ld	hl,4	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	a,l
	ld	(__x),a
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	a,l
	ld	(__y),a
	ld	hl,31 % 256	;const
	ld	a,l
	ld	(__t),a
	call	_draw_invalidate_coloured_tile_g
	ld	hl,_breaking_idx
	ld	a,(hl)
	inc	(hl)
	ld	a,(_breaking_idx)
	cp	#(3 % 256)
	jp	nz,i_162
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_breaking_idx),a
.i_162
	ld	a,#(1 % 256 % 256)
	ld	(_do_process_breakable),a
	ld	hl,7 % 256	;const
	call	_wyz_play_sound
.i_161
	ret


;	SECTION	text

._hoffs_x
	defm	""
	defb	12

	defm	""
	defb	14

	defm	""
	defb	16

	defm	""
	defb	16

	defm	""
	defb	12

;	SECTION	code



._render_hitter
	ld	hl,(_gpy)
	ld	h,0
	ld	bc,6
	add	hl,bc
	ld	h,0
	ld	a,l
	ld	(_hitter_y),a
	ld	a,(_p_facing)
	and	a
	jp	z,i_164
	ld	hl,(_gpx)
	ld	h,0
	push	hl
	ld	de,_hoffs_x
	ld	hl,(_hitter_frame)
	ld	h,0
	add	hl,de
	ld	l,(hl)
	ld	h,0
	pop	de
	add	hl,de
	ld	h,0
	ld	a,l
	ld	(_hitter_x),a
	ld	hl,_sprite_20_a
	ld	(_hitter_n_f),hl
	ld	hl,(_hitter_x)
	ld	h,0
	ld	bc,7
	add	hl,bc
	ex	de,hl
	ld	l,#(4 % 256)
	call	l_asr_u
	ld	h,0
	ld	a,l
	ld	(_gpxx),a
	ld	hl,(_hitter_y)
	ld	h,0
	inc	hl
	inc	hl
	inc	hl
	ex	de,hl
	ld	l,#(4 % 256)
	call	l_asr_u
	ld	h,0
	ld	a,l
	ld	(_gpyy),a
	jp	i_165
.i_164
	ld	hl,(_gpx)
	ld	h,0
	ld	bc,8
	add	hl,bc
	push	hl
	ld	de,_hoffs_x
	ld	hl,(_hitter_frame)
	ld	h,0
	add	hl,de
	ld	l,(hl)
	ld	h,0
	pop	de
	ex	de,hl
	and	a
	sbc	hl,de
	ld	h,0
	ld	a,l
	ld	(_hitter_x),a
	ld	hl,_sprite_21_a
	ld	(_hitter_n_f),hl
	ld	a,(_hitter_x)
	ld	e,a
	ld	d,0
	ld	l,#(4 % 256)
	call	l_asr_u
	ld	h,0
	ld	a,l
	ld	(_gpxx),a
	ld	hl,(_hitter_y)
	ld	h,0
	inc	hl
	inc	hl
	inc	hl
	ex	de,hl
	ld	l,#(4 % 256)
	call	l_asr_u
	ld	h,0
	ld	a,l
	ld	(_gpyy),a
.i_165
	ld	a,(_hitter_frame)
	cp	#(1 % 256)
	jr	z,i_167_uge
	jp	c,i_167
.i_167_uge
	ld	a,(_hitter_frame)
	cp	#(3 % 256)
	jr	z,i_168_i_167
	jr	c,i_168_i_167
.i_167
	jp	i_166
.i_168_i_167
	ld	hl,(_gpxx)
	ld	h,0
	push	hl
	ld	hl,(_gpyy)
	ld	h,0
	push	hl
	call	_break_wall
	pop	bc
	pop	bc
.i_166
	; enter: IX = sprite structure address
	; IY = clipping rectangle, set it to "ClipStruct" for full screen
	; BC = animate bitdef displacement (0 for no animation)
	; H = new row coord in chars
	; L = new col coord in chars
	; D = new horizontal rotation (0..7) ie horizontal pixel position
	; E = new vertical rotation (0..7) ie vertical pixel position
	ld ix, (_sp_hitter)
	ld iy, vpClipStruct
	ld hl, (_hitter_n_f)
	ld de, (_hitter_c_f)
	or a
	sbc hl, de
	ld b, h
	ld c, l
	ld a, (_hitter_y)
	srl a
	srl a
	srl a
	add 2
	ld h, a
	ld a, (_hitter_x)
	srl a
	srl a
	srl a
	add 1
	ld l, a
	ld a, (_hitter_x)
	and 7
	ld d, a
	ld a, (_hitter_y)
	and 7
	ld e, a
	call SPMoveSprAbs
	ld hl, (_hitter_n_f)
	ld (_hitter_c_f), hl
	ld	hl,_hitter_frame
	ld	a,(hl)
	inc	(hl)
	ld	a,(_hitter_frame)
	cp	#(5 % 256)
	jp	nz,i_169
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_hitter_on),a
	ld ix, (_sp_hitter)
	ld iy, vpClipStruct
	ld bc, 0
	ld hl, 0xfefe
	ld de, 0
	call SPMoveSprAbs
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_p_hitting),a
.i_169
	ret



._player_init
	xor	a
	ld	(_p_vy),a
	xor	a
	ld	(_p_vx),a
	ld	a,#(1 % 256 % 256)
	ld	(_p_jmp_ct),a
	ld	a,#(0 % 256 % 256)
	ld	(_p_jmp_on),a
	ld	a,#(0 % 256 % 256)
	ld	(_p_frame),a
	ld	a,#(0 % 256 % 256)
	ld	(_p_subframe),a
	ld	hl,255 % 256	;const
	ld	a,l
	ld	(_p_facing_h),a
	ld	h,0
	ld	a,l
	ld	(_p_facing_v),a
	ld	a,#(0 % 256 % 256)
	ld	(_p_state),a
	ld	a,#(0 % 256 % 256)
	ld	(_p_state_ct),a
	ld	a,#(0 % 256 % 256)
	ld	(_p_objs),a
	ld	a,#(0 % 256 % 256)
	ld	(_p_keys),a
	ld	a,#(0 % 256 % 256)
	ld	(_p_killed),a
	ld	a,#(0 % 256 % 256)
	ld	(_p_disparando),a
	ld	a,#(0 % 256 % 256)
	ld	(_p_hitting),a
	ld	a,#(0 % 256 % 256)
	ld	(_hitter_on),a
	ld	a,#(0 % 256 % 256)
	ld	(_p_killme),a
	ld	hl,(_n_pant)
	ld	h,0
	ld	a,l
	ld	(_p_safe_pant),a
	ld	a,(_gpx)
	ld	e,a
	ld	d,0
	ld	l,#(4 % 256)
	call	l_asr_u
	ld	h,0
	ld	a,l
	ld	(_p_safe_x),a
	ld	a,(_gpy)
	ld	e,a
	ld	d,0
	ld	l,#(4 % 256)
	call	l_asr_u
	ld	h,0
	ld	a,l
	ld	(_p_safe_y),a
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_breaking_idx),a
	ret



._player_calc_bounding_box
	ld a, (_gpx)
	add 4
	srl a
	srl a
	srl a
	srl a
	ld (_ptx1), a
	ld a, (_gpx)
	add 11
	srl a
	srl a
	srl a
	srl a
	ld (_ptx2), a
	ld a, (_gpy)
	add 8
	srl a
	srl a
	srl a
	srl a
	ld (_pty1), a
	ld a, (_gpy)
	add 15
	srl a
	srl a
	srl a
	srl a
	ld (_pty2), a
	ret



._player_kill
	ld	hl,_p_life
	ld	a,(hl)
	dec	(hl)
	ld	l,a
	ld	h,0
	call	_wyz_stop_sound
	ld	a,#(0 % 256 % 256)
	ld	(_half_life),a
	ld	a,#(2 % 256 % 256)
	ld	(_p_state),a
	ld	a,#(50 % 256 % 256)
	ld	(_p_state_ct),a
	ld	hl,0 % 256	;const
	call	_wyz_play_sample
	ld	hl,50	;const
	push	hl
	call	_active_sleep
	pop	bc
	ld	a,(_p_engine)
	cp	#(1 % 256)
	jp	z,i_170
	ld	hl,(_p_safe_pant)
	ld	h,0
	ld	a,l
	ld	(_n_pant),a
	ld	hl,(_p_safe_x)
	ld	h,0
	ld	a,l
	ld	(_gpjt),a
	ld	hl,15 % 256	;const
	ld	a,l
	ld	(_gpit),a
.i_171
	ld	hl,_gpit
	ld	a,(hl)
	dec	(hl)
	ld	l,a
	ld	h,0
	ld	a,h
	or	l
	jp	z,i_172
	ld	hl,(_gpjt)
	ld	h,0
	ld	a,l
	ld	(_cx1),a
	ld	hl,(_p_safe_y)
	ld	h,0
	inc	hl
	ld	h,0
	ld	a,l
	ld	(_cy1),a
	call	_attr
	ld	h,0
	ld	a,l
	ld	(_at1),a
	ld	hl,(_gpjt)
	ld	h,0
	ld	a,l
	ld	(_cx1),a
	ld	hl,(_p_safe_y)
	ld	h,0
	ld	a,l
	ld	(_cy1),a
	call	_attr
	ld	h,0
	ld	a,l
	ld	(_at2),a
	ld	hl,_at1
	ld	a,(hl)
	and	#(12 % 256)
	jp	z,i_174
	ld	a,(_at2)
	ld	e,a
	ld	d,0
	ld	hl,8	;const
	call	l_and
	call	l_lneg
	jr	c,i_175_i_174
.i_174
	jp	i_173
.i_175_i_174
	jp	i_172
.i_173
	ld	hl,_gpjt
	ld	a,(hl)
	inc	(hl)
	ld	a,(_gpjt)
	cp	#(15 % 256)
	jp	nz,i_176
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_gpjt),a
.i_176
	jp	i_171
.i_172
	ld	hl,(_gpjt)
	ld	h,0
	ld	a,l
	ld	(_p_safe_x),a
	ld	e,a
	ld	d,0
	ld	l,#(4 % 256)
	call	l_asl
	ld	h,0
	ld	a,l
	ld	(_gpx),a
	ld	a,(_p_safe_y)
	ld	e,a
	ld	d,0
	ld	l,#(4 % 256)
	call	l_asl
	ld	h,0
	ld	a,l
	ld	(_gpy),a
	ld	a,(_gpx)
	ld	e,a
	ld	d,0
	ld	l,#(4 % 256)
	call	l_asl
	ld	(_p_x),hl
	ld	a,(_gpy)
	ld	e,a
	ld	d,0
	ld	l,#(4 % 256)
	call	l_asl
	ld	(_p_y),hl
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_p_jmp_on),a
	ld	a,l
	call	l_sxt
	ld	a,l
	ld	(_p_vy),a
	ld	a,l
	call	l_sxt
	ld	a,l
	ld	(_p_vx),a
.i_170
	ld	hl,(_level_data+10)
	ld	h,0
	call	_wyz_play_music
	ret



._player_move
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_wall_h),a
	ld	h,0
	ld	a,l
	ld	(_wall_v),a
	ld	a,(_do_gravity)
	and	a
	jp	z,i_177
	ld	hl,_p_vy
	call	l_gchar
	ld	de,115	;const
	ex	de,hl
	call	l_le
	jp	nc,i_178
	ld	hl,_p_vy
	call	l_gchar
	ld	bc,12
	add	hl,bc
	ld	a,l
	call	l_sxt
	ld	a,l
	ld	(_p_vy),a
	jp	i_179
.i_178
	ld	hl,127	;const
	ld	a,l
	call	l_sxt
	ld	a,l
	ld	(_p_vy),a
.i_179
.i_177
	ld	a,(_p_gotten)
	and	a
	jp	z,i_180
	ld	hl,0	;const
	ld	a,l
	call	l_sxt
	ld	a,l
	ld	(_p_vy),a
.i_180
	ld	a,(_p_engine)
	cp	#(1 % 256)
	jp	nz,i_181
	ld	a,#(1 % 256 % 256)
	ld	(_p_gotten),a
	ld	a,(_pad0)
	ld	e,a
	ld	d,0
	ld	hl,2	;const
	call	l_and
	ld	de,0	;const
	ex	de,hl
	call	l_eq
	jp	c,i_183
	ld	a,(_pad0)
	ld	e,a
	ld	d,0
	ld	hl,1	;const
	call	l_and
	ld	de,0	;const
	ex	de,hl
	call	l_eq
	jp	c,i_183
	ld	hl,0	;const
	jr	i_184
.i_183
	ld	hl,1	;const
.i_184
	call	l_lneg
	jp	nc,i_182
	ld	hl,_p_vy
	call	l_gchar
	ld	bc,-4
	add	hl,bc
	ld	a,l
	call	l_sxt
	ld	a,l
	ld	(_p_vy),a
	ld	hl,_p_vy
	call	l_gchar
	ld	de,16	;const
	ex	de,hl
	call	l_lt
	jp	nc,i_185
	ld	hl,65520	;const
	ld	a,l
	call	l_sxt
	ld	a,l
	ld	(_p_vy),a
.i_185
.i_182
	ld	hl,_pad0
	ld	a,(hl)
	and	#(2 % 256)
	jp	nz,i_186
	ld	hl,_p_vy
	call	l_gchar
	ld	de,32	;const
	ex	de,hl
	call	l_lt
	jp	nc,i_187
	ld	hl,_p_vy
	call	l_gchar
	ld	bc,8
	add	hl,bc
	ld	a,l
	call	l_sxt
	ld	a,l
	ld	(_p_vy),a
.i_187
.i_186
	ld	a,(_pad0)
	ld	e,a
	ld	d,0
	ld	hl,1	;const
	call	l_and
	ld	de,0	;const
	ex	de,hl
	call	l_eq
	jp	c,i_189
	ld	a,(_pad0)
	ld	e,a
	ld	d,0
	ld	hl,1	;const
	call	l_and
	ld	de,0	;const
	ex	de,hl
	call	l_eq
	jp	nc,i_188
.i_189
	ld	hl,_p_vy
	call	l_gchar
	ld	de,65504	;const
	ex	de,hl
	call	l_gt
	jp	nc,i_191
	ld	hl,_p_vy
	call	l_gchar
	ld	bc,-8
	add	hl,bc
	ld	a,l
	call	l_sxt
	ld	a,l
	ld	(_p_vy),a
.i_191
.i_188
.i_181
	ld	hl,(_p_y)
	push	hl
	ld	hl,_p_vy
	call	l_gchar
	pop	de
	add	hl,de
	ld	(_p_y),hl
	xor	a
	or	h
	jp	p,i_192
	ld	hl,0	;const
	ld	(_p_y),hl
.i_192
	ld	hl,(_p_y)
	ld	de,2304	;const
	ex	de,hl
	call	l_gt
	jp	nc,i_193
	ld	hl,2304	;const
	ld	(_p_y),hl
.i_193
	ld	hl,(_p_y)
	ex	de,hl
	ld	l,#(4 % 256)
	call	l_asr
	ld	h,0
	ld	a,l
	ld	(_gpy),a
	call _player_calc_bounding_box
	xor a
	ld (_hit_v), a
	ld a, (_ptx1)
	ld (_cx1), a
	ld a, (_ptx2)
	ld (_cx2), a
	ld a, (_p_vy)
	ld c, a
	ld a, (_ptgmy)
	add c
	or a
	jp z, _va_collision_done
	bit 7, a
	jr z, _va_collision_vy_positive
	._va_collision_vy_negative
	ld a, (_pty1)
	ld (_cy1), a
	ld (_cy2), a
	call _cm_two_points
	ld a, (_at1)
	and 8
	jr nz, _va_col_vy_neg_do
	ld a, (_at2)
	and 8
	jr z, _va_collision_checkevil
	._va_col_vy_neg_do
	xor a
	ld (_p_vy), a
	ld a, (_pty1)
	inc a
	sla a
	sla a
	sla a
	sla a
	sub 8
	ld (_gpy), a
	ld d, 0
	ld e, a
	ld l, 4
	call l_asl
	ld (_p_y), hl
	ld a, 1
	ld (_wall_v), a
	jr _va_collision_checkevil
	._va_collision_vy_positive
	ld a, (_pty2)
	ld (_cy1), a
	ld (_cy2), a
	call _cm_two_points
	ld a, (_at1)
	and 8
	jr nz, _va_col_vy_pos_do
	ld a, (_at2)
	and 8
	jr nz, _va_col_vy_pos_do
	ld a, (_gpy)
	dec a
	and 15
	cp 8
	jr nc, _va_collision_checkevil
	ld a, (_at1)
	and 4
	jr nz, _va_col_vy_pos_do
	ld a, (_at2)
	and 4
	jr z, _va_collision_checkevil
	._va_col_vy_pos_do
	xor a
	ld (_p_vy), a
	ld a, (_pty2)
	dec a
	sla a
	sla a
	sla a
	sla a
	ld (_gpy), a
	ld d, 0
	ld e, a
	ld l, 4
	call l_asl
	ld (_p_y), hl
	ld a, 2
	ld (_wall_v), a
	._va_collision_checkevil
	._va_collision_done
	ld	a,(_gpx)
	ld	e,a
	ld	d,0
	ld	l,#(4 % 256)
	call	l_asr_u
	ld	h,0
	ld	a,l
	ld	(_gpxx),a
	ld	a,(_gpy)
	ld	e,a
	ld	d,0
	ld	l,#(4 % 256)
	call	l_asr_u
	ld	h,0
	ld	a,l
	ld	(_gpyy),a
	ld	hl,(_gpy)
	ld	h,0
	ld	bc,16
	add	hl,bc
	ex	de,hl
	ld	l,#(4 % 256)
	call	l_asr_u
	ld	h,0
	ld	a,l
	ld	(_cy2),a
	ld	h,0
	ld	a,l
	ld	(_cy1),a
	ld	hl,(_ptx1)
	ld	h,0
	ld	a,l
	ld	(_cx1),a
	ld	hl,(_ptx2)
	ld	h,0
	ld	a,l
	ld	(_cx2),a
	call	_cm_two_points
	ld	hl,_at1
	ld	a,(hl)
	and	#(12 % 256)
	jp	nz,i_194
	ld	hl,_at2
	ld	a,(hl)
	and	#(12 % 256)
	jp	z,i_196
.i_194
	ld	a,(_gpy)
	ld	e,a
	ld	d,0
	ld	hl,15	;const
	call	l_and
	ld	de,8	;const
	ex	de,hl
	call	l_ult
	jp	nc,i_196
	ld	hl,1	;const
	jr	i_197
.i_196
	ld	hl,0	;const
.i_197
	ld	h,0
	ld	a,l
	ld	(_possee),a
	ld	a,(_p_engine)
	cp	#(1 % 256)
	jp	z,i_198
	ld	a,(_possee)
	and	a
	jp	z,i_199
	ld	hl,(_n_pant)
	ld	h,0
	ld	a,l
	ld	(_p_safe_pant),a
	ld	hl,(_gpxx)
	ld	h,0
	ld	a,l
	ld	(_p_safe_x),a
	ld	hl,(_gpyy)
	ld	h,0
	ld	a,l
	ld	(_p_safe_y),a
.i_199
.i_198
	ld	a,(_p_engine)
	and	a
	jp	nz,i_200
	ld	hl,_pad_this_frame
	ld	a,(hl)
	and	#(1 % 256)
	cp	#(0 % 256)
	ld	hl,0
	jp	nz,i_202
	inc	hl
	ld	a,(_p_jmp_on)
	cp	#(0 % 256)
	jp	nz,i_202
	ld	a,(_possee)
	and	a
	jp	nz,i_203
	ld	a,(_p_gotten)
	and	a
	jp	z,i_202
.i_203
	jr	i_205_i_202
.i_202
	jp	i_201
.i_205_i_202
	ld	a,#(1 % 256 % 256)
	ld	(_p_jmp_on),a
	ld	a,#(0 % 256 % 256)
	ld	(_p_jmp_ct),a
	ld	hl,2 % 256	;const
	call	_wyz_play_sound
.i_201
	ld	hl,_pad0
	ld	a,(hl)
	and	#(1 % 256)
	cp	#(0 % 256)
	ld	hl,0
	jp	nz,i_207
	inc	hl
	ld	a,(_p_jmp_on)
	and	a
	jr	nz,i_208_i_207
.i_207
	jp	i_206
.i_208_i_207
	ld	hl,_p_vy
	call	l_gchar
	push	hl
	ld	a,(_p_jmp_ct)
	ld	e,a
	ld	d,0
	ld	l,#(1 % 256)
	call	l_asr_u
	ld	de,36
	ex	de,hl
	and	a
	sbc	hl,de
	pop	de
	ex	de,hl
	and	a
	sbc	hl,de
	ld	a,l
	call	l_sxt
	ld	a,l
	ld	(_p_vy),a
	ld	hl,_p_vy
	call	l_gchar
	ld	de,65458	;const
	ex	de,hl
	call	l_lt
	jp	nc,i_209
	ld	hl,65458	;const
	ld	a,l
	call	l_sxt
	ld	a,l
	ld	(_p_vy),a
.i_209
	ld	hl,_p_jmp_ct
	ld	a,(hl)
	inc	(hl)
	ld	a,(_p_jmp_ct)
	cp	#(8 % 256)
	jp	nz,i_210
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_p_jmp_on),a
.i_210
.i_206
	ld	a,(_pad0)
	ld	e,a
	ld	d,0
	ld	hl,1	;const
	call	l_and
	ld	de,0	;const
	ex	de,hl
	call	l_eq
	ccf
	jp	nc,i_211
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_p_jmp_on),a
.i_211
.i_200
	ld	a,(_possee)
	and	a
	jp	z,i_212
	ld	hl,(_gpy)
	ld	h,0
	ld	bc,16
	add	hl,bc
	ex	de,hl
	ld	l,#(4 % 256)
	call	l_asr_u
	ld	h,0
	ld	a,l
	ld	(_cy2),a
	ld	h,0
	ld	a,l
	ld	(_cy1),a
	ld	hl,(_ptx1)
	ld	h,0
	ld	a,l
	ld	(_cx1),a
	ld	hl,(_ptx2)
	ld	h,0
	ld	a,l
	ld	(_cx2),a
	call	_cm_two_points
	ld	hl,_at1
	ld	a,(hl)
	and	#(32 % 256)
	jp	z,i_213
	ld	hl,1 % 256	;const
	ld	a,l
	ld	(_p_gotten),a
	xor	a
	ld	(_ptgmy),a
	ld	hl,_at1
	ld	a,(hl)
	rrca
	jp	nc,i_214
	ld	hl,64	;const
	jp	i_215
.i_214
	ld	hl,65472	;const
.i_215
	ld	a,l
	call	l_sxt
	ld	a,l
	ld	(_ptgmx),a
.i_213
	ld	hl,_at2
	ld	a,(hl)
	and	#(32 % 256)
	jp	z,i_216
	ld	hl,1 % 256	;const
	ld	a,l
	ld	(_p_gotten),a
	xor	a
	ld	(_ptgmy),a
	ld	hl,_at2
	ld	a,(hl)
	rrca
	jp	nc,i_217
	ld	hl,64	;const
	jp	i_218
.i_217
	ld	hl,65472	;const
.i_218
	ld	a,l
	call	l_sxt
	ld	a,l
	ld	(_ptgmx),a
.i_216
.i_212
	ld	a,(_pad0)
	ld	e,a
	ld	d,0
	ld	hl,4	;const
	call	l_and
	ld	de,0	;const
	ex	de,hl
	call	l_eq
	jp	c,i_219
	ld	a,(_pad0)
	ld	e,a
	ld	d,0
	ld	hl,8	;const
	call	l_and
	ld	de,0	;const
	ex	de,hl
	call	l_eq
	jp	c,i_219
	ld	hl,0	;const
	jr	i_220
.i_219
	ld	hl,1	;const
.i_220
	ld	h,0
	ld	a,l
	ld	(_rda),a
	ld	hl,(_rda)
	ld	h,0
	call	l_lneg
	jp	nc,i_221
	ld	hl,_p_vx
	call	l_gchar
	xor	a
	or	h
	jp	m,i_222
	or	l
	jp	z,i_222
	ld	hl,_p_vx
	call	l_gchar
	ld	bc,-24
	add	hl,bc
	ld	a,l
	call	l_sxt
	ld	a,l
	ld	(_p_vx),a
	ld	hl,_p_vx
	call	l_gchar
	xor	a
	or	h
	jp	p,i_223
	ld	hl,0	;const
	ld	a,l
	call	l_sxt
	ld	a,l
	ld	(_p_vx),a
.i_223
	jp	i_224
.i_222
	ld	hl,_p_vx
	call	l_gchar
	xor	a
	or	h
	jp	p,i_225
	ld	hl,_p_vx
	call	l_gchar
	ld	bc,24
	add	hl,bc
	ld	a,l
	call	l_sxt
	ld	a,l
	ld	(_p_vx),a
	ld	hl,_p_vx
	call	l_gchar
	xor	a
	or	h
	jp	m,i_226
	or	l
	jp	z,i_226
	ld	hl,0	;const
	ld	a,l
	call	l_sxt
	ld	a,l
	ld	(_p_vx),a
.i_226
.i_225
.i_224
.i_221
	ld	hl,_pad0
	ld	a,(hl)
	and	#(4 % 256)
	jp	nz,i_227
	ld	hl,_p_vx
	call	l_gchar
	ld	de,65472	;const
	ex	de,hl
	call	l_gt
	jp	nc,i_228
	ld	a,#(0 % 256 % 256)
	ld	(_p_facing),a
	ld	hl,_p_vx
	call	l_gchar
	ld	bc,-16
	add	hl,bc
	ld	a,l
	call	l_sxt
	ld	a,l
	ld	(_p_vx),a
.i_228
.i_227
	ld	hl,_pad0
	ld	a,(hl)
	and	#(8 % 256)
	jp	nz,i_229
	ld	hl,_p_vx
	call	l_gchar
	ld	de,64	;const
	ex	de,hl
	call	l_lt
	jp	nc,i_230
	ld	hl,_p_vx
	call	l_gchar
	ld	bc,16
	add	hl,bc
	ld	a,l
	call	l_sxt
	ld	a,l
	ld	(_p_vx),a
	ld	hl,1 % 256	;const
	ld	a,l
	ld	(_p_facing),a
.i_230
.i_229
	ld	hl,(_p_x)
	push	hl
	ld	hl,_p_vx
	call	l_gchar
	pop	de
	add	hl,de
	ld	(_p_x),hl
	ld	a,(_p_gotten)
	and	a
	jp	z,i_231
	ld	hl,(_p_x)
	push	hl
	ld	hl,_ptgmx
	call	l_gchar
	pop	de
	add	hl,de
	ld	(_p_x),hl
.i_231
	ld	hl,(_p_x)
	xor	a
	or	h
	jp	p,i_232
	ld	hl,0	;const
	ld	(_p_x),hl
.i_232
	ld	hl,(_p_x)
	ld	de,3584	;const
	ex	de,hl
	call	l_gt
	jp	nc,i_233
	ld	hl,3584	;const
	ld	(_p_x),hl
.i_233
	ld	hl,(_p_x)
	ex	de,hl
	ld	l,#(4 % 256)
	call	l_asr
	ld	h,0
	ld	a,l
	ld	(_gpx),a
	call _player_calc_bounding_box
	xor a
	ld (_hit_h), a
	ld a, (_pty1)
	ld (_cy1), a
	ld a, (_pty2)
	ld (_cy2), a
	ld a, (_p_vx)
	ld c, a
	ld a, (_ptgmx)
	add c
	or a
	jp z, _ha_collision_done
	bit 7, a
	jr z, _ha_collision_vx_positive
	._ha_collision_vx_negative
	ld a, (_ptx1)
	ld (_cx1), a
	ld (_cx2), a
	call _cm_two_points
	ld a, (_at1)
	and 8
	jr nz, _ha_col_vx_neg_do
	ld a, (_at2)
	and 8
	jr z, _ha_collision_checkevil
	._ha_col_vx_neg_do
	xor a
	ld (_p_vx), a
	ld a, (_ptx1)
	inc a
	sla a
	sla a
	sla a
	sla a
	sub 4
	ld (_gpx), a
	ld d, 0
	ld e, a
	ld l, 4
	call l_asl
	ld (_p_x), hl
	ld a, 3
	ld (_wall_h), a
	jr _ha_collision_checkevil
	._ha_collision_vx_positive
	ld a, (_ptx2)
	ld (_cx1), a
	ld (_cx2), a
	call _cm_two_points
	ld a, (_at1)
	and 8
	jr nz, _ha_col_vx_pos_do
	ld a, (_at2)
	and 8
	jr z, _ha_collision_checkevil
	._ha_col_vx_pos_do
	xor a
	ld (_p_vx), a
	ld a, (_ptx2)
	dec a
	sla a
	sla a
	sla a
	sla a
	add 4
	ld (_gpx), a
	ld d, 0
	ld e, a
	ld l, 4
	call l_asl
	ld (_p_x), hl
	ld a, 4
	ld (_wall_h), a
	._ha_collision_checkevil
	._ha_collision_done
	ld	hl,_pad0
	ld	a,(hl)
	and	#(128 % 256)
	cp	#(0 % 256)
	ld	hl,0
	jp	nz,i_235
	inc	hl
	ld	hl,(_p_disparando)
	ld	h,0
	call	l_lneg
	jr	c,i_236_i_235
.i_235
	jp	i_234
.i_236_i_235
	ld	a,#(1 % 256 % 256)
	ld	(_p_disparando),a
	ld	a,(_hitter_on)
	and	a
	jp	nz,i_237
	ld	a,#(0 % 256 % 256)
	ld	(_hitter_hit),a
	ld	a,#(1 % 256 % 256)
	ld	(_hitter_on),a
	ld	a,#(0 % 256 % 256)
	ld	(_hitter_frame),a
	ld	a,#(1 % 256 % 256)
	ld	(_p_hitting),a
	ld	hl,8 % 256	;const
	call	_wyz_play_sound
.i_237
.i_234
	ld	a,(_pad0)
	ld	e,a
	ld	d,0
	ld	hl,128	;const
	call	l_and
	ld	de,0	;const
	ex	de,hl
	call	l_eq
	ccf
	jp	nc,i_238
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_p_disparando),a
.i_238
	ld	hl,(_gpx)
	ld	h,0
	ld	bc,8
	add	hl,bc
	ex	de,hl
	ld	l,#(4 % 256)
	call	l_asr_u
	ld	h,0
	ld	a,l
	ld	(_cx1),a
	ld	hl,(_gpy)
	ld	h,0
	ld	bc,8
	add	hl,bc
	ex	de,hl
	ld	l,#(4 % 256)
	call	l_asr_u
	ld	h,0
	ld	a,l
	ld	(_cy1),a
	call	_qtile
	ld	de,22	;const
	ex	de,hl
	call	l_eq
	jp	nc,i_239
	ld	hl,(_cx1)
	ld	h,0
	ld	a,l
	ld	(__x),a
	ld	hl,(_cy1)
	ld	h,0
	ld	a,l
	ld	(__y),a
	ld	a,#(0 % 256 % 256)
	ld	(__t),a
	ld	hl,(_behs)
	ld	h,0
	ld	a,l
	ld	(__n),a
	call	_update_tile
	ld	a,(_flags+1)
	cp	#(99 % 256)
	jp	z,i_240
	jp	nc,i_240
	ld	hl,_flags+1
	inc	(hl)
	ld	l,(hl)
	ld	h,0
	dec	l
.i_240
	ld	hl,5 % 256	;const
	call	_wyz_play_sound
.i_239
	ld	a,#(0 % 256 % 256)
	ld	(_hit),a
	ld	a,(_hit_v)
	cp	#(1 % 256)
	jp	nz,i_241
	ld	a,#(1 % 256 % 256)
	ld	(_hit),a
	ld	hl,_p_vy
	call	l_gchar
	call	l_neg
	push	hl
	ld	hl,100	;const
	push	hl
	call	_addsign
	pop	bc
	pop	bc
	ld	a,l
	call	l_sxt
	ld	a,l
	ld	(_p_vy),a
	jp	i_242
.i_241
	ld	a,(_hit_h)
	cp	#(1 % 256)
	jp	nz,i_243
	ld	a,#(1 % 256 % 256)
	ld	(_hit),a
	ld	hl,_p_vx
	call	l_gchar
	call	l_neg
	push	hl
	ld	hl,100	;const
	push	hl
	call	_addsign
	pop	bc
	pop	bc
	ld	a,l
	call	l_sxt
	ld	a,l
	ld	(_p_vx),a
.i_243
.i_242
	ld	a,(_hit)
	and	a
	jp	z,i_244
	ld	a,(_p_life)
	cp	#(0 % 256)
	jp	z,i_246
	jp	c,i_246
	ld	a,(_p_state)
	cp	#(0 % 256)
	jr	z,i_247_i_246
.i_246
	jp	i_245
.i_247_i_246
	ld	hl,6 % 256	;const
	ld	a,l
	ld	(_p_killme),a
.i_245
.i_244
	ld	hl,(_possee)
	ld	h,0
	call	l_lneg
	jp	nc,i_249
	ld	hl,(_p_gotten)
	ld	h,0
	call	l_lneg
	jr	c,i_250_i_249
.i_249
	jp	i_248
.i_250_i_249
	ld	hl,_player_frames
	push	hl
	ld	hl,(_p_facing)
	ld	h,0
	ld	de,8
	add	hl,de
	add	hl,hl
	pop	de
	add	hl,de
	call	l_gint	;
	ld	(_p_n_f),hl
	jp	i_251
.i_248
	ld	a,(_p_facing)
	ld	e,a
	ld	d,0
	ld	l,#(2 % 256)
	call	l_asl
	ld	h,0
	ld	a,l
	ld	(_gpit),a
	ld	hl,_p_vx
	call	l_gchar
	ld	a,h
	or	l
	jp	nz,i_252
	ld	hl,_player_frames
	push	hl
	ld	hl,(_gpit)
	ld	h,0
	inc	hl
	add	hl,hl
	pop	de
	add	hl,de
	call	l_gint	;
	ld	(_p_n_f),hl
	jp	i_253
.i_252
	ld	hl,_p_subframe
	ld	a,(hl)
	inc	(hl)
	ld	a,(_p_subframe)
	cp	#(4 % 256)
	jp	nz,i_254
	ld	a,#(0 % 256 % 256)
	ld	(_p_subframe),a
	ld	hl,(_p_frame)
	ld	h,0
	inc	hl
	ld	de,3	;const
	ex	de,hl
	call	l_and
	ld	h,0
	ld	a,l
	ld	(_p_frame),a
.i_254
	ld	hl,_player_frames
	push	hl
	ld	hl,(_gpit)
	ld	h,0
	ex	de,hl
	ld	hl,(_p_frame)
	ld	h,0
	add	hl,de
	add	hl,hl
	pop	de
	add	hl,de
	call	l_gint	;
	ld	(_p_n_f),hl
.i_253
.i_251
	ret



._distance
	ld	hl,4	;const
	add	hl,sp
	ld	e,(hl)
	ld	d,0
	ld	hl,10-2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ex	de,hl
	and	a
	sbc	hl,de
	push	hl
	call	_abs
	pop	bc
	ld	a,l
	call	l_sxt
	dec	sp
	ld	a,l
	pop	hl
	ld	l,a
	push	hl
	ld	hl,3	;const
	add	hl,sp
	ld	e,(hl)
	ld	d,0
	ld	hl,9-2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ex	de,hl
	and	a
	sbc	hl,de
	push	hl
	call	_abs
	pop	bc
	ld	a,l
	call	l_sxt
	dec	sp
	ld	a,l
	pop	hl
	ld	l,a
	push	hl
	ld	l,h
	ld	h,0
	ex	de,hl
	ld	hl,2-2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	l_ult
	jp	nc,i_255
	pop	hl
	push	hl
	ld	l,h
	ld	h,0
	jp	i_256
.i_255
	ld	hl,0	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
.i_256
	ld	a,l
	call	l_sxt
	dec	sp
	ld	a,l
	pop	hl
	ld	l,a
	push	hl
	ld	hl,2	;const
	add	hl,sp
	ld	e,(hl)
	ld	d,0
	ld	hl,3-2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	add	hl,de
	push	hl
	ld	hl,2	;const
	add	hl,sp
	ld	e,(hl)
	ld	d,0
	ld	l,#(1 % 256)
	call	l_asr_u
	pop	de
	ex	de,hl
	and	a
	sbc	hl,de
	push	hl
	ld	hl,2	;const
	add	hl,sp
	ld	e,(hl)
	ld	d,0
	ld	l,#(2 % 256)
	call	l_asr_u
	pop	de
	ex	de,hl
	and	a
	sbc	hl,de
	push	hl
	ld	hl,2	;const
	add	hl,sp
	ld	e,(hl)
	ld	d,0
	ld	l,#(4 % 256)
	call	l_asr_u
	pop	de
	add	hl,de
	ld	h,0
	inc	sp
	pop	bc
	ret



._init_cocos
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_gpit),a
.i_257
.i_259
	ld	a,(_gpit)
	cp	#(3 % 256)
	jp	z,i_258
	jp	nc,i_258
	ld	hl,_coco_s
	push	hl
	ld	hl,_gpit
	ld	a,(hl)
	inc	(hl)
	ld	l,a
	ld	h,0
	pop	de
	add	hl,de
	ld	(hl),#(0 % 256 % 256)
	ld	l,(hl)
	ld	h,0
	jp	i_257
.i_258
	ret



._shoot_coco
	ld	hl,(__en_x)
	ld	h,0
	ld	bc,4
	add	hl,bc
	ld	h,0
	ld	a,l
	ld	(_coco_x0),a
	ld	hl,(_enit)
	ld	h,0
	ld	a,l
	ld	(_coco_it),a
	ld	de,_coco_s
	ld	hl,(_coco_it)
	ld	h,0
	add	hl,de
	ld	a,(hl)
	and	a
	jp	nz,i_260
	ld	hl,(_coco_x0)
	ld	h,0
	push	hl
	ld	hl,(__en_y)
	ld	h,0
	push	hl
	ld	hl,(_gpx)
	ld	h,0
	push	hl
	ld	hl,(_gpy)
	ld	h,0
	push	hl
	call	_distance
	pop	bc
	pop	bc
	pop	bc
	pop	bc
	ld	h,0
	ld	a,l
	ld	(_coco_d),a
	cp	#(64 % 256)
	jr	z,i_261_uge
	jp	c,i_261
.i_261_uge
	ld	hl,3 % 256	;const
	call	_wyz_play_sound
	ld	de,_coco_s
	ld	hl,(_coco_it)
	ld	h,0
	add	hl,de
	ld	(hl),#(1 % 256 % 256)
	ld	de,_coco_x
	ld	hl,(_coco_it)
	ld	h,0
	add	hl,de
	push	hl
	ld	hl,_coco_x0
	ld	a,(hl)
	pop	de
	ld	(de),a
	ld	de,_coco_y
	ld	hl,(_coco_it)
	ld	h,0
	add	hl,de
	push	hl
	ld	hl,__en_y
	ld	a,(hl)
	pop	de
	ld	(de),a
	ld	de,_coco_vx
	ld	hl,(_coco_it)
	ld	h,0
	add	hl,de
	push	hl
	ld	hl,(_gpx)
	ld	h,0
	ex	de,hl
	ld	hl,(_coco_x0)
	ld	h,0
	ex	de,hl
	and	a
	sbc	hl,de
	ld	de,6
	call	l_mult
	ex	de,hl
	ld	hl,(_coco_d)
	ld	h,0
	call	l_div
	ld	a,l
	call	l_sxt
	pop	de
	ld	a,l
	ld	(de),a
	ld	de,_coco_vy
	ld	hl,(_coco_it)
	ld	h,0
	add	hl,de
	push	hl
	ld	hl,(_gpy)
	ld	h,0
	ex	de,hl
	ld	hl,(__en_y)
	ld	h,0
	ex	de,hl
	and	a
	sbc	hl,de
	ld	de,6
	call	l_mult
	ex	de,hl
	ld	hl,(_coco_d)
	ld	h,0
	call	l_div
	ld	a,l
	call	l_sxt
	pop	de
	ld	a,l
	ld	(de),a
.i_261
.i_260
	ret



._move_cocos
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_coco_it),a
	jp	i_264
.i_262
	ld	hl,_coco_it
	ld	a,(hl)
	inc	(hl)
.i_264
	ld	a,(_coco_it)
	cp	#(3 % 256)
	jp	z,i_263
	jp	nc,i_263
	ld	de,_coco_s
	ld	hl,(_coco_it)
	ld	h,0
	add	hl,de
	ld	a,(hl)
	and	a
	jp	z,i_265
	ld	de,_coco_x
	ld	hl,(_coco_it)
	ld	h,0
	add	hl,de
	push	hl
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	de,_coco_vx
	ld	hl,(_coco_it)
	ld	h,0
	add	hl,de
	call	l_gchar
	pop	de
	add	hl,de
	pop	de
	ld	a,l
	ld	(de),a
	ld	de,_coco_y
	ld	hl,(_coco_it)
	ld	h,0
	add	hl,de
	push	hl
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	de,_coco_vy
	ld	hl,(_coco_it)
	ld	h,0
	add	hl,de
	call	l_gchar
	pop	de
	add	hl,de
	pop	de
	ld	a,l
	ld	(de),a
	ld	de,_coco_x
	ld	hl,(_coco_it)
	ld	h,0
	add	hl,de
	ld	e,(hl)
	ld	d,0
	ld	hl,240	;const
	call	l_uge
	jp	c,i_267
	ld	de,_coco_y
	ld	hl,(_coco_it)
	ld	h,0
	add	hl,de
	ld	e,(hl)
	ld	d,0
	ld	hl,160	;const
	call	l_uge
	jp	nc,i_266
.i_267
	ld	de,_coco_s
	ld	hl,(_coco_it)
	ld	h,0
	add	hl,de
	ld	(hl),#(0 % 256 % 256)
.i_266
	ld	de,_coco_x
	ld	hl,(_coco_it)
	ld	h,0
	add	hl,de
	ld	l,(hl)
	ld	h,0
	inc	hl
	inc	hl
	inc	hl
	ld	h,0
	ld	a,l
	ld	(_ctx),a
	ld	de,_coco_y
	ld	hl,(_coco_it)
	ld	h,0
	add	hl,de
	ld	l,(hl)
	ld	h,0
	inc	hl
	inc	hl
	inc	hl
	ld	h,0
	ld	a,l
	ld	(_cty),a
	ld	a,(_p_state)
	and	a
	jp	nz,i_269
	ld	hl,(_ctx)
	ld	h,0
	ld	a,l
	ld	(_cx1),a
	ld	hl,(_cty)
	ld	h,0
	ld	a,l
	ld	(_cy1),a
	ld	hl,(_gpx)
	ld	h,0
	ld	a,l
	ld	(_cx2),a
	ld	hl,(_gpy)
	ld	h,0
	ld	a,l
	ld	(_cy2),a
	call	_collide_pixel
	ld	a,h
	or	l
	jp	z,i_270
	ld	de,_coco_s
	ld	hl,(_coco_it)
	ld	h,0
	add	hl,de
	ld	(hl),#(0 % 256 % 256)
	ld	hl,6 % 256	;const
	ld	a,l
	ld	(_p_killme),a
.i_270
.i_269
.i_265
	jp	i_262
.i_263
	ret



._mons_col_sc_x
	ld	hl,__en_mx
	call	l_gchar
	ld	de,0	;const
	ex	de,hl
	call	l_gt
	jp	nc,i_271
	ld	hl,(__en_x)
	ld	h,0
	ld	bc,15
	add	hl,bc
	jp	i_272
.i_271
	ld	hl,(__en_x)
	ld	h,0
.i_272
	ex	de,hl
	ld	l,#(4 % 256)
	call	l_asr_u
	ld	h,0
	ld	a,l
	ld	(_cx2),a
	ld	h,0
	ld	a,l
	ld	(_cx1),a
	ld	a,(__en_y)
	ld	e,a
	ld	d,0
	ld	l,#(4 % 256)
	call	l_asr_u
	ld	h,0
	ld	a,l
	ld	(_cy1),a
	ld	hl,(__en_y)
	ld	h,0
	ld	bc,15
	add	hl,bc
	ex	de,hl
	ld	l,#(4 % 256)
	call	l_asr_u
	ld	h,0
	ld	a,l
	ld	(_cy2),a
	call	_cm_two_points
	ld	hl,_at1
	ld	a,(hl)
	and	#(8 % 256)
	jp	nz,i_273
	ld	hl,_at2
	ld	a,(hl)
	and	#(8 % 256)
	jp	nz,i_273
	ld	hl,0	;const
	jr	i_274
.i_273
	ld	hl,1	;const
.i_274
	ld	h,0
	ret



._mons_col_sc_y
	ld	hl,__en_my
	call	l_gchar
	ld	de,0	;const
	ex	de,hl
	call	l_gt
	jp	nc,i_275
	ld	hl,(__en_y)
	ld	h,0
	ld	bc,15
	add	hl,bc
	jp	i_276
.i_275
	ld	hl,(__en_y)
	ld	h,0
.i_276
	ex	de,hl
	ld	l,#(4 % 256)
	call	l_asr_u
	ld	h,0
	ld	a,l
	ld	(_cy2),a
	ld	h,0
	ld	a,l
	ld	(_cy1),a
	ld	a,(__en_x)
	ld	e,a
	ld	d,0
	ld	l,#(4 % 256)
	call	l_asr_u
	ld	h,0
	ld	a,l
	ld	(_cx1),a
	ld	hl,(__en_x)
	ld	h,0
	ld	bc,15
	add	hl,bc
	ex	de,hl
	ld	l,#(4 % 256)
	call	l_asr_u
	ld	h,0
	ld	a,l
	ld	(_cx2),a
	call	_cm_two_points
	ld	hl,_at1
	ld	a,(hl)
	and	#(8 % 256)
	jp	nz,i_277
	ld	hl,_at2
	ld	a,(hl)
	and	#(8 % 256)
	jp	nz,i_277
	ld	hl,0	;const
	jr	i_278
.i_277
	ld	hl,1	;const
.i_278
	ld	h,0
	ret



._limit
	ld	hl,6	;const
	call	l_gintspsp	;
	ld	hl,6	;const
	add	hl,sp
	call	l_gint	;
	pop	de
	call	l_lt
	jp	nc,i_279
	ld	hl,4	;const
	add	hl,sp
	call	l_gint	;
	ret


.i_279
	ld	hl,6	;const
	call	l_gintspsp	;
	ld	hl,4	;const
	add	hl,sp
	call	l_gint	;
	pop	de
	call	l_gt
	jp	nc,i_280
	pop	bc
	pop	hl
	push	hl
	push	bc
	ret


.i_280
	ld	hl,6	;const
	add	hl,sp
	call	l_gint	;
	ret



._enems_kill
	ld	hl,_en_an_n_f
	push	hl
	ld	hl,(_enit)
	ld	h,0
	add	hl,hl
	pop	de
	add	hl,de
	push	hl
	ld	hl,_sprite_17_a
	pop	de
	call	l_pint
	ld	a,(_killable)
	and	a
	jp	z,i_281
	ld	de,_en_an_state
	ld	hl,(_enit)
	ld	h,0
	add	hl,de
	ld	(hl),#(4 % 256 % 256)
	ld	de,_en_an_count
	ld	hl,(_enit)
	ld	h,0
	add	hl,de
	ld	(hl),#(12 % 256 % 256)
	ld	hl,7 % 256	;const
	call	_wyz_play_sound
	ld	a,(__en_t)
	ld	e,a
	ld	d,0
	ld	hl,128	;const
	call	l_or
	ld	h,0
	ld	a,l
	ld	(__en_t),a
	ld	hl,_p_killed
	ld	a,(hl)
	inc	(hl)
	ld	l,a
	ld	h,0
.i_281
	ret



._enems_init
	ld	a,(_do_respawn)
	and	a
	jp	z,i_282
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_gpit),a
	jp	i_285
.i_283
	ld	hl,_gpit
	ld	a,(hl)
	inc	(hl)
.i_285
	ld	a,(_gpit)
	cp	#(3 % 256)
	jp	z,i_284
	jp	nc,i_284
	ld	de,_en_an_count
	ld	hl,(_gpit)
	ld	h,0
	add	hl,de
	ld	(hl),#(3 % 256 % 256)
	ld	de,_en_an_state
	ld	hl,(_gpit)
	ld	h,0
	add	hl,de
	ld	(hl),#(0 % 256 % 256)
	ld	hl,(_enoffs)
	ld	h,0
	ex	de,hl
	ld	hl,(_gpit)
	ld	h,0
	add	hl,de
	ld	h,0
	ld	a,l
	ld	(_enoffsmasi),a
	ld	hl,_baddies
	push	hl
	ld	hl,(_enoffsmasi)
	ld	h,0
	ld	b,h
	ld	c,l
	add	hl,hl
	add	hl,hl
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	ld	bc,8
	add	hl,bc
	push	hl
	ld	a,(hl)
	and	#(127 % 256)
	pop	de
	ld	(de),a
	ld	de,_en_an_state
	ld	hl,(_gpit)
	ld	h,0
	add	hl,de
	ld	(hl),#(0 % 256 % 256)
	ld	hl,_baddies
	push	hl
	ld	hl,(_enoffsmasi)
	ld	h,0
	ld	b,h
	ld	c,l
	add	hl,hl
	add	hl,hl
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	ld	bc,9
	add	hl,bc
	push	hl
	ld	hl,_level_data+6
	ld	a,(hl)
	pop	de
	ld	(de),a
	ld	hl,_baddies
	push	hl
	ld	hl,(_enoffsmasi)
	ld	h,0
	ld	b,h
	ld	c,l
	add	hl,hl
	add	hl,hl
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	ld	bc,8
	add	hl,bc
	ld	l,(hl)
	ld	h,0
	ld	a,l
	ld	(__en_t),a
	ld	e,a
	ld	d,0
	ld	l,#(3 % 256)
	call	l_asr_u
	ld	h,0
	ld	a,l
	ld	(_gpt),a
	and	a
	jp	z,i_287
	ld	a,(_gpt)
	cp	#(16 % 256)
	jp	z,i_287
	jr	c,i_288_i_287
.i_287
	jp	i_286
.i_288_i_287
	ld	de,_en_an_base_frame
	ld	hl,(_gpit)
	ld	h,0
	add	hl,de
	push	hl
	ld	a,(__en_t)
	ld	e,a
	ld	d,0
	ld	hl,3	;const
	call	l_and
	add	hl,hl
	pop	de
	ld	a,l
	ld	(de),a
	ld	hl,(_gpt)
	ld	h,0
.i_291
	ld	a,l
	cp	#(2% 256)
	jp	nz,i_293
.i_292
	ld	de,_en_an_base_frame
	ld	hl,(_gpit)
	ld	h,0
	add	hl,de
	ld	(hl),#(4 % 256 % 256)
	ld	hl,_en_an_x
	push	hl
	ld	hl,(_gpit)
	ld	h,0
	add	hl,hl
	pop	de
	add	hl,de
	push	hl
	ld	hl,_baddies
	push	hl
	ld	hl,(_enoffsmasi)
	ld	h,0
	ld	b,h
	ld	c,l
	add	hl,hl
	add	hl,hl
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	inc	hl
	inc	hl
	ld	e,(hl)
	ld	d,0
	ld	l,#(4 % 256)
	call	l_asl
	pop	de
	call	l_pint
	ld	hl,_baddies
	push	hl
	ld	hl,(_enoffsmasi)
	ld	h,0
	ld	b,h
	ld	c,l
	add	hl,hl
	add	hl,hl
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	push	hl
	ld	hl,_baddies
	push	hl
	ld	hl,(_enoffsmasi)
	ld	h,0
	ld	b,h
	ld	c,l
	add	hl,hl
	add	hl,hl
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	inc	hl
	inc	hl
	ld	a,(hl)
	pop	de
	ld	(de),a
	ld	hl,_en_an_y
	push	hl
	ld	hl,(_gpit)
	ld	h,0
	add	hl,hl
	pop	de
	add	hl,de
	push	hl
	ld	hl,_baddies
	push	hl
	ld	hl,(_enoffsmasi)
	ld	h,0
	ld	b,h
	ld	c,l
	add	hl,hl
	add	hl,hl
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	inc	hl
	inc	hl
	inc	hl
	ld	e,(hl)
	ld	d,0
	ld	l,#(4 % 256)
	call	l_asl
	pop	de
	call	l_pint
	ld	hl,_baddies
	push	hl
	ld	hl,(_enoffsmasi)
	ld	h,0
	ld	b,h
	ld	c,l
	add	hl,hl
	add	hl,hl
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	inc	hl
	push	hl
	ld	hl,_baddies
	push	hl
	ld	hl,(_enoffsmasi)
	ld	h,0
	ld	b,h
	ld	c,l
	add	hl,hl
	add	hl,hl
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	inc	hl
	inc	hl
	inc	hl
	ld	a,(hl)
	pop	de
	ld	(de),a
	ld	de,_en_an_vx
	ld	hl,(_gpit)
	ld	h,0
	add	hl,de
	push	hl
	ld	de,_en_an_vy
	ld	hl,(_gpit)
	ld	h,0
	add	hl,de
	push	hl
	ld	hl,0	;const
	ld	a,l
	call	l_sxt
	pop	de
	ld	a,l
	ld	(de),a
	ld	a,l
	call	l_sxt
	pop	de
	ld	a,l
	ld	(de),a
	ld	de,_en_an_state
	ld	hl,(_gpit)
	ld	h,0
	add	hl,de
	ld	(hl),#(0 % 256 % 256)
	ld	l,(hl)
	ld	h,0
.i_293
.i_290
.i_286
	jp	i_283
.i_284
.i_282
	ret



._enems_move_spr_abs
	ld	hl,(_enit)
	ld	h,0
	ld	de,1
	add	hl,de
	ld	h,0
	push	hl
	call	sp_Border
	pop	bc
	; enter: IX = sprite structure address
	; IY = clipping rectangle, set it to "ClipStruct" for full screen
	; BC = animate bitdef displacement (0 for no animation)
	; H = new row coord in chars
	; L = new col coord in chars
	; D = new horizontal rotation (0..7) ie horizontal pixel position
	; E = new vertical rotation (0..7) ie vertical pixel position
	ld a, (_enit)
	sla a
	ld c, a
	ld b, 0
	ld hl, _sp_moviles
	add hl, bc
	ld e, (hl)
	inc hl
	ld d, (hl)
	push de
	pop ix
	ld iy, vpClipStruct
	ld hl, _en_an_c_f
	add hl, bc
	ld e, (hl)
	inc hl
	ld d, (hl)
	ld hl, _en_an_n_f
	add hl, bc
	ld a, (hl)
	inc hl
	ld h, (hl)
	ld l, a
	or a
	sbc hl, de
	push bc
	ld b, h
	ld c, l
	ld a, (__en_y)
	srl a
	srl a
	srl a
	add 2
	ld h, a
	ld a, (__en_x)
	srl a
	srl a
	srl a
	add 1
	ld l, a
	ld a, (__en_x)
	and 7
	ld d, a
	ld a, (__en_y)
	and 7
	ld e, a
	call SPMoveSprAbs
	pop bc
	ld hl, _en_an_c_f
	add hl, bc
	ex de, hl
	ld hl, _en_an_n_f
	add hl, bc
	ldi
	ldi
	ld	hl,0 % 256	;const
	push	hl
	call	sp_Border
	pop	bc
	ret



._enems_move
	ld	hl,0	;const
	ld	a,l
	call	l_sxt
	ld	a,l
	ld	(_ptgmx),a
	ld	a,l
	call	l_sxt
	ld	a,l
	ld	(_ptgmy),a
	ld	h,0
	ld	a,l
	ld	(_p_gotten),a
	ld	a,#(0 % 256 % 256)
	ld	(_tocado),a
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_enit),a
	jp	i_296
.i_294
	ld	hl,(_enit)
	ld	h,0
	inc	hl
	ld	a,l
	ld	(_enit),a
.i_296
	ld	a,(_enit)
	cp	#(3 % 256)
	jp	z,i_295
	jp	nc,i_295
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_animate),a
	ld	h,0
	ld	a,l
	ld	(_killable),a
	ld	h,0
	ld	a,l
	ld	(_active),a
	ld	hl,(_enoffs)
	ld	h,0
	ex	de,hl
	ld	hl,(_enit)
	ld	h,0
	add	hl,de
	ld	h,0
	ld	a,l
	ld	(_enoffsmasi),a
	ld hl, (_enoffsmasi)
	ld h, 0
	add hl, hl
	ld d, h
	ld e, l
	add hl, hl
	add hl, hl
	add hl, de
	ld de, _baddies
	add hl, de
	ld (__baddies_pointer), hl
	ld a, (hl)
	ld (__en_x), a
	inc hl
	ld a, (hl)
	ld (__en_y), a
	inc hl
	ld a, (hl)
	ld (__en_x1), a
	inc hl
	ld a, (hl)
	ld (__en_y1), a
	inc hl
	ld a, (hl)
	ld (__en_x2), a
	inc hl
	ld a, (hl)
	ld (__en_y2), a
	inc hl
	ld a, (hl)
	ld (__en_mx), a
	inc hl
	ld a, (hl)
	ld (__en_my), a
	inc hl
	ld a, (hl)
	ld (__en_t), a
	inc hl
	ld a, (hl)
	ld (__en_life), a
	ld	a,(__en_t)
	and	a
	jp	nz,i_297
	ld	hl,_en_an_n_f
	push	hl
	ld	hl,(_enit)
	ld	h,0
	add	hl,hl
	pop	de
	add	hl,de
	push	hl
	ld	hl,_sprite_18_a
	pop	de
	call	l_pint
	jp	i_298
.i_297
	ld	de,_en_an_state
	ld	hl,(_enit)
	ld	h,0
	add	hl,de
	ld	a,(hl)
	cp	#(4 % 256)
	jp	nz,i_299
	ld	de,_en_an_count
	ld	hl,(_enit)
	ld	h,0
	add	hl,de
	ld	a,(hl)
	and	a
	jp	z,i_300
	ld	de,_en_an_count
	ld	hl,(_enit)
	ld	h,0
	add	hl,de
	dec	(hl)
	ld	hl,_en_an_n_f
	push	hl
	ld	hl,(_enit)
	ld	h,0
	add	hl,hl
	pop	de
	add	hl,de
	push	hl
	ld	hl,_sprite_17_a
	pop	de
	call	l_pint
	jp	i_301
.i_300
	ld	de,_en_an_state
	ld	hl,(_enit)
	ld	h,0
	add	hl,de
	ld	(hl),#(0 % 256 % 256)
	ld	hl,_en_an_n_f
	push	hl
	ld	hl,(_enit)
	ld	h,0
	add	hl,hl
	pop	de
	add	hl,de
	push	hl
	ld	hl,_sprite_18_a
	pop	de
	call	l_pint
.i_301
	jp	i_302
.i_299
	ld	hl,__en_t
	ld	a,(hl)
	and	#(4 % 256)
	jp	z,i_303
	ld	hl,1 % 256	;const
	ld	a,l
	ld	(_enemy_shoots),a
	jp	i_304
.i_303
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_enemy_shoots),a
.i_304
	ld	a,(__en_t)
	ld	e,a
	ld	d,0
	ld	l,#(3 % 256)
	call	l_asr_u
	ld	h,0
	ld	a,l
	ld	(_gpt),a
	ld	e,a
	ld	d,0
	ld	hl,8	;const
	call	l_eq
	jp	nc,i_305
	ld a, (__en_x)
	ld c, a
	ld a, (_gpx)
	add 12
	cp c
	jp c, _enems_move_pregotten_not
	ld a, (_gpx)
	ld c, a
	ld a, (__en_x)
	add 12
	cp c
	jp c, _enems_move_pregotten_not
	ld a, 1
	jr _enems_move_pregotten_set
	._enems_move_pregotten_not
	xor a
	._enems_move_pregotten_set
	ld (_pregotten), a
.i_305
	ld	hl,(_gpt)
	ld	h,0
.i_308
	ld	a,l
	cp	#(1% 256)
	jp	z,i_309
	cp	#(8% 256)
	jp	z,i_310
	cp	#(2% 256)
	jp	z,i_314
	jp	i_328
.i_309
	ld	hl,1 % 256	;const
	ld	a,l
	ld	(_killable),a
.i_310
	ld a, 1
	ld (_active), a
	ld (_animate), a
	ld a, (__en_mx)
	ld c, a
	ld a, (__en_x)
	add a, c
	ld (__en_x), a
	ld c, a
	ld a, (__en_x1)
	cp c
	jr z, _enems_lm_change_axis_x
	ld a, (__en_x2)
	cp c
	jr z, _enems_lm_change_axis_x
	call _mons_col_sc_x
	xor a
	or l
	jr z, _enems_lm_change_axis_x_done
	._enems_lm_change_axis_x
	ld a, (__en_mx)
	neg
	ld (__en_mx), a
	._enems_lm_change_axis_x_done
	ld a, (__en_my)
	ld c, a
	ld a, (__en_y)
	add a, c
	ld (__en_y), a
	ld c, a
	ld a, (__en_y1)
	cp c
	jr z, _enems_lm_change_axis_y
	ld a, (__en_y2)
	cp c
	jr z, _enems_lm_change_axis_y
	call _mons_col_sc_y
	xor a
	or l
	jr z, _enems_lm_change_axis_y_done
	._enems_lm_change_axis_y
	ld a, (__en_my)
	neg
	ld (__en_my), a
	._enems_lm_change_axis_y_done
	ld	hl,(_enemy_shoots)
	ld	h,0
	ld	a,h
	or	l
	jp	z,i_312
	call	_rand
	ld	de,63	;const
	ex	de,hl
	call	l_and
	dec	hl
	ld	a,h	
	or	l
	jp	nz,i_312
	inc	hl
	jr	i_313
.i_312
	ld	hl,0	;const
.i_313
	ld	a,h
	or	l
	call	nz,_shoot_coco
.i_311
	jp	i_307
.i_314
	ld	hl,1 % 256	;const
	ld	a,l
	ld	(_animate),a
	ld	h,0
	ld	a,l
	ld	(_killable),a
	ld	h,0
	ld	a,l
	ld	(_active),a
	ld	de,_en_an_state
	ld	hl,(_enit)
	ld	h,0
	add	hl,de
	ld	l,(hl)
	ld	h,0
.i_317
	ld	a,l
	cp	#(0% 256)
	jp	z,i_318
	cp	#(1% 256)
	jp	z,i_320
	cp	#(2% 256)
	jp	z,i_323
	jp	i_316
.i_318
	ld	hl,(_gpx)
	ld	h,0
	push	hl
	ld	hl,(_gpy)
	ld	h,0
	push	hl
	ld	hl,(__en_x)
	ld	h,0
	push	hl
	ld	hl,(__en_y)
	ld	h,0
	push	hl
	call	_distance
	pop	bc
	pop	bc
	pop	bc
	pop	bc
	ld	de,96	;const
	ex	de,hl
	call	l_le
	jp	nc,i_319
	ld	de,_en_an_state
	ld	hl,(_enit)
	ld	h,0
	add	hl,de
	ld	(hl),#(1 % 256 % 256)
	ld	l,(hl)
	ld	h,0
.i_319
	jp	i_316
.i_320
	ld	hl,(_gpx)
	ld	h,0
	push	hl
	ld	hl,(_gpy)
	ld	h,0
	push	hl
	ld	hl,(__en_x)
	ld	h,0
	push	hl
	ld	hl,(__en_y)
	ld	h,0
	push	hl
	call	_distance
	pop	bc
	pop	bc
	pop	bc
	pop	bc
	ld	de,96	;const
	ex	de,hl
	call	l_gt
	jp	nc,i_321
	ld	de,_en_an_state
	ld	hl,(_enit)
	ld	h,0
	add	hl,de
	ld	(hl),#(2 % 256 % 256)
	ld	l,(hl)
	ld	h,0
	jp	i_322
.i_321
	ld	de,_en_an_vx
	ld	hl,(_enit)
	ld	h,0
	add	hl,de
	push	hl
	ld	de,_en_an_vx
	ld	hl,(_enit)
	ld	h,0
	add	hl,de
	call	l_gchar
	push	hl
	ld	hl,(_p_x)
	push	hl
	ld	hl,_en_an_x
	push	hl
	ld	hl,(_enit)
	ld	h,0
	add	hl,hl
	pop	de
	add	hl,de
	call	l_gint	;
	pop	de
	ex	de,hl
	and	a
	sbc	hl,de
	push	hl
	ld	hl,4	;const
	push	hl
	call	_addsign
	pop	bc
	pop	bc
	pop	de
	add	hl,de
	push	hl
	ld	hl,65472	;const
	push	hl
	ld	hl,64	;const
	push	hl
	call	_limit
	pop	bc
	pop	bc
	pop	bc
	ld	a,l
	call	l_sxt
	pop	de
	ld	a,l
	ld	(de),a
	ld	de,_en_an_vy
	ld	hl,(_enit)
	ld	h,0
	add	hl,de
	push	hl
	ld	de,_en_an_vy
	ld	hl,(_enit)
	ld	h,0
	add	hl,de
	call	l_gchar
	push	hl
	ld	hl,(_p_y)
	push	hl
	ld	hl,_en_an_y
	push	hl
	ld	hl,(_enit)
	ld	h,0
	add	hl,hl
	pop	de
	add	hl,de
	call	l_gint	;
	pop	de
	ex	de,hl
	and	a
	sbc	hl,de
	push	hl
	ld	hl,4	;const
	push	hl
	call	_addsign
	pop	bc
	pop	bc
	pop	de
	add	hl,de
	push	hl
	ld	hl,65472	;const
	push	hl
	ld	hl,64	;const
	push	hl
	call	_limit
	pop	bc
	pop	bc
	pop	bc
	ld	a,l
	call	l_sxt
	pop	de
	ld	a,l
	ld	(de),a
	ld	hl,_en_an_x
	push	hl
	ld	hl,(_enit)
	ld	h,0
	add	hl,hl
	pop	de
	add	hl,de
	push	hl
	ld	hl,_en_an_x
	push	hl
	ld	hl,(_enit)
	ld	h,0
	add	hl,hl
	pop	de
	add	hl,de
	ld	e,(hl)
	inc	hl
	ld	d,(hl)
	push	de
	ld	de,_en_an_vx
	ld	hl,(_enit)
	ld	h,0
	add	hl,de
	call	l_gchar
	pop	de
	add	hl,de
	push	hl
	ld	hl,0	;const
	push	hl
	ld	hl,3584	;const
	push	hl
	call	_limit
	pop	bc
	pop	bc
	pop	bc
	pop	de
	call	l_pint
	ld	hl,_en_an_y
	push	hl
	ld	hl,(_enit)
	ld	h,0
	add	hl,hl
	pop	de
	add	hl,de
	push	hl
	ld	hl,_en_an_y
	push	hl
	ld	hl,(_enit)
	ld	h,0
	add	hl,hl
	pop	de
	add	hl,de
	ld	e,(hl)
	inc	hl
	ld	d,(hl)
	push	de
	ld	de,_en_an_vy
	ld	hl,(_enit)
	ld	h,0
	add	hl,de
	call	l_gchar
	pop	de
	add	hl,de
	push	hl
	ld	hl,0	;const
	push	hl
	ld	hl,2304	;const
	push	hl
	call	_limit
	pop	bc
	pop	bc
	pop	bc
	pop	de
	call	l_pint
.i_322
	jp	i_316
.i_323
	ld	hl,_en_an_x
	push	hl
	ld	hl,(_enit)
	ld	h,0
	add	hl,hl
	pop	de
	add	hl,de
	push	hl
	ld	e,(hl)
	inc	hl
	ld	d,(hl)
	push	de
	ld	hl,(__en_x1)
	ld	h,0
	ex	de,hl
	ld	hl,(__en_x)
	ld	h,0
	ex	de,hl
	and	a
	sbc	hl,de
	push	hl
	ld	hl,16	;const
	push	hl
	call	_addsign
	pop	bc
	pop	bc
	pop	de
	add	hl,de
	pop	de
	call	l_pint
	ld	hl,_en_an_y
	push	hl
	ld	hl,(_enit)
	ld	h,0
	add	hl,hl
	pop	de
	add	hl,de
	push	hl
	ld	e,(hl)
	inc	hl
	ld	d,(hl)
	push	de
	ld	hl,(__en_y1)
	ld	h,0
	ex	de,hl
	ld	hl,(__en_y)
	ld	h,0
	ex	de,hl
	and	a
	sbc	hl,de
	push	hl
	ld	hl,16	;const
	push	hl
	call	_addsign
	pop	bc
	pop	bc
	pop	de
	add	hl,de
	pop	de
	call	l_pint
	ld	hl,(_gpx)
	ld	h,0
	push	hl
	ld	hl,(_gpy)
	ld	h,0
	push	hl
	ld	hl,(__en_x)
	ld	h,0
	push	hl
	ld	hl,(__en_y)
	ld	h,0
	push	hl
	call	_distance
	pop	bc
	pop	bc
	pop	bc
	pop	bc
	ld	de,96	;const
	ex	de,hl
	call	l_le
	jp	nc,i_324
	ld	de,_en_an_state
	ld	hl,(_enit)
	ld	h,0
	add	hl,de
	ld	(hl),#(1 % 256 % 256)
	ld	l,(hl)
	ld	h,0
.i_324
.i_316
	ld	hl,_en_an_x
	push	hl
	ld	hl,(_enit)
	ld	h,0
	add	hl,hl
	pop	de
	add	hl,de
	ld	e,(hl)
	inc	hl
	ld	d,(hl)
	ld	l,#(4 % 256)
	call	l_asr
	ld	h,0
	ld	a,l
	ld	(__en_x),a
	ld	hl,_en_an_y
	push	hl
	ld	hl,(_enit)
	ld	h,0
	add	hl,hl
	pop	de
	add	hl,de
	ld	e,(hl)
	inc	hl
	ld	d,(hl)
	ld	l,#(4 % 256)
	call	l_asr
	ld	h,0
	ld	a,l
	ld	(__en_y),a
	ld	de,_en_an_state
	ld	hl,(_enit)
	ld	h,0
	add	hl,de
	ld	a,(hl)
	cp	#(2 % 256)
	jp	nz,i_326
	ld	hl,(__en_x)
	ld	h,0
	ex	de,hl
	ld	hl,(__en_x1)
	ld	h,0
	call	l_eq
	jp	nc,i_326
	ld	hl,(__en_y)
	ld	h,0
	ex	de,hl
	ld	hl,(__en_y1)
	ld	h,0
	call	l_eq
	jr	c,i_327_i_326
.i_326
	jp	i_325
.i_327_i_326
	ld	de,_en_an_state
	ld	hl,(_enit)
	ld	h,0
	add	hl,de
	ld	(hl),#(0 % 256 % 256)
	ld	l,(hl)
	ld	h,0
.i_325
	jp	i_307
.i_328
	ld	hl,_en_an_n_f
	push	hl
	ld	hl,(_enit)
	ld	h,0
	add	hl,hl
	pop	de
	add	hl,de
	push	hl
	ld	hl,_sprite_18_a
	pop	de
	call	l_pint
.i_307
	ld	a,(_active)
	and	a
	jp	z,i_329
	ld	a,(_animate)
	and	a
	jp	z,i_330
	ld	a,(_gpt)
	cp	#(2 % 256)
	jp	nz,i_331
	ld	hl,(_gpx)
	ld	h,0
	ex	de,hl
	ld	hl,(__en_x)
	ld	h,0
	call	l_ugt
	ld	hl,0	;const
	rl	l
	ld	h,0
	ld	a,l
	ld	(_gpjt),a
	jp	i_332
.i_331
	ld	hl,__en_mx
	call	l_gchar
	ld	a,h
	or	l
	jp	z,i_333
	ld	hl,(__en_x)
	ld	h,0
	ld	bc,4
	add	hl,bc
	ex	de,hl
	ld	l,#(3 % 256)
	call	l_asr_u
	ld	de,1	;const
	ex	de,hl
	call	l_and
	jp	i_334
.i_333
	ld	hl,(__en_y)
	ld	h,0
	ld	bc,4
	add	hl,bc
	ex	de,hl
	ld	l,#(3 % 256)
	call	l_asr_u
	ld	de,1	;const
	ex	de,hl
	call	l_and
.i_334
	ld	h,0
	ld	a,l
	ld	(_gpjt),a
.i_332
	ld	hl,_en_an_n_f
	push	hl
	ld	hl,(_enit)
	ld	h,0
	add	hl,hl
	pop	de
	add	hl,de
	push	hl
	ld	hl,_enem_frames
	push	hl
	ld	de,_en_an_base_frame
	ld	hl,(_enit)
	ld	h,0
	add	hl,de
	ld	e,(hl)
	ld	d,0
	ld	hl,(_gpjt)
	ld	h,0
	add	hl,de
	add	hl,hl
	pop	de
	add	hl,de
	call	l_gint	;
	pop	de
	call	l_pint
.i_330
	ld	a,(_hitter_on)
	and	a
	jp	z,i_336
	ld	a,(_killable)
	and	a
	jp	z,i_336
	ld	a,(_hitter_hit)
	cp	#(0 % 256)
	jr	z,i_337_i_336
.i_336
	jp	i_335
.i_337_i_336
	ld	hl,(_hitter_x)
	ld	h,0
	push	hl
	ld	a,(_p_facing)
	and	a
	jp	z,i_338
	ld	hl,6	;const
	jp	i_339
.i_338
	ld	hl,1	;const
.i_339
	pop	de
	add	hl,de
	ld	h,0
	ld	a,l
	ld	(_cx1),a
	ld	hl,(_hitter_y)
	ld	h,0
	inc	hl
	inc	hl
	inc	hl
	ld	h,0
	ld	a,l
	ld	(_cy1),a
	ld	hl,(__en_x)
	ld	h,0
	ld	a,l
	ld	(_cx2),a
	ld	hl,(__en_y)
	ld	h,0
	ld	a,l
	ld	(_cy2),a
	ld	a,(_hitter_frame)
	ld	e,a
	ld	d,0
	ld	hl,3	;const
	call	l_ule
	jp	nc,i_341
	call	_collide_pixel
	ld	a,h
	or	l
	jr	nz,i_342_i_341
.i_341
	jp	i_340
.i_342_i_341
	ld	a,#(1 % 256 % 256)
	ld	(_hitter_hit),a
	ld	hl,1 % 256	;const
	push	hl
	call	_enems_kill
	pop	bc
	jp	i_343
.i_340
.i_335
	ld a, (_gpt)
	cp 8
	jp nz, _enems_platforms_done
	ld a, (_p_jmp_on)
	or a
	jp nz, _enems_collision_skip
	ld a, (_pregotten)
	or a
	jp z, _enems_collision_skip
	ld a, (_p_gotten)
	or a
	jp nz, _enems_collision_skip
	ld a, (__en_mx)
	or a
	jr z, _enems_plats_horz_done
	ld a, (__en_y)
	ld c, a
	ld a, (_gpy)
	add 16
	cp c
	jr c, _enems_plats_horz_done
	ld a, (_gpy)
	add 10
	ld c, a
	ld a, (__en_y)
	cp c
	jr c, _enems_plats_horz_done
	._enems_plats_horz_do
	ld a, 1
	ld (_p_gotten), a
	ld a, (__en_mx)
	sla a
	sla a
	sla a
	sla a ; times 4
	ld (_ptgmx), a
	jr _enems_plats_gpy_set
	._enems_plats_horz_done
	._enems_plats_vert_check_1
	ld a, (_gpy)
	add 10
	ld c, a
	ld a, (__en_y)
	cp c
	jr c, _enems_plats_vert_done
	ld a, (__en_my)
	bit 7, a
	jr z, _enems_plats_vert_check_2 ; _en_my is positive
	ld a, (__en_y)
	ld c, a
	ld a, (_gpy)
	add 17
	cp c
	jr nc, _enems_plats_vert_do
	._enems_plats_vert_check_2
	ld a, (__en_y)
	ld c, a
	ld a, (__en_my)
	ld b, a
	ld a, (_gpy)
	add 17
	add b
	cp c
	jr c, _enems_plats_vert_done
	._enems_plats_vert_do
	ld a, 1
	ld (_p_gotten), a
	ld a, (__en_my)
	sla a
	sla a
	sla a
	sla a ; times 4
	ld (_ptgmy), a
	xor a
	ld (_p_vy), a
	._enems_plats_gpy_set
	ld a, (__en_y)
	sub 16
	ld (_gpy), a
	ld d, 0
	ld e, a
	ld l, 4
	call l_asl
	ld (_p_y), hl
	._enems_plats_vert_done
	jp _enems_collision_skip
	._enems_platforms_done
	ld a, (_tocado)
	or a
	jr nz, _enems_collision_skip
	ld a, (_p_state)
	or a
	jr nz, _enems_collision_skip
	ld a, (__en_x)
	ld c, a
	ld a, (_gpx)
	add 8
	cp c
	jr c, _enems_collision_skip
	ld a, (_gpx)
	ld c, a
	ld a, (__en_x)
	add 8
	cp c
	jr c, _enems_collision_skip
	ld a, (__en_y)
	ld c, a
	ld a, (_gpy)
	add 8
	cp c
	jr c, _enems_collision_skip
	ld a, (_gpy)
	ld c, a
	ld a, (__en_y)
	add 8
	cp c
	jr c, _enems_collision_skip
	ld	a,(_p_life)
	and	a
	jp	z,i_344
	ld	hl,1 % 256	;const
	ld	a,l
	ld	(_tocado),a
.i_344
	ld	a,#(6 % 256 % 256)
	ld	(_p_killme),a
	ld	a,(_gpt)
	cp	#(2 % 256)
	jp	nz,i_345
	ld	hl,1 % 256	;const
	push	hl
	call	_enems_kill
	pop	bc
.i_345
	._enems_collision_skip
.i_329
.i_302
.i_298
.i_343
.i_346
	.enems_loop_continue_a
	call	_enems_move_spr_abs
	ld hl, (__baddies_pointer)
	ld a, (__en_x)
	ld (hl), a
	inc hl
	ld a, (__en_y)
	ld (hl), a
	inc hl
	ld a, (__en_x1)
	ld (hl), a
	inc hl
	ld a, (__en_y1)
	ld (hl), a
	inc hl
	ld a, (__en_x2)
	ld (hl), a
	inc hl
	ld a, (__en_y2)
	ld (hl), a
	inc hl
	ld a, (__en_mx)
	ld (hl), a
	inc hl
	ld a, (__en_my)
	ld (hl), a
	inc hl
	ld a, (__en_t)
	ld (hl), a
	inc hl
	ld a, (__en_life)
	ld (hl), a
	jp	i_294
.i_295
	ret



._advance_worm
	call _rand
	ld a, l
	and 15
	ld (_gpjt), a
	ld bc, (_gpit)
	ld b, 0
	ld de, (_gpt)
	ld d, 0
	ld hl, _behs
	add hl, de
	ld a, (hl)
	ld hl, _map_attr
	add hl, bc
	ld (hl), a
	ld a, (_gpd)
	ld d, a
	or a
	jr nz, _draw_scr_alt_tile_skip
	ld a, (_gpjt)
	cp 1
	jr nz, _draw_scr_alt_tile_skip
	ld a, 19
	jr _draw_scr_alt_tile_done
	._draw_scr_alt_tile_skip
	ld a, d
	._draw_scr_alt_tile_done
	ld hl, _map_buff
	add hl, bc
	ld (hl), a
	ld (__t), a
	call _draw_coloured_tile
	ld a, (__x)
	add 2
	cp 30 + 1
	jr c, _advance_worm_no_inc_y
	ld a, (__y)
	add 2
	ld (__y), a
	ld a, 1
	._advance_worm_no_inc_y
	ld (__x), a
	ld hl, _gpit
	inc (hl)
	ret



._draw_scr_background
	ld	de,_seed1
	ld	hl,(_n_pant)
	ld	h,0
	call	l_pint
	ld	de,_seed2
	ld	hl,(_level)
	ld	h,0
	call	l_pint
	call	_srand
	ld	hl,_map
	push	hl
	ld	a,(_n_pant)
	ld	e,a
	ld	d,0
	ld	l,#(6 % 256)
	call	l_asl
	pop	de
	add	hl,de
	push	hl
	ld	a,(_n_pant)
	ld	e,a
	ld	d,0
	ld	l,#(3 % 256)
	call	l_asl
	pop	de
	add	hl,de
	push	hl
	ld	a,(_n_pant)
	ld	e,a
	ld	d,0
	ld	l,#(1 % 256)
	call	l_asl
	pop	de
	add	hl,de
	ex	de,hl
	ld	hl,(_n_pant)
	ld	h,0
	add	hl,de
	ld	(_map_pointer),hl
	._draw_scr_packed_unpacked
	ld a, 1
	ld (__x), a
	ld a, 2
	ld (__y), a
	xor a
	ld (_gpit), a
	._draw_scr_background_loop
	and 1
	jr z, draw_scr_background_new_byte
	ld a, (_gpc)
	and 15
	jr draw_scr_background_set_t
	.draw_scr_background_new_byte
	ld hl, (_map_pointer)
	ld a, (hl)
	inc hl
	ld (_map_pointer), hl
	ld (_gpc), a
	srl a
	srl a
	srl a
	srl a
	.draw_scr_background_set_t
	ld (_gpt), a
	ld (_gpd), a
	call _advance_worm
	ld a, (_gpit)
	cp 150
	jr nz, _draw_scr_background_loop
	ld a, 240
	ld (_hotspot_y), a
	ld a, (_n_pant)
	ld b, a
	sla a
	add b
	ld c, a
	ld b, 0
	ld hl, _hotspots
	add hl, bc
	ld a, (hl)
	ld b, a
	srl a
	srl a
	srl a
	srl a
	ld (__x), a
	ld a, b
	and 15
	ld (__y), a
	inc hl
	ld b, (hl)
	inc hl
	ld c, (hl)
	ld a, b
	and c
	jr z, _hotspots_setup_done
	._hotspots_setup_do
	ld a, (__x)
	ld e, a
	sla a
	sla a
	sla a
	sla a
	ld (_hotspot_x), a
	ld a, (__y)
	ld d, a
	sla a
	sla a
	sla a
	sla a
	ld (_hotspot_y), a
	sub d
	add e
	ld e, a
	ld d, 0
	ld hl, _map_buff
	add hl, de
	ld a, (hl)
	ld (_orig_tile), a
	ld a, b
	cp 3
	jp nz, _hotspots_setup_set
	._hotspots_setup_set_refill
	xor a
	._hotspots_setup_set
	add 16
	ld (__t), a
	call _draw_coloured_tile_gamearea
	._hotspots_setup_done
	ret



._draw_scr
	ld	a,#(1 % 256 % 256)
	ld	(_is_rendering),a
	ld	a,(_no_draw)
	and	a
	jp	z,i_347
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_no_draw),a
	jp	i_348
.i_347
	call	_draw_scr_background
.i_348
	ld	a,#(0 % 256 % 256)
	ld	(_f_zone_ac),a
	ld	hl,(_n_pant)
	ld	h,0
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	ld	h,0
	ld	a,l
	ld	(_enoffs),a
	call	_enems_init
	ld	hl,1 % 256	;const
	ld	a,l
	ld	(_do_respawn),a
	call	_run_entering_script
	call	_init_cocos
	ld	hl,(_n_pant)
	ld	h,0
	ex	de,hl
	ld	hl,(_level_data)
	ld	h,0
	call	l_div_u
	ex	de,hl
	ld	h,0
	ld	a,l
	ld	(_x_pant),a
	ld	hl,(_n_pant)
	ld	h,0
	ex	de,hl
	ld	hl,(_level_data)
	ld	h,0
	call	l_div_u
	ld	h,0
	ld	a,l
	ld	(_y_pant),a
	ld	a,(_p_engine)
	cp	#(1 % 256)
	jp	nz,i_349
	ld	hl,(_n_pant)
	ld	h,0
	ld	a,l
	ld	(_p_safe_pant),a
	ld	a,(_gpx)
	ld	e,a
	ld	d,0
	ld	l,#(4 % 256)
	call	l_asr_u
	ld	h,0
	ld	a,l
	ld	(_p_safe_x),a
	ld	a,(_gpy)
	ld	e,a
	ld	d,0
	ld	l,#(4 % 256)
	call	l_asr_u
	ld	h,0
	ld	a,l
	ld	(_p_safe_y),a
.i_349
	call	_invalidate_viewport
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_is_rendering),a
	ret



._update_hud
	ld	hl,(_p_objs)
	ld	h,0
	ex	de,hl
	ld	hl,(_objs_old)
	ld	h,0
	call	l_ne
	jp	nc,i_350
	call	_draw_objs
	ld	hl,(_p_objs)
	ld	h,0
	ld	a,l
	ld	(_objs_old),a
.i_350
	ld	hl,(_p_life)
	ld	h,0
	ex	de,hl
	ld	hl,(_life_old)
	ld	h,0
	call	l_ne
	jp	nc,i_351
	ld	a,#(3 % 256 % 256)
	ld	(__x),a
	ld	a,#(0 % 256 % 256)
	ld	(__y),a
	ld	hl,(_p_life)
	ld	h,0
	ld	a,l
	ld	(__t),a
	call	_print_number2
	ld	hl,(_p_life)
	ld	h,0
	ld	a,l
	ld	(_life_old),a
.i_351
	ld	hl,(_flags+1)
	ld	h,0
	ex	de,hl
	ld	hl,(_flag_old)
	ld	h,0
	call	l_ne
	jp	nc,i_352
	ld	a,#(29 % 256 % 256)
	ld	(__x),a
	ld	a,#(0 % 256 % 256)
	ld	(__y),a
	ld	hl,(_flags+1)
	ld	h,0
	ld	a,l
	ld	(__t),a
	call	_print_number2
	ld	hl,(_flags+1)
	ld	h,0
	ld	a,l
	ld	(_flag_old),a
.i_352
	ret



._init_lava
	ld	hl,(_level_data+1)
	ld	h,0
	ld	de,20
	call	l_mult
	ld	h,0
	ld	a,l
	ld	(_lava_y),a
	ld	a,#(0 % 256 % 256)
	ld	(_lava_ct),a
	ld	hl,_flags+30
	ld	(hl),#(0 % 256 % 256)
	ld	l,(hl)
	ld	h,0
	ret



._lava_reenter
	ld	a,(_lava_y)
	ld	e,a
	ld	d,0
	ld	hl,20	;const
	call	l_div_u
	ex	de,hl
	ld	hl,(_n_pant)
	ld	h,0
	call	l_eq
	jp	nc,i_353
	ld	a,(_lava_y)
	ld	e,a
	ld	d,0
	ld	hl,20	;const
	call	l_div_u
	ex	de,hl
	ld	de,2
	add	hl,de
	ld	h,0
	ld	a,l
	ld	(_gpd),a
	ld	hl,20 % 256	;const
	ld	a,l
	ld	(_gpjt),a
	jp	i_356
.i_354
	ld	hl,_gpjt
	ld	a,(hl)
	dec	(hl)
.i_356
	ld	hl,(_gpjt)
	ld	h,0
	ex	de,hl
	ld	hl,(_gpd)
	ld	h,0
	call	l_uge
	jp	nc,i_355
	ld	hl,3 % 256	;const
	ld	a,l
	ld	(_gpit),a
	jp	i_359
.i_357
	ld	hl,(_gpit)
	ld	h,0
	inc	hl
	inc	hl
	ld	h,0
	ld	a,l
	ld	(_gpit),a
.i_359
	ld	a,(_gpit)
	cp	#(29 % 256)
	jp	z,i_358
	jp	nc,i_358
	ld	hl,(_gpit)
	ld	h,0
	ld	a,l
	ld	(__x),a
	ld	hl,(_gpjt)
	ld	h,0
	ld	a,l
	ld	(__y),a
	ld	hl,18 % 256	;const
	ld	a,l
	ld	(__t),a
	call	_draw_coloured_tile
	call	_invalidate_tile
	jp	i_357
.i_358
	jp	i_354
.i_355
.i_353
	ret



._do_lava
	ld	a,(_lava_y)
	ld	e,a
	ld	d,0
	ld	hl,20	;const
	call	l_div_u
	ex	de,hl
	ld	h,0
	ld	a,l
	ld	(_gpd),a
	ld	a,(_lava_y)
	ld	e,a
	ld	d,0
	ld	hl,20	;const
	call	l_div_u
	ex	de,hl
	ld	hl,(_n_pant)
	ld	h,0
	call	l_eq
	ld	hl,0	;const
	rl	l
	ld	h,0
	ld	a,l
	ld	(_gpjt),a
	ld	hl,_lava_ct
	ld	a,(hl)
	inc	(hl)
	ld	l,a
	ld	h,0
	ld	de,7
	call	l_eq
	jp	nc,i_360
	ld	hl,_lava_y
	ld	a,(hl)
	dec	(hl)
	ld	a,#(0 % 256 % 256)
	ld	(_lava_ct),a
	ld	a,(_gpjt)
	and	a
	jp	z,i_361
	ld	hl,9 % 256	;const
	call	_wyz_play_sound
	ld	a,(_gpd)
	cp	#(19 % 256)
	jp	z,i_362
	jp	nc,i_362
	ld	hl,3 % 256	;const
	ld	a,l
	ld	(_gpit),a
	jp	i_365
.i_363
	ld	hl,(_gpit)
	ld	h,0
	inc	hl
	inc	hl
	ld	h,0
	ld	a,l
	ld	(_gpit),a
.i_365
	ld	a,(_gpit)
	cp	#(29 % 256)
	jp	z,i_364
	jp	nc,i_364
	ld	hl,(_gpit)
	ld	h,0
	ld	a,l
	ld	(__x),a
	ld	hl,(_gpd)
	ld	h,0
	ld	de,2
	add	hl,de
	ld	h,0
	ld	a,l
	ld	(__y),a
	ld	hl,18 % 256	;const
	ld	a,l
	ld	(__t),a
	call	_draw_coloured_tile
	call	_invalidate_tile
	jp	i_363
.i_364
.i_362
.i_361
.i_360
	ld	a,(_gpjt)
	and	a
	jp	z,i_367
	ld	a,(_gpy)
	ld	e,a
	ld	d,0
	ld	l,#(3 % 256)
	call	l_asr_u
	push	hl
	ld	hl,(_gpd)
	ld	h,0
	dec	hl
	pop	de
	call	l_uge
	jr	c,i_368_i_367
.i_367
	jp	i_366
.i_368_i_367
	ld	hl,1 % 256	;const
	ret


.i_366
	ld	hl,0 % 256	;const
	ret


.i_369
	ret



._flick_screen
	ld	hl,(_p_x)
	ld	de,0	;const
	call	l_eq
	jp	nc,i_371
	ld	hl,_p_vx
	call	l_gchar
	ld	de,0	;const
	ex	de,hl
	call	l_lt
	jp	nc,i_371
	ld	a,(_x_pant)
	cp	#(0 % 256)
	jp	z,i_371
	jp	c,i_371
	jr	i_372_i_371
.i_371
	jp	i_370
.i_372_i_371
	ld	hl,(_n_pant)
	ld	h,0
	dec	hl
	ld	h,0
	ld	a,l
	ld	(_n_pant),a
	ld	hl,3584	;const
	ld	(_p_x),hl
	ld	hl,224 % 256	;const
	ld	a,l
	ld	(_gpx),a
	jp	i_373
.i_370
	ld	hl,(_p_x)
	ld	de,3584	;const
	call	l_eq
	jp	nc,i_375
	ld	hl,_p_vx
	call	l_gchar
	ld	de,0	;const
	ex	de,hl
	call	l_gt
	jp	nc,i_375
	ld	hl,(_x_pant)
	ld	h,0
	push	hl
	ld	hl,(_level_data)
	ld	h,0
	dec	hl
	pop	de
	call	l_ult
	jr	c,i_376_i_375
.i_375
	jp	i_374
.i_376_i_375
	ld	hl,(_n_pant)
	ld	h,0
	inc	hl
	ld	h,0
	ld	a,l
	ld	(_n_pant),a
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_gpx),a
	ld	(_p_x),hl
.i_374
.i_373
	ld	hl,(_p_y)
	ld	de,0	;const
	call	l_eq
	jp	nc,i_378
	ld	hl,_p_vy
	call	l_gchar
	ld	de,0	;const
	ex	de,hl
	call	l_lt
	jp	nc,i_378
	ld	a,(_y_pant)
	cp	#(0 % 256)
	jp	z,i_378
	jp	c,i_378
	jr	i_379_i_378
.i_378
	jp	i_377
.i_379_i_378
	ld	hl,(_n_pant)
	ld	h,0
	ex	de,hl
	ld	hl,(_level_data)
	ld	h,0
	ex	de,hl
	and	a
	sbc	hl,de
	ld	h,0
	ld	a,l
	ld	(_n_pant),a
	ld	hl,2304	;const
	ld	(_p_y),hl
	ld	a,#(144 % 256 % 256)
	ld	(_gpy),a
	ld	hl,_p_vy
	call	l_gchar
	ld	de,65458	;const
	ex	de,hl
	call	l_gt
	jp	nc,i_380
	ld	hl,65458	;const
	ld	a,l
	call	l_sxt
	ld	a,l
	ld	(_p_vy),a
.i_380
	jp	i_381
.i_377
	ld	hl,(_p_y)
	ld	de,2304	;const
	call	l_eq
	jp	nc,i_383
	ld	hl,_p_vy
	call	l_gchar
	ld	de,0	;const
	ex	de,hl
	call	l_gt
	jp	nc,i_383
	ld	hl,(_y_pant)
	ld	h,0
	push	hl
	ld	hl,(_level_data+1)
	ld	h,0
	dec	hl
	pop	de
	call	l_ult
	jr	c,i_384_i_383
.i_383
	jp	i_382
.i_384_i_383
	ld	hl,(_n_pant)
	ld	h,0
	ex	de,hl
	ld	hl,(_level_data)
	ld	h,0
	add	hl,de
	ld	h,0
	ld	a,l
	ld	(_n_pant),a
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_gpy),a
	ld	(_p_y),hl
.i_382
.i_381
	ret



._hide_sprites
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	a,h
	or	l
	jp	nz,i_385
	ld ix, (_sp_player)
	ld iy, vpClipStruct
	ld bc, 0
	ld hl, 0xdede
	ld de, 0
	call SPMoveSprAbs
.i_385
	xor a
	.hide_sprites_enems_loop
	ld (_gpit), a
	sla a
	ld c, a
	ld b, 0
	ld hl, _sp_moviles
	add hl, bc
	ld e, (hl)
	inc hl
	ld d, (hl)
	push de
	pop ix
	ld iy, vpClipStruct
	ld bc, 0
	ld hl, 0xfefe
	ld de, 0
	call SPMoveSprAbs
	ld a, (_gpit)
	inc a
	cp 3
	jr nz, hide_sprites_enems_loop
	xor a
	.hide_sprites_cocos_loop
	ld (_gpit), a
	sla a
	ld c, a
	ld b, 0
	ld hl, _sp_cocos
	add hl, bc
	ld e, (hl)
	inc hl
	ld d, (hl)
	push de
	pop ix
	ld iy, vpClipStruct
	ld bc, 0
	ld hl, 0xfefe
	ld de, 0
	call SPMoveSprAbs
	ld a, (_gpit)
	inc a
	cp 3
	jr nz, hide_sprites_cocos_loop
	ld ix, (_sp_hitter)
	ld iy, vpClipStruct
	ld bc, 0
	ld hl, 0xfefe
	ld de, 0
	call SPMoveSprAbs
	ret



._main
	di
	ld	hl,61937	;const
	push	hl
	call	sp_InitIM2
	pop	bc
	ld	hl,61937	;const
	push	hl
	call	sp_CreateGenericISR
	pop	bc
	ld	hl,255 % 256	;const
	push	hl
	ld	hl,_ISR
	push	hl
	call	sp_RegisterHook
	pop	bc
	pop	bc
	ld	hl,0 % 256	;const
	push	hl
	push	hl
	call	sp_Initialize
	pop	bc
	pop	bc
	ld	hl,0 % 256	;const
	push	hl
	call	sp_Border
	pop	bc
	ld	hl,0 % 256	;const
	push	hl
	ld	hl,60 % 256	;const
	push	hl
	ld	hl,14	;const
	push	hl
	ld	hl,_AD_FREE
	push	hl
	call	sp_AddMemory
	pop	bc
	pop	bc
	pop	bc
	pop	bc
	ld	hl,sp_JoyKeyboard
	ld	(_joyfunc),hl
	ld	hl,_tileset
	ld	(_gen_pt),hl
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_gpit),a
.i_388
	ld	hl,(_gpit)
	ld	h,0
	push	hl
	ld	hl,(_gen_pt)
	push	hl
	call	sp_TileArray
	pop	bc
	pop	bc
	ld	hl,(_gen_pt)
	ld	bc,8
	add	hl,bc
	ld	(_gen_pt),hl
	ld	hl,_gpit
	ld	a,(hl)
	inc	(hl)
.i_386
	ld	hl,(_gpit)
	ld	h,0
	ld	a,h
	or	l
	jp	nz,i_388
.i_387
	ld	hl,0 % 256	;const
	push	hl
	ld	hl,3 % 256	;const
	push	hl
	ld	hl,_sprite_2_a
	push	hl
	ld	hl,1 % 256	;const
	push	hl
	ld	hl,128 % 256	;const
	push	hl
	call	sp_CreateSpr
	pop	bc
	pop	bc
	pop	bc
	pop	bc
	pop	bc
	ld	(_sp_player),hl
	push	hl
	ld	hl,_sprite_2_b
	push	hl
	ld	hl,128 % 256	;const
	push	hl
	call	sp_AddColSpr
	pop	bc
	pop	bc
	pop	bc
	ld	hl,(_sp_player)
	push	hl
	ld	hl,_sprite_2_c
	push	hl
	ld	hl,128 % 256	;const
	push	hl
	call	sp_AddColSpr
	pop	bc
	pop	bc
	pop	bc
	ld	hl,_sprite_2_a
	ld	(_p_n_f),hl
	ld	(_p_c_f),hl
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_gpit),a
	jp	i_391
.i_389
	ld	hl,_gpit
	ld	a,(hl)
	inc	(hl)
.i_391
	ld	a,(_gpit)
	cp	#(3 % 256)
	jp	z,i_390
	jp	nc,i_390
	ld	hl,_sp_moviles
	push	hl
	ld	hl,(_gpit)
	ld	h,0
	add	hl,hl
	pop	de
	add	hl,de
	push	hl
	ld	hl,0 % 256	;const
	push	hl
	ld	hl,3 % 256	;const
	push	hl
	ld	de,_sprite_9_a
	push	de
	push	hl
	ld	hl,128 % 256	;const
	push	hl
	call	sp_CreateSpr
	pop	bc
	pop	bc
	pop	bc
	pop	bc
	pop	bc
	pop	de
	call	l_pint
	ld	hl,_sp_moviles
	push	hl
	ld	hl,(_gpit)
	ld	h,0
	add	hl,hl
	pop	de
	add	hl,de
	ld	e,(hl)
	inc	hl
	ld	d,(hl)
	push	de
	ld	hl,_sprite_9_b
	push	hl
	ld	hl,128 % 256	;const
	push	hl
	call	sp_AddColSpr
	pop	bc
	pop	bc
	pop	bc
	ld	hl,_sp_moviles
	push	hl
	ld	hl,(_gpit)
	ld	h,0
	add	hl,hl
	pop	de
	add	hl,de
	ld	e,(hl)
	inc	hl
	ld	d,(hl)
	push	de
	ld	hl,_sprite_9_c
	push	hl
	ld	hl,128 % 256	;const
	push	hl
	call	sp_AddColSpr
	pop	bc
	pop	bc
	pop	bc
	ld	hl,_en_an_c_f
	push	hl
	ld	hl,(_gpit)
	ld	h,0
	add	hl,hl
	pop	de
	add	hl,de
	push	hl
	ld	hl,_en_an_n_f
	push	hl
	ld	hl,(_gpit)
	ld	h,0
	add	hl,hl
	pop	de
	add	hl,de
	push	hl
	ld	hl,_sprite_9_a
	pop	de
	call	l_pint
	pop	de
	call	l_pint
	jp	i_389
.i_390
	ld	hl,0 % 256	;const
	push	hl
	ld	hl,2 % 256	;const
	push	hl
	ld	de,_sprite_20_a
	push	de
	push	hl
	ld	hl,128 % 256	;const
	push	hl
	call	sp_CreateSpr
	pop	bc
	pop	bc
	pop	bc
	pop	bc
	pop	bc
	ld	(_sp_hitter),hl
	push	hl
	ld	hl,_sprite_20_a+32
	push	hl
	ld	hl,128 % 256	;const
	push	hl
	call	sp_AddColSpr
	pop	bc
	pop	bc
	pop	bc
	ld	hl,_sprite_20_a
	ld	(_hitter_c_f),hl
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_gpit),a
	jp	i_394
.i_392
	ld	hl,_gpit
	ld	a,(hl)
	inc	(hl)
.i_394
	ld	a,(_gpit)
	cp	#(3 % 256)
	jp	z,i_393
	jp	nc,i_393
	ld	hl,_sp_cocos
	push	hl
	ld	hl,(_gpit)
	ld	h,0
	add	hl,hl
	pop	de
	add	hl,de
	push	hl
	ld	hl,0 % 256	;const
	push	hl
	ld	hl,2 % 256	;const
	push	hl
	ld	hl,_sprite_19_a
	push	hl
	ld	hl,1 % 256	;const
	push	hl
	ld	hl,128 % 256	;const
	push	hl
	call	sp_CreateSpr
	pop	bc
	pop	bc
	pop	bc
	pop	bc
	pop	bc
	pop	de
	call	l_pint
	ld	hl,_sp_cocos
	push	hl
	ld	hl,(_gpit)
	ld	h,0
	add	hl,hl
	pop	de
	add	hl,de
	ld	e,(hl)
	inc	hl
	ld	d,(hl)
	push	de
	ld	hl,_sprite_19_a+32
	push	hl
	ld	hl,128 % 256	;const
	push	hl
	call	sp_AddColSpr
	pop	bc
	pop	bc
	pop	bc
	jp	i_392
.i_393
	ei
	call	_cortina
	call	_wyz_init
.i_395
	call	sp_UpdateNow
	ld	hl,0 % 256	;const
	push	hl
	ld	hl,16384	;const
	push	hl
	call	_get_resource
	pop	bc
	pop	bc
	ld	hl,0 % 256	;const
	call	_wyz_play_music
	call	_select_joyfunc
	call	_wyz_stop_sound
	ld	a,#(1 % 256 % 256)
	ld	(_mlplaying),a
	ld	a,#(0 % 256 % 256)
	ld	(_silent_level),a
	ld	a,#(0 % 256 % 256)
	ld	(_level),a
	ld	hl,9 % 256	;const
	ld	a,l
	ld	(_p_life),a
	call	_cortina
	call	sp_UpdateNow
	ld	hl,1 % 256	;const
	push	hl
	ld	hl,16384	;const
	push	hl
	call	_get_resource
	pop	bc
	pop	bc
	ld	a,#(0 % 256 % 256)
	ld	(_script_result),a
	ld	a,#(0 % 256 % 256)
	ld	(_p_killme),a
	ld	hl,1 % 256	;const
	ld	a,l
	ld	(_level),a
.i_397
	ld	hl,(_mlplaying)
	ld	h,0
	ld	a,h
	or	l
	jp	z,i_398
	call	_prepare_level
	ld	hl,(_silent_level)
	ld	h,0
	call	l_lneg
	jp	nc,i_399
	call	_blackout_area
	ld	a,#(12 % 256 % 256)
	ld	(__x),a
	ld	a,#(12 % 256 % 256)
	ld	(__y),a
	ld	a,#(71 % 256 % 256)
	ld	(__t),a
	ld	hl,i_1+107
	ld	(_gp_gen),hl
	call	_print_str
	ld	a,#(18 % 256 % 256)
	ld	(__x),a
	ld	a,#(12 % 256 % 256)
	ld	(__y),a
	ld	hl,(_level)
	ld	h,0
	inc	hl
	ld	h,0
	ld	a,l
	ld	(__t),a
	call	_print_number2
	call	sp_UpdateNow
	ld	hl,8 % 256	;const
	call	_wyz_play_sound
	ld	hl,250	;const
	push	hl
	call	_active_sleep
	pop	bc
.i_399
	ld	a,#(0 % 256 % 256)
	ld	(_silent_level),a
	ld	hl,1 % 256	;const
	ld	a,l
	ld	(_playing),a
	call	_init_cocos
	call	_player_init
	ld	a,#(0 % 256 % 256)
	ld	(_maincounter),a
	ld	a,#(0 % 256 % 256)
	ld	(_script_result),a
	ld	a,(_level_data+9)
	and	a
	jp	z,i_400
	ld	hl,42 % 256	;const
	push	hl
	call	_run_script
	pop	bc
.i_400
	call	_init_lava
	ld	a,#(1 % 256 % 256)
	ld	(_do_respawn),a
	ld	hl,255 % 256	;const
	ld	a,l
	ld	(_killed_old),a
	ld	h,0
	ld	a,l
	ld	(_life_old),a
	ld	h,0
	ld	a,l
	ld	(_keys_old),a
	ld	h,0
	ld	a,l
	ld	(_objs_old),a
	ld	a,#(99 % 256 % 256)
	ld	(_flag_old),a
	ld	a,#(0 % 256 % 256)
	ld	(_success),a
	ld	a,#(0 % 256 % 256)
	ld	(_do_process_breakable),a
	ld	hl,_breaking_f
	ld	(_gen_pt),hl
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_gpit),a
	jp	i_403
.i_401
	ld	hl,_gpit
	ld	a,(hl)
	inc	(hl)
.i_403
	ld	a,(_gpit)
	cp	#(3 % 256)
	jp	z,i_402
	jp	nc,i_402
	ld	hl,(_gen_pt)
	inc	hl
	ld	(_gen_pt),hl
	dec	hl
	ld	(hl),#(0 % 256 % 256)
	ld	l,(hl)
	ld	h,0
	jp	i_401
.i_402
	ld	hl,(_level_data+10)
	ld	h,0
	call	_wyz_play_music
	ld	a,#(255 % 256 % 256)
	ld	(_o_pant),a
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_no_draw),a
.i_404
	ld	hl,(_playing)
	ld	h,0
	ld	a,h
	or	l
	jp	z,i_405
	call	_read_controller
	ld	hl,(_n_pant)
	ld	h,0
	ex	de,hl
	ld	hl,(_o_pant)
	ld	h,0
	call	l_ne
	jp	nc,i_406
	ld	hl,(_n_pant)
	ld	h,0
	ld	a,l
	ld	(_o_pant),a
	call	_draw_scr
	ld	a,(_flags+30)
	ld	e,a
	ld	d,0
	ld	hl,1	;const
	call	l_eq
	call	c,_lava_reenter
.i_407
.i_406
	call	_update_hud
	ld	hl,_maincounter
	ld	a,(hl)
	inc	(hl)
	ld	hl,(_half_life)
	ld	h,0
	call	l_lneg
	ld	hl,0	;const
	rl	l
	ld	h,0
	ld	a,l
	ld	(_half_life),a
	call	_player_move
	ld	hl,(_hitter_on)
	ld	h,0
	ld	a,h
	or	l
	call	nz,_render_hitter
.i_408
	call	_enems_move
	call	_move_cocos
	ld	hl,(_do_process_breakable)
	ld	h,0
	ld	a,h
	or	l
	call	nz,_process_breakable
.i_409
	ld	a,(_p_state)
	ld	e,a
	ld	d,0
	ld	hl,2	;const
	call	l_and
	ld	de,0	;const
	ex	de,hl
	call	l_eq
	jp	c,i_411
	ld	a,(_half_life)
	cp	#(0 % 256)
	jp	nz,i_410
.i_411
	ld ix, (_sp_player)
	ld iy, vpClipStruct
	ld hl, (_p_n_f)
	ld de, (_p_c_f)
	or a
	sbc hl, de
	ld b, h
	ld c, l
	ld a, (_gpy)
	srl a
	srl a
	srl a
	add 2
	ld h, a
	ld a, (_gpx)
	srl a
	srl a
	srl a
	add 1
	ld l, a
	ld a, (_gpx)
	and 7
	ld d, a
	ld a, (_gpy)
	and 7
	ld e, a
	call SPMoveSprAbs
	jp	i_413
.i_410
	ld ix, (_sp_player)
	ld iy, vpClipStruct
	ld hl, (_p_n_f)
	ld de, (_p_c_f)
	or a
	sbc hl, de
	ld b, h
	ld c, l
	ld hl, 0xfefe
	ld de, 0
	call SPMoveSprAbs
.i_413
	ld	hl,(_p_n_f)
	ld	(_p_c_f),hl
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_gpit),a
	jp	i_416
.i_414
	ld	hl,_gpit
	ld	a,(hl)
	inc	(hl)
.i_416
	ld	a,(_gpit)
	cp	#(3 % 256)
	jp	z,i_415
	jp	nc,i_415
	ld	de,_coco_s
	ld	hl,(_gpit)
	ld	h,0
	add	hl,de
	ld	a,(hl)
	cp	#(1 % 256)
	jp	nz,i_417
	ld	de,_coco_x
	ld	hl,(_gpit)
	ld	h,0
	add	hl,de
	ld	l,(hl)
	ld	h,0
	ld	a,l
	ld	(_rdx),a
	ld	de,_coco_y
	ld	hl,(_gpit)
	ld	h,0
	add	hl,de
	ld	l,(hl)
	ld	h,0
	ld	a,l
	ld	(_rdy),a
	ld a, (_gpit)
	sla a
	ld c, a
	ld b, 0
	ld hl, _sp_cocos
	add hl, bc
	ld e, (hl)
	inc hl
	ld d, (hl)
	push de
	pop ix
	ld iy, vpClipStruct
	ld bc, 0
	ld a, (_rdy)
	srl a
	srl a
	srl a
	add 2
	ld h, a
	ld a, (_rdx)
	srl a
	srl a
	srl a
	add 1
	ld l, a
	ld a, (_rdx)
	and 7
	ld d, a
	ld a, (_rdy)
	and 7
	ld e, a
	call SPMoveSprAbs
	jp	i_418
.i_417
	ld a, (_gpit)
	sla a
	ld c, a
	ld b, 0
	ld hl, _sp_cocos
	add hl, bc
	ld e, (hl)
	inc hl
	ld d, (hl)
	push de
	pop ix
	ld iy, vpClipStruct
	ld bc, 0
	ld hl, 0xfefe
	ld de, 0
	call SPMoveSprAbs
.i_418
	jp	i_414
.i_415
.i_419
	ld	a,(_isrc)
	ld	e,a
	ld	d,0
	ld	hl,2	;const
	call	l_ult
	jp	nc,i_420
	halt
	jp	i_419
.i_420
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_isrc),a
	call	sp_UpdateNow
	ld	a,(_flags+30)
	ld	e,a
	ld	d,0
	ld	hl,1	;const
	call	l_eq
	jp	nc,i_421
	call	_do_lava
	ld	a,h
	or	l
	jp	z,i_422
	ld	a,#(10 % 256 % 256)
	ld	(_p_killme),a
	ld	a,#(2 % 256 % 256)
	ld	(_success),a
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_playing),a
.i_422
.i_421
	ld	a,(_p_state)
	and	a
	jp	z,i_423
	ld	hl,_p_state_ct
	ld	a,(hl)
	dec	(hl)
	ld	a,(_p_state_ct)
	and	a
	jp	nz,i_424
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_p_state),a
.i_424
.i_423
	ld a, (_hotspot_x)
	ld c, a
	ld a, (_gpx)
	add 8
	cp c
	jp c, _hotspots_skip
	ld a, (_gpx)
	ld c, a
	ld a, (_hotspot_x)
	add 8
	cp c
	jp c, _hotspots_skip
	ld a, (_hotspot_y)
	ld c, a
	ld a, (_gpy)
	add 8
	cp c
	jp c, _hotspots_skip
	ld a, (_gpy)
	ld c, a
	ld a, (_hotspot_y)
	add 8
	cp c
	jp c, _hotspots_skip
	ld	a,#(0 % 256 % 256)
	ld	(_gpit),a
	ld	hl,_hotspots
	push	hl
	ld	hl,(_n_pant)
	ld	h,0
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	pop	de
	add	hl,de
	inc	hl
	inc	hl
	ld	a,(hl)
	and	a
	jp	z,i_425
	ld	hl,_hotspots
	push	hl
	ld	hl,(_n_pant)
	ld	h,0
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	pop	de
	add	hl,de
	inc	hl
	ld	l,(hl)
	ld	h,0
.i_428
	ld	a,l
	cp	#(1% 256)
	jp	z,i_429
	cp	#(3% 256)
	jp	z,i_430
	jp	i_427
.i_429
	ld	hl,_p_objs
	ld	a,(hl)
	inc	(hl)
	ld	hl,3 % 256	;const
	call	_wyz_play_sound
	jp	i_427
.i_430
	ld	hl,(_p_life)
	ld	h,0
	inc	hl
	ld	h,0
	ld	a,l
	ld	(_p_life),a
	ld	hl,5 % 256	;const
	call	_wyz_play_sound
.i_427
.i_425
	ld	a,(_gpit)
	and	a
	jp	nz,i_431
	ld	a,(_hotspot_x)
	ld	e,a
	ld	d,0
	ld	l,#(4 % 256)
	call	l_asr_u
	ld	h,0
	ld	a,l
	ld	(__x),a
	ld	a,(_hotspot_y)
	ld	e,a
	ld	d,0
	ld	l,#(4 % 256)
	call	l_asr_u
	ld	h,0
	ld	a,l
	ld	(__y),a
	ld	hl,(_orig_tile)
	ld	h,0
	ld	a,l
	ld	(__t),a
	call	_draw_invalidate_coloured_tile_g
	ld	hl,_hotspots
	push	hl
	ld	hl,(_n_pant)
	ld	h,0
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	pop	de
	add	hl,de
	inc	hl
	inc	hl
	ld	(hl),#(0 % 256 % 256)
	ld	l,(hl)
	ld	h,0
	jp	i_432
.i_431
	ld	hl,6 % 256	;const
	call	_wyz_play_sound
.i_432
	ld	hl,240 % 256	;const
	ld	a,l
	ld	(_hotspot_y),a
	._hotspots_skip
	call	_do_ingame_scripting
	ld	hl,2239	;const
	push	hl
	call	sp_KeyPressed
	pop	bc
	ld	a,h
	or	l
	jp	z,i_433
	call	sp_WaitForNoKey
	call	_wyz_stop_sound
	ld	hl,8 % 256	;const
	call	_wyz_play_sound
.i_434
	ld	hl,2239	;const
	push	hl
	call	sp_KeyPressed
	pop	bc
	ld	a,h
	or	l
	jp	z,i_434
.i_435
	call	sp_WaitForNoKey
.i_433
	ld	hl,4319	;const
	push	hl
	call	sp_KeyPressed
	pop	bc
	ld	a,h
	or	l
	jp	z,i_436
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_playing),a
.i_436
	ld	a,(_level_data+7)
	cp	#(0 % 256)
	jp	nz,i_438
	ld	hl,(_p_objs)
	ld	h,0
	ex	de,hl
	ld	hl,(_level_data+5)
	ld	h,0
	call	l_eq
	jp	c,i_440
.i_438
	jr	i_438_i_439
.i_439
	ld	a,h
	or	l
	jp	nz,i_440
.i_438_i_439
	ld	a,(_level_data+7)
	cp	#(1 % 256)
	jp	nz,i_441
	ld	hl,(_n_pant)
	ld	h,0
	ex	de,hl
	ld	hl,(_level_data+8)
	ld	h,0
	call	l_eq
	jp	c,i_440
.i_441
	jr	i_441_i_442
.i_442
	ld	a,h
	or	l
	jp	nz,i_440
.i_441_i_442
	ld	a,(_level_data+7)
	cp	#(2 % 256)
	jp	nz,i_443
	ld	a,(_script_result)
	cp	#(1 % 256)
	jp	nz,i_443
	ld	hl,1	;const
	jr	i_444
.i_443
	ld	hl,0	;const
.i_444
	ld	a,h
	or	l
	jp	nz,i_440
	jr	i_445
.i_440
	ld	hl,1	;const
.i_445
	ld	a,h
	or	l
	jp	z,i_437
	ld	a,#(1 % 256 % 256)
	ld	(_success),a
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_playing),a
.i_437
	ld	a,(_p_life)
	cp	#(0 % 256)
	jp	z,i_447
	ld	a,(_script_result)
	cp	#(2 % 256)
	jp	nz,i_446
.i_447
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_playing),a
.i_446
	ld	a,(_script_result)
	cp	#(2 % 256)
	jp	z,i_449
	jp	c,i_449
	ld	hl,(_script_result)
	ld	h,0
	ld	a,l
	ld	(_success),a
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_playing),a
.i_449
	ld	hl,(_p_killme)
	ld	h,0
	ld	a,h
	or	l
	jp	z,i_450
	call	_player_kill
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_p_killme),a
.i_450
	call	_flick_screen
	jp	i_404
.i_405
	call	_wyz_stop_sound
	ld	hl,0 % 256	;const
	push	hl
	call	_hide_sprites
	pop	bc
	call	sp_UpdateNow
	ld	hl,(_success)
	ld	h,0
.i_453
	ld	a,l
	cp	#(0% 256)
	jp	z,i_454
	cp	#(1% 256)
	jp	z,i_455
	cp	#(3% 256)
	jp	z,i_456
	cp	#(4% 256)
	jp	z,i_457
	jp	i_452
.i_454
	ld	hl,i_1+94
	ld	(_gp_gen),hl
	call	_print_message
	ld	a,#(0 % 256 % 256)
	ld	(_mlplaying),a
	ld	hl,250	;const
	push	hl
	call	_active_sleep
	pop	bc
	jp	i_452
.i_455
	ld	hl,i_1+113
	ld	(_gp_gen),hl
	call	_print_message
	ld	hl,_level
	ld	a,(hl)
	inc	(hl)
	ld	hl,250	;const
	push	hl
	call	_active_sleep
	pop	bc
	jp	i_452
.i_456
	call	_blackout_area
	ld	hl,(_warp_to_level)
	ld	h,0
	ld	a,l
	ld	(_level),a
	jp	i_452
.i_457
	ld	hl,2 % 256	;const
	push	hl
	ld	hl,16384	;const
	push	hl
	call	_get_resource
	pop	bc
	pop	bc
	ld	hl,1000	;const
	push	hl
	call	_active_sleep
	pop	bc
	call	_wyz_stop_sound
	call	_cortina
	ld	hl,130	;const
	push	hl
	call	_active_sleep
	pop	bc
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_mlplaying),a
.i_452
	jp	i_397
.i_398
	call	_cortina
	jp	i_395
.i_396
	ret


;	SECTION	text

.i_1
	defm	"            "
	defb	0

	defm	"#$$$$$$$$$$$$$$$$$$$$$$$$%"
	defb	0

	defm	"&                        '"
	defb	0

	defm	"())))))))))))))))))))))))*"
	defb	0

	defm	" GAME OVER! "
	defb	0

	defm	"LEVEL"
	defb	0

	defm	" ZONE CLEAR "
	defb	0

;	SECTION	code



; --- Start of Static Variables ---

;	SECTION	bss

.__en_t	defs	1
.__en_x	defs	1
.__en_y	defs	1
._sp_moviles	defs	6
._hitter_type	defs	1
.__en_x1	defs	1
.__en_y1	defs	1
.__en_x2	defs	1
.__en_y2	defs	1
._lava_ct	defs	1
._en_an_base_frame	defs	3
._hotspot_x	defs	1
._hotspot_y	defs	1
._p_hitting	defs	1
._en_an_c_f	defs	6
.__en_mx	defs	1
.__en_my	defs	1
._map_pointer	defs	2
._en_an_state	defs	3
._flags	defs	32
._p_facing	defs	1
._p_frame	defs	1
._en_an_n_f	defs	6
._p_c_f	defs	2
._hitter_on	defs	1
._pregotten	defs	1
._hit_h	defs	1
._hit_v	defs	1
._killed_old	defs	1
._p_n_f	defs	2
._gpaux	defs	1
._map_attr	defs	150
._active	defs	1
._sp_hitter	defs	2
.__n	defs	1
._do_respawn	defs	1
.__t	defs	1
.__x	defs	1
.__y	defs	1
._mlplaying	defs	1
._life_old	defs	1
._coco_d	defs	1
._coco_s	defs	3
._coco_x	defs	3
._coco_y	defs	3
._p_engine	defs	1
._hitter_c_f	defs	2
._gen_pt	defs	2
._no_draw	defs	1
._p_state	defs	1
._ptgmx	defs	1
._ptgmy	defs	1
._hitter_n_f	defs	2
._warp_to_level	defs	1
._hitter_hit	defs	1
._sp_player	defs	2
._gp_gen	defs	2
._killable	defs	1
._enoffs	defs	1
._pad_this_frame	defs	1
._silent_level	defs	1
._sp_cocos	defs	6
._p_killed	defs	1
._lava_y	defs	1
._pad0	defs	1
._p_killme	defs	1
._p_jmp_ct	defs	1
._n_pant	defs	1
._p_jmp_on	defs	1
._o_pant	defs	1
._p_life	defs	1
._hitter_x	defs	1
._hitter_y	defs	1
._enit	defs	1
._p_safe_x	defs	1
._p_safe_y	defs	1
._joyfunc	defs	2
._gpcx	defs	1
._p_objs	defs	1
._p_gotten	defs	1
._fzx1	defs	1
._fzx2	defs	1
._fzy1	defs	1
._fzy2	defs	1
._gpcy	defs	1
._gpit	defs	1
._en_an_vx	defs	3
._p_keys	defs	1
._en_an_vy	defs	3
._gpjt	defs	1
._playing	defs	1
._sc_c	defs	1
._main_script_offset	defs	2
._keyp	defs	1
._sc_m	defs	1
._sc_n	defs	1
._keys	defs	10
._level_ac	defs	1
._exti	defs	1
._sc_x	defs	1
._sc_y	defs	1
._p_vx	defs	1
._p_vy	defs	1
._gpxx	defs	1
._gpyy	defs	1
._objs_old	defs	1
._extx	defs	1
._exty	defs	1
._maincounter	defs	1
._ptx1	defs	1
._ptx2	defs	1
._pty1	defs	1
._pty2	defs	1
._flag_old	defs	1
._f_zone_ac	defs	1
._at1	defs	1
._at2	defs	1
._action_pressed	defs	1
.__en_life	defs	1
._cx1	defs	1
._cx2	defs	1
._cy1	defs	1
._cy2	defs	1
._enemy_shoots	defs	1
._p_subframe	defs	1
._p_state_ct	defs	1
._animate	defs	1
._next_script	defs	2
._gpc	defs	1
._gpd	defs	1
._coco_x0	defs	1
._p_g	defs	1
._en_an_x	defs	6
._en_an_y	defs	6
._hit	defs	1
._ctx	defs	1
._gps	defs	1
._gpt	defs	1
._rda	defs	1
._p_x	defs	2
._AD_FREE	defs	900
._p_y	defs	2
._gpx	defs	1
._gpy	defs	1
._rdb	defs	1
._rdx	defs	1
._rdy	defs	1
._wall_h	defs	1
._stepbystep	defs	1
._cty	defs	1
._coco_vx	defs	3
._enoffsmasi	defs	1
._coco_vy	defs	3
._coco_it	defs	1
._keys_old	defs	1
._wall_v	defs	1
._tocado	defs	1
._x_pant	defs	1
._is_rendering	defs	1
._p_facing_h	defs	1
._y_pant	defs	1
.__baddies_pointer	defs	2
._p_facing_v	defs	1
._possee	defs	1
._orig_tile	defs	1
._hitter_frame	defs	1
._success	defs	1
._en_an_count	defs	3
._p_disparando	defs	1
._p_safe_pant	defs	1
;	SECTION	code



; --- Start of Scope Defns ---

	LIB	sp_GetKey
	LIB	sp_BlockAlloc
	XDEF	__en_t
	XDEF	_read_vbyte
	LIB	sp_ScreenStr
	XDEF	__en_x
	XDEF	__en_y
	XDEF	_hotspots
	XDEF	_mons_col_sc_x
	XDEF	_mons_col_sc_y
	XDEF	_draw_scr
	LIB	sp_PixelUp
	XDEF	_enems_move_spr_abs
	XDEF	_wyz_play_sample
	XDEF	_prepare_level
	XDEF	_wyz_play_music
	LIB	sp_JoyFuller
	LIB	sp_MouseAMXInit
	XDEF	_blackout_area
	LIB	sp_MouseAMX
	XDEF	_sp_moviles
	XDEF	_hitter_type
	XDEF	__en_x1
	LIB	sp_SetMousePosAMX
	XDEF	__en_y1
	XDEF	_u_malloc
	LIB	sp_Validate
	LIB	sp_HashAdd
	XDEF	__en_x2
	XDEF	__en_y2
	XDEF	_cortina
	XDEF	_lava_ct
	LIB	sp_Border
	LIB	sp_Inkey
	XDEF	_enems_kill
	XDEF	_en_an_base_frame
	XDEF	_enems_init
	XDEF	_draw_objs
	XDEF	_wyz_play_sound
	XDEF	_hotspot_x
	XDEF	_hotspot_y
	LIB	sp_CreateSpr
	LIB	sp_MoveSprAbs
	LIB	sp_BlockCount
	LIB	sp_AddMemory
	XDEF	_half_life
	XDEF	_p_hitting
	XDEF	_en_an_c_f
	XDEF	__en_mx
	XDEF	__en_my
	XDEF	_map_pointer
	XDEF	_hoffs_x
	XDEF	_read_controller
	XDEF	_en_an_state
	XDEF	_flags
	LIB	sp_PrintAt
	LIB	sp_Pause
	XDEF	_enems_move
	LIB	sp_ListFirst
	LIB	sp_HeapSiftUp
	LIB	sp_ListCount
	XDEF	_p_facing
	XDEF	_invalidate_tile
	XDEF	_p_frame
	XDEF	_en_an_n_f
	LIB	sp_Heapify
	XDEF	_p_c_f
	XDEF	_hitter_on
	LIB	sp_MoveSprRel
	XDEF	_hide_sprites
	XDEF	_pregotten
	XDEF	_hit_h
	LIB	sp_TileArray
	LIB	sp_MouseSim
	LIB	sp_BlockFit
	XDEF	_map_buff
	defc	_map_buff	=	61697
	XDEF	_resources
	XDEF	_breaking_idx
	XDEF	_hit_v
	LIB	sp_HeapExtract
	LIB	sp_HuffExtract
	XDEF	_killed_old
	LIB	sp_SetMousePosSim
	XDEF	_p_n_f
	XDEF	_gpaux
	LIB	sp_ClearRect
	XDEF	_print_message
	LIB	sp_HuffGetState
	XDEF	_map_attr
	XDEF	_baddies
	XDEF	_invalidate_viewport
	XDEF	_active
	XDEF	_seed1
	XDEF	_seed2
	XDEF	_init_lava
	LIB	sp_ListAppend
	XDEF	_keyscancodes
	XDEF	_level
	LIB	sp_ListCreate
	LIB	sp_ListConcat
	XDEF	_sp_hitter
	XDEF	_limit
	LIB	sp_JoyKempston
	LIB	sp_UpdateNow
	LIB	sp_MouseKempston
	LIB	sp_PrintString
	LIB	sp_PixelDown
	LIB	sp_MoveSprAbsC
	LIB	sp_PixelLeft
	XDEF	_enem_frames
	LIB	sp_InitAlloc
	LIB	sp_DeleteSpr
	XDEF	_get_resource
	LIB	sp_JoyTimexEither
	XDEF	__n
	XDEF	_unpack_RAMn
	XDEF	_flick_screen
	XDEF	_do_respawn
	XDEF	_player_kill
	XDEF	__t
	XDEF	__x
	XDEF	__y
	XDEF	_wyz_init
	XDEF	_player_init
	XDEF	_level_sequence
	XDEF	_mlplaying
	XDEF	_life_old
	LIB	sp_Invalidate
	LIB	sp_CreateGenericISR
	LIB	sp_JoyKeyboard
	XDEF	_coco_d
	LIB	sp_FreeBlock
	XDEF	_coco_s
	LIB	sp_PrintAtDiff
	LIB	sp_UpdateNowEx
	XDEF	_run_fire_script
	XDEF	_coco_x
	XDEF	_coco_y
	XDEF	_p_engine
	XDEF	_player_move
	XDEF	_hitter_c_f
	XDEF	_gen_pt
	XDEF	_no_draw
	XDEF	_read_byte
	XDEF	_sprite_10_a
	XDEF	_sprite_10_b
	XDEF	_sprite_10_c
	XDEF	_addsign
	XDEF	_sprite_11_a
	XDEF	_sprite_11_b
	XDEF	_sprite_11_c
	XDEF	_collide_pixel
	XDEF	_sprite_12_a
	XDEF	_sprite_12_b
	XDEF	_p_state
	XDEF	_sprite_12_c
	XDEF	_sprite_13_a
	XDEF	_sprite_13_b
	XDEF	_sprite_13_c
	XDEF	_sprite_20_a
	XDEF	_sprite_14_a
	XDEF	_sprite_14_b
	XDEF	_sprite_14_c
	XDEF	_sprite_21_a
	XDEF	_sprite_15_a
	XDEF	_sprite_15_b
	XDEF	_sprite_15_c
	LIB	sp_RegisterHookLast
	LIB	sp_IntLargeRect
	LIB	sp_IntPtLargeRect
	LIB	sp_HashDelete
	LIB	sp_GetCharAddr
	XDEF	_ptgmx
	XDEF	_ptgmy
	LIB	sp_RemoveHook
	XDEF	_hitter_n_f
	XDEF	_warp_to_level
	XDEF	_sprite_16_a
	XDEF	_sprite_16_b
	XDEF	_sprite_16_c
	XDEF	_sprite_17_a
	XDEF	_sprite_18_a
	XDEF	_sprite_19_a
	XDEF	_hitter_hit
	LIB	sp_MoveSprRelC
	LIB	sp_InitIM2
	XDEF	_sprite_19_b
	XDEF	_player_frames
	XDEF	_cm_two_points
	XDEF	_qtile
	XDEF	_randres
	XDEF	_srand
	XDEF	_do_ingame_scripting
	XDEF	_sp_player
	XDEF	_stop_player
	XDEF	_wall_broken
	XDEF	_move_cocos
	XDEF	_gp_gen
	LIB	sp_GetTiles
	LIB	sp_Pallette
	LIB	sp_WaitForNoKey
	XDEF	_killable
	XDEF	_enoffs
	XDEF	_safe_byte
	defc	_safe_byte	=	23301
	XDEF	_pad_this_frame
	XDEF	_silent_level
	XDEF	_utaux
	LIB	sp_JoySinclair1
	LIB	sp_JoySinclair2
	LIB	sp_ListPrepend
	XDEF	_sp_cocos
	XDEF	_init_cocos
	XDEF	_behs
	XDEF	_draw_invalidate_coloured_tile_g
	XDEF	_p_killed
	LIB	sp_GetAttrAddr
	LIB	sp_HashCreate
	XDEF	_lava_y
	XDEF	_pad0
	XDEF	_p_killme
	LIB	sp_Random32
	LIB	sp_ListInsert
	XDEF	_p_jmp_ct
	LIB	sp_ListFree
	XDEF	_n_pant
	XDEF	_spriteset
	XDEF	_advance_worm
	XDEF	_p_jmp_on
	XDEF	_ISR
	LIB	sp_IntRect
	LIB	sp_ListLast
	LIB	sp_ListCurr
	XDEF	_o_pant
	XDEF	_p_life
	XDEF	_hitter_x
	XDEF	_hitter_y
	XDEF	_enit
	XDEF	_p_safe_x
	XDEF	_p_safe_y
	XDEF	_print_number2
	XDEF	_main
	LIB	sp_ListSearch
	LIB	sp_WaitForKey
	XDEF	_draw_coloured_tile
	LIB	sp_Wait
	LIB	sp_GetScrnAddr
	XDEF	_joyfunc
	LIB	sp_PutTiles
	XDEF	_gpcx
	XDEF	_p_objs
	XDEF	_p_gotten
	XDEF	_fzx1
	XDEF	_fzx2
	XDEF	_fzy1
	XDEF	_fzy2
	XDEF	_gpcy
	LIB	sp_RemoveDList
	XDEF	_gpit
	XDEF	_en_an_vx
	XDEF	_p_keys
	XDEF	_en_an_vy
	XDEF	_gpjt
	XDEF	_playing
	XDEF	_attr
	XDEF	_sc_c
	XDEF	_main_script_offset
	LIB	sp_ListNext
	XDEF	_player_calc_bounding_box
	XDEF	_keyp
	XDEF	_sc_m
	XDEF	_sc_n
	LIB	sp_HuffDecode
	XDEF	_keys
	XDEF	_level_ac
	XDEF	_rand
	LIB	sp_Swap
	XDEF	_run_entering_script
	XDEF	_exti
	XDEF	_sc_x
	XDEF	_isrc
	defc	_isrc	=	23296
	XDEF	_sc_y
	XDEF	_print_str
	XDEF	_levels
	XDEF	_asm_int_2
	defc	_asm_int_2	=	23299
	XDEF	_p_vx
	XDEF	_p_vy
	XDEF	_gpxx
	XDEF	_gpyy
	XDEF	_objs_old
	LIB	sp_ListPrev
	XDEF	_extx
	XDEF	_exty
	XDEF	_maincounter
	XDEF	_lava_reenter
	XDEF	_ptx1
	XDEF	_ptx2
	XDEF	_pty1
	XDEF	_pty2
	XDEF	_active_sleep
	XDEF	_flag_old
	LIB	sp_RegisterHook
	LIB	sp_ListRemove
	LIB	sp_ListTrim
	XDEF	_f_zone_ac
	LIB	sp_MoveSprAbsNC
	XDEF	_break_wall
	LIB	sp_HuffDelete
	XDEF	_update_tile
	XDEF	_readxy
	XDEF	_at1
	XDEF	_at2
	XDEF	_level_data
	LIB	sp_ListAdd
	LIB	sp_KeyPressed
	XDEF	_action_pressed
	XDEF	_button_pressed
	XDEF	__en_life
	LIB	sp_PrintAtInv
	XDEF	_draw_coloured_tile_gamearea
	XDEF	_cx1
	XDEF	_cx2
	XDEF	_cy1
	XDEF	_cy2
	XDEF	_enemy_shoots
	LIB	sp_CompDListAddr
	XDEF	_p_subframe
	XDEF	_u_free
	XDEF	_abs
	XDEF	_p_state_ct
	XDEF	_game_ending
	LIB	sp_CharRight
	XDEF	_animate
	XDEF	_next_script
	XDEF	_run_script
	LIB	sp_InstallISR
	XDEF	_do_process_breakable
	XDEF	_process_breakable
	XDEF	_gpc
	XDEF	_breaking_f
	defc	_breaking_f	=	61853
	LIB	sp_HuffAccumulate
	LIB	sp_HuffSetState
	XDEF	_gpd
	XDEF	_coco_x0
	XDEF	_p_g
	XDEF	_en_an_x
	XDEF	_en_an_y
	XDEF	_hit
	XDEF	_map
	XDEF	_sprite_1_a
	XDEF	_sprite_1_b
	XDEF	_sprite_1_c
	XDEF	_ctx
	XDEF	_gps
	XDEF	_gpt
	XDEF	_rda
	XDEF	_breaking_x
	defc	_breaking_x	=	61847
	XDEF	_breaking_y
	defc	_breaking_y	=	61850
	LIB	sp_SwapEndian
	LIB	sp_CharLeft
	XDEF	_p_x
	XDEF	_AD_FREE
	LIB	sp_CharDown
	LIB	sp_HeapSiftDown
	LIB	sp_HuffCreate
	XDEF	_p_y
	XDEF	_gpx
	XDEF	_gpy
	XDEF	_rdb
	XDEF	_sprite_2_a
	XDEF	_sprite_2_b
	LIB	sp_HuffEncode
	XDEF	_sprite_2_c
	XDEF	_sprite_3_a
	XDEF	_sprite_3_b
	XDEF	_sprite_3_c
	XDEF	_ram_page
	LIB	sp_JoyTimexRight
	LIB	sp_PixelRight
	XDEF	_rdx
	XDEF	_rdy
	XDEF	_script_result
	LIB	sp_Initialize
	XDEF	_sprite_4_a
	XDEF	_sprite_4_b
	XDEF	_sprite_4_c
	XDEF	_sprite_5_a
	XDEF	_tileset
	XDEF	_sprite_5_b
	LIB	sp_JoyTimexLeft
	LIB	sp_SetMousePosKempston
	XDEF	_sprite_5_c
	XDEF	_sprite_6_a
	XDEF	_script
	LIB	sp_ComputePos
	XDEF	_sprite_6_b
	XDEF	_sprite_6_c
	XDEF	_sprite_7_a
	XDEF	_sprite_7_b
	XDEF	_sprite_7_c
	XDEF	_sprite_8_a
	XDEF	_sprite_8_b
	XDEF	_sprite_8_c
	XDEF	_sprite_9_a
	XDEF	_sprite_9_b
	XDEF	_sprite_9_c
	XDEF	_wyz_stop_sound
	XDEF	_wall_h
	XDEF	_stepbystep
	XDEF	_reloc_player
	XDEF	_cty
	XDEF	_coco_vx
	XDEF	_enoffsmasi
	XDEF	_coco_vy
	XDEF	_coco_it
	XDEF	_keys_old
	XDEF	_update_hud
	XDEF	_spacer
	XDEF	_do_lava
	XDEF	_wall_v
	LIB	sp_IntIntervals
	XDEF	_my_malloc
	XDEF	_tocado
	XDEF	_x_pant
	XDEF	_do_gravity
	XDEF	_is_rendering
	LIB	sp_inp
	XDEF	_SetRAMBank
	LIB	sp_IterateSprChar
	LIB	sp_AddColSpr
	LIB	sp_outp
	XDEF	_sc_terminado
	XDEF	_asm_int
	defc	_asm_int	=	23297
	XDEF	_is_cutscene
	XDEF	_p_facing_h
	XDEF	_y_pant
	LIB	sp_IntPtInterval
	LIB	sp_RegisterHookFirst
	XDEF	__baddies_pointer
	LIB	sp_HashLookup
	XDEF	_p_facing_v
	LIB	sp_PFill
	XDEF	_possee
	LIB	sp_HashRemove
	XDEF	_sc_continuar
	LIB	sp_CharUp
	XDEF	_orig_tile
	XDEF	_hitter_frame
	XDEF	_success
	XDEF	_textbuff
	defc	_textbuff	=	23302
	LIB	sp_MoveSprRelNC
	XDEF	_ram_destination
	XDEF	_do_extern_action
	XDEF	_en_an_count
	XDEF	_select_joyfunc
	XDEF	_p_disparando
	XDEF	_shoot_coco
	LIB	sp_IterateDList
	XDEF	_distance
	XDEF	_draw_scr_background
	XDEF	_game_over
	LIB	sp_LookupKey
	LIB	sp_HeapAdd
	LIB	sp_CompDirtyAddr
	LIB	sp_EmptyISR
	XDEF	_p_safe_pant
	XDEF	_render_hitter
	XDEF	_ram_address
	LIB	sp_StackSpace


; --- End of Scope Defns ---


; --- End of Compilation ---
