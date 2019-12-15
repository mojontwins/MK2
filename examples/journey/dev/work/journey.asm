;* * * * *  Small-C/Plus z88dk * * * * *
;  Version: 20100416.1
;
;	Reconstructed for z80 Module Assembler
;
;	Module compile time: Sun Dec 15 10:28:20 2019



	MODULE	mk2.c


	INCLUDE "z80_crt0.hdr"


	LIB SPMoveSprAbs
	LIB SPPrintAtInv
	LIB SPTileArray
	LIB SPInvalidate
	LIB SPCompDListAddr
;	SECTION	text

._keyscancodes
	defw	763,765,509,1277,383,0,507,509,735,479
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

._do_gravity
	defm	""
	defb	1

;	SECTION	code


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

._unpack
	ld	hl,4	;const
	add	hl,sp
	call	l_gint	;
	ld	a,h
	or	l
	jp	z,i_9
	ld	de,_ram_address
	ld	hl,6-2	;const
	add	hl,sp
	call	l_gint	;
	call	l_pint
	ld	de,_ram_destination
	ld	hl,4-2	;const
	add	hl,sp
	call	l_gint	;
	call	l_pint
	ld hl, (_ram_address)
	ld de, (_ram_destination)
	call depack
.i_9
	ret


	._s_title
	BINARY "../bin/title.bin"
	._s_marco
	._s_ending
	BINARY "../bin/ending.bin"
	._level_data defs 16
	._map
	defs 1800
	._bolts
	defs 4*32
	._baddies
	defs 4 * 7 * 3 * 12
	._hotspots defs 4 * 7 * 3
	._behs
	defs 48
	._tileset
	BINARY "../bin/font.bin"
	defs 192*8+256
	._level0_map
	BINARY "../bin/level0.map.c.bin"
	._level1_map
	BINARY "../bin/level1.map.c.bin"
	._level0_bolts
	BINARY "../bin/level0.locks.c.bin"
	._level1_bolts
	BINARY "../bin/level1.locks.c.bin"
	._level0_enems
	BINARY "../bin/level0.enems.c.bin"
	._level1_enems
	BINARY "../bin/level1.enems.c.bin"
	._level0_hotspots
	BINARY "../bin/level0.hotspots.c.bin"
	._level1_hotspots
	BINARY "../bin/level1.hotspots.c.bin"
	._level0_behs
	BINARY "../bin/level0.behs.c.bin"
	._level1_behs
	BINARY "../bin/level1.behs.c.bin"
	._level0_ts
	BINARY "../bin/level0.ts.c.bin"
	._level1_ts
	BINARY "../bin/level1.ts.c.bin"
;	SECTION	text

._levels
	defb	4
	defb	7
	defb	16
	defb	4
	defb	5
	defb	99
	defb	12
	defb	0
	defb	1
	defw	_level0_map
	defw	_level0_bolts
	defw	_level0_enems
	defw	_level0_hotspots
	defw	_level0_behs
	defw	_level0_ts
	defb	4
	defb	7
	defb	0
	defb	1
	defb	5
	defb	99
	defb	12
	defb	0
	defb	1
	defw	_level1_map
	defw	_level1_bolts
	defw	_level1_enems
	defw	_level1_hotspots
	defw	_level1_behs
	defw	_level1_ts

;	SECTION	code

	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	._sprite_1_a
	defb 0, 240
	defb 3, 224
	defb 6, 192
	defb 13, 192
	defb 11, 192
	defb 11, 192
	defb 15, 128
	defb 3, 0
	defb 60, 0
	defb 127, 0
	defb 103, 0
	defb 7, 0
	defb 3, 0
	defb 126, 0
	defb 124, 0
	defb 64, 0
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	._sprite_1_b
	defb 0, 15
	defb 224, 7
	defb 0, 3
	defb 16, 3
	defb 80, 3
	defb 80, 3
	defb 240, 3
	defb 224, 1
	defb 24, 0
	defb 252, 0
	defb 236, 0
	defb 226, 0
	defb 214, 0
	defb 46, 0
	defb 0, 0
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	._sprite_1_c
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	._sprite_2_a
	defb 3, 224
	defb 6, 192
	defb 13, 192
	defb 11, 192
	defb 11, 192
	defb 15, 192
	defb 3, 192
	defb 12, 128
	defb 31, 0
	defb 55, 0
	defb 55, 0
	defb 54, 0
	defb 6, 0
	defb 6, 224
	defb 6, 224
	defb 7, 224
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	._sprite_2_b
	defb 224, 7
	defb 0, 3
	defb 16, 3
	defb 80, 3
	defb 80, 3
	defb 240, 3
	defb 224, 3
	defb 16, 3
	defb 248, 1
	defb 232, 1
	defb 232, 1
	defb 200, 1
	defb 96, 1
	defb 96, 7
	defb 96, 7
	defb 112, 3
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	._sprite_2_c
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	._sprite_3_a
	defb 0, 240
	defb 3, 224
	defb 6, 192
	defb 13, 192
	defb 11, 192
	defb 11, 192
	defb 15, 192
	defb 3, 192
	defb 12, 192
	defb 15, 192
	defb 7, 192
	defb 8, 128
	defb 23, 0
	defb 43, 0
	defb 48, 0
	defb 32, 2
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	._sprite_3_b
	defb 0, 15
	defb 224, 7
	defb 0, 3
	defb 16, 3
	defb 80, 3
	defb 80, 3
	defb 240, 3
	defb 224, 3
	defb 16, 3
	defb 176, 3
	defb 176, 3
	defb 96, 0
	defb 228, 0
	defb 252, 0
	defb 124, 0
	defb 0, 0
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	._sprite_3_c
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	._sprite_4_a
	defb 0, 240
	defb 3, 224
	defb 6, 192
	defb 13, 192
	defb 11, 192
	defb 11, 192
	defb 15, 192
	defb 3, 192
	defb 12, 0
	defb 127, 0
	defb 103, 0
	defb 7, 0
	defb 31, 128
	defb 56, 0
	defb 48, 1
	defb 0, 3
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	._sprite_4_b
	defb 0, 15
	defb 224, 7
	defb 0, 3
	defb 16, 3
	defb 80, 3
	defb 80, 3
	defb 240, 3
	defb 224, 3
	defb 16, 0
	defb 254, 0
	defb 230, 0
	defb 224, 0
	defb 248, 1
	defb 28, 0
	defb 12, 128
	defb 0, 192
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	._sprite_4_c
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	._sprite_5_a
	defb 0, 240
	defb 7, 224
	defb 0, 192
	defb 8, 192
	defb 10, 192
	defb 10, 192
	defb 15, 192
	defb 7, 128
	defb 24, 0
	defb 63, 0
	defb 55, 0
	defb 71, 0
	defb 107, 0
	defb 116, 0
	defb 0, 0
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	._sprite_5_b
	defb 0, 15
	defb 192, 7
	defb 96, 3
	defb 176, 3
	defb 208, 3
	defb 208, 3
	defb 240, 1
	defb 192, 0
	defb 60, 0
	defb 254, 0
	defb 230, 0
	defb 224, 0
	defb 192, 0
	defb 126, 0
	defb 62, 0
	defb 2, 0
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	._sprite_5_c
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	._sprite_6_a
	defb 7, 224
	defb 0, 192
	defb 8, 192
	defb 10, 192
	defb 10, 192
	defb 15, 192
	defb 7, 192
	defb 8, 192
	defb 31, 128
	defb 23, 128
	defb 23, 128
	defb 19, 128
	defb 6, 128
	defb 6, 224
	defb 6, 224
	defb 14, 192
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	._sprite_6_b
	defb 192, 7
	defb 96, 3
	defb 176, 3
	defb 208, 3
	defb 208, 3
	defb 240, 3
	defb 192, 3
	defb 48, 1
	defb 248, 0
	defb 236, 0
	defb 236, 0
	defb 108, 0
	defb 96, 0
	defb 96, 7
	defb 96, 7
	defb 224, 7
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	._sprite_6_c
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	._sprite_7_a
	defb 0, 240
	defb 7, 224
	defb 0, 192
	defb 8, 192
	defb 10, 192
	defb 10, 192
	defb 15, 192
	defb 7, 192
	defb 8, 192
	defb 13, 192
	defb 13, 192
	defb 6, 0
	defb 39, 0
	defb 63, 0
	defb 62, 0
	defb 0, 0
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	._sprite_7_b
	defb 0, 15
	defb 192, 7
	defb 96, 3
	defb 176, 3
	defb 208, 3
	defb 208, 3
	defb 240, 3
	defb 192, 3
	defb 48, 3
	defb 240, 3
	defb 224, 3
	defb 16, 1
	defb 232, 0
	defb 212, 0
	defb 12, 0
	defb 4, 64
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	._sprite_7_c
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	._sprite_8_a
	defb 0, 240
	defb 7, 224
	defb 0, 192
	defb 8, 192
	defb 10, 192
	defb 10, 192
	defb 15, 192
	defb 7, 192
	defb 8, 0
	defb 127, 0
	defb 103, 0
	defb 7, 0
	defb 31, 128
	defb 56, 0
	defb 48, 1
	defb 0, 3
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	._sprite_8_b
	defb 0, 15
	defb 192, 7
	defb 96, 3
	defb 176, 3
	defb 208, 3
	defb 208, 3
	defb 240, 3
	defb 192, 3
	defb 48, 0
	defb 254, 0
	defb 230, 0
	defb 224, 0
	defb 248, 1
	defb 28, 0
	defb 12, 128
	defb 0, 192
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	._sprite_8_c
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	._sprite_9_a
	defb 1, 240
	defb 7, 224
	defb 15, 128
	defb 47, 0
	defb 111, 0
	defb 75, 0
	defb 95, 0
	defb 44, 0
	defb 24, 0
	defb 12, 128
	defb 15, 192
	defb 7, 224
	defb 6, 224
	defb 6, 224
	defb 4, 224
	defb 0, 225
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	._sprite_9_b
	defb 128, 31
	defb 192, 15
	defb 224, 7
	defb 240, 3
	defb 240, 3
	defb 120, 1
	defb 236, 0
	defb 246, 0
	defb 114, 0
	defb 242, 0
	defb 240, 0
	defb 96, 3
	defb 64, 15
	defb 96, 7
	defb 32, 7
	defb 0, 135
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	._sprite_9_c
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	._sprite_10_a
	defb 1, 248
	defb 3, 240
	defb 7, 224
	defb 15, 192
	defb 15, 192
	defb 30, 128
	defb 55, 0
	defb 111, 0
	defb 78, 0
	defb 79, 0
	defb 15, 0
	defb 6, 192
	defb 2, 240
	defb 6, 224
	defb 4, 224
	defb 0, 225
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	._sprite_10_b
	defb 128, 15
	defb 224, 7
	defb 240, 1
	defb 244, 0
	defb 246, 0
	defb 210, 0
	defb 250, 0
	defb 52, 0
	defb 24, 0
	defb 48, 1
	defb 240, 3
	defb 224, 7
	defb 96, 7
	defb 96, 7
	defb 32, 7
	defb 0, 135
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	._sprite_10_c
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	._sprite_11_a
	defb 0, 255
	defb 0, 192
	defb 30, 128
	defb 63, 0
	defb 55, 0
	defb 63, 0
	defb 30, 128
	defb 15, 192
	defb 0, 224
	defb 3, 224
	defb 14, 192
	defb 14, 192
	defb 7, 224
	defb 1, 240
	defb 0, 252
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	._sprite_11_b
	defb 0, 255
	defb 0, 127
	defb 0, 63
	defb 0, 15
	defb 32, 7
	defb 144, 3
	defb 152, 1
	defb 56, 1
	defb 248, 1
	defb 176, 3
	defb 0, 7
	defb 0, 127
	defb 0, 3
	defb 200, 1
	defb 112, 3
	defb 0, 7
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	._sprite_11_c
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	._sprite_12_a
	defb 0, 224
	defb 15, 192
	defb 31, 128
	defb 59, 0
	defb 63, 0
	defb 63, 0
	defb 31, 128
	defb 13, 192
	defb 7, 224
	defb 0, 224
	defb 7, 224
	defb 14, 192
	defb 14, 192
	defb 7, 224
	defb 0, 240
	defb 0, 254
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	._sprite_12_b
	defb 0, 127
	defb 0, 63
	defb 128, 31
	defb 192, 15
	defb 224, 7
	defb 224, 3
	defb 164, 0
	defb 68, 0
	defb 142, 0
	defb 30, 0
	defb 252, 0
	defb 56, 1
	defb 0, 3
	defb 128, 1
	defb 228, 0
	defb 56, 1
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	._sprite_12_c
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	._sprite_13_a
	defb 1, 240
	defb 7, 224
	defb 3, 192
	defb 12, 192
	defb 26, 128
	defb 30, 128
	defb 12, 128
	defb 0, 128
	defb 30, 128
	defb 31, 128
	defb 11, 192
	defb 11, 192
	defb 3, 192
	defb 10, 192
	defb 0, 224
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	._sprite_13_b
	defb 192, 15
	defb 192, 15
	defb 224, 7
	defb 0, 7
	defb 96, 7
	defb 208, 3
	defb 240, 3
	defb 96, 3
	defb 0, 3
	defb 176, 3
	defb 240, 3
	defb 224, 7
	defb 96, 7
	defb 96, 7
	defb 64, 15
	defb 0, 31
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	._sprite_13_c
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	._sprite_14_a
	defb 3, 240
	defb 3, 240
	defb 7, 224
	defb 0, 224
	defb 6, 224
	defb 11, 192
	defb 15, 192
	defb 6, 192
	defb 0, 192
	defb 13, 192
	defb 15, 192
	defb 7, 224
	defb 6, 224
	defb 6, 224
	defb 2, 240
	defb 0, 248
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	._sprite_14_b
	defb 128, 15
	defb 224, 7
	defb 192, 3
	defb 48, 3
	defb 88, 1
	defb 120, 1
	defb 48, 1
	defb 0, 1
	defb 120, 1
	defb 248, 1
	defb 208, 3
	defb 208, 3
	defb 192, 3
	defb 80, 3
	defb 0, 7
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	._sprite_14_c
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	._sprite_15_a
	defb 0, 0
	defb 127, 0
	defb 63, 0
	defb 31, 128
	defb 0, 192
	defb 3, 240
	defb 3, 240
	defb 1, 248
	defb 0, 252
	defb 0, 252
	defb 1, 240
	defb 7, 224
	defb 6, 224
	defb 4, 224
	defb 6, 224
	defb 0, 240
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	._sprite_15_b
	defb 0, 0
	defb 254, 0
	defb 254, 0
	defb 252, 0
	defb 172, 0
	defb 248, 0
	defb 224, 1
	defb 240, 3
	defb 240, 3
	defb 48, 3
	defb 240, 3
	defb 192, 7
	defb 0, 31
	defb 0, 127
	defb 0, 127
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	._sprite_15_c
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	._sprite_16_a
	defb 0, 0
	defb 127, 0
	defb 63, 0
	defb 31, 128
	defb 1, 192
	defb 3, 240
	defb 3, 240
	defb 1, 248
	defb 0, 252
	defb 0, 248
	defb 1, 248
	defb 3, 240
	defb 3, 240
	defb 3, 240
	defb 1, 248
	defb 0, 252
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	._sprite_16_b
	defb 0, 0
	defb 254, 0
	defb 254, 0
	defb 248, 0
	defb 88, 1
	defb 240, 3
	defb 192, 3
	defb 224, 7
	defb 224, 7
	defb 96, 7
	defb 224, 7
	defb 192, 15
	defb 128, 15
	defb 0, 31
	defb 128, 31
	defb 0, 31
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	._sprite_16_c
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	._sprite_18_a
	defb 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255
	._sprite_18_b
	defb 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255
	._sprite_18_c
	defb 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255
	.sound_play
	ld hl, soundEffectsData ;address of sound effects data
	;di
	push iy
	ld b,0
	ld c,a
	add hl,bc
	add hl,bc
	ld a,(hl)
	inc hl
	ld h,(hl)
	ld l,a
	push hl
	pop ix ;put it into ix
	.readData
	ld a,(ix+0) ;read block type
	or a
	jr nz,readData_sound
	pop iy
	;ei
	ret
	.readData_sound
	ld c,(ix+1) ;read duration 1
	ld b,(ix+2)
	ld e,(ix+3) ;read duration 2
	ld d,(ix+4)
	push de
	pop iy
	dec a
	jr nz,sfxRoutineNoise
	;this routine generate tone with many parameters
	.sfxRoutineTone
	ld e,(ix+5) ;freq
	ld d,(ix+6)
	ld a,(ix+9) ;duty
	ld (sfxRoutineTone_duty + 1),a
	ld hl,0
	.sfxRoutineTone_l0
	push bc
	push iy
	pop bc
	.sfxRoutineTone_l1
	add hl,de
	ld a,h
	.sfxRoutineTone_duty
	cp 0
	sbc a,a
	and 16
	.sfxRoutineTone_border
	or 0
	out ($fe),a
	dec bc
	ld a,b
	or c
	jr nz,sfxRoutineTone_l1
	ld a,(sfxRoutineTone_duty + 1)
	add a,(ix+10) ;duty change
	ld (sfxRoutineTone_duty + 1),a
	ld c,(ix+7) ;slide
	ld b,(ix+8)
	ex de,hl
	add hl,bc
	ex de,hl
	pop bc
	dec bc
	ld a,b
	or c
	jr nz,sfxRoutineTone_l0
	ld c,11
	.nextData
	add ix,bc ;skip to the next block
	jr readData
	;this routine generate noise with two parameters
	.sfxRoutineNoise
	ld e,(ix+5) ;pitch
	ld d,1
	ld h,d
	ld l,d
	.sfxRoutineNoise_l0
	push bc
	push iy
	pop bc
	.sfxRoutineNoise_l1
	ld a,(hl)
	and 16
	.sfxRoutineNoise_border
	or 0
	out ($fe),a
	dec d
	jr nz,sfxRoutineNoise_l2
	ld d,e
	inc hl
	ld a,h
	and $1f
	ld h,a
	.sfxRoutineNoise_l2
	dec bc
	ld a,b
	or c
	jr nz,sfxRoutineNoise_l1
	ld a,e
	add a,(ix+6) ;slide
	ld e,a
	pop bc
	dec bc
	ld a,b
	or c
	jr nz,sfxRoutineNoise_l0
	ld c,7
	jr nextData
	.soundEffectsData
	defw soundEffectsData_sfx0
	defw soundEffectsData_sfx1
	defw soundEffectsData_sfx2
	defw soundEffectsData_sfx3
	defw soundEffectsData_sfx4
	defw soundEffectsData_sfx5
	defw soundEffectsData_sfx6
	defw soundEffectsData_sfx7
	defw soundEffectsData_sfx8
	defw soundEffectsData_sfx9
	defw soundEffectsData_sfx10
	defw soundEffectsData_sfx11
	.soundEffectsData_sfx0
	defb 0x01
	defw 0x000a,0x03e8,0x00c8,0x0016,0x1680
	defb 0x00
	.soundEffectsData_sfx1
	defb 0x01
	defw 0x0064,0x0014,0x01f4,0x0002,0x0010
	defb 0x00
	.soundEffectsData_sfx2
	defb 0x02
	defw 0x0001,0x03e8,0x000a
	defb 0x01
	defw 0x0014,0x0064,0x0190,0xfff0,0x0080
	defb 0x02
	defw 0x0001,0x07d0,0x0001
	defb 0x00
	.soundEffectsData_sfx3
	defb 0x01
	defw 0x0014,0x00c8,0x0d48,0x000a,0x0040
	defb 0x00
	.soundEffectsData_sfx4
	defb 0x01
	defw 0x0050,0x0014,0x03e8,0xffff,0x0080
	defb 0x00
	.soundEffectsData_sfx5
	defb 0x01
	defw 0x0004,0x03e8,0x03e8,0x0190,0x0080
	defb 0x00
	.soundEffectsData_sfx6
	defb 0x01
	defw 0x0002,0x0fa0,0x0190,0x00c8,0x0040
	defb 0x01
	defw 0x0002,0x0fa0,0x00c8,0x00c8,0x0020
	defb 0x00
	.soundEffectsData_sfx7
	defb 0x01
	defw 0x000a,0x03e8,0x00c8,0x0002,0x0010
	defb 0x01
	defw 0x0001,0x0fa0,0x0000,0x0000,0x0000
	defb 0x01
	defw 0x000a,0x03e8,0x00c8,0xfffe,0x0010
	defb 0x01
	defw 0x0001,0x07d0,0x0000,0x0000,0x0000
	defb 0x01
	defw 0x000a,0x03e8,0x00b4,0xfffe,0x0010
	defb 0x01
	defw 0x0001,0x0fa0,0x0000,0x0000,0x0000
	defb 0x00
	.soundEffectsData_sfx8
	defb 0x02
	defw 0x0001,0x03e8,0x0014
	defb 0x01
	defw 0x0001,0x03e8,0x0000,0x0000,0x0000
	defb 0x02
	defw 0x0001,0x03e8,0x0001
	defb 0x00
	.soundEffectsData_sfx9
	defb 0x02
	defw 0x0014,0x0032,0x0101
	defb 0x00
	.soundEffectsData_sfx10
	defb 0x02
	defw 0x0064,0x01f4,0x0264
	defb 0x00
	.soundEffectsData_sfx11
	defb 0x01
	defw 0x0014,0x01f4,0x00c8,0x0005,0x0110
	defb 0x01
	defw 0x0001,0x03e8,0x0000,0x0000,0x0000
	defb 0x01
	defw 0x001e,0x01f4,0x00c8,0x0008,0x0110
	defb 0x01
	defw 0x0001,0x07d0,0x0000,0x0000,0x0000
	defb 0x00

._beep_fx
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	(_asm_int),hl
	push ix
	push iy
	ld a, (_asm_int)
	call sound_play
	pop ix
	pop iy
	ret


	defw 0

._ISR
	ld	hl,(_isrc)
	ld	h,0
	inc	hl
	ld	a,l
	ld	(_isrc),a
	ret


;	SECTION	text

._spacer
	defw	i_1+0
;	SECTION	code


._draw_coloured_tile
	ld a, (__x)
	sub 1
	srl a
	ld (_xx), a
	ld a, (__y)
	sub 2
	srl a
	ld (_yy), a
	ld	hl,(_xx)
	ld	h,0
	ld	a,l
	ld	(_cx1),a
	ld	hl,(_yy)
	ld	h,0
	ld	a,l
	ld	(_cy1),a
	call	_attr
	ld	de,8	;const
	ex	de,hl
	call	l_and
	ld	a,h
	or	l
	jp	nz,i_12
	ld	a,(__t)
	cp	#(16 % 256)
	jr	z,i_13_uge
	jp	c,i_13
.i_13_uge
	ld	a,(__t)
	cp	#(19 % 256)
	jp	z,i_13
	ld	hl,1	;const
	jr	i_14
.i_13
	ld	hl,0	;const
.i_14
	ld	a,h
	or	l
	jp	nz,i_12
	jr	i_15
.i_12
	ld	hl,1	;const
.i_15
	call	l_lneg
	ld	hl,0	;const
	rl	l
	ld	h,0
	ld	a,l
	ld	(_nocast),a
	ld a, (__t)
	sla a
	sla a
	add 64
	ld (__ta), a
	ld hl, _tileset + 2048
	ld b, 0
	ld c, a
	add hl, bc
	ld (_gen_pt), hl
	ld	a,(__t)
	ld	e,a
	ld	d,0
	ld	hl,19	;const
	call	l_eq
	jp	nc,i_16
	ld hl, _tileset + 2048 + 192
	ld (_gen_pt_alt), hl
	ld	hl,192 % 256	;const
	ld	a,l
	ld	(_t_alt),a
	jp	i_17
.i_16
	ld hl, _tileset + 2048 + 128
	ld de, (__ta)
	ld d, 0
	add hl, de
	ld (_gen_pt_alt), hl
	ld	hl,(__ta)
	ld	h,0
	ld	de,128
	add	hl,de
	ld	h,0
	ld	a,l
	ld	(_t_alt),a
.i_17
	ld	de,_tileset+2048
	ld	hl,(_t_alt)
	ld	h,0
	add	hl,de
	ld	(_gen_pt_alt),hl
	ld a, (_xx)
	dec a
	ld (_cx1), a
	ld a, (_yy)
	or a
	jr z, _dct_1_set_yy
	dec a
	._dct_1_set_yy
	ld (_cy1), a
	ld a, (_nocast)
	or a
	jr z, _dct_a1_set
	call _attr
	ld a, l
	and 8
	jr z, _dct_a1_set
	ld a, 1
	._dct_a1_set
	ld (_a1), a
	ld a, (_xx)
	ld (_cx1), a
	ld a, (_yy)
	or a
	jr z, _dct_2_set_yy
	dec a
	._dct_2_set_yy
	ld (_cy1), a
	ld a, (_nocast)
	or a
	jr z, _dct_a2_set
	call _attr
	ld a, l
	and 8
	jr z, _dct_a2_set
	ld a, 1
	._dct_a2_set
	ld (_a2), a
	ld a, (_xx)
	dec a
	ld (_cx1), a
	ld a, (_yy)
	ld (_cy1), a
	ld a, (_nocast)
	or a
	jr z, _dct_a3_set
	call _attr
	ld a, l
	and 8
	jr z, _dct_a3_set
	ld a, 1
	._dct_a3_set
	ld (_a3), a
	ld a, (_a1)
	or a
	jr nz, _dct_1_shadow
	ld a, (_a2)
	or a
	jr z, _dct_1_no_shadow
	ld a, (_a3)
	or a
	jr z, _dct_1_no_shadow
	._dct_1_shadow
	ld hl, (_gen_pt_alt)
	ld a, (hl)
	ld (_c1), a
	ld a, (_t_alt)
	ld (_t1), a
	jr _dct_1_increment
	._dct_1_no_shadow
	ld hl, (_gen_pt)
	ld a, (hl)
	ld (_c1), a
	ld a, (__ta)
	ld (_t1), a
	._dct_1_increment
	ld hl, (_gen_pt)
	inc hl
	ld (_gen_pt), hl
	ld hl, (_gen_pt_alt)
	inc hl
	ld (_gen_pt_alt), hl
	ld hl, __ta
	inc (hl)
	ld hl, _t_alt
	inc (hl)
	ld a, (_a2)
	or a
	jr z, _dct_2_no_shadow
	._dct_2_shadow
	ld hl, (_gen_pt_alt)
	ld a, (hl)
	ld (_c2), a
	ld a, (_t_alt)
	ld (_t2), a
	jr _dct_2_increment
	._dct_2_no_shadow
	ld hl, (_gen_pt)
	ld a, (hl)
	ld (_c2), a
	ld a, (__ta)
	ld (_t2), a
	._dct_2_increment
	ld hl, (_gen_pt)
	inc hl
	ld (_gen_pt), hl
	ld hl, (_gen_pt_alt)
	inc hl
	ld (_gen_pt_alt), hl
	ld hl, __ta
	inc (hl)
	ld hl, _t_alt
	inc (hl)
	ld a, (_a3)
	or a
	jr z, _dct_3_no_shadow
	._dct_3_shadow
	ld hl, (_gen_pt_alt)
	ld a, (hl)
	ld (_c3), a
	ld a, (_t_alt)
	ld (_t3), a
	jr _dct_3_increment
	._dct_3_no_shadow
	ld hl, (_gen_pt)
	ld a, (hl)
	ld (_c3), a
	ld a, (__ta)
	ld (_t3), a
	._dct_3_increment
	ld hl, (_gen_pt)
	inc hl
	ld (_gen_pt), hl
	ld hl, (_gen_pt_alt)
	inc hl
	ld (_gen_pt_alt), hl
	ld hl, __ta
	inc (hl)
	ld hl, _t_alt
	inc (hl)
	ld hl, (_gen_pt)
	ld a, (hl)
	ld (_c4), a
	ld a, (__ta)
	ld (_t4), a
	ld a, (__x)
	ld c, a
	ld a, (__y)
	call SPCompDListAddr
	ld a, (_c1)
	ld (hl), a
	inc hl
	ld a, (_t1)
	ld (hl), a
	inc hl
	inc hl
	inc hl
	ld a, (_c2)
	ld (hl), a
	inc hl
	ld a, (_t2)
	ld (hl), a
	ld bc, 123
	add hl, bc
	ld a, (_c3)
	ld (hl), a
	inc hl
	ld a, (_t3)
	ld (hl), a
	inc hl
	inc hl
	inc hl
	ld a, (_c4)
	ld (hl), a
	inc hl
	ld a, (_t4)
	ld (hl), a
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
	ld	a,#(17 % 256 % 256)
	ld	(__x),a
	ld	a,#(0 % 256 % 256)
	ld	(__y),a
	ld	hl,(_level_data+5)
	ld	h,0
	ex	de,hl
	ld	hl,(_p_objs)
	ld	h,0
	ex	de,hl
	and	a
	sbc	hl,de
	ld	h,0
	ld	a,l
	ld	(__t),a
	call	_print_number2
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



._step
	ld a, 16
	out (254), a
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	xor 16
	out (254), a
	ret



._cortina
	ld b, 7
	.fade_out_extern
	push bc
	ld e, 3 ; 3 tercios
	ld hl, 22528 ; aqu� empiezan los atributos
	.fade_out_bucle
	ld a, (hl ) ; nos traemos el atributo actual
	ld d, a ; tomar atributo
	and 7 ; aislar la tinta
	jr z, ink_done ; si vale 0, no se decrementa
	dec a ; decrementamos tinta
	.ink_done
	ld b, a ; en b tenemos ahora la tinta ya procesada.
	ld a, d ; tomar atributo
	and 56 ; aislar el papel, sin modificar su posición en el byte
	jr z, paper_done ; si vale 0, no se decrementa
	sub 8 ; decrementamos papel restando 8
	.paper_done
	ld c, a ; en c tenemos ahora el papel ya procesado.
	ld a, d
	and 192 ; nos quedamos con bits 6 y 7 (0x40 y 0x80)
	or c ; a�adimos paper
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
	ld	hl,250 % 256	;const
	ld	a,l
	ld	(_gpjt),a
.i_31
	ld	hl,1 % 256	;const
	ld	a,l
	ld	(_gpit),a
.i_29
	ld	hl,(_gpjt)
	ld	h,0
	dec	hl
	ld	a,l
	ld	(_gpjt),a
	ld	a,h
	or	l
	jp	nz,i_31
.i_30
	call	_button_pressed
	ld	a,h
	or	l
	jp	nz,i_27
.i_32
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
	; Music generated by beepola
	call musicstart
.i_33
	call	sp_GetKey
	ld	h,0
	ld	a,l
	ld	(_gpit),a
	cp	#(49 % 256)
	jp	z,i_36
	ld	a,(_gpit)
	cp	#(50 % 256)
	jp	nz,i_35
.i_36
	ld	hl,sp_JoyKeyboard
	ld	(_joyfunc),hl
	ld	hl,(_gpit)
	ld	h,0
	ld	bc,-49
	add	hl,bc
	ld	a,h
	or	l
	jp	z,i_38
	ld	hl,6	;const
	jp	i_39
.i_38
	ld	hl,0	;const
.i_39
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
	jp	i_34
.i_35
	ld	a,(_gpit)
	cp	#(51 % 256)
	jp	nz,i_41
	ld	hl,sp_JoyKempston
	ld	(_joyfunc),hl
	jp	i_34
.i_41
	ld	a,(_gpit)
	cp	#(52 % 256)
	jp	nz,i_43
	ld	hl,sp_JoySinclair1
	ld	(_joyfunc),hl
	jp	i_34
.i_43
.i_42
.i_40
	jp	i_33
.i_34
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
	ld	hl,_levels
	push	hl
	ld	hl,(_level)
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
	inc	hl
	ld	d,(hl)
	push	de
	ld	hl,_map
	push	hl
	call	_unpack
	pop	bc
	pop	bc
	ld	hl,_levels
	push	hl
	ld	hl,(_level)
	ld	h,0
	push	de
	ld	de,21
	call	l_mult
	pop	de
	pop	de
	add	hl,de
	ld	bc,11
	add	hl,bc
	ld	e,(hl)
	inc	hl
	ld	d,(hl)
	push	de
	ld	hl,_bolts
	push	hl
	call	_unpack
	pop	bc
	pop	bc
	ld	hl,_levels
	push	hl
	ld	hl,(_level)
	ld	h,0
	push	de
	ld	de,21
	call	l_mult
	pop	de
	pop	de
	add	hl,de
	ld	bc,13
	add	hl,bc
	ld	e,(hl)
	inc	hl
	ld	d,(hl)
	push	de
	ld	hl,_baddies
	push	hl
	call	_unpack
	pop	bc
	pop	bc
	ld	hl,_levels
	push	hl
	ld	hl,(_level)
	ld	h,0
	push	de
	ld	de,21
	call	l_mult
	pop	de
	pop	de
	add	hl,de
	ld	bc,15
	add	hl,bc
	ld	e,(hl)
	inc	hl
	ld	d,(hl)
	push	de
	ld	hl,_hotspots
	push	hl
	call	_unpack
	pop	bc
	pop	bc
	ld	hl,_levels
	push	hl
	ld	hl,(_level)
	ld	h,0
	push	de
	ld	de,21
	call	l_mult
	pop	de
	pop	de
	add	hl,de
	ld	bc,17
	add	hl,bc
	ld	e,(hl)
	inc	hl
	ld	d,(hl)
	push	de
	ld	hl,_behs
	push	hl
	call	_unpack
	pop	bc
	pop	bc
	ld	hl,_levels
	push	hl
	ld	hl,(_level)
	ld	h,0
	push	de
	ld	de,21
	call	l_mult
	pop	de
	pop	de
	add	hl,de
	ld	bc,19
	add	hl,bc
	ld	e,(hl)
	inc	hl
	ld	d,(hl)
	push	de
	ld	hl,_tileset+512
	push	hl
	call	_unpack
	pop	bc
	pop	bc
	ld	hl,_level_data
	push	hl
	ld	hl,_levels
	push	hl
	ld	hl,(_level)
	ld	h,0
	push	de
	ld	de,21
	call	l_mult
	pop	de
	pop	de
	add	hl,de
	ld	a,(hl)
	pop	de
	ld	(de),a
	ld	hl,_level_data+1
	push	hl
	ld	hl,_levels
	push	hl
	ld	hl,(_level)
	ld	h,0
	push	de
	ld	de,21
	call	l_mult
	pop	de
	pop	de
	add	hl,de
	inc	hl
	ld	a,(hl)
	pop	de
	ld	(de),a
	ld	hl,_level_data+5
	push	hl
	ld	hl,_levels
	push	hl
	ld	hl,(_level)
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
	ld	hl,_level_data+6
	push	hl
	ld	hl,_levels
	push	hl
	ld	hl,(_level)
	ld	h,0
	push	de
	ld	de,21
	call	l_mult
	pop	de
	pop	de
	add	hl,de
	ld	bc,8
	add	hl,bc
	ld	a,(hl)
	pop	de
	ld	(de),a
	ld	hl,_level_data+7
	push	hl
	ld	hl,_levels
	push	hl
	ld	hl,(_level)
	ld	h,0
	push	de
	ld	de,21
	call	l_mult
	pop	de
	pop	de
	add	hl,de
	ld	bc,7
	add	hl,bc
	ld	a,(hl)
	pop	de
	ld	(de),a
	ld	hl,_levels
	push	hl
	ld	hl,(_level)
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
	ld	a,l
	ld	(_n_pant),a
	ld	hl,_levels
	push	hl
	ld	hl,(_level)
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
	ld	e,(hl)
	ld	d,0
	ld	l,#(4 % 256)
	call	l_asl
	ld	h,0
	ld	a,l
	ld	(_gpx),a
	ld	hl,_levels
	push	hl
	ld	hl,(_level)
	ld	h,0
	push	de
	ld	de,21
	call	l_mult
	pop	de
	pop	de
	add	hl,de
	ld	bc,4
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
	ld	hl,_s_ending
	push	hl
	ld	hl,16384	;const
	push	hl
	call	_unpack
	pop	bc
	pop	bc
	ld	hl,4 % 256	;const
	ld	a,l
	ld	(_bs),a
.i_48
	ld	hl,2 % 256	;const
	push	hl
	call	_beep_fx
	pop	bc
	ld	hl,3 % 256	;const
	push	hl
	call	_beep_fx
	pop	bc
.i_46
	ld	hl,(_bs)
	ld	h,0
	dec	hl
	ld	a,l
	ld	(_bs),a
	ld	a,h
	or	l
	jp	nz,i_48
.i_47
	ld	hl,6 % 256	;const
	push	hl
	call	_beep_fx
	pop	bc
	ret



._game_over
	ld	a,#(6 % 256 % 256)
	ld	(__x),a
	ld	a,#(0 % 256 % 256)
	ld	(__y),a
	ld	hl,(_p_life)
	ld	h,0
	ld	a,l
	ld	(__t),a
	call	_print_number2
	ld	hl,i_1+13
	ld	(_gp_gen),hl
	call	_print_message
	ld	hl,4 % 256	;const
	ld	a,l
	ld	(_bs),a
.i_51
	ld	hl,2 % 256	;const
	push	hl
	call	_beep_fx
	pop	bc
	ld	hl,3 % 256	;const
	push	hl
	call	_beep_fx
	pop	bc
.i_49
	ld	hl,(_bs)
	ld	h,0
	dec	hl
	ld	a,l
	ld	(_bs),a
	ld	a,h
	or	l
	jp	nz,i_51
.i_50
	ld	hl,10 % 256	;const
	push	hl
	call	_beep_fx
	pop	bc
	ret



._process_tile
	ld	hl,(_x0)
	ld	h,0
	ld	a,l
	ld	(_cx1),a
	ld	hl,(_y0)
	ld	h,0
	ld	a,l
	ld	(_cy1),a
	call	_qtile
	ld	de,15	;const
	ex	de,hl
	call	l_eq
	jp	nc,i_53
	ld	a,(_p_keys)
	and	a
	jr	nz,i_54_i_53
.i_53
	jp	i_52
.i_54_i_53
	ld	hl,(_x0)
	ld	h,0
	ld	a,l
	ld	(__x),a
	ld	hl,(_y0)
	ld	h,0
	ld	a,l
	ld	(__y),a
	ld	a,#(0 % 256 % 256)
	ld	(__n),a
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(__t),a
	call	_update_tile
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_gpit),a
	jp	i_57
.i_55
	ld	hl,_gpit
	ld	a,(hl)
	inc	(hl)
.i_57
	ld	a,(_gpit)
	cp	#(32 % 256)
	jp	z,i_56
	jp	nc,i_56
	ld	hl,_bolts
	push	hl
	ld	hl,(_gpit)
	ld	h,0
	add	hl,hl
	add	hl,hl
	pop	de
	add	hl,de
	inc	hl
	ld	a,(_x0)
	cp	(hl)
	jp	nz,i_59
	ld	hl,_bolts
	push	hl
	ld	hl,(_gpit)
	ld	h,0
	add	hl,hl
	add	hl,hl
	pop	de
	add	hl,de
	inc	hl
	inc	hl
	ld	a,(_y0)
	cp	(hl)
	jp	nz,i_59
	ld	hl,_bolts
	push	hl
	ld	hl,(_gpit)
	ld	h,0
	add	hl,hl
	add	hl,hl
	pop	de
	add	hl,de
	ld	a,(_n_pant)
	cp	(hl)
	jr	z,i_60_i_59
.i_59
	jp	i_58
.i_60_i_59
	ld	hl,_bolts
	push	hl
	ld	hl,(_gpit)
	ld	h,0
	add	hl,hl
	add	hl,hl
	pop	de
	add	hl,de
	inc	hl
	inc	hl
	inc	hl
	ld	(hl),#(0 % 256 % 256)
	ld	l,(hl)
	ld	h,0
	jp	i_56
.i_58
	jp	i_55
.i_56
	ld	hl,_p_keys
	ld	a,(hl)
	dec	(hl)
	ld	hl,8 % 256	;const
	push	hl
	call	_beep_fx
	pop	bc
.i_52
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
	ld	a,#(1 % 256 % 256)
	ld	(_p_facing),a
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
	ld	a,#(9 % 256 % 256)
	ld	(_p_life),a
	ld	a,#(0 % 256 % 256)
	ld	(_p_objs),a
	ld	a,#(0 % 256 % 256)
	ld	(_p_keys),a
	ld	a,#(0 % 256 % 256)
	ld	(_p_killed),a
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_p_disparando),a
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
	ld	hl,(_p_killme)
	ld	h,0
	push	hl
	call	_beep_fx
	pop	bc
	ld	a,#(2 % 256 % 256)
	ld	(_p_state),a
	ld	hl,50 % 256	;const
	ld	a,l
	ld	(_p_state_ct),a
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
	jp	z,i_61
	ld	hl,_p_vy
	call	l_gchar
	ld	de,121	;const
	ex	de,hl
	call	l_le
	jp	nc,i_62
	ld	hl,_p_vy
	call	l_gchar
	ld	bc,6
	add	hl,bc
	ld	a,l
	call	l_sxt
	ld	a,l
	ld	(_p_vy),a
	jp	i_63
.i_62
	ld	hl,127	;const
	ld	a,l
	call	l_sxt
	ld	a,l
	ld	(_p_vy),a
.i_63
.i_61
	ld	a,(_p_gotten)
	and	a
	jp	z,i_64
	ld	hl,0	;const
	ld	a,l
	call	l_sxt
	ld	a,l
	ld	(_p_vy),a
.i_64
	ld	hl,(_p_y)
	push	hl
	ld	hl,_p_vy
	call	l_gchar
	pop	de
	add	hl,de
	ld	(_p_y),hl
	xor	a
	or	h
	jp	p,i_65
	ld	hl,0	;const
	ld	(_p_y),hl
.i_65
	ld	hl,(_p_y)
	ld	de,2304	;const
	ex	de,hl
	call	l_gt
	jp	nc,i_66
	ld	hl,2304	;const
	ld	(_p_y),hl
.i_66
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
	jp	nz,i_67
	ld	hl,_at2
	ld	a,(hl)
	and	#(12 % 256)
	jp	z,i_69
.i_67
	ld	a,(_gpy)
	ld	e,a
	ld	d,0
	ld	hl,15	;const
	call	l_and
	ld	de,8	;const
	ex	de,hl
	call	l_ult
	jp	nc,i_69
	ld	hl,1	;const
	jr	i_70
.i_69
	ld	hl,0	;const
.i_70
	ld	h,0
	ld	a,l
	ld	(_possee),a
	ld	hl,_pad_this_frame
	ld	a,(hl)
	and	#(128 % 256)
	cp	#(0 % 256)
	ld	hl,0
	jp	nz,i_72
	inc	hl
	ld	a,(_p_jmp_on)
	cp	#(0 % 256)
	jp	nz,i_72
	ld	a,(_possee)
	and	a
	jp	nz,i_73
	ld	a,(_p_gotten)
	and	a
	jp	z,i_72
.i_73
	jr	i_75_i_72
.i_72
	jp	i_71
.i_75_i_72
	ld	a,#(1 % 256 % 256)
	ld	(_p_jmp_on),a
	ld	a,#(0 % 256 % 256)
	ld	(_p_jmp_ct),a
	ld	hl,1 % 256	;const
	push	hl
	call	_beep_fx
	pop	bc
.i_71
	ld	hl,_pad0
	ld	a,(hl)
	and	#(128 % 256)
	cp	#(0 % 256)
	ld	hl,0
	jp	nz,i_77
	inc	hl
	ld	a,(_p_jmp_on)
	and	a
	jr	nz,i_78_i_77
.i_77
	jp	i_76
.i_78_i_77
	ld	hl,_p_vy
	call	l_gchar
	push	hl
	ld	a,(_p_jmp_ct)
	ld	e,a
	ld	d,0
	ld	l,#(1 % 256)
	call	l_asr_u
	ld	de,20
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
	ld	de,65456	;const
	ex	de,hl
	call	l_lt
	jp	nc,i_79
	ld	hl,65456	;const
	ld	a,l
	call	l_sxt
	ld	a,l
	ld	(_p_vy),a
.i_79
	ld	hl,_p_jmp_ct
	ld	a,(hl)
	inc	(hl)
	ld	a,(_p_jmp_ct)
	cp	#(8 % 256)
	jp	nz,i_80
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_p_jmp_on),a
.i_80
.i_76
	ld	a,(_pad0)
	ld	e,a
	ld	d,0
	ld	hl,128	;const
	call	l_and
	ld	de,0	;const
	ex	de,hl
	call	l_eq
	ccf
	jp	nc,i_81
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_p_jmp_on),a
.i_81
	ld	a,(_pad0)
	ld	e,a
	ld	d,0
	ld	hl,4	;const
	call	l_and
	ld	de,0	;const
	ex	de,hl
	call	l_eq
	jp	c,i_82
	ld	a,(_pad0)
	ld	e,a
	ld	d,0
	ld	hl,8	;const
	call	l_and
	ld	de,0	;const
	ex	de,hl
	call	l_eq
	jp	c,i_82
	ld	hl,0	;const
	jr	i_83
.i_82
	ld	hl,1	;const
.i_83
	ld	h,0
	ld	a,l
	ld	(_rda),a
	ld	hl,(_rda)
	ld	h,0
	call	l_lneg
	jp	nc,i_84
	ld	hl,_p_vx
	call	l_gchar
	xor	a
	or	h
	jp	m,i_85
	or	l
	jp	z,i_85
	ld	hl,_p_vx
	call	l_gchar
	ld	bc,-4
	add	hl,bc
	ld	a,l
	call	l_sxt
	ld	a,l
	ld	(_p_vx),a
	ld	hl,_p_vx
	call	l_gchar
	xor	a
	or	h
	jp	p,i_86
	ld	hl,0	;const
	ld	a,l
	call	l_sxt
	ld	a,l
	ld	(_p_vx),a
.i_86
	jp	i_87
.i_85
	ld	hl,_p_vx
	call	l_gchar
	xor	a
	or	h
	jp	p,i_88
	ld	hl,_p_vx
	call	l_gchar
	ld	bc,4
	add	hl,bc
	ld	a,l
	call	l_sxt
	ld	a,l
	ld	(_p_vx),a
	ld	hl,_p_vx
	call	l_gchar
	xor	a
	or	h
	jp	m,i_89
	or	l
	jp	z,i_89
	ld	hl,0	;const
	ld	a,l
	call	l_sxt
	ld	a,l
	ld	(_p_vx),a
.i_89
.i_88
.i_87
.i_84
	ld	hl,_pad0
	ld	a,(hl)
	and	#(4 % 256)
	jp	nz,i_90
	ld	hl,_p_vx
	call	l_gchar
	ld	de,65488	;const
	ex	de,hl
	call	l_gt
	jp	nc,i_91
	ld	a,#(0 % 256 % 256)
	ld	(_p_facing),a
	ld	hl,_p_vx
	call	l_gchar
	ld	bc,-6
	add	hl,bc
	ld	a,l
	call	l_sxt
	ld	a,l
	ld	(_p_vx),a
.i_91
.i_90
	ld	hl,_pad0
	ld	a,(hl)
	and	#(8 % 256)
	jp	nz,i_92
	ld	hl,_p_vx
	call	l_gchar
	ld	de,48	;const
	ex	de,hl
	call	l_lt
	jp	nc,i_93
	ld	hl,_p_vx
	call	l_gchar
	ld	bc,6
	add	hl,bc
	ld	a,l
	call	l_sxt
	ld	a,l
	ld	(_p_vx),a
	ld	hl,1 % 256	;const
	ld	a,l
	ld	(_p_facing),a
.i_93
.i_92
	ld	hl,(_p_x)
	push	hl
	ld	hl,_p_vx
	call	l_gchar
	pop	de
	add	hl,de
	ld	(_p_x),hl
	ld	a,(_p_gotten)
	and	a
	jp	z,i_94
	ld	hl,(_p_x)
	push	hl
	ld	hl,_ptgmx
	call	l_gchar
	pop	de
	add	hl,de
	ld	(_p_x),hl
.i_94
	ld	hl,(_p_x)
	xor	a
	or	h
	jp	p,i_95
	ld	hl,0	;const
	ld	(_p_x),hl
.i_95
	ld	hl,(_p_x)
	ld	de,3584	;const
	ex	de,hl
	call	l_gt
	jp	nc,i_96
	ld	hl,3584	;const
	ld	(_p_x),hl
.i_96
	ld	hl,(_p_x)
	ex	de,hl
	ld	l,#(4 % 256)
	call	l_asr
	ld	h,0
	ld	a,l
	ld	(_gpx),a
	call _player_calc_bounding_box
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
	ld	hl,(_p_x)
	ex	de,hl
	ld	l,#(4 % 256)
	call	l_asr
	ld	h,0
	ld	a,l
	ld	(_gpx),a
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
	ld	a,(_wall_h)
	cp	#(3 % 256)
	jp	nz,i_97
	ld	hl,(_gpx)
	ld	h,0
	inc	hl
	inc	hl
	inc	hl
	ex	de,hl
	ld	l,#(4 % 256)
	call	l_asr_u
	ld	h,0
	ld	a,l
	ld	(_cx1),a
	call	_attr
	ld	de,10	;const
	ex	de,hl
	call	l_eq
	jp	nc,i_98
	ld	hl,(_cy1)
	ld	h,0
	ld	a,l
	ld	(_y1),a
	ld	h,0
	ld	a,l
	ld	(_y0),a
	ld	hl,(_cx1)
	ld	h,0
	ld	a,l
	ld	(_x0),a
	ld	hl,(_cx1)
	ld	h,0
	dec	hl
	ld	h,0
	ld	a,l
	ld	(_x1),a
	call	_process_tile
.i_98
	jp	i_99
.i_97
	ld	a,(_wall_h)
	cp	#(4 % 256)
	jp	nz,i_100
	ld	hl,(_gpx)
	ld	h,0
	ld	bc,12
	add	hl,bc
	ex	de,hl
	ld	l,#(4 % 256)
	call	l_asr_u
	ld	h,0
	ld	a,l
	ld	(_cx1),a
	call	_attr
	ld	de,10	;const
	ex	de,hl
	call	l_eq
	jp	nc,i_101
	ld	hl,(_cy1)
	ld	h,0
	ld	a,l
	ld	(_y1),a
	ld	h,0
	ld	a,l
	ld	(_y0),a
	ld	hl,(_cx1)
	ld	h,0
	ld	a,l
	ld	(_x0),a
	ld	hl,(_cx1)
	ld	h,0
	inc	hl
	ld	h,0
	ld	a,l
	ld	(_x1),a
	call	_process_tile
.i_101
.i_100
.i_99
	ld	a,(_hit_v)
	and	a
	jp	z,i_102
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
	ld	hl,(_p_y)
	ld	de,65280	;const
	ex	de,hl
	call	l_and
	ld	(_p_y),hl
	ld	a,(_gpy)
	ld	e,a
	ld	d,0
	ld	hl,240	;const
	call	l_and
	ld	h,0
	ld	a,l
	ld	(_gpy),a
	ld	a,(_p_life)
	cp	#(0 % 256)
	jp	z,i_104
	jp	c,i_104
	ld	a,(_p_state)
	cp	#(0 % 256)
	jr	z,i_105_i_104
.i_104
	jp	i_103
.i_105_i_104
	ld	hl,3 % 256	;const
	ld	a,l
	ld	(_p_killme),a
.i_103
.i_102
	ld	hl,(_possee)
	ld	h,0
	call	l_lneg
	jp	nc,i_107
	ld	hl,(_p_gotten)
	ld	h,0
	call	l_lneg
	jr	c,i_108_i_107
.i_107
	jp	i_106
.i_108_i_107
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
	jp	i_109
.i_106
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
	jp	nz,i_110
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
	jp	i_111
.i_110
	ld	hl,_p_subframe
	ld	a,(hl)
	inc	(hl)
	ld	a,(_p_subframe)
	cp	#(4 % 256)
	jp	nz,i_112
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
	call	_step
.i_112
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
.i_111
.i_109
	ret



._enems_init
	ld	a,(_do_respawn)
	and	a
	jp	z,i_113
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_gpit),a
	jp	i_116
.i_114
	ld	hl,_gpit
	ld	a,(hl)
	inc	(hl)
.i_116
	ld	a,(_gpit)
	cp	#(3 % 256)
	jp	z,i_115
	jp	nc,i_115
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
	jp	z,i_118
	ld	a,(_gpt)
	cp	#(16 % 256)
	jp	z,i_118
	jr	c,i_119_i_118
.i_118
	jp	i_117
.i_119_i_118
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
.i_122
	ld	a,l
.i_123
.i_121
.i_117
	jp	i_114
.i_115
.i_113
	ret



._enems_move_spr_abs
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
	jp	i_126
.i_124
	ld	hl,(_enit)
	ld	h,0
	inc	hl
	ld	a,l
	ld	(_enit),a
.i_126
	ld	a,(_enit)
	cp	#(3 % 256)
	jp	z,i_125
	jp	nc,i_125
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
	jp	nz,i_127
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
	jp	i_128
.i_127
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
	jp	nc,i_129
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
.i_129
	ld	hl,(_gpt)
	ld	h,0
.i_132
	ld	a,l
	cp	#(1% 256)
	jp	z,i_133
	cp	#(8% 256)
	jp	z,i_134
	jp	i_135
.i_133
	ld	hl,1 % 256	;const
	ld	a,l
	ld	(_killable),a
.i_134
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
	jr nz, _enems_lm_change_axis_x_done
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
	jr nz, _enems_lm_change_axis_y_done
	._enems_lm_change_axis_y
	ld a, (__en_my)
	neg
	ld (__en_my), a
	._enems_lm_change_axis_y_done
	jp	i_131
.i_135
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
.i_131
	ld	a,(_active)
	and	a
	jp	z,i_136
	ld	a,(_animate)
	and	a
	jp	z,i_137
	ld	hl,__en_mx
	call	l_gchar
	ld	a,h
	or	l
	jp	z,i_138
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
	jp	i_139
.i_138
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
.i_139
	ld	h,0
	ld	a,l
	ld	(_gpjt),a
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
.i_137
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
	add 12
	cp c
	jr c, _enems_collision_skip
	ld a, (_gpx)
	ld c, a
	ld a, (__en_x)
	add 12
	cp c
	jr c, _enems_collision_skip
	ld a, (__en_y)
	ld c, a
	ld a, (_gpy)
	add 12
	cp c
	jr c, _enems_collision_skip
	ld a, (_gpy)
	ld c, a
	ld a, (__en_y)
	add 12
	cp c
	jr c, _enems_collision_skip
	ld	a,(_p_life)
	and	a
	jp	z,i_140
	ld	hl,1 % 256	;const
	ld	a,l
	ld	(_tocado),a
.i_140
	ld	hl,2 % 256	;const
	ld	a,l
	ld	(_p_killme),a
	._enems_collision_skip
.i_136
.i_128
.i_141
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
	jp	i_124
.i_125
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
	._draw_scr_get_scr_address
	ld a, (_n_pant)
	sla a
	ld d, 0
	ld e, a
	ld hl, _map
	add hl, de ; HL = map + (n_pant << 1)
	ld e, (hl)
	inc hl
	ld d, (hl) ; DE = index
	ld hl, _map
	add hl, de ; HL = map + index
	ld (_map_pointer), hl
	._draw_scr_rle
	xor a
	ld (_gpit), a
	ld a, 1
	ld (__x), a
	ld a, 2
	ld (__y), a
	._draw_scr_loop
	ld a, (_gpit)
	cp 150
	jr z, _draw_scr_loop_done
	ld hl, (_map_pointer)
	ld a, (hl)
	inc hl
	ld (_map_pointer), hl
	ld c, a
	and 0x0f
	ld (_gpt), a
	ld (_gpd), a
	ld a, c
	ld (_gpc), a
	._draw_scr_advance_loop
	ld a, (_gpc)
	cp 0x10
	jr c, _draw_scr_advance_loop_done
	sub 0x10
	ld (_gpc), a
	call _advance_worm
	jr _draw_scr_advance_loop
	._draw_scr_advance_loop_done
	call _advance_worm
	jr _draw_scr_loop
	._draw_scr_loop_done
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
	jr nz, _hotspots_setup_do
	call _rand
	ld a, l
	and 7
	cp 2
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
	ld a, c
	or a
	jr z, _hotspots_setup_set_refill
	ld a, b
	jp _hotspots_setup_set
	._hotspots_setup_set_refill
	xor a
	._hotspots_setup_set
	add 16
	ld (__t), a
	call _draw_coloured_tile_gamearea
	._hotspots_setup_done
	ld hl, _bolts
	ld b, 32
	._open_locks_loop
	push bc
	ld a, (_n_pant)
	ld c, a
	ld a, (hl)
	inc hl
	cp c
	jr nz, _open_locks_done
	ld a, (hl)
	inc hl
	ld d, a
	ld a, (hl)
	inc hl
	ld e, a
	ld a, (hl)
	inc hl
	or a
	jr nz, _open_locks_done
	._open_locks_do
	ld a, d
	ld (__x), a
	ld a, e
	ld (__y), a
	sla a
	sla a
	sla a
	sla a
	sub e
	add d
	ld b, 0
	ld c, a
	xor a
	push hl
	ld hl, _map_attr
	add hl, bc
	ld (hl), a
	ld hl, _map_buff
	add hl, bc
	ld (hl), a
	ld (__t), a
	call _draw_coloured_tile_gamearea
	pop hl
	._open_locks_done
	pop bc
	dec b
	jr nz, _open_locks_loop
	ret



._draw_scr
	ld	a,#(1 % 256 % 256)
	ld	(_is_rendering),a
	ld	a,(_no_draw)
	and	a
	jp	z,i_142
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_no_draw),a
	jp	i_143
.i_142
	call	_draw_scr_background
.i_143
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
	jp	nc,i_144
	call	_draw_objs
	ld	hl,(_p_objs)
	ld	h,0
	ld	a,l
	ld	(_objs_old),a
.i_144
	ld	hl,(_p_life)
	ld	h,0
	ex	de,hl
	ld	hl,(_life_old)
	ld	h,0
	call	l_ne
	jp	nc,i_145
	ld	a,#(6 % 256 % 256)
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
.i_145
	ret



._flick_screen
	ld	hl,(_p_x)
	ld	de,0	;const
	call	l_eq
	jp	nc,i_147
	ld	hl,_p_vx
	call	l_gchar
	ld	de,0	;const
	ex	de,hl
	call	l_lt
	jp	nc,i_147
	ld	a,(_x_pant)
	cp	#(0 % 256)
	jp	z,i_147
	jp	c,i_147
	jr	i_148_i_147
.i_147
	jp	i_146
.i_148_i_147
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
	jp	i_149
.i_146
	ld	hl,(_p_x)
	ld	de,3584	;const
	call	l_eq
	jp	nc,i_151
	ld	hl,_p_vx
	call	l_gchar
	ld	de,0	;const
	ex	de,hl
	call	l_gt
	jp	nc,i_151
	ld	hl,(_x_pant)
	ld	h,0
	push	hl
	ld	hl,(_level_data)
	ld	h,0
	dec	hl
	pop	de
	call	l_ult
	jr	c,i_152_i_151
.i_151
	jp	i_150
.i_152_i_151
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
.i_150
.i_149
	ld	hl,(_p_y)
	ld	de,0	;const
	call	l_eq
	jp	nc,i_154
	ld	hl,_p_vy
	call	l_gchar
	ld	de,0	;const
	ex	de,hl
	call	l_lt
	jp	nc,i_154
	ld	a,(_y_pant)
	cp	#(0 % 256)
	jp	z,i_154
	jp	c,i_154
	jr	i_155_i_154
.i_154
	jp	i_153
.i_155_i_154
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
	ld	de,65456	;const
	ex	de,hl
	call	l_gt
	jp	nc,i_156
	ld	hl,65456	;const
	ld	a,l
	call	l_sxt
	ld	a,l
	ld	(_p_vy),a
.i_156
	jp	i_157
.i_153
	ld	hl,(_p_y)
	ld	de,2304	;const
	call	l_eq
	jp	nc,i_159
	ld	hl,_p_vy
	call	l_gchar
	ld	de,0	;const
	ex	de,hl
	call	l_gt
	jp	nc,i_159
	ld	hl,(_y_pant)
	ld	h,0
	push	hl
	ld	hl,(_level_data+1)
	ld	h,0
	dec	hl
	pop	de
	call	l_ult
	jr	c,i_160_i_159
.i_159
	jp	i_158
.i_160_i_159
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
.i_158
.i_157
	ret



._hide_sprites
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	a,h
	or	l
	jp	nz,i_161
	ld ix, (_sp_player)
	ld iy, vpClipStruct
	ld bc, 0
	ld hl, 0xdede
	ld de, 0
	call SPMoveSprAbs
.i_161
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
	ld	hl,40 % 256	;const
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
.i_164
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
.i_162
	ld	hl,(_gpit)
	ld	h,0
	ld	a,h
	or	l
	jp	nz,i_164
.i_163
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
	jp	i_167
.i_165
	ld	hl,_gpit
	ld	a,(hl)
	inc	(hl)
.i_167
	ld	a,(_gpit)
	cp	#(3 % 256)
	jp	z,i_166
	jp	nc,i_166
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
	jp	i_165
.i_166
	ei
	call	_cortina
.i_168
	call	sp_UpdateNow
	ld	hl,_s_title
	push	hl
	ld	hl,16384	;const
	push	hl
	call	_unpack
	pop	bc
	pop	bc
	call	_select_joyfunc
	ld	a,#(1 % 256 % 256)
	ld	(_mlplaying),a
	ld	a,#(0 % 256 % 256)
	ld	(_silent_level),a
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_level),a
.i_170
	ld	hl,(_mlplaying)
	ld	h,0
	ld	a,h
	or	l
	jp	z,i_171
	call	_prepare_level
	ld	hl,(_silent_level)
	ld	h,0
	call	l_lneg
	jp	nc,i_172
	call	_blackout_area
	ld	a,#(12 % 256 % 256)
	ld	(__x),a
	ld	a,#(12 % 256 % 256)
	ld	(__y),a
	ld	a,#(71 % 256 % 256)
	ld	(__t),a
	ld	hl,i_1+26
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
	ld	hl,250	;const
	push	hl
	call	_active_sleep
	pop	bc
.i_172
	ld	a,#(0 % 256 % 256)
	ld	(_silent_level),a
	ld	hl,1 % 256	;const
	ld	a,l
	ld	(_playing),a
	call	_player_init
	ld	a,#(0 % 256 % 256)
	ld	(_maincounter),a
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
	ld	a,#(0 % 256 % 256)
	ld	(_success),a
	ld	a,#(255 % 256 % 256)
	ld	(_o_pant),a
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_no_draw),a
.i_173
	ld	hl,(_playing)
	ld	h,0
	ld	a,h
	or	l
	jp	z,i_174
	call	_read_controller
	ld	hl,(_n_pant)
	ld	h,0
	ex	de,hl
	ld	hl,(_o_pant)
	ld	h,0
	call	l_ne
	jp	nc,i_175
	ld	hl,(_n_pant)
	ld	h,0
	ld	a,l
	ld	(_o_pant),a
	call	_draw_scr
.i_175
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
	call	_enems_move
	ld	a,(_p_state)
	ld	e,a
	ld	d,0
	ld	hl,2	;const
	call	l_and
	ld	de,0	;const
	ex	de,hl
	call	l_eq
	jp	c,i_177
	ld	a,(_half_life)
	cp	#(0 % 256)
	jp	nz,i_176
.i_177
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
	jp	i_179
.i_176
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
.i_179
	ld	hl,(_p_n_f)
	ld	(_p_c_f),hl
.i_180
	ld	a,(_isrc)
	ld	e,a
	ld	d,0
	ld	hl,2	;const
	call	l_ult
	jp	nc,i_181
	halt
	jp	i_180
.i_181
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_isrc),a
	call	sp_UpdateNow
	ld	a,(_p_state)
	and	a
	jp	z,i_182
	ld	hl,_p_state_ct
	ld	a,(hl)
	dec	(hl)
	ld	a,(_p_state_ct)
	and	a
	jp	nz,i_183
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_p_state),a
.i_183
.i_182
	ld a, (_hotspot_x)
	ld c, a
	ld a, (_gpx)
	add 12
	cp c
	jp c, _hotspots_skip
	ld a, (_gpx)
	ld c, a
	ld a, (_hotspot_x)
	add 12
	cp c
	jp c, _hotspots_skip
	ld a, (_hotspot_y)
	ld c, a
	ld a, (_gpy)
	add 12
	cp c
	jp c, _hotspots_skip
	ld a, (_gpy)
	ld c, a
	ld a, (_hotspot_y)
	add 12
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
	jp	nz,i_184
	ld	hl,(_p_life)
	ld	h,0
	inc	hl
	ld	h,0
	ld	a,l
	ld	(_p_life),a
	cp	#(9 % 256)
	jp	z,i_185
	jp	c,i_185
	ld	hl,9 % 256	;const
	ld	a,l
	ld	(_p_life),a
.i_185
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
	ld	(hl),#(2 % 256 % 256)
	ld	hl,7 % 256	;const
	push	hl
	call	_beep_fx
	pop	bc
	jp	i_186
.i_184
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
.i_189
	ld	a,l
	cp	#(1% 256)
	jp	z,i_190
	cp	#(2% 256)
	jp	z,i_191
	jp	i_188
.i_190
	ld	hl,_p_objs
	ld	a,(hl)
	inc	(hl)
	ld	hl,6 % 256	;const
	push	hl
	call	_beep_fx
	pop	bc
	jp	i_188
.i_191
	ld	hl,_p_keys
	ld	a,(hl)
	inc	(hl)
	ld	hl,6 % 256	;const
	push	hl
	call	_beep_fx
	pop	bc
.i_188
.i_186
	ld	a,(_gpit)
	and	a
	jp	nz,i_192
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
	jp	i_193
.i_192
	ld	hl,2 % 256	;const
	push	hl
	call	_beep_fx
	pop	bc
.i_193
	ld	hl,240 % 256	;const
	ld	a,l
	ld	(_hotspot_y),a
	._hotspots_skip
	ld	a,(_level_data+7)
	cp	#(0 % 256)
	jp	nz,i_195
	ld	hl,(_p_objs)
	ld	h,0
	ex	de,hl
	ld	hl,(_level_data+5)
	ld	h,0
	call	l_eq
	jp	c,i_197
.i_195
	jr	i_195_i_196
.i_196
	ld	a,h
	or	l
	jp	nz,i_197
.i_195_i_196
	ld	a,(_level_data+7)
	cp	#(1 % 256)
	jp	nz,i_198
	ld	hl,(_n_pant)
	ld	h,0
	ex	de,hl
	ld	hl,(_level_data+8)
	ld	h,0
	call	l_eq
	jp	nc,i_198
	ld	hl,1	;const
	jr	i_199
.i_198
	ld	hl,0	;const
.i_199
	ld	a,h
	or	l
	jp	nz,i_197
	jr	i_200
.i_197
	ld	hl,1	;const
.i_200
	ld	a,h
	or	l
	jp	z,i_194
	ld	a,#(1 % 256 % 256)
	ld	(_success),a
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_playing),a
.i_194
	ld	a,(_p_life)
	and	a
	jp	nz,i_201
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_playing),a
.i_201
	ld	hl,(_p_killme)
	ld	h,0
	ld	a,h
	or	l
	jp	z,i_202
	call	_player_kill
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_p_killme),a
.i_202
	call	_flick_screen
	jp	i_173
.i_174
	ld	hl,0 % 256	;const
	push	hl
	call	_hide_sprites
	pop	bc
	call	sp_UpdateNow
	ld	hl,(_success)
	ld	h,0
.i_205
	ld	a,l
	cp	#(0% 256)
	jp	z,i_206
	cp	#(1% 256)
	jp	z,i_207
	jp	i_204
.i_206
	ld	hl,i_1+13
	ld	(_gp_gen),hl
	call	_print_message
	ld	a,#(0 % 256 % 256)
	ld	(_mlplaying),a
	ld	hl,250	;const
	push	hl
	call	_active_sleep
	pop	bc
	jp	i_204
.i_207
	ld	hl,i_1+32
	ld	(_gp_gen),hl
	call	_print_message
	ld	hl,_level
	ld	a,(hl)
	inc	(hl)
	ld	hl,250	;const
	push	hl
	call	_active_sleep
	pop	bc
.i_204
	ld	a,(_level)
	ld	e,a
	ld	d,0
	ld	hl,2	;const
	call	l_eq
	jp	nc,i_208
	call	_game_ending
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_mlplaying),a
.i_208
	jp	i_170
.i_171
	call	_cortina
	jp	i_168
.i_169
	ret


	; *****************************************************************************
	; * Phaser1 Engine, with synthesised drums
	; *
	; * Original code by Shiru - .http
	; * Modified by Chris Cowley
	; *
	; * Produced by Beepola v1.05.01
	; ******************************************************************************
	.musicstart
	LD HL,MUSICDATA ; <- Pointer to Music Data. Change
	; this to play a different song
	LD A,(HL) ; Get the loop start pointer
	LD (PATTERN_LOOP_BEGIN),A
	INC HL
	LD A,(HL) ; Get the song end pointer
	LD (PATTERN_LOOP_END),A
	INC HL
	LD E,(HL)
	INC HL
	LD D,(HL)
	INC HL
	LD (INSTRUM_TBL),HL
	LD (CURRENT_INST),HL
	ADD HL,DE
	LD (PATTERN_ADDR),HL
	XOR A
	LD (PATTERN_PTR),A ; Set the pattern pointer to zero
	LD H,A
	LD L,A
	LD (NOTE_PTR),HL ; Set the note offset (within this pattern) to 0
	.player
	DI
	PUSH IY
	;LD A,BORDER_COL
	xor a
	LD H,$00
	LD L,A
	LD (CNT_1A),HL
	LD (CNT_1B),HL
	LD (DIV_1A),HL
	LD (DIV_1B),HL
	LD (CNT_2),HL
	LD (DIV_2),HL
	LD (OUT_1),A
	LD (OUT_2),A
	JR MAIN_LOOP
	; ********************************************************************************************************
	; * NEXT_PATTERN
	; *
	; * Select the next pattern in sequence (and handle looping if weve reached PATTERN_LOOP_END
	; * Execution falls through to PLAYNOTE to play the first note from our next pattern
	; ********************************************************************************************************
	.next_pattern
	LD A,(PATTERN_PTR)
	INC A
	INC A
	DEFB $FE ; CP n
	.pattern_loop_end DEFB 0
	JR NZ,NO_PATTERN_LOOP
	; Handle Pattern Looping at and of song
	DEFB $3E ; LD A,n
	.pattern_loop_begin DEFB 0
	.no_pattern_loop LD (PATTERN_PTR),A
	LD HL,$0000
	LD (NOTE_PTR),HL ; Start of pattern (NOTE_PTR = 0)
	.main_loop
	LD IYL,0 ; Set channel = 0
	.read_loop
	LD HL,(PATTERN_ADDR)
	LD A,(PATTERN_PTR)
	LD E,A
	LD D,0
	ADD HL,DE
	LD E,(HL)
	INC HL
	LD D,(HL) ; Now DE = Start of Pattern data
	LD HL,(NOTE_PTR)
	INC HL ; Increment the note pointer and...
	LD (NOTE_PTR),HL ; ..store it
	DEC HL
	ADD HL,DE ; Now HL = address of note data
	LD A,(HL)
	OR A
	JR Z,NEXT_PATTERN ; select next pattern
	BIT 7,A
	JP Z,RENDER ; Play the currently defined note(S) and drum
	LD IYH,A
	AND $3F
	CP $3C
	JP NC,OTHER ; Other parameters
	ADD A,A
	LD B,0
	LD C,A
	LD HL,FREQ_TABLE
	ADD HL,BC
	LD E,(HL)
	INC HL
	LD D,(HL)
	LD A,IYL ; IYL = 0 for channel 1, or = 1 for channel 2
	OR A
	JR NZ,SET_NOTE2
	LD (DIV_1A),DE
	EX DE,HL
	DEFB $DD,$21 ; LD IX,nn
	.current_inst
	DEFW $0000
	LD A,(IX+$00)
	OR A
	JR Z,L809B ; Original code jumps into byte 2 of the DJNZ (invalid opcode FD)
	LD B,A
	.l8098 ADD HL,HL
	DJNZ L8098
	.l809b LD E,(IX+$01)
	LD D,(IX+$02)
	ADD HL,DE
	LD (DIV_1B),HL
	LD IYL,1 ; Set channel = 1
	LD A,IYH
	AND $40
	JR Z,READ_LOOP ; No phase reset
	LD HL,OUT_1 ; Reset phaser
	RES 4,(HL)
	LD HL,$0000
	LD (CNT_1A),HL
	LD H,(IX+$03)
	LD (CNT_1B),HL
	JR READ_LOOP
	.set_note2
	LD (DIV_2),DE
	LD A,IYH
	LD HL,OUT_2
	RES 4,(HL)
	LD HL,$0000
	LD (CNT_2),HL
	JP READ_LOOP
	.set_stop
	LD HL,$0000
	LD A,IYL
	OR A
	JR NZ,SET_STOP2
	; Stop channel 1 note
	LD (DIV_1A),HL
	LD (DIV_1B),HL
	LD HL,OUT_1
	RES 4,(HL)
	LD IYL,1
	JP READ_LOOP
	.set_stop2
	; Stop channel 2 note
	LD (DIV_2),HL
	LD HL,OUT_2
	RES 4,(HL)
	JP READ_LOOP
	.other CP $3C
	JR Z,SET_STOP ; Stop note
	CP $3E
	JR Z,SKIP_CH1 ; No changes to channel 1
	INC HL ; Instrument change
	LD L,(HL)
	LD H,$00
	ADD HL,HL
	LD DE,(NOTE_PTR)
	INC DE
	LD (NOTE_PTR),DE ; Increment the note pointer
	DEFB $01 ; LD BC,nn
	.instrum_tbl
	DEFW $0000
	ADD HL,BC
	LD (CURRENT_INST),HL
	JP READ_LOOP
	.skip_ch1
	LD IYL,$01
	JP READ_LOOP
	.exit_player
	LD HL,$2758
	EXX
	POP IY
	EI
	RET
	.render
	AND $7F ; L813A
	CP $76
	JP NC,DRUMS
	LD D,A
	EXX
	DEFB $21 ; LD HL,nn
	.cnt_1a DEFW $0000
	DEFB $DD,$21 ; LD IX,nn
	.cnt_1b DEFW $0000
	DEFB $01 ; LD BC,nn
	.div_1a DEFW $0000
	DEFB $11 ; LD DE,nn
	.div_1b DEFW $0000
	DEFB $3E ; LD A,n
	.out_1 DEFB $0
	EXX
	EX AF,AF ; beware!
	DEFB $21 ; LD HL,nn
	.cnt_2 DEFW $0000
	DEFB $01 ; LD BC,nn
	.div_2 DEFW $0000
	DEFB $3E ; LD A,n
	.out_2 DEFB $00
	.play_note
	; Read keyboard
	LD E,A
	XOR A
	IN A,($FE)
	OR $E0
	INC A
	.player_wait_key
	JR NZ,EXIT_PLAYER
	LD A,E
	LD E,0
	.l8168 EXX
	EX AF,AF ; beware!
	ADD HL,BC
	OUT ($FE),A
	JR C,L8171
	JR L8173
	.l8171 XOR $10
	.l8173 ADD IX,DE
	JR C,L8179
	JR L817B
	.l8179 XOR $10
	.l817b EX AF,AF ; beware!
	OUT ($FE),A
	EXX
	ADD HL,BC
	JR C,L8184
	JR L8186
	.l8184 XOR $10
	.l8186 NOP
	JP L818A
	.l818a EXX
	EX AF,AF ; beware!
	ADD HL,BC
	OUT ($FE),A
	JR C,L8193
	JR L8195
	.l8193 XOR $10
	.l8195 ADD IX,DE
	JR C,L819B
	JR L819D
	.l819b XOR $10
	.l819d EX AF,AF ; beware!
	OUT ($FE),A
	EXX
	ADD HL,BC
	JR C,L81A6
	JR L81A8
	.l81a6 XOR $10
	.l81a8 NOP
	JP L81AC
	.l81ac EXX
	EX AF,AF ; beware!
	ADD HL,BC
	OUT ($FE),A
	JR C,L81B5
	JR L81B7
	.l81b5 XOR $10
	.l81b7 ADD IX,DE
	JR C,L81BD
	JR L81BF
	.l81bd XOR $10
	.l81bf EX AF,AF ; beware!
	OUT ($FE),A
	EXX
	ADD HL,BC
	JR C,L81C8
	JR L81CA
	.l81c8 XOR $10
	.l81ca NOP
	JP L81CE
	.l81ce EXX
	EX AF,AF ; beware!
	ADD HL,BC
	OUT ($FE),A
	JR C,L81D7
	JR L81D9
	.l81d7 XOR $10
	.l81d9 ADD IX,DE
	JR C,L81DF
	JR L81E1
	.l81df XOR $10
	.l81e1 EX AF,AF ; beware!
	OUT ($FE),A
	EXX
	ADD HL,BC
	JR C,L81EA
	JR L81EC
	.l81ea XOR $10
	.l81ec DEC E
	JP NZ,L8168
	EXX
	EX AF,AF ; beware!
	ADD HL,BC
	OUT ($FE),A
	JR C,L81F9
	JR L81FB
	.l81f9 XOR $10
	.l81fb ADD IX,DE
	JR C,L8201
	JR L8203
	.l8201 XOR $10
	.l8203 EX AF,AF ; beware!
	OUT ($FE),A
	EXX
	ADD HL,BC
	JR C,L820C
	JR L820E
	.l820c XOR $10
	.l820e DEC D
	JP NZ,PLAY_NOTE
	LD (CNT_2),HL
	LD (OUT_2),A
	EXX
	EX AF,AF ; beware!
	LD (CNT_1A),HL
	LD (CNT_1B),IX
	LD (OUT_1),A
	JP MAIN_LOOP
	; ************************************************************
	; * DRUMS - Synthesised
	; ************************************************************
	.drums
	ADD A,A ; On entry A=$75+Drum number (i.e. $76 to $7E)
	LD B,0
	LD C,A
	LD HL,DRUM_TABLE - 236
	ADD HL,BC
	LD E,(HL)
	INC HL
	LD D,(HL)
	EX DE,HL
	JP (HL)
	.drum_tone1 LD L,16
	JR DRUM_TONE
	.drum_tone2 LD L,12
	JR DRUM_TONE
	.drum_tone3 LD L,8
	JR DRUM_TONE
	.drum_tone4 LD L,6
	JR DRUM_TONE
	.drum_tone5 LD L,4
	JR DRUM_TONE
	.drum_tone6 LD L,2
	.drum_tone
	LD DE,3700
	LD BC,$0101
	xor a
	.dt_loop0 OUT ($FE),A
	DEC B
	JR NZ,DT_LOOP1
	XOR 16
	LD B,C
	EX AF,AF ; beware!
	LD A,C
	ADD A,L
	LD C,A
	EX AF,AF ; beware!
	.dt_loop1 DEC E
	JR NZ,DT_LOOP0
	DEC D
	JR NZ,DT_LOOP0
	JP MAIN_LOOP
	.drum_noise1 LD DE,2480
	LD IXL,1
	JR DRUM_NOISE
	.drum_noise2 LD DE,1070
	LD IXL,10
	JR DRUM_NOISE
	.drum_noise3 LD DE,365
	LD IXL,101
	.drum_noise
	LD H,D
	LD L,E
	xor a
	LD C,A
	.dn_loop0 LD A,(HL)
	AND 16
	OR C
	OUT ($FE),A
	LD B,IXL
	.dn_loop1 DJNZ DN_LOOP1
	INC HL
	DEC E
	JR NZ,DN_LOOP0
	DEC D
	JR NZ,DN_LOOP0
	JP MAIN_LOOP
	.pattern_addr DEFW $0000
	.pattern_ptr DEFB 0
	.note_ptr DEFW $0000
	; **************************************************************
	; * Frequency Table
	; **************************************************************
	.freq_table
	DEFW 178,189,200,212,225,238,252,267,283,300,318,337
	DEFW 357,378,401,425,450,477,505,535,567,601,637,675
	DEFW 715,757,802,850,901,954,1011,1071,1135,1202,1274,1350
	DEFW 1430,1515,1605,1701,1802,1909,2023,2143,2270,2405,2548,2700
	DEFW 2860,3030,3211,3402,3604,3818,4046,4286,4541,4811,5097,5400
	; *****************************************************************
	; * Synth Drum Lookup Table
	; *****************************************************************
	.drum_table
	DEFW DRUM_TONE1,DRUM_TONE2,DRUM_TONE3,DRUM_TONE4,DRUM_TONE5,DRUM_TONE6
	DEFW DRUM_NOISE1,DRUM_NOISE2,DRUM_NOISE3
	.musicdata
	DEFB 0 ; Pattern loop begin * 2
	DEFB 2 ; Song length * 2
	DEFW 4 ; Offset to start of song (length of instrument table)
	DEFB 2 ; Multiple
	DEFW 0 ; Detune
	DEFB 0 ; Phase
	.PATTERNDATA DEFW PAT0
	; *** Pattern data - $00 marks the end of a pattern ***
	.PAT0
	DEFB $BD,0
	DEFB 230
	DEFB 147
	DEFB 118
	DEFB 4
	DEFB 190
	DEFB 159
	DEFB 124
	DEFB 4
	DEFB 166
	DEFB 156
	DEFB 125
	DEFB 4
	DEFB 190
	DEFB 159
	DEFB 123
	DEFB 4
	DEFB 173
	DEFB 147
	DEFB 118
	DEFB 4
	DEFB 163
	DEFB 154
	DEFB 124
	DEFB 4
	DEFB 164
	DEFB 159
	DEFB 125
	DEFB 4
	DEFB 168
	DEFB 154
	DEFB 123
	DEFB 4
	DEFB 166
	DEFB 147
	DEFB 118
	DEFB 4
	DEFB 190
	DEFB 159
	DEFB 124
	DEFB 4
	DEFB 166
	DEFB 156
	DEFB 125
	DEFB 4
	DEFB 190
	DEFB 159
	DEFB 123
	DEFB 4
	DEFB 173
	DEFB 147
	DEFB 118
	DEFB 4
	DEFB 175
	DEFB 154
	DEFB 124
	DEFB 4
	DEFB 176
	DEFB 159
	DEFB 125
	DEFB 4
	DEFB 180
	DEFB 154
	DEFB 123
	DEFB 4
	DEFB 178
	DEFB 147
	DEFB 118
	DEFB 4
	DEFB 190
	DEFB 159
	DEFB 124
	DEFB 4
	DEFB 175
	DEFB 156
	DEFB 125
	DEFB 4
	DEFB 190
	DEFB 159
	DEFB 123
	DEFB 4
	DEFB 176
	DEFB 147
	DEFB 118
	DEFB 4
	DEFB 178
	DEFB 154
	DEFB 124
	DEFB 4
	DEFB 176
	DEFB 159
	DEFB 125
	DEFB 4
	DEFB 175
	DEFB 154
	DEFB 123
	DEFB 4
	DEFB 173
	DEFB 147
	DEFB 118
	DEFB 4
	DEFB 190
	DEFB 159
	DEFB 124
	DEFB 4
	DEFB 176
	DEFB 156
	DEFB 125
	DEFB 4
	DEFB 190
	DEFB 159
	DEFB 123
	DEFB 4
	DEFB 175
	DEFB 147
	DEFB 118
	DEFB 4
	DEFB 176
	DEFB 154
	DEFB 124
	DEFB 4
	DEFB 178
	DEFB 159
	DEFB 125
	DEFB 4
	DEFB 180
	DEFB 154
	DEFB 123
	DEFB 4
	DEFB 178
	DEFB 147
	DEFB 118
	DEFB 4
	DEFB 190
	DEFB 159
	DEFB 124
	DEFB 4
	DEFB 178
	DEFB 156
	DEFB 125
	DEFB 4
	DEFB 190
	DEFB 159
	DEFB 123
	DEFB 4
	DEFB 173
	DEFB 147
	DEFB 118
	DEFB 4
	DEFB 175
	DEFB 154
	DEFB 124
	DEFB 4
	DEFB 176
	DEFB 159
	DEFB 125
	DEFB 4
	DEFB 180
	DEFB 154
	DEFB 123
	DEFB 4
	DEFB 178
	DEFB 147
	DEFB 118
	DEFB 4
	DEFB 190
	DEFB 159
	DEFB 124
	DEFB 4
	DEFB 178
	DEFB 156
	DEFB 125
	DEFB 4
	DEFB 190
	DEFB 159
	DEFB 123
	DEFB 4
	DEFB 173
	DEFB 147
	DEFB 118
	DEFB 4
	DEFB 175
	DEFB 154
	DEFB 124
	DEFB 4
	DEFB 176
	DEFB 159
	DEFB 125
	DEFB 4
	DEFB 180
	DEFB 154
	DEFB 123
	DEFB 4
	DEFB 178
	DEFB 147
	DEFB 118
	DEFB 4
	DEFB 190
	DEFB 159
	DEFB 124
	DEFB 4
	DEFB 175
	DEFB 156
	DEFB 125
	DEFB 4
	DEFB 190
	DEFB 159
	DEFB 123
	DEFB 4
	DEFB 176
	DEFB 147
	DEFB 118
	DEFB 4
	DEFB 178
	DEFB 154
	DEFB 124
	DEFB 4
	DEFB 176
	DEFB 159
	DEFB 125
	DEFB 4
	DEFB 175
	DEFB 154
	DEFB 123
	DEFB 4
	DEFB 173
	DEFB 147
	DEFB 118
	DEFB 4
	DEFB 190
	DEFB 159
	DEFB 124
	DEFB 4
	DEFB 168
	DEFB 156
	DEFB 125
	DEFB 4
	DEFB 190
	DEFB 159
	DEFB 123
	DEFB 4
	DEFB 166
	DEFB 147
	DEFB 118
	DEFB 4
	DEFB 168
	DEFB 154
	DEFB 124
	DEFB 4
	DEFB 170
	DEFB 159
	DEFB 125
	DEFB 4
	DEFB 171
	DEFB 154
	DEFB 123
	DEFB 4
	DEFB $00
;	SECTION	text

.i_1
	defm	"            "
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
.__en_x1	defs	1
.__en_y1	defs	1
.__en_x2	defs	1
.__en_y2	defs	1
._en_an_base_frame	defs	3
._hotspot_x	defs	1
._hotspot_y	defs	1
._en_an_c_f	defs	6
.__en_mx	defs	1
.__en_my	defs	1
._map_pointer	defs	2
._en_an_state	defs	3
._p_facing	defs	1
._p_frame	defs	1
._en_an_n_f	defs	6
._p_c_f	defs	2
._pregotten	defs	1
._hit_h	defs	1
._gen_pt_alt	defs	2
._hit_v	defs	1
._killed_old	defs	1
._p_n_f	defs	2
._gpaux	defs	1
._map_attr	defs	150
._active	defs	1
._a1	defs	2
._c1	defs	1
._c2	defs	1
._c3	defs	1
._c4	defs	1
._a2	defs	2
._a3	defs	2
._t_alt	defs	1
._t1	defs	1
._t2	defs	1
._t3	defs	1
._t4	defs	1
._x0	defs	1
._y0	defs	1
._x1	defs	1
._y1	defs	1
.__n	defs	1
._do_respawn	defs	1
.__t	defs	1
.__x	defs	1
.__y	defs	1
._bs	defs	1
._mlplaying	defs	1
._life_old	defs	1
._p_engine	defs	1
._xx	defs	1
._yy	defs	1
._gen_pt	defs	2
._no_draw	defs	1
._p_state	defs	1
._ptgmx	defs	1
._ptgmy	defs	1
._sp_player	defs	2
._gp_gen	defs	2
._killable	defs	1
._enoffs	defs	1
._pad_this_frame	defs	1
._silent_level	defs	1
._p_killed	defs	1
._pad0	defs	1
._p_killme	defs	1
._p_jmp_ct	defs	1
._n_pant	defs	1
._p_jmp_on	defs	1
._o_pant	defs	1
._p_life	defs	1
._enit	defs	1
._joyfunc	defs	2
._gpcx	defs	1
._p_objs	defs	1
._p_gotten	defs	1
._gpcy	defs	1
._gpit	defs	1
._gpjt	defs	1
._p_keys	defs	1
._playing	defs	1
._keys	defs	10
._p_vx	defs	1
._p_vy	defs	1
._gpxx	defs	1
._gpyy	defs	1
._objs_old	defs	1
._maincounter	defs	1
._ptx1	defs	1
._ptx2	defs	1
._pty1	defs	1
._pty2	defs	1
._at1	defs	1
._at2	defs	1
._action_pressed	defs	1
.__en_life	defs	1
._nocast	defs	1
._cx1	defs	1
._cx2	defs	1
._cy1	defs	1
._cy2	defs	1
._p_subframe	defs	1
._p_state_ct	defs	1
.__ta	defs	1
._animate	defs	1
._gpc	defs	1
._gpd	defs	1
._p_g	defs	1
._hit	defs	1
._gps	defs	1
._gpt	defs	1
._rda	defs	1
._rdb	defs	1
._p_x	defs	2
._AD_FREE	defs	600
._p_y	defs	2
._gpx	defs	1
._gpy	defs	1
._rdx	defs	1
._rdy	defs	1
._keys_old	defs	1
._wall_h	defs	1
._enoffsmasi	defs	1
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
._success	defs	1
._en_an_count	defs	3
._p_disparando	defs	1
;	SECTION	code



; --- Start of Scope Defns ---

	LIB	sp_GetKey
	LIB	sp_BlockAlloc
	XDEF	__en_t
	LIB	sp_ScreenStr
	XDEF	__en_x
	XDEF	__en_y
	XDEF	_hotspots
	XDEF	_draw_scr
	LIB	sp_PixelUp
	XDEF	_enems_move_spr_abs
	XDEF	_prepare_level
	LIB	sp_JoyFuller
	LIB	sp_MouseAMXInit
	XDEF	_blackout_area
	LIB	sp_MouseAMX
	XDEF	_sp_moviles
	XDEF	__en_x1
	LIB	sp_SetMousePosAMX
	XDEF	__en_y1
	XDEF	_u_malloc
	LIB	sp_Validate
	LIB	sp_HashAdd
	XDEF	__en_x2
	XDEF	__en_y2
	XDEF	_cortina
	LIB	sp_Border
	LIB	sp_Inkey
	XDEF	_en_an_base_frame
	XDEF	_enems_init
	XDEF	_draw_objs
	XDEF	_hotspot_x
	XDEF	_hotspot_y
	LIB	sp_CreateSpr
	LIB	sp_MoveSprAbs
	LIB	sp_BlockCount
	LIB	sp_AddMemory
	XDEF	_half_life
	XDEF	_en_an_c_f
	XDEF	__en_mx
	XDEF	__en_my
	XDEF	_map_pointer
	XDEF	_read_controller
	XDEF	_en_an_state
	XDEF	_enems_move
	LIB	sp_PrintAt
	LIB	sp_Pause
	LIB	sp_ListFirst
	LIB	sp_HeapSiftUp
	LIB	sp_ListCount
	XDEF	_p_facing
	XDEF	_invalidate_tile
	XDEF	_p_frame
	XDEF	_en_an_n_f
	LIB	sp_Heapify
	XDEF	_bolts
	XDEF	_p_c_f
	LIB	sp_MoveSprRel
	XDEF	_hide_sprites
	XDEF	_pregotten
	XDEF	_hit_h
	LIB	sp_TileArray
	LIB	sp_MouseSim
	LIB	sp_BlockFit
	XDEF	_map_buff
	defc	_map_buff	=	61697
	XDEF	_gen_pt_alt
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
	XDEF	_a1
	LIB	sp_ListAppend
	XDEF	_keyscancodes
	XDEF	_level
	XDEF	_c1
	XDEF	_c2
	LIB	sp_ListCreate
	LIB	sp_ListConcat
	XDEF	_c3
	XDEF	_c4
	XDEF	_a2
	XDEF	_a3
	XDEF	_t_alt
	XDEF	_level1_hotspots
	LIB	sp_JoyKempston
	LIB	sp_UpdateNow
	LIB	sp_MouseKempston
	LIB	sp_PrintString
	LIB	sp_PixelDown
	LIB	sp_MoveSprAbsC
	LIB	sp_PixelLeft
	XDEF	_t1
	XDEF	_t2
	XDEF	_t3
	XDEF	_t4
	XDEF	_x0
	LIB	sp_InitAlloc
	XDEF	_y0
	XDEF	_x1
	XDEF	_y1
	XDEF	_enem_frames
	LIB	sp_DeleteSpr
	LIB	sp_JoyTimexEither
	XDEF	__n
	XDEF	_flick_screen
	XDEF	_do_respawn
	XDEF	_player_kill
	XDEF	__t
	XDEF	__x
	XDEF	__y
	XDEF	_bs
	XDEF	_player_init
	XDEF	_mlplaying
	XDEF	_life_old
	LIB	sp_Invalidate
	LIB	sp_CreateGenericISR
	LIB	sp_JoyKeyboard
	LIB	sp_FreeBlock
	LIB	sp_PrintAtDiff
	LIB	sp_UpdateNowEx
	XDEF	_run_fire_script
	XDEF	_p_engine
	XDEF	_player_move
	XDEF	_xx
	XDEF	_yy
	XDEF	_gen_pt
	XDEF	_no_draw
	XDEF	_s_marco
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
	XDEF	_srand
	XDEF	_sprite_14_a
	XDEF	_sprite_14_b
	XDEF	_sprite_14_c
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
	XDEF	_sprite_16_a
	XDEF	_sprite_16_b
	XDEF	_sprite_16_c
	XDEF	_sprite_18_a
	XDEF	_player_frames
	XDEF	_cm_two_points
	XDEF	_qtile
	LIB	sp_MoveSprRelC
	LIB	sp_InitIM2
	XDEF	_randres
	XDEF	_sp_player
	XDEF	_gp_gen
	XDEF	_beep_fx
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
	XDEF	_behs
	XDEF	_draw_invalidate_coloured_tile_g
	XDEF	_p_killed
	LIB	sp_GetAttrAddr
	LIB	sp_HashCreate
	XDEF	_pad0
	XDEF	_p_killme
	LIB	sp_Random32
	LIB	sp_ListInsert
	XDEF	_p_jmp_ct
	LIB	sp_ListFree
	XDEF	_n_pant
	XDEF	_advance_worm
	XDEF	_p_jmp_on
	XDEF	_ISR
	LIB	sp_IntRect
	LIB	sp_ListLast
	LIB	sp_ListCurr
	XDEF	_o_pant
	XDEF	_p_life
	XDEF	_enit
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
	XDEF	_gpcy
	XDEF	_attr
	XDEF	_s_title
	LIB	sp_RemoveDList
	XDEF	_gpit
	XDEF	_gpjt
	XDEF	_p_keys
	XDEF	_playing
	XDEF	_player_calc_bounding_box
	LIB	sp_ListNext
	LIB	sp_HuffDecode
	XDEF	_keys
	XDEF	_rand
	LIB	sp_Swap
	XDEF	_isrc
	defc	_isrc	=	23296
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
	XDEF	_maincounter
	XDEF	_ptx1
	XDEF	_ptx2
	XDEF	_pty1
	XDEF	_pty2
	XDEF	_active_sleep
	LIB	sp_RegisterHook
	LIB	sp_ListRemove
	LIB	sp_ListTrim
	LIB	sp_MoveSprAbsNC
	LIB	sp_HuffDelete
	XDEF	_update_tile
	XDEF	_at1
	XDEF	_at2
	XDEF	_level_data
	LIB	sp_ListAdd
	LIB	sp_KeyPressed
	XDEF	_action_pressed
	XDEF	_button_pressed
	XDEF	__en_life
	LIB	sp_PrintAtInv
	XDEF	_nocast
	XDEF	_step
	XDEF	_draw_coloured_tile_gamearea
	XDEF	_cx1
	XDEF	_cx2
	XDEF	_cy1
	XDEF	_cy2
	LIB	sp_CompDListAddr
	XDEF	_p_subframe
	XDEF	_u_free
	XDEF	_abs
	XDEF	_p_state_ct
	XDEF	__ta
	XDEF	_s_ending
	LIB	sp_CharRight
	XDEF	_animate
	XDEF	_game_ending
	LIB	sp_InstallISR
	XDEF	_gpc
	XDEF	_gpd
	LIB	sp_HuffAccumulate
	LIB	sp_HuffSetState
	XDEF	_p_g
	XDEF	_hit
	XDEF	_map
	XDEF	_sprite_1_a
	XDEF	_sprite_1_b
	XDEF	_sprite_1_c
	XDEF	_gps
	XDEF	_gpt
	XDEF	_rda
	XDEF	_rdb
	XDEF	_sprite_2_a
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
	XDEF	_sprite_2_b
	XDEF	_sprite_2_c
	XDEF	_sprite_3_a
	LIB	sp_HuffEncode
	XDEF	_sprite_3_b
	XDEF	_sprite_3_c
	XDEF	_sprite_4_a
	XDEF	_sprite_4_b
	XDEF	_level0_hotspots
	LIB	sp_JoyTimexRight
	LIB	sp_PixelRight
	XDEF	_rdx
	XDEF	_rdy
	XDEF	_sprite_4_c
	LIB	sp_Initialize
	XDEF	_sprite_5_a
	XDEF	_sprite_5_b
	XDEF	_sprite_5_c
	XDEF	_sprite_6_a
	XDEF	_tileset
	XDEF	_sprite_6_b
	LIB	sp_JoyTimexLeft
	LIB	sp_SetMousePosKempston
	XDEF	_sprite_6_c
	XDEF	_sprite_7_a
	XDEF	_sprite_7_b
	LIB	sp_ComputePos
	XDEF	_sprite_7_c
	XDEF	_sprite_8_a
	XDEF	_sprite_8_b
	XDEF	_sprite_8_c
	XDEF	_sprite_9_a
	XDEF	_sprite_9_b
	XDEF	_sprite_9_c
	XDEF	_process_tile
	XDEF	_keys_old
	XDEF	_update_hud
	XDEF	_wall_h
	XDEF	_enoffsmasi
	XDEF	_spacer
	XDEF	_wall_v
	LIB	sp_IntIntervals
	XDEF	_my_malloc
	XDEF	_tocado
	XDEF	_x_pant
	XDEF	_do_gravity
	XDEF	_is_rendering
	LIB	sp_inp
	LIB	sp_IterateSprChar
	LIB	sp_AddColSpr
	LIB	sp_outp
	XDEF	_level0_behs
	XDEF	_asm_int
	defc	_asm_int	=	23297
	XDEF	_p_facing_h
	XDEF	_y_pant
	LIB	sp_IntPtInterval
	LIB	sp_RegisterHookFirst
	XDEF	__baddies_pointer
	LIB	sp_HashLookup
	XDEF	_p_facing_v
	XDEF	_level1_behs
	LIB	sp_PFill
	XDEF	_level0_enems
	XDEF	_possee
	XDEF	_level0_bolts
	LIB	sp_HashRemove
	LIB	sp_CharUp
	XDEF	_orig_tile
	XDEF	_success
	LIB	sp_MoveSprRelNC
	XDEF	_level0_map
	XDEF	_ram_destination
	XDEF	_en_an_count
	XDEF	_level1_map
	XDEF	_select_joyfunc
	XDEF	_unpack
	XDEF	_p_disparando
	XDEF	_level0_ts
	LIB	sp_IterateDList
	XDEF	_level1_ts
	XDEF	_level1_enems
	XDEF	_level1_bolts
	XDEF	_draw_scr_background
	XDEF	_game_over
	LIB	sp_LookupKey
	LIB	sp_HeapAdd
	LIB	sp_CompDirtyAddr
	LIB	sp_EmptyISR
	XDEF	_ram_address
	LIB	sp_StackSpace


; --- End of Scope Defns ---


; --- End of Compilation ---
