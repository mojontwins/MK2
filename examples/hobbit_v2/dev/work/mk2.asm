;* * * * *  Small-C/Plus z88dk * * * * *
;  Version: 20100416.1
;
;	Reconstructed for z80 Module Assembler
;
;	Module compile time: Sun Nov 24 10:17:43 2019



	MODULE	mk2.c


	INCLUDE "z80_crt0.hdr"


	LIB SPMoveSprAbs
;	SECTION	text

._behs
	defm	""
	defb	0

	defm	""
	defb	8

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	4

	defm	""
	defb	8

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	8

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	24

	defm	""
	defb	8

	defm	""
	defb	1

	defm	""
	defb	1

	defm	""
	defb	1

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	1

	defm	""
	defb	1

	defm	""
	defb	1

	defm	""
	defb	1

	defm	""
	defb	1

	defm	""
	defb	1

	defm	""
	defb	1

	defm	""
	defb	1

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

	defm	""
	defb	0

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

	.vpClipStruct defb 1, 1 + 20, 1, 1 + 30
;	SECTION	text

._half_life
	defm	""
	defb	0

;	SECTION	code


;	SECTION	text

._map_buff
	defw	61440
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


	._main_script
	BINARY "../bin/scripts.bin"
	._script defw 0
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
	jp	z,i_13
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
.i_13
	ret


	._s_title
	BINARY "../bin/title.bin"
	._s_marco
	._s_ending
	BINARY "../bin/ending.bin"
	._map
	BINARY "../bin/map.bin"
	._tileset
	BINARY "../bin/ts.bin"
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	._sprite_1_a
	defb 0, 224
	defb 31, 192
	defb 15, 224
	defb 31, 192
	defb 28, 192
	defb 59, 128
	defb 59, 128
	defb 123, 0
	defb 124, 0
	defb 127, 0
	defb 111, 0
	defb 31, 128
	defb 63, 128
	defb 31, 128
	defb 47, 128
	defb 0, 192
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	._sprite_1_b
	defb 0, 63
	defb 192, 15
	defb 240, 7
	defb 240, 7
	defb 64, 3
	defb 184, 3
	defb 48, 3
	defb 48, 1
	defb 68, 1
	defb 254, 0
	defb 254, 0
	defb 142, 0
	defb 254, 0
	defb 252, 1
	defb 248, 3
	defb 0, 7
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
	defb 0, 136
	defb 55, 128
	defb 31, 192
	defb 31, 192
	defb 28, 192
	defb 59, 128
	defb 58, 128
	defb 122, 0
	defb 124, 0
	defb 127, 0
	defb 111, 0
	defb 31, 128
	defb 63, 128
	defb 57, 128
	defb 22, 192
	defb 0, 224
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	._sprite_2_b
	defb 0, 63
	defb 192, 15
	defb 240, 7
	defb 240, 7
	defb 64, 3
	defb 184, 3
	defb 32, 3
	defb 32, 1
	defb 68, 1
	defb 254, 0
	defb 254, 0
	defb 30, 0
	defb 254, 0
	defb 252, 1
	defb 248, 3
	defb 0, 7
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
	defb 0, 24
	defb 103, 0
	defb 63, 128
	defb 31, 192
	defb 28, 192
	defb 59, 128
	defb 56, 128
	defb 120, 0
	defb 124, 0
	defb 111, 0
	defb 55, 128
	defb 15, 192
	defb 63, 128
	defb 62, 128
	defb 29, 192
	defb 0, 224
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	._sprite_3_b
	defb 0, 63
	defb 192, 15
	defb 240, 7
	defb 240, 7
	defb 64, 3
	defb 184, 3
	defb 136, 3
	defb 136, 1
	defb 68, 1
	defb 254, 0
	defb 254, 0
	defb 62, 0
	defb 254, 0
	defb 60, 1
	defb 216, 3
	defb 0, 7
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
	defb 0, 248
	defb 3, 240
	defb 12, 224
	defb 11, 128
	defb 90, 0
	defb 90, 0
	defb 124, 0
	defb 127, 0
	defb 60, 0
	defb 24, 128
	defb 56, 128
	defb 24, 192
	defb 28, 192
	defb 3, 128
	defb 120, 0
	defb 0, 135
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	._sprite_4_b
	defb 0, 63
	defb 192, 15
	defb 64, 7
	defb 184, 3
	defb 32, 3
	defb 32, 3
	defb 68, 1
	defb 252, 1
	defb 124, 1
	defb 56, 1
	defb 54, 0
	defb 54, 0
	defb 118, 0
	defb 230, 0
	defb 0, 25
	defb 0, 255
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
	defb 0, 252
	defb 3, 240
	defb 15, 224
	defb 15, 224
	defb 2, 192
	defb 29, 192
	defb 12, 192
	defb 12, 128
	defb 34, 128
	defb 127, 0
	defb 127, 0
	defb 113, 0
	defb 127, 0
	defb 63, 128
	defb 31, 192
	defb 0, 224
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	._sprite_5_b
	defb 0, 7
	defb 248, 3
	defb 240, 7
	defb 248, 3
	defb 56, 3
	defb 220, 1
	defb 220, 1
	defb 222, 0
	defb 62, 0
	defb 254, 0
	defb 246, 0
	defb 248, 1
	defb 252, 1
	defb 248, 1
	defb 244, 1
	defb 0, 3
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
	defb 0, 252
	defb 3, 240
	defb 15, 224
	defb 15, 224
	defb 2, 192
	defb 29, 192
	defb 4, 192
	defb 4, 128
	defb 34, 128
	defb 127, 0
	defb 127, 0
	defb 120, 0
	defb 127, 0
	defb 63, 128
	defb 31, 192
	defb 0, 224
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	._sprite_6_b
	defb 0, 17
	defb 236, 1
	defb 248, 3
	defb 248, 3
	defb 56, 3
	defb 220, 1
	defb 92, 1
	defb 94, 0
	defb 62, 0
	defb 254, 0
	defb 246, 0
	defb 248, 1
	defb 252, 1
	defb 156, 1
	defb 104, 3
	defb 0, 7
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
	defb 0, 252
	defb 3, 240
	defb 15, 224
	defb 15, 224
	defb 2, 192
	defb 29, 192
	defb 17, 192
	defb 17, 128
	defb 34, 128
	defb 127, 0
	defb 127, 0
	defb 124, 0
	defb 127, 0
	defb 60, 128
	defb 27, 192
	defb 0, 224
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	._sprite_7_b
	defb 0, 24
	defb 230, 0
	defb 252, 1
	defb 248, 3
	defb 56, 3
	defb 220, 1
	defb 28, 1
	defb 30, 0
	defb 62, 0
	defb 246, 0
	defb 236, 1
	defb 240, 3
	defb 252, 1
	defb 124, 1
	defb 184, 3
	defb 0, 7
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
	defb 0, 252
	defb 3, 240
	defb 2, 224
	defb 29, 192
	defb 4, 192
	defb 4, 192
	defb 34, 128
	defb 63, 128
	defb 62, 128
	defb 28, 128
	defb 108, 0
	defb 108, 0
	defb 110, 0
	defb 103, 0
	defb 0, 152
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	._sprite_8_b
	defb 0, 31
	defb 192, 15
	defb 48, 7
	defb 208, 1
	defb 90, 0
	defb 90, 0
	defb 62, 0
	defb 254, 0
	defb 60, 0
	defb 24, 1
	defb 28, 1
	defb 24, 3
	defb 56, 3
	defb 192, 1
	defb 30, 0
	defb 0, 225
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
	defb 0, 252
	defb 3, 240
	defb 15, 224
	defb 29, 192
	defb 25, 192
	defb 25, 192
	defb 27, 192
	defb 15, 224
	defb 15, 224
	defb 21, 128
	defb 32, 128
	defb 16, 192
	defb 0, 224
	defb 0, 224
	defb 30, 192
	defb 0, 193
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	._sprite_9_b
	defb 0, 127
	defb 128, 31
	defb 224, 15
	defb 112, 7
	defb 48, 7
	defb 48, 7
	defb 176, 7
	defb 224, 15
	defb 224, 15
	defb 64, 31
	defb 0, 7
	defb 8, 3
	defb 4, 1
	defb 0, 1
	defb 120, 3
	defb 0, 131
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
	defb 0, 254
	defb 1, 248
	defb 7, 240
	defb 14, 224
	defb 12, 224
	defb 12, 224
	defb 13, 224
	defb 7, 240
	defb 7, 240
	defb 2, 248
	defb 0, 224
	defb 16, 192
	defb 32, 128
	defb 16, 128
	defb 14, 224
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
	defb 0, 63
	defb 192, 15
	defb 240, 7
	defb 184, 3
	defb 152, 3
	defb 152, 3
	defb 216, 3
	defb 240, 7
	defb 240, 7
	defb 168, 1
	defb 4, 1
	defb 8, 3
	defb 0, 7
	defb 0, 15
	defb 112, 7
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
	defb 0, 248
	defb 7, 224
	defb 31, 192
	defb 51, 128
	defb 45, 128
	defb 97, 0
	defb 105, 0
	defb 115, 0
	defb 127, 0
	defb 127, 0
	defb 61, 128
	defb 63, 128
	defb 29, 192
	defb 13, 224
	defb 0, 242
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
	defb 0, 63
	defb 192, 15
	defb 240, 7
	defb 152, 3
	defb 104, 3
	defb 12, 1
	defb 76, 1
	defb 156, 1
	defb 252, 1
	defb 252, 1
	defb 252, 1
	defb 252, 1
	defb 220, 3
	defb 216, 3
	defb 0, 39
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
	defb 0, 248
	defb 7, 224
	defb 31, 192
	defb 51, 128
	defb 45, 128
	defb 97, 0
	defb 101, 0
	defb 115, 0
	defb 127, 0
	defb 127, 0
	defb 62, 128
	defb 63, 128
	defb 30, 192
	defb 7, 224
	defb 0, 248
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	._sprite_12_b
	defb 0, 63
	defb 192, 15
	defb 240, 7
	defb 152, 3
	defb 104, 3
	defb 12, 1
	defb 44, 1
	defb 156, 1
	defb 254, 0
	defb 254, 0
	defb 254, 0
	defb 254, 0
	defb 222, 0
	defb 108, 1
	defb 0, 147
	defb 0, 255
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
	defb 0, 248
	defb 7, 224
	defb 1, 192
	defb 63, 128
	defb 17, 128
	defb 51, 128
	defb 17, 128
	defb 63, 128
	defb 1, 192
	defb 15, 192
	defb 35, 128
	defb 96, 0
	defb 23, 0
	defb 0, 192
	defb 56, 131
	defb 0, 199
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	._sprite_13_b
	defb 0, 31
	defb 128, 7
	defb 240, 3
	defb 224, 1
	defb 24, 1
	defb 48, 1
	defb 24, 1
	defb 240, 1
	defb 240, 0
	defb 2, 0
	defb 206, 0
	defb 0, 1
	defb 192, 3
	defb 28, 1
	defb 0, 227
	defb 0, 255
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
	defb 0, 248
	defb 7, 224
	defb 3, 192
	defb 63, 128
	defb 17, 128
	defb 57, 128
	defb 17, 128
	defb 63, 128
	defb 3, 0
	defb 79, 0
	defb 115, 0
	defb 0, 128
	defb 3, 192
	defb 56, 128
	defb 0, 199
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	._sprite_14_b
	defb 0, 31
	defb 128, 7
	defb 240, 3
	defb 224, 1
	defb 24, 1
	defb 144, 1
	defb 24, 1
	defb 240, 1
	defb 240, 3
	defb 128, 3
	defb 196, 1
	defb 6, 0
	defb 232, 0
	defb 0, 3
	defb 28, 193
	defb 0, 227
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
	._sprite_15_b
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
	._sprite_16_b
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
	; Extra sprites ahead...
	._sprite_e
	defb 255, 255
	defb 255, 255
	defb 255, 255
	defb 255, 255
	defb 255, 255
	defb 255, 255
	defb 255, 255
	defb 255, 255
	defb 255, 255
	defb 255, 255
	defb 255, 255
	defb 255, 255
	defb 255, 255
	defb 255, 255
	defb 255, 255
	defb 255, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 255, 255
	defb 255, 255
	defb 255, 255
	defb 255, 255
	defb 255, 255
	defb 255, 255
	defb 255, 255
	defb 255, 255
	defb 255, 255
	defb 255, 255
	defb 255, 255
	defb 255, 255
	defb 255, 255
	defb 255, 255
	defb 255, 255
	defb 255, 255
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
	defb 255, 255
	defb 255, 255
	defb 255, 255
	defb 255, 255
	defb 255, 255
	defb 255, 255
	defb 255, 255
	defb 255, 255
	defb 255, 255
	defb 255, 255
	defb 255, 255
	defb 255, 255
	defb 255, 255
	defb 255, 255
	defb 255, 255
	defb 255, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 255, 255
	defb 255, 255
	defb 255, 255
	defb 255, 255
	defb 255, 255
	defb 255, 255
	defb 255, 255
	defb 255, 255
	defb 255, 255
	defb 255, 255
	defb 255, 255
	defb 255, 255
	defb 255, 255
	defb 255, 255
	defb 255, 255
	defb 255, 255
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
	._baddies
	BINARY "../bin/enems.bin"

._addons_between
	ld	hl,8	;const
	add	hl,sp
	ld	e,(hl)
	ld	d,0
	ld	hl,8-2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	l_ult
	jp	nc,i_14
	ld	hl,8	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	jp	i_15
.i_14
	ld	hl,6	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
.i_15
	push	hl
	ld	hl,12	;const
	add	hl,sp
	ld	e,(hl)
	ld	d,0
	ld	hl,8-2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	add	hl,de
	pop	de
	call	l_ule
	jp	nc,i_16
	ld	hl,10	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,10	;const
	add	hl,sp
	ld	e,(hl)
	ld	d,0
	ld	hl,10-2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	l_ult
	jp	nc,i_17
	ld	hl,8	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	jp	i_18
.i_17
	ld	hl,10	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
.i_18
	ex	de,hl
	ld	hl,6-2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	add	hl,de
	pop	de
	call	l_ule
	jp	nc,i_16
	ld	hl,1	;const
	jr	i_19
.i_16
	ld	hl,0	;const
.i_19
	ld	h,0
	ret


	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	._arrow_sprites
	BINARY "../bin/sparrow.bin"
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


;	SECTION	text

._spacer
	defw	i_1+0
;	SECTION	code


._attr
	ld	hl,4	;const
	call	l_gcharspsp	;
	ld	hl,0	;const
	pop	de
	call	l_lt
	jp	c,i_22
	ld	hl,2	;const
	call	l_gcharspsp	;
	ld	hl,0	;const
	pop	de
	call	l_lt
	jp	c,i_22
	ld	hl,4	;const
	call	l_gcharspsp	;
	ld	hl,14	;const
	pop	de
	call	l_gt
	jp	c,i_22
	ld	hl,2	;const
	call	l_gcharspsp	;
	ld	hl,9	;const
	pop	de
	call	l_gt
	jp	nc,i_21
.i_22
	ld	hl,0 % 256	;const
	ret


.i_21
	ld	hl,_map_attr
	push	hl
	ld	hl,6	;const
	call	l_gcharspsp	;
	ld	hl,6	;const
	call	l_gcharspsp	;
	ld	hl,4	;const
	pop	de
	call	l_asl
	pop	de
	add	hl,de
	push	hl
	ld	hl,6	;const
	add	hl,sp
	call	l_gchar
	pop	de
	ex	de,hl
	and	a
	sbc	hl,de
	pop	de
	add	hl,de
	ld	l,(hl)
	ld	h,0
	ret



._qtile
	ld	hl,(_map_buff)
	push	hl
	ld	hl,6	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,6	;const
	add	hl,sp
	ld	e,(hl)
	ld	d,0
	ld	l,#(4 % 256)
	call	l_asl
	pop	de
	add	hl,de
	ex	de,hl
	ld	hl,6-2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ex	de,hl
	and	a
	sbc	hl,de
	pop	de
	add	hl,de
	ld	l,(hl)
	ld	h,0
	ret



._draw_coloured_tile
	ld	hl,2	;const
	add	hl,sp
	push	hl
	ld	hl,4	;const
	add	hl,sp
	ld	e,(hl)
	ld	d,0
	ld	l,#(2 % 256)
	call	l_asl
	ld	de,64
	add	hl,de
	pop	de
	ld	a,l
	ld	(de),a
	ld	de,_tileset+2048
	ld	hl,4-2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	add	hl,de
	ld	(_gen_pt),hl
	ld	hl,4	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,8	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,(_gen_pt)
	inc	hl
	ld	(_gen_pt),hl
	dec	hl
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,8	;const
	add	hl,sp
	inc	(hl)
	ld	l,(hl)
	ld	h,0
	dec	l
	push	hl
	call	sp_PrintAtInv
	pop	bc
	pop	bc
	pop	bc
	pop	bc
	ld	hl,4	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,8	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	inc	hl
	push	hl
	ld	hl,(_gen_pt)
	inc	hl
	ld	(_gen_pt),hl
	dec	hl
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,8	;const
	add	hl,sp
	inc	(hl)
	ld	l,(hl)
	ld	h,0
	dec	l
	push	hl
	call	sp_PrintAtInv
	pop	bc
	pop	bc
	pop	bc
	pop	bc
	ld	hl,4	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	inc	hl
	push	hl
	ld	hl,8	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,(_gen_pt)
	inc	hl
	ld	(_gen_pt),hl
	dec	hl
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,8	;const
	add	hl,sp
	inc	(hl)
	ld	l,(hl)
	ld	h,0
	dec	l
	push	hl
	call	sp_PrintAtInv
	pop	bc
	pop	bc
	pop	bc
	pop	bc
	ld	hl,4	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	inc	hl
	push	hl
	ld	hl,8	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	inc	hl
	push	hl
	ld	hl,(_gen_pt)
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,8	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	call	sp_PrintAtInv
	pop	bc
	pop	bc
	pop	bc
	pop	bc
	ret



._draw_coloured_tile_gamearea
	ld	hl,6	;const
	add	hl,sp
	ld	e,(hl)
	ld	d,0
	ld	l,#(1 % 256)
	call	l_asl
	ld	de,1
	add	hl,de
	ld	h,0
	push	hl
	ld	hl,6	;const
	add	hl,sp
	ld	e,(hl)
	ld	d,0
	ld	l,#(1 % 256)
	call	l_asl
	ld	de,1
	add	hl,de
	ld	h,0
	push	hl
	ld	hl,6	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	call	_draw_coloured_tile
	pop	bc
	pop	bc
	pop	bc
	ret



._print_number2
	ld	hl,4	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,8	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,7 % 256	;const
	push	hl
	ld	hl,8	;const
	add	hl,sp
	ld	e,(hl)
	ld	d,0
	ld	hl,10	;const
	call	l_div_u
	ld	de,16
	add	hl,de
	ld	h,0
	push	hl
	call	sp_PrintAtInv
	pop	bc
	pop	bc
	pop	bc
	pop	bc
	ld	hl,4	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,8	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	inc	hl
	push	hl
	ld	hl,7 % 256	;const
	push	hl
	ld	hl,8	;const
	add	hl,sp
	ld	e,(hl)
	ld	d,0
	ld	hl,10	;const
	call	l_div_u
	ex	de,hl
	ld	de,16
	add	hl,de
	ld	h,0
	push	hl
	call	sp_PrintAtInv
	pop	bc
	pop	bc
	pop	bc
	pop	bc
	ret



._print_str
.i_24
	pop	bc
	pop	hl
	push	hl
	push	bc
	ld	a,(hl)
	and	a
	jp	z,i_25
	ld	hl,6	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,10	;const
	add	hl,sp
	inc	(hl)
	ld	l,(hl)
	ld	h,0
	dec	l
	push	hl
	ld	hl,8	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,8	;const
	add	hl,sp
	inc	(hl)
	ld	a,(hl)
	inc	hl
	jr	nz,ASMPC+3
	inc	(hl)
	ld	h,(hl)
	ld	l,a
	dec	hl
	ld	l,(hl)
	ld	h,0
	ld	bc,-32
	add	hl,bc
	push	hl
	call	sp_PrintAtInv
	pop	bc
	pop	bc
	pop	bc
	pop	bc
	jp	i_24
.i_25
	ret


;	SECTION	text

._utaux
	defm	""
	defb	0

;	SECTION	code



._update_tile
	ld	a,(__y)
	ld	e,a
	ld	d,0
	ld	l,#(4 % 256)
	call	l_asl
	ex	de,hl
	ld	hl,(__y)
	ld	h,0
	ex	de,hl
	and	a
	sbc	hl,de
	ex	de,hl
	ld	hl,(__x)
	ld	h,0
	add	hl,de
	ld	h,0
	ld	a,l
	ld	(_utaux),a
	ld	de,_map_attr
	ld	hl,(_utaux)
	ld	h,0
	add	hl,de
	push	hl
	ld	hl,__n
	ld	a,(hl)
	pop	de
	ld	(de),a
	ld	de,(_map_buff)
	ld	hl,(_utaux)
	ld	h,0
	add	hl,de
	push	hl
	ld	hl,__t
	ld	a,(hl)
	pop	de
	ld	(de),a
	ld	hl,(__x)
	ld	h,0
	push	hl
	ld	hl,(__y)
	ld	h,0
	push	hl
	ld	hl,(__t)
	ld	h,0
	push	hl
	call	_draw_coloured_tile_gamearea
	pop	bc
	pop	bc
	pop	bc
	ret



._print_message
	ld	hl,10 % 256	;const
	push	hl
	ld	hl,11 % 256	;const
	push	hl
	ld	hl,87 % 256	;const
	push	hl
	ld	hl,(_spacer)
	push	hl
	call	_print_str
	pop	bc
	pop	bc
	pop	bc
	pop	bc
	ld	hl,10 % 256	;const
	push	hl
	ld	hl,12 % 256	;const
	push	hl
	ld	hl,87 % 256	;const
	push	hl
	ld	hl,8	;const
	add	hl,sp
	call	l_gint	;
	push	hl
	call	_print_str
	pop	bc
	pop	bc
	pop	bc
	pop	bc
	ld	hl,10 % 256	;const
	push	hl
	ld	hl,13 % 256	;const
	push	hl
	ld	hl,87 % 256	;const
	push	hl
	ld	hl,(_spacer)
	push	hl
	call	_print_str
	pop	bc
	pop	bc
	pop	bc
	pop	bc
	call	sp_UpdateNow
	call	sp_WaitForNoKey
	ret



._button_pressed
	call	sp_GetKey
	ld	a,h
	or	l
	jp	nz,i_27
	ld	hl,(_joyfunc)
	push	hl
	ld	hl,_keys
	pop	de
	ld	bc,i_28
	push	hl
	push	bc
	push	de
	ld	a,1
	ret
.i_28
	pop	bc
	ld	de,128	;const
	ex	de,hl
	call	l_and
	ld	de,0	;const
	ex	de,hl
	call	l_eq
	jp	c,i_27
	ld	hl,0	;const
	jr	i_29
.i_27
	ld	hl,1	;const
.i_29
	ld	h,0
	ret



._msc_init_all
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_sc_c),a
	jp	i_32
.i_30
	ld	hl,(_sc_c)
	ld	h,0
	inc	hl
	ld	a,l
	ld	(_sc_c),a
.i_32
	ld	a,(_sc_c)
	cp	#(32 % 256)
	jp	z,i_31
	jp	nc,i_31
	ld	de,_flags
	ld	hl,(_sc_c)
	ld	h,0
	add	hl,de
	ld	(hl),#(0 % 256 % 256)
	ld	l,(hl)
	ld	h,0
	jp	i_30
.i_31
	ret



._read_byte
	dec	sp
	ld	hl,0	;const
	add	hl,sp
	push	hl
	ld	hl,(_script)
	inc	hl
	ld	(_script),hl
	dec	hl
	ld	a,(hl)
	pop	de
	ld	(de),a
	ld	hl,0	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	inc	sp
	ret



._read_vbyte
	call	_read_byte
	ld	h,0
	ld	a,l
	ld	(_sc_c),a
	ld	hl,_sc_c
	ld	a,(hl)
	rlca
	jp	nc,i_33
	ld	hl,_flags
	push	hl
	ld	a,(_sc_c)
	ld	e,a
	ld	d,0
	ld	hl,127	;const
	call	l_and
	pop	de
	add	hl,de
	ld	l,(hl)
	ld	h,0
	jp	i_34
.i_33
	ld	hl,(_sc_c)
	ld	h,0
.i_34
	ld	h,0
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
	ld	(_p_vy),hl
	ld	(_p_vx),hl
	ret



._reloc_player
	call	_read_vbyte
	ex	de,hl
	ld	l,#(10 % 256)
	call	l_asl
	ld	(_p_x),hl
	call	_read_vbyte
	ex	de,hl
	ld	l,#(10 % 256)
	call	l_asl
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
	ld hl, (_asm_int)
	ld a, (hl)
	ld (_asm_int_2), a
	inc hl
	ld a, (hl)
	ld (_asm_int_2 + 1), a
	ld	hl,(_0ch)
	ld	(_script),hl
	ld	a,h
	or	l
	jp	nz,i_35
	ret


.i_35
	ld	de,(_script)
	ld	hl,(_main_script_offset)
	add	hl,de
	ld	(_script),hl
.i_36
	call	_read_byte
	ld	h,0
	ld	a,l
	ld	(_sc_c),a
	ld	de,255	;const
	ex	de,hl
	call	l_ne
	jp	nc,i_37
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
.i_38
	ld	hl,(_sc_terminado)
	ld	h,0
	call	l_lneg
	jp	nc,i_39
	call	_read_byte
.i_42
	ld	a,l
	cp	#(240% 256)
	jp	z,i_43
	cp	#(255% 256)
	jr	z,i_44
.i_43
	jp	i_41
.i_44
	ld	a,#(1 % 256 % 256)
	ld	(_sc_terminado),a
	ld	hl,1 % 256	;const
	ld	a,l
	ld	(_sc_continuar),a
.i_41
	jp	i_38
.i_39
	ld	a,(_sc_continuar)
	and	a
	jp	z,i_45
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_sc_terminado),a
.i_46
	ld	hl,(_sc_terminado)
	ld	h,0
	call	l_lneg
	jp	nc,i_47
	call	_read_byte
.i_50
	ld	a,l
	cp	#(244% 256)
	jp	z,i_51
	cp	#(255% 256)
	jp	z,i_54
	jp	i_49
.i_51
.i_52
	call	_read_byte
	ld	h,0
	ld	a,l
	ld	(_sc_x),a
	ld	de,255
	call	l_ne
	jp	nc,i_53
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
	jp	i_52
.i_53
	jp	i_49
.i_54
	ld	hl,1 % 256	;const
	ld	a,l
	ld	(_sc_terminado),a
.i_49
	jp	i_46
.i_47
.i_45
	ld	hl,(_next_script)
	ld	(_script),hl
	jp	i_36
.i_37
	ret



._enem_move_spr_abs
	; enter: IX = sprite structure address
	; IY = clipping rectangle, set it to "ClipStruct" for full screen
	; BC = animate bitdef displacement (0 for no animation)
	; H = new row coord in chars
	; L = new col coord in chars
	; D = new horizontal rotation (0..7) ie horizontal pixel position
	; E = new vertical rotation (0..7) ie vertical pixel position
	ld a, (_gpit)
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
	ld a, (_gpen_cy)
	srl a
	srl a
	srl a
	add 1
	ld h, a
	ld a, (_gpen_cx)
	srl a
	srl a
	srl a
	add 1
	ld l, a
	ld a, (_gpen_cx)
	and 7
	ld d, a
	ld a, (_gpen_cy)
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


._init_player
	ld	hl,1024	;const
	ld	(_p_x),hl
	ld	hl,8192	;const
	ld	(_p_y),hl
	ld	hl,0	;const
	ld	(_p_vy),hl
	ld	(_p_vx),hl
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
	ld	a,#(10 % 256 % 256)
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



._collide
	ld	hl,8	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	bc,8
	add	hl,bc
	ex	de,hl
	ld	hl,6-2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	l_uge
	jp	nc,i_57
	ld	hl,8	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,6	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	bc,8
	add	hl,bc
	pop	de
	call	l_ule
	jp	nc,i_57
	ld	hl,6	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	bc,8
	add	hl,bc
	ex	de,hl
	ld	hl,4-2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	call	l_uge
	jp	nc,i_57
	ld	hl,6	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,4	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	bc,8
	add	hl,bc
	pop	de
	call	l_ule
	jp	nc,i_57
	ld	hl,1	;const
	jr	i_58
.i_57
	ld	hl,0	;const
.i_58
	ld	h,0
	ret



._collide_pixel
	ld	hl,8	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,6	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	inc	hl
	pop	de
	call	l_uge
	jp	nc,i_60
	ld	hl,8	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,6	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	bc,14
	add	hl,bc
	pop	de
	call	l_ule
	jp	nc,i_60
	ld	hl,6	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,4	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	inc	hl
	pop	de
	call	l_uge
	jp	nc,i_60
	ld	hl,6	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,4	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	bc,14
	add	hl,bc
	pop	de
	call	l_ule
	jr	c,i_61_i_60
.i_60
	jp	i_59
.i_61_i_60
	ld	hl,1 % 256	;const
	ret


.i_59
	ld	hl,0 % 256	;const
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
.i_64
	ld	hl,2 % 256	;const
	push	hl
	call	_beep_fx
	pop	bc
	ld	hl,3 % 256	;const
	push	hl
	call	_beep_fx
	pop	bc
.i_62
	ld	hl,(_bs)
	ld	h,0
	dec	hl
	ld	a,l
	ld	(_bs),a
	ld	a,h
	or	l
	jp	nz,i_64
.i_63
	ld	hl,6 % 256	;const
	push	hl
	call	_beep_fx
	pop	bc
	ret



._game_over
	ld	hl,1 % 256	;const
	push	hl
	ld	hl,23 % 256	;const
	push	hl
	ld	hl,(_p_life)
	ld	h,0
	push	hl
	call	_print_number2
	pop	bc
	pop	bc
	pop	bc
	ld	hl,i_1+13
	push	hl
	call	_print_message
	pop	bc
	ld	hl,4 % 256	;const
	ld	a,l
	ld	(_bs),a
.i_67
	ld	hl,2 % 256	;const
	push	hl
	call	_beep_fx
	pop	bc
	ld	hl,3 % 256	;const
	push	hl
	call	_beep_fx
	pop	bc
.i_65
	ld	hl,(_bs)
	ld	h,0
	dec	hl
	ld	a,l
	ld	(_bs),a
	ld	a,h
	or	l
	jp	nz,i_67
.i_66
	ld	hl,10 % 256	;const
	push	hl
	call	_beep_fx
	pop	bc
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
	ld hl, 22528 ; aquí empiezan los atributos
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
	jp	nc,i_68
	ld	hl,0	;const
	jp	i_69
.i_68
	ld	hl,4	;const
	call	l_gintspsp	;
	ld	hl,0	;const
	pop	de
	call	l_gt
	jp	nc,i_70
	pop	bc
	pop	hl
	push	hl
	push	bc
	jp	i_71
.i_70
	pop	bc
	pop	hl
	push	hl
	push	bc
	call	l_neg
.i_71
.i_69
	ret



._abs
	pop	bc
	pop	hl
	push	hl
	push	bc
	xor	a
	or	h
	jp	p,i_72
	pop	bc
	pop	hl
	push	hl
	push	bc
	call	l_neg
	ret


.i_72
	pop	bc
	pop	hl
	push	hl
	push	bc
	ret


.i_73
	ret



._kill_player
	ld	hl,_p_life
	ld	a,(hl)
	dec	(hl)
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
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



._move
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_wall_h),a
	ld	h,0
	ld	a,l
	ld	(_wall_v),a
	ld	hl,(_joyfunc)
	push	hl
	ld	hl,_keys
	pop	de
	ld	bc,i_74
	push	hl
	push	bc
	push	de
	ld	a,1
	ret
.i_74
	pop	bc
	ld	h,0
	ld	a,l
	ld	(_gpit),a
	ld	a,(_do_gravity)
	and	a
	jp	z,i_75
	ld	hl,(_p_vy)
	ld	de,512	;const
	ex	de,hl
	call	l_lt
	jp	nc,i_76
	ld	hl,(_p_vy)
	ld	bc,32
	add	hl,bc
	ld	(_p_vy),hl
	jp	i_77
.i_76
	ld	hl,512	;const
	ld	(_p_vy),hl
.i_77
.i_75
	ld	a,(_p_gotten)
	and	a
	jp	z,i_78
	ld	hl,0	;const
	ld	(_p_vy),hl
.i_78
	ld	de,(_p_y)
	ld	hl,(_p_vy)
	add	hl,de
	ld	(_p_y),hl
	xor	a
	or	h
	jp	p,i_79
	ld	hl,0	;const
	ld	(_p_y),hl
.i_79
	ld	hl,(_p_y)
	ld	de,9216	;const
	ex	de,hl
	call	l_gt
	jp	nc,i_80
	ld	hl,9216	;const
	ld	(_p_y),hl
.i_80
	ld	hl,(_p_x)
	ex	de,hl
	ld	l,#(6 % 256)
	call	l_asr
	ld	h,0
	ld	a,l
	ld	(_gpx),a
	ld	hl,(_p_y)
	ex	de,hl
	ld	l,#(6 % 256)
	call	l_asr
	ld	h,0
	ld	a,l
	ld	(_gpy),a
	ld	a,(_gpx)
	ld	e,a
	ld	d,0
	ld	l,#(4 % 256)
	call	l_asr_u
	ld	h,0
	ld	a,l
	ld	(_ptx1),a
	ld	hl,(_gpx)
	ld	h,0
	ld	bc,15
	add	hl,bc
	ex	de,hl
	ld	l,#(4 % 256)
	call	l_asr_u
	ld	h,0
	ld	a,l
	ld	(_ptx2),a
	ld	a,(_gpy)
	ld	e,a
	ld	d,0
	ld	l,#(4 % 256)
	call	l_asr_u
	ld	h,0
	ld	a,l
	ld	(_pty1),a
	ld	hl,(_gpy)
	ld	h,0
	ld	bc,15
	add	hl,bc
	ex	de,hl
	ld	l,#(4 % 256)
	call	l_asr_u
	ld	h,0
	ld	a,l
	ld	(_pty2),a
	ld	a,#(0 % 256 % 256)
	ld	(_hit_v),a
	ld	de,(_p_vy)
	ld	hl,(_ptgmy)
	add	hl,de
	xor	a
	or	h
	jp	p,i_81
	ld	hl,(_ptx1)
	ld	h,0
	push	hl
	ld	hl,(_pty1)
	ld	h,0
	push	hl
	call	_attr
	pop	bc
	pop	bc
	ld	h,0
	ld	a,l
	ld	(_pt1),a
	ld	hl,(_ptx2)
	ld	h,0
	push	hl
	ld	hl,(_pty1)
	ld	h,0
	push	hl
	call	_attr
	pop	bc
	pop	bc
	ld	h,0
	ld	a,l
	ld	(_pt2),a
	ld	hl,_pt1
	ld	a,(hl)
	and	#(8 % 256)
	jp	nz,i_83
	ld	hl,_pt2
	ld	a,(hl)
	and	#(8 % 256)
	jp	z,i_82
.i_83
	ld	hl,0	;const
	ld	(_p_vy),hl
	ld	hl,(_pty1)
	ld	h,0
	inc	hl
	ex	de,hl
	ld	l,#(10 % 256)
	call	l_asl
	ld	(_p_y),hl
	ld	hl,1 % 256	;const
	ld	a,l
	ld	(_wall_v),a
.i_82
.i_81
	ld	de,(_p_vy)
	ld	hl,(_ptgmy)
	add	hl,de
	xor	a
	or	h
	jp	m,i_85
	or	l
	jp	z,i_85
	ld	hl,(_ptx1)
	ld	h,0
	push	hl
	ld	hl,(_pty2)
	ld	h,0
	push	hl
	call	_attr
	pop	bc
	pop	bc
	ld	h,0
	ld	a,l
	ld	(_pt1),a
	ld	hl,(_ptx2)
	ld	h,0
	push	hl
	ld	hl,(_pty2)
	ld	h,0
	push	hl
	call	_attr
	pop	bc
	pop	bc
	ld	h,0
	ld	a,l
	ld	(_pt2),a
	ld	hl,_pt1
	ld	a,(hl)
	and	#(8 % 256)
	jp	nz,i_87
	ld	hl,_pt2
	ld	a,(hl)
	and	#(8 % 256)
	jp	nz,i_87
	ld	hl,(_gpy)
	ld	h,0
	dec	hl
	ld	de,15	;const
	ex	de,hl
	call	l_and
	ld	de,8	;const
	ex	de,hl
	call	l_ult
	jp	nc,i_88
	ld	hl,_pt1
	ld	a,(hl)
	and	#(4 % 256)
	jp	nz,i_89
	ld	hl,_pt2
	ld	a,(hl)
	and	#(4 % 256)
	jp	z,i_88
.i_89
	ld	hl,1	;const
	jr	i_91
.i_88
	ld	hl,0	;const
.i_91
	ld	a,h
	or	l
	jp	nz,i_87
	jr	i_92
.i_87
	ld	hl,1	;const
.i_92
	ld	a,h
	or	l
	jp	z,i_86
	ld	hl,0	;const
	ld	(_p_vy),hl
	ld	hl,(_pty2)
	ld	h,0
	dec	hl
	ex	de,hl
	ld	l,#(10 % 256)
	call	l_asl
	ld	(_p_y),hl
	ld	hl,2 % 256	;const
	ld	a,l
	ld	(_wall_v),a
.i_86
.i_85
	ld	hl,(_p_vy)
	ld	a,h
	or	l
	jp	z,i_93
	ld	a,(_pt1)
	cp	#(1 % 256)
	jp	z,i_94
	ld	a,(_pt2)
	cp	#(1 % 256)
	jp	z,i_94
	ld	hl,0	;const
	jr	i_95
.i_94
	ld	hl,1	;const
.i_95
	ld	h,0
	ld	a,l
	ld	(_hit_v),a
.i_93
	ld	hl,(_p_y)
	ex	de,hl
	ld	l,#(6 % 256)
	call	l_asr
	ld	h,0
	ld	a,l
	ld	(_gpy),a
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
	ld	(_pty3),a
	ld	hl,(_ptx1)
	ld	h,0
	push	hl
	ld	hl,(_pty3)
	ld	h,0
	push	hl
	call	_attr
	pop	bc
	pop	bc
	ld	de,12	;const
	ex	de,hl
	call	l_and
	ld	a,h
	or	l
	jp	nz,i_96
	ld	hl,(_ptx2)
	ld	h,0
	push	hl
	ld	hl,(_pty3)
	ld	h,0
	push	hl
	call	_attr
	pop	bc
	pop	bc
	ld	de,12	;const
	ex	de,hl
	call	l_and
	ld	a,h
	or	l
	jp	nz,i_96
	jr	i_97
.i_96
	ld	hl,1	;const
.i_97
	ld	a,h
	or	l
	jp	z,i_98
	ld	a,(_gpy)
	ld	e,a
	ld	d,0
	ld	hl,15	;const
	call	l_and
	ld	de,8	;const
	ex	de,hl
	call	l_ult
	jp	nc,i_98
	ld	hl,1	;const
	jr	i_99
.i_98
	ld	hl,0	;const
.i_99
	ld	h,0
	ld	a,l
	ld	(_possee),a
	ld	hl,_gpit
	ld	a,(hl)
	and	#(128 % 256)
	cp	#(0 % 256)
	ld	hl,0
	jp	nz,i_101
	inc	hl
	ld	a,(_p_jmp_on)
	cp	#(0 % 256)
	jp	nz,i_101
	ld	a,(_possee)
	and	a
	jp	nz,i_102
	ld	a,(_p_gotten)
	and	a
	jp	z,i_101
.i_102
	jr	i_104_i_101
.i_101
	jp	i_100
.i_104_i_101
	ld	a,#(1 % 256 % 256)
	ld	(_p_jmp_on),a
	ld	a,#(0 % 256 % 256)
	ld	(_p_jmp_ct),a
	ld	hl,1 % 256	;const
	push	hl
	call	_beep_fx
	pop	bc
.i_100
	ld	hl,_gpit
	ld	a,(hl)
	and	#(128 % 256)
	cp	#(0 % 256)
	ld	hl,0
	jp	nz,i_106
	inc	hl
	ld	a,(_p_jmp_on)
	and	a
	jr	nz,i_107_i_106
.i_106
	jp	i_105
.i_107_i_106
	ld	hl,(_p_vy)
	push	hl
	ld	a,(_p_jmp_ct)
	ld	e,a
	ld	d,0
	ld	l,#(1 % 256)
	call	l_asr_u
	ld	de,224
	ex	de,hl
	and	a
	sbc	hl,de
	pop	de
	ex	de,hl
	and	a
	sbc	hl,de
	ld	(_p_vy),hl
	ld	de,65280	;const
	ex	de,hl
	call	l_lt
	jp	nc,i_108
	ld	hl,65280	;const
	ld	(_p_vy),hl
.i_108
	ld	hl,_p_jmp_ct
	ld	a,(hl)
	inc	(hl)
	ld	a,(_p_jmp_ct)
	cp	#(8 % 256)
	jp	nz,i_109
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_p_jmp_on),a
.i_109
.i_105
	ld	a,(_gpit)
	ld	e,a
	ld	d,0
	ld	hl,128	;const
	call	l_and
	ld	de,0	;const
	ex	de,hl
	call	l_eq
	ccf
	jp	nc,i_110
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_p_jmp_on),a
.i_110
	ld	a,(_gpit)
	ld	e,a
	ld	d,0
	ld	hl,4	;const
	call	l_and
	ld	de,0	;const
	ex	de,hl
	call	l_eq
	jp	c,i_112
	ld	a,(_gpit)
	ld	e,a
	ld	d,0
	ld	hl,8	;const
	call	l_and
	ld	de,0	;const
	ex	de,hl
	call	l_eq
	jp	c,i_112
	ld	hl,0	;const
	jr	i_113
.i_112
	ld	hl,1	;const
.i_113
	call	l_lneg
	jp	nc,i_111
	ld	hl,(_p_vx)
	xor	a
	or	h
	jp	m,i_114
	or	l
	jp	z,i_114
	ld	hl,(_p_vx)
	ld	bc,-48
	add	hl,bc
	ld	(_p_vx),hl
	xor	a
	or	h
	jp	p,i_115
	ld	hl,0	;const
	ld	(_p_vx),hl
.i_115
	jp	i_116
.i_114
	ld	hl,(_p_vx)
	xor	a
	or	h
	jp	p,i_117
	ld	hl,(_p_vx)
	ld	bc,48
	add	hl,bc
	ld	(_p_vx),hl
	xor	a
	or	h
	jp	m,i_118
	or	l
	jp	z,i_118
	ld	hl,0	;const
	ld	(_p_vx),hl
.i_118
.i_117
.i_116
.i_111
	ld	hl,_gpit
	ld	a,(hl)
	and	#(4 % 256)
	jp	nz,i_119
	ld	hl,(_p_vx)
	ld	de,65280	;const
	ex	de,hl
	call	l_gt
	jp	nc,i_120
	ld	a,#(0 % 256 % 256)
	ld	(_p_facing),a
	ld	hl,(_p_vx)
	ld	bc,-64
	add	hl,bc
	ld	(_p_vx),hl
.i_120
.i_119
	ld	hl,_gpit
	ld	a,(hl)
	and	#(8 % 256)
	jp	nz,i_121
	ld	hl,(_p_vx)
	ld	de,256	;const
	ex	de,hl
	call	l_lt
	jp	nc,i_122
	ld	hl,(_p_vx)
	ld	bc,64
	add	hl,bc
	ld	(_p_vx),hl
	ld	hl,1 % 256	;const
	ld	a,l
	ld	(_p_facing),a
.i_122
.i_121
	ld	de,(_p_x)
	ld	hl,(_p_vx)
	add	hl,de
	ld	(_p_x),hl
	ld	a,(_p_gotten)
	and	a
	jp	z,i_123
	ld	de,(_p_x)
	ld	hl,(_ptgmx)
	add	hl,de
	ld	(_p_x),hl
.i_123
	ld	hl,(_p_x)
	xor	a
	or	h
	jp	p,i_124
	ld	hl,0	;const
	ld	(_p_x),hl
.i_124
	ld	hl,(_p_x)
	ld	de,14336	;const
	ex	de,hl
	call	l_gt
	jp	nc,i_125
	ld	hl,14336	;const
	ld	(_p_x),hl
.i_125
	ld	hl,(_p_x)
	ex	de,hl
	ld	l,#(6 % 256)
	call	l_asr
	ld	h,0
	ld	a,l
	ld	(_gpx),a
	ld	hl,(_p_y)
	ex	de,hl
	ld	l,#(6 % 256)
	call	l_asr
	ld	h,0
	ld	a,l
	ld	(_gpy),a
	ld	a,(_gpx)
	ld	e,a
	ld	d,0
	ld	l,#(4 % 256)
	call	l_asr_u
	ld	h,0
	ld	a,l
	ld	(_ptx1),a
	ld	hl,(_gpx)
	ld	h,0
	ld	bc,15
	add	hl,bc
	ex	de,hl
	ld	l,#(4 % 256)
	call	l_asr_u
	ld	h,0
	ld	a,l
	ld	(_ptx2),a
	ld	a,(_gpy)
	ld	e,a
	ld	d,0
	ld	l,#(4 % 256)
	call	l_asr_u
	ld	h,0
	ld	a,l
	ld	(_pty1),a
	ld	hl,(_gpy)
	ld	h,0
	ld	bc,15
	add	hl,bc
	ex	de,hl
	ld	l,#(4 % 256)
	call	l_asr_u
	ld	h,0
	ld	a,l
	ld	(_pty2),a
	ld	a,#(0 % 256 % 256)
	ld	(_hit_h),a
	ld	de,(_p_vx)
	ld	hl,(_ptgmx)
	add	hl,de
	xor	a
	or	h
	jp	p,i_126
	ld	hl,(_ptx1)
	ld	h,0
	push	hl
	ld	hl,(_pty1)
	ld	h,0
	push	hl
	call	_attr
	pop	bc
	pop	bc
	ld	h,0
	ld	a,l
	ld	(_pt1),a
	ld	hl,(_ptx1)
	ld	h,0
	push	hl
	ld	hl,(_pty2)
	ld	h,0
	push	hl
	call	_attr
	pop	bc
	pop	bc
	ld	h,0
	ld	a,l
	ld	(_pt2),a
	ld	hl,_pt1
	ld	a,(hl)
	and	#(8 % 256)
	jp	nz,i_128
	ld	hl,_pt2
	ld	a,(hl)
	and	#(8 % 256)
	jp	z,i_127
.i_128
	ld	hl,0	;const
	ld	(_p_vx),hl
	ld	hl,(_ptx1)
	ld	h,0
	inc	hl
	ex	de,hl
	ld	l,#(10 % 256)
	call	l_asl
	ld	(_p_x),hl
	ld	hl,3 % 256	;const
	ld	a,l
	ld	(_wall_h),a
	jp	i_130
.i_127
	ld	a,(_pt1)
	cp	#(1 % 256)
	jp	z,i_132
	ld	a,(_pt2)
	cp	#(1 % 256)
	jp	nz,i_131
.i_132
	ld	hl,1 % 256	;const
	ld	a,l
	ld	(_hit_h),a
.i_131
.i_130
.i_126
	ld	de,(_p_vx)
	ld	hl,(_ptgmx)
	add	hl,de
	xor	a
	or	h
	jp	m,i_134
	or	l
	jp	z,i_134
	ld	hl,(_ptx2)
	ld	h,0
	push	hl
	ld	hl,(_pty1)
	ld	h,0
	push	hl
	call	_attr
	pop	bc
	pop	bc
	ld	h,0
	ld	a,l
	ld	(_pt1),a
	ld	hl,(_ptx2)
	ld	h,0
	push	hl
	ld	hl,(_pty2)
	ld	h,0
	push	hl
	call	_attr
	pop	bc
	pop	bc
	ld	h,0
	ld	a,l
	ld	(_pt2),a
	ld	hl,_pt1
	ld	a,(hl)
	and	#(8 % 256)
	jp	nz,i_136
	ld	hl,_pt2
	ld	a,(hl)
	and	#(8 % 256)
	jp	z,i_135
.i_136
	ld	hl,0	;const
	ld	(_p_vx),hl
	ld	hl,(_ptx2)
	ld	h,0
	dec	hl
	ex	de,hl
	ld	l,#(10 % 256)
	call	l_asl
	ld	(_p_x),hl
	ld	hl,4 % 256	;const
	ld	a,l
	ld	(_wall_h),a
	jp	i_138
.i_135
	ld	a,(_pt1)
	cp	#(1 % 256)
	jp	z,i_140
	ld	a,(_pt2)
	cp	#(1 % 256)
	jp	nz,i_139
.i_140
	ld	hl,1 % 256	;const
	ld	a,l
	ld	(_hit_h),a
.i_139
.i_138
.i_134
	ld	hl,(_p_x)
	ex	de,hl
	ld	l,#(6 % 256)
	call	l_asr
	ld	h,0
	ld	a,l
	ld	(_gpx),a
	ld	a,#(0 % 256 % 256)
	ld	(_hit),a
	ld	a,(_hit_v)
	cp	#(1 % 256)
	jp	nz,i_142
	ld	a,#(1 % 256 % 256)
	ld	(_hit),a
	ld	hl,(_p_vy)
	call	l_neg
	ld	(_p_vy),hl
	jp	i_143
.i_142
	ld	a,(_hit_h)
	cp	#(1 % 256)
	jp	nz,i_144
	ld	a,#(1 % 256 % 256)
	ld	(_hit),a
	ld	hl,(_p_vx)
	call	l_neg
	ld	(_p_vx),hl
.i_144
.i_143
	ld	a,(_hit)
	and	a
	jp	z,i_145
	ld	a,(_p_life)
	cp	#(0 % 256)
	jp	z,i_147
	jp	c,i_147
	ld	a,(_p_state)
	cp	#(0 % 256)
	jr	z,i_148_i_147
.i_147
	jp	i_146
.i_148_i_147
	ld	hl,3 % 256	;const
	push	hl
	call	_kill_player
	pop	bc
.i_146
.i_145
	ld	hl,(_possee)
	ld	h,0
	call	l_lneg
	jp	nc,i_150
	ld	hl,(_p_gotten)
	ld	h,0
	call	l_lneg
	jr	c,i_151_i_150
.i_150
	jp	i_149
.i_151_i_150
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
	jp	i_152
.i_149
	ld	a,(_p_facing)
	ld	e,a
	ld	d,0
	ld	l,#(2 % 256)
	call	l_asl
	ld	h,0
	ld	a,l
	ld	(_gpit),a
	ld	hl,(_p_vx)
	ld	a,h
	or	l
	jp	nz,i_153
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
	jp	i_154
.i_153
	ld	hl,_p_subframe
	ld	a,(hl)
	inc	(hl)
	ld	a,(_p_subframe)
	cp	#(4 % 256)
	jp	nz,i_155
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
.i_155
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
.i_154
.i_152
	ret



._run_entering_script
	ld	hl,41 % 256	;const
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
	ret



._draw_scr_background
	ld	de,_seed1
	ld	hl,(_n_pant)
	ld	h,0
	call	l_pint
	ld	hl,_seed2
	push	hl
	ld	hl,(_n_pant)
	ld	h,0
	inc	hl
	pop	de
	call	l_pint
	call	_srand
	ld	hl,_map
	push	hl
	ld	hl,(_n_pant)
	ld	h,0
	ld	de,75
	call	l_mult
	pop	de
	add	hl,de
	ld	(_map_pointer),hl
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_gpy),a
	ld	h,0
	ld	a,l
	ld	(_gpx),a
	ld	h,0
	ld	a,l
	ld	(_gpit),a
.i_158
	call	_rand
	ld	de,15	;const
	ex	de,hl
	call	l_and
	ld	h,0
	ld	a,l
	ld	(_gpjt),a
	ld	hl,_gpit
	ld	a,(hl)
	rrca
	jp	nc,i_159
	ld	a,(_gpc)
	ld	e,a
	ld	d,0
	ld	hl,15	;const
	call	l_and
	ld	h,0
	ld	a,l
	ld	(_gpd),a
	jp	i_160
.i_159
	ld	hl,(_map_pointer)
	inc	hl
	ld	(_map_pointer),hl
	dec	hl
	ld	l,(hl)
	ld	h,0
	ld	a,l
	ld	(_gpc),a
	ld	e,a
	ld	d,0
	ld	l,#(4 % 256)
	call	l_asr_u
	ld	h,0
	ld	a,l
	ld	(_gpd),a
.i_160
	ld	de,_map_attr
	ld	hl,(_gpit)
	ld	h,0
	add	hl,de
	push	hl
	ld	de,_behs
	ld	hl,(_gpd)
	ld	h,0
	add	hl,de
	ld	a,(hl)
	pop	de
	ld	(de),a
	ld	de,(_map_buff)
	ld	hl,(_gpit)
	ld	h,0
	add	hl,de
	push	hl
	ld	hl,_gpd
	ld	a,(hl)
	pop	de
	ld	(de),a
	ld	hl,(_gpx)
	ld	h,0
	push	hl
	ld	hl,(_gpy)
	ld	h,0
	push	hl
	ld	hl,(_gpd)
	ld	h,0
	push	hl
	call	_draw_coloured_tile_gamearea
	pop	bc
	pop	bc
	pop	bc
	ld	hl,_gpx
	ld	a,(hl)
	inc	(hl)
	ld	a,(_gpx)
	cp	#(15 % 256)
	jp	nz,i_161
	ld	a,#(0 % 256 % 256)
	ld	(_gpx),a
	ld	hl,_gpy
	ld	a,(hl)
	inc	(hl)
	ld	l,a
	ld	h,0
.i_161
.i_156
	ld	hl,_gpit
	ld	a,(hl)
	inc	(hl)
	ld	e,a
	ld	d,0
	ld	hl,149	;const
	call	l_ult
	jp	c,i_158
.i_157
	ret



._draw_scr
	ld	a,(_no_draw)
	and	a
	jp	z,i_162
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_no_draw),a
	jp	i_163
.i_162
	call	_draw_scr_background
.i_163
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
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_gpit),a
	jp	i_166
.i_164
	ld	hl,_gpit
	ld	a,(hl)
	inc	(hl)
.i_166
	ld	a,(_gpit)
	cp	#(3 % 256)
	jp	z,i_165
	jp	nc,i_165
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
	add	hl,hl
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	ld	bc,10
	add	hl,bc
	call	l_gchar
	ex	de,hl
	ld	l,#(3 % 256)
	call	l_asr
	ld	h,0
	ld	a,l
	ld	(_gpt),a
	and	a
	jp	z,i_168
	ld	a,(_gpt)
	cp	#(16 % 256)
	jp	z,i_168
	jr	c,i_169_i_168
.i_168
	jp	i_167
.i_169_i_168
	ld	de,_en_an_base_frame
	ld	hl,(_gpit)
	ld	h,0
	add	hl,de
	push	hl
	ld	hl,_baddies
	push	hl
	ld	hl,(_enoffsmasi)
	ld	h,0
	add	hl,hl
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	ld	bc,10
	add	hl,bc
	call	l_gchar
	ld	de,3	;const
	ex	de,hl
	call	l_and
	add	hl,hl
	pop	de
	ld	a,l
	ld	(de),a
	ld	hl,(_gpt)
	ld	h,0
.i_172
	ld	a,l
	cp	#(2% 256)
	jp	nz,i_174
.i_173
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
	add	hl,hl
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	ld	e,(hl)
	inc	hl
	ld	d,(hl)
	ld	l,#(6 % 256)
	call	l_asl
	pop	de
	call	l_pint
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
	add	hl,hl
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	inc	hl
	inc	hl
	ld	e,(hl)
	inc	hl
	ld	d,(hl)
	ld	l,#(6 % 256)
	call	l_asl
	pop	de
	call	l_pint
	ld	hl,_en_an_vx
	push	hl
	ld	hl,(_gpit)
	ld	h,0
	add	hl,hl
	pop	de
	add	hl,de
	push	hl
	ld	hl,_en_an_vy
	push	hl
	ld	hl,(_gpit)
	ld	h,0
	add	hl,hl
	pop	de
	add	hl,de
	ld	de,0	;const
	ex	de,hl
	call	l_pint
	pop	de
	call	l_pint
	ld	de,_en_an_state
	ld	hl,(_gpit)
	ld	h,0
	add	hl,de
	ld	(hl),#(0 % 256 % 256)
	ld	l,(hl)
	ld	h,0
.i_174
.i_171
	jp	i_175
.i_167
	ld	hl,_en_an_n_f
	push	hl
	ld	hl,(_gpit)
	ld	h,0
	add	hl,hl
	pop	de
	add	hl,de
	push	hl
	ld	hl,_sprite_18_a
	pop	de
	call	l_pint
.i_175
	jp	i_164
.i_165
	ld	hl,1 % 256	;const
	ld	a,l
	ld	(_do_respawn),a
	call	_run_entering_script
	ld	a,(_n_pant)
	ld	e,a
	ld	d,0
	ld	hl,10	;const
	call	l_div_u
	ex	de,hl
	ld	h,0
	ld	a,l
	ld	(_x_pant),a
	ld	a,(_n_pant)
	ld	e,a
	ld	d,0
	ld	hl,10	;const
	call	l_div_u
	ld	h,0
	ld	a,l
	ld	(_y_pant),a
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
	jp	nc,i_176
	pop	hl
	push	hl
	ld	l,h
	ld	h,0
	jp	i_177
.i_176
	ld	hl,0	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
.i_177
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



._limit
	ld	hl,6	;const
	call	l_gintspsp	;
	ld	hl,6	;const
	add	hl,sp
	call	l_gint	;
	pop	de
	call	l_lt
	jp	nc,i_178
	ld	hl,4	;const
	add	hl,sp
	call	l_gint	;
	ret


.i_178
	ld	hl,6	;const
	call	l_gintspsp	;
	ld	hl,4	;const
	add	hl,sp
	call	l_gint	;
	pop	de
	call	l_gt
	jp	nc,i_179
	pop	bc
	pop	hl
	push	hl
	push	bc
	ret


.i_179
	ld	hl,6	;const
	add	hl,sp
	call	l_gint	;
	ret



._mueve_bicharracos
	ld	a,#(0 % 256 % 256)
	ld	(_p_gotten),a
	ld	hl,0	;const
	ld	(_ptgmx),hl
	ld	(_ptgmy),hl
	ld	a,#(0 % 256 % 256)
	ld	(_tocado),a
	ld	a,#(0 % 256 % 256)
	ld	(_p_gotten),a
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_gpit),a
	jp	i_182
.i_180
	ld	hl,_gpit
	ld	a,(hl)
	inc	(hl)
.i_182
	ld	a,(_gpit)
	cp	#(3 % 256)
	jp	z,i_181
	jp	nc,i_181
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
	add	hl,hl
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	call	l_gint	;
	ld	h,0
	ld	a,l
	ld	(_gpen_x),a
	ld	hl,_baddies
	push	hl
	ld	hl,(_enoffsmasi)
	ld	h,0
	add	hl,hl
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	inc	hl
	inc	hl
	call	l_gint	;
	ld	h,0
	ld	a,l
	ld	(_gpen_y),a
	ld	de,_en_an_state
	ld	hl,(_gpit)
	ld	h,0
	add	hl,de
	ld	a,(hl)
	cp	#(4 % 256)
	jp	nz,i_183
	ld	de,_en_an_count
	ld	hl,(_gpit)
	ld	h,0
	add	hl,de
	dec	(hl)
	ld	de,_en_an_count
	ld	hl,(_gpit)
	ld	h,0
	add	hl,de
	ld	a,(hl)
	and	a
	jp	nz,i_184
	ld	de,_en_an_state
	ld	hl,(_gpit)
	ld	h,0
	add	hl,de
	ld	(hl),#(0 % 256 % 256)
	ld	hl,_en_an_n_f
	push	hl
	ld	hl,(_gpit)
	ld	h,0
	add	hl,hl
	pop	de
	add	hl,de
	push	hl
	ld	hl,_sprite_18_a
	pop	de
	call	l_pint
	jp	i_180
.i_184
.i_183
	ld	hl,(_gpx)
	ld	h,0
	ld	bc,15
	add	hl,bc
	push	hl
	ld	hl,_baddies
	push	hl
	ld	hl,(_enoffsmasi)
	ld	h,0
	add	hl,hl
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	call	l_gint	;
	pop	de
	call	l_uge
	jp	nc,i_185
	ld	hl,(_gpx)
	ld	h,0
	push	hl
	ld	hl,_baddies
	push	hl
	ld	hl,(_enoffsmasi)
	ld	h,0
	add	hl,hl
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	call	l_gint	;
	ld	bc,15
	add	hl,bc
	pop	de
	call	l_ule
	jp	nc,i_185
	ld	hl,1	;const
	jr	i_186
.i_185
	ld	hl,0	;const
.i_186
	ld	h,0
	ld	a,l
	ld	(_pregotten),a
	ld	hl,_baddies
	push	hl
	ld	hl,(_enoffsmasi)
	ld	h,0
	add	hl,hl
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	ld	bc,10
	add	hl,bc
	call	l_gchar
	ld	de,4	;const
	ex	de,hl
	call	l_and
	ld	a,h
	or	l
	jp	z,i_187
	ld	hl,1 % 256	;const
	ld	a,l
	ld	(_enemy_shoots),a
	jp	i_188
.i_187
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_enemy_shoots),a
.i_188
	ld	hl,_baddies
	push	hl
	ld	hl,(_enoffsmasi)
	ld	h,0
	add	hl,hl
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	ld	bc,10
	add	hl,bc
	call	l_gchar
	ex	de,hl
	ld	l,#(3 % 256)
	call	l_asr
	ld	h,0
	ld	a,l
	ld	(_gpt),a
	ld	hl,(_gpt)
	ld	h,0
.i_191
	ld	a,l
	cp	#(1% 256)
	jp	z,i_192
	cp	#(8% 256)
	jp	z,i_193
	cp	#(2% 256)
	jp	z,i_200
	cp	#(10% 256)
	jp	z,i_214
	jp	i_226
.i_192
	ld	hl,1 % 256	;const
	ld	a,l
	ld	(_killable),a
.i_193
	ld	hl,1 % 256	;const
	ld	a,l
	ld	(_animate),a
	ld	h,0
	ld	a,l
	ld	(_active),a
	ld	hl,_baddies
	push	hl
	ld	hl,(_enoffsmasi)
	ld	h,0
	add	hl,hl
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	push	hl
	ld	e,(hl)
	inc	hl
	ld	d,(hl)
	push	de
	ld	hl,_baddies
	push	hl
	ld	hl,(_enoffsmasi)
	ld	h,0
	add	hl,hl
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	ld	bc,8
	add	hl,bc
	call	l_gchar
	pop	de
	add	hl,de
	pop	de
	call	l_pint
	ld	hl,_baddies
	push	hl
	ld	hl,(_enoffsmasi)
	ld	h,0
	add	hl,hl
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	inc	hl
	inc	hl
	push	hl
	ld	e,(hl)
	inc	hl
	ld	d,(hl)
	push	de
	ld	hl,_baddies
	push	hl
	ld	hl,(_enoffsmasi)
	ld	h,0
	add	hl,hl
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	ld	bc,9
	add	hl,bc
	call	l_gchar
	pop	de
	add	hl,de
	pop	de
	call	l_pint
	ld	hl,_baddies
	push	hl
	ld	hl,(_enoffsmasi)
	ld	h,0
	add	hl,hl
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	call	l_gint	;
	ld	h,0
	ld	a,l
	ld	(_gpen_cx),a
	ld	hl,_baddies
	push	hl
	ld	hl,(_enoffsmasi)
	ld	h,0
	add	hl,hl
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	inc	hl
	inc	hl
	call	l_gint	;
	ld	h,0
	ld	a,l
	ld	(_gpen_cy),a
	ld	a,(_gpen_cx)
	ld	e,a
	ld	d,0
	ld	l,#(4 % 256)
	call	l_asr_u
	ld	h,0
	ld	a,l
	ld	(_gpen_xx),a
	ld	a,(_gpen_cy)
	ld	e,a
	ld	d,0
	ld	l,#(4 % 256)
	call	l_asr_u
	ld	h,0
	ld	a,l
	ld	(_gpen_yy),a
	ld	hl,(_gpen_cx)
	ld	h,0
	push	hl
	ld	hl,_baddies
	push	hl
	ld	hl,(_enoffsmasi)
	ld	h,0
	add	hl,hl
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	ld	bc,4
	add	hl,bc
	ld	l,(hl)
	ld	h,0
	pop	de
	call	l_eq
	jp	c,i_195
	ld	hl,(_gpen_cx)
	ld	h,0
	push	hl
	ld	hl,_baddies
	push	hl
	ld	hl,(_enoffsmasi)
	ld	h,0
	add	hl,hl
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	ld	bc,6
	add	hl,bc
	ld	l,(hl)
	ld	h,0
	pop	de
	call	l_eq
	jp	nc,i_194
.i_195
	ld	hl,_baddies
	push	hl
	ld	hl,(_enoffsmasi)
	ld	h,0
	add	hl,hl
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	ld	bc,8
	add	hl,bc
	push	hl
	ld	hl,_baddies
	push	hl
	ld	hl,(_enoffsmasi)
	ld	h,0
	add	hl,hl
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	ld	bc,8
	add	hl,bc
	call	l_gchar
	call	l_neg
	ld	a,l
	call	l_sxt
	pop	de
	ld	a,l
	ld	(de),a
.i_194
	ld	hl,(_gpen_cy)
	ld	h,0
	push	hl
	ld	hl,_baddies
	push	hl
	ld	hl,(_enoffsmasi)
	ld	h,0
	add	hl,hl
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	ld	bc,5
	add	hl,bc
	ld	l,(hl)
	ld	h,0
	pop	de
	call	l_eq
	jp	c,i_198
	ld	hl,(_gpen_cy)
	ld	h,0
	push	hl
	ld	hl,_baddies
	push	hl
	ld	hl,(_enoffsmasi)
	ld	h,0
	add	hl,hl
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	ld	bc,7
	add	hl,bc
	ld	l,(hl)
	ld	h,0
	pop	de
	call	l_eq
	jp	nc,i_197
.i_198
	ld	hl,_baddies
	push	hl
	ld	hl,(_enoffsmasi)
	ld	h,0
	add	hl,hl
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	ld	bc,9
	add	hl,bc
	push	hl
	ld	hl,_baddies
	push	hl
	ld	hl,(_enoffsmasi)
	ld	h,0
	add	hl,hl
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	ld	bc,9
	add	hl,bc
	call	l_gchar
	call	l_neg
	ld	a,l
	call	l_sxt
	pop	de
	ld	a,l
	ld	(de),a
.i_197
	jp	i_190
.i_200
	ld	hl,1 % 256	;const
	ld	a,l
	ld	(_animate),a
	ld	h,0
	ld	a,l
	ld	(_killable),a
	ld	h,0
	ld	a,l
	ld	(_active),a
	ld	hl,_en_an_x
	push	hl
	ld	hl,(_gpit)
	ld	h,0
	add	hl,hl
	pop	de
	add	hl,de
	ld	e,(hl)
	inc	hl
	ld	d,(hl)
	ld	l,#(6 % 256)
	call	l_asr
	ld	h,0
	ld	a,l
	ld	(_gpen_cx),a
	ld	hl,_en_an_y
	push	hl
	ld	hl,(_gpit)
	ld	h,0
	add	hl,hl
	pop	de
	add	hl,de
	ld	e,(hl)
	inc	hl
	ld	d,(hl)
	ld	l,#(6 % 256)
	call	l_asr
	ld	h,0
	ld	a,l
	ld	(_gpen_cy),a
	ld	de,_en_an_state
	ld	hl,(_gpit)
	ld	h,0
	add	hl,de
	ld	l,(hl)
	ld	h,0
.i_203
	ld	a,l
	cp	#(0% 256)
	jp	z,i_204
	cp	#(1% 256)
	jp	z,i_206
	cp	#(2% 256)
	jp	z,i_209
	jp	i_202
.i_204
	ld	hl,(_gpx)
	ld	h,0
	push	hl
	ld	hl,(_gpy)
	ld	h,0
	push	hl
	ld	hl,(_gpen_cx)
	ld	h,0
	push	hl
	ld	hl,(_gpen_cy)
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
	jp	nc,i_205
	ld	de,_en_an_state
	ld	hl,(_gpit)
	ld	h,0
	add	hl,de
	ld	(hl),#(1 % 256 % 256)
	ld	l,(hl)
	ld	h,0
.i_205
	jp	i_202
.i_206
	ld	hl,(_gpx)
	ld	h,0
	push	hl
	ld	hl,(_gpy)
	ld	h,0
	push	hl
	ld	hl,(_gpen_cx)
	ld	h,0
	push	hl
	ld	hl,(_gpen_cy)
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
	jp	nc,i_207
	ld	de,_en_an_state
	ld	hl,(_gpit)
	ld	h,0
	add	hl,de
	ld	(hl),#(2 % 256 % 256)
	ld	l,(hl)
	ld	h,0
	jp	i_208
.i_207
	ld	hl,_en_an_vx
	push	hl
	ld	hl,(_gpit)
	ld	h,0
	add	hl,hl
	pop	de
	add	hl,de
	push	hl
	ld	hl,_en_an_vx
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
	ld	hl,(_p_x)
	push	hl
	ld	hl,_en_an_x
	push	hl
	ld	hl,(_gpit)
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
	ld	hl,16	;const
	push	hl
	call	_addsign
	pop	bc
	pop	bc
	pop	de
	add	hl,de
	push	hl
	ld	hl,65408	;const
	push	hl
	ld	hl,128	;const
	push	hl
	call	_limit
	pop	bc
	pop	bc
	pop	bc
	pop	de
	call	l_pint
	ld	hl,_en_an_vy
	push	hl
	ld	hl,(_gpit)
	ld	h,0
	add	hl,hl
	pop	de
	add	hl,de
	push	hl
	ld	hl,_en_an_vy
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
	ld	hl,(_p_y)
	push	hl
	ld	hl,_en_an_y
	push	hl
	ld	hl,(_gpit)
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
	ld	hl,16	;const
	push	hl
	call	_addsign
	pop	bc
	pop	bc
	pop	de
	add	hl,de
	push	hl
	ld	hl,65408	;const
	push	hl
	ld	hl,128	;const
	push	hl
	call	_limit
	pop	bc
	pop	bc
	pop	bc
	pop	de
	call	l_pint
	ld	hl,_en_an_x
	push	hl
	ld	hl,(_gpit)
	ld	h,0
	add	hl,hl
	pop	de
	add	hl,de
	push	hl
	ld	hl,_en_an_x
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
	ld	hl,_en_an_vx
	push	hl
	ld	hl,(_gpit)
	ld	h,0
	add	hl,hl
	pop	de
	add	hl,de
	call	l_gint	;
	pop	de
	add	hl,de
	push	hl
	ld	hl,0	;const
	push	hl
	ld	hl,14336	;const
	push	hl
	call	_limit
	pop	bc
	pop	bc
	pop	bc
	pop	de
	call	l_pint
	ld	hl,_en_an_y
	push	hl
	ld	hl,(_gpit)
	ld	h,0
	add	hl,hl
	pop	de
	add	hl,de
	push	hl
	ld	hl,_en_an_y
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
	ld	hl,_en_an_vy
	push	hl
	ld	hl,(_gpit)
	ld	h,0
	add	hl,hl
	pop	de
	add	hl,de
	call	l_gint	;
	pop	de
	add	hl,de
	push	hl
	ld	hl,0	;const
	push	hl
	ld	hl,9216	;const
	push	hl
	call	_limit
	pop	bc
	pop	bc
	pop	bc
	pop	de
	call	l_pint
.i_208
	jp	i_202
.i_209
	ld	hl,_en_an_x
	push	hl
	ld	hl,(_gpit)
	ld	h,0
	add	hl,hl
	pop	de
	add	hl,de
	push	hl
	ld	e,(hl)
	inc	hl
	ld	d,(hl)
	push	de
	ld	hl,_baddies
	push	hl
	ld	hl,(_enoffsmasi)
	ld	h,0
	add	hl,hl
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	ld	e,(hl)
	inc	hl
	ld	d,(hl)
	push	de
	ld	hl,(_gpen_cx)
	ld	h,0
	pop	de
	ex	de,hl
	and	a
	sbc	hl,de
	push	hl
	ld	hl,64	;const
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
	ld	hl,(_gpit)
	ld	h,0
	add	hl,hl
	pop	de
	add	hl,de
	push	hl
	ld	e,(hl)
	inc	hl
	ld	d,(hl)
	push	de
	ld	hl,_baddies
	push	hl
	ld	hl,(_enoffsmasi)
	ld	h,0
	add	hl,hl
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	inc	hl
	inc	hl
	ld	e,(hl)
	inc	hl
	ld	d,(hl)
	push	de
	ld	hl,(_gpen_cy)
	ld	h,0
	pop	de
	ex	de,hl
	and	a
	sbc	hl,de
	push	hl
	ld	hl,64	;const
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
	ld	hl,(_gpen_cx)
	ld	h,0
	push	hl
	ld	hl,(_gpen_cy)
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
	jp	nc,i_210
	ld	de,_en_an_state
	ld	hl,(_gpit)
	ld	h,0
	add	hl,de
	ld	(hl),#(1 % 256 % 256)
	ld	l,(hl)
	ld	h,0
.i_210
.i_202
	ld	hl,_en_an_x
	push	hl
	ld	hl,(_gpit)
	ld	h,0
	add	hl,hl
	pop	de
	add	hl,de
	ld	e,(hl)
	inc	hl
	ld	d,(hl)
	ld	l,#(6 % 256)
	call	l_asr
	ld	h,0
	ld	a,l
	ld	(_gpen_cx),a
	ld	hl,_en_an_y
	push	hl
	ld	hl,(_gpit)
	ld	h,0
	add	hl,hl
	pop	de
	add	hl,de
	ld	e,(hl)
	inc	hl
	ld	d,(hl)
	ld	l,#(6 % 256)
	call	l_asr
	ld	h,0
	ld	a,l
	ld	(_gpen_cy),a
	ld	de,_en_an_state
	ld	hl,(_gpit)
	ld	h,0
	add	hl,de
	ld	a,(hl)
	cp	#(2 % 256)
	jp	nz,i_212
	ld	hl,(_gpen_cx)
	ld	h,0
	push	hl
	ld	hl,_baddies
	push	hl
	ld	hl,(_enoffsmasi)
	ld	h,0
	add	hl,hl
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	call	l_gint	;
	pop	de
	call	l_eq
	jp	nc,i_212
	ld	hl,(_gpen_cy)
	ld	h,0
	push	hl
	ld	hl,_baddies
	push	hl
	ld	hl,(_enoffsmasi)
	ld	h,0
	add	hl,hl
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	inc	hl
	inc	hl
	call	l_gint	;
	pop	de
	call	l_eq
	jr	c,i_213_i_212
.i_212
	jp	i_211
.i_213_i_212
	ld	de,_en_an_state
	ld	hl,(_gpit)
	ld	h,0
	add	hl,de
	ld	(hl),#(0 % 256 % 256)
	ld	l,(hl)
	ld	h,0
.i_211
	jp	i_190
.i_214
	ld	hl,_baddies
	push	hl
	ld	hl,(_enoffsmasi)
	ld	h,0
	add	hl,hl
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	ld	bc,7
	add	hl,bc
	ld	(hl),#(0 % 256 % 256)
	ld	hl,_baddies
	push	hl
	ld	hl,(_enoffsmasi)
	ld	h,0
	add	hl,hl
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	ld	bc,9
	add	hl,bc
	call	l_gchar
	ld	a,h
	or	l
	jp	z,i_215
	ld	hl,_baddies
	push	hl
	ld	hl,(_enoffsmasi)
	ld	h,0
	add	hl,hl
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	push	hl
	ld	e,(hl)
	inc	hl
	ld	d,(hl)
	push	de
	ld	hl,_baddies
	push	hl
	ld	hl,(_enoffsmasi)
	ld	h,0
	add	hl,hl
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	ld	bc,8
	add	hl,bc
	call	l_gchar
	pop	de
	add	hl,de
	pop	de
	call	l_pint
	ld	hl,_en_an_n_f
	push	hl
	ld	hl,(_gpit)
	ld	h,0
	add	hl,hl
	pop	de
	add	hl,de
	push	hl
	ld	hl,_arrow_sprites
	push	hl
	ld	hl,_baddies
	push	hl
	ld	hl,(_enoffsmasi)
	ld	h,0
	add	hl,hl
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	ld	bc,8
	add	hl,bc
	call	l_gchar
	ld	de,0	;const
	ex	de,hl
	call	l_lt
	jp	nc,i_216
	ld	hl,0	;const
	jp	i_217
.i_216
	ld	hl,144	;const
.i_217
	pop	de
	add	hl,de
	pop	de
	call	l_pint
	ld	hl,_baddies
	push	hl
	ld	hl,(_enoffsmasi)
	ld	h,0
	add	hl,hl
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	ld	e,(hl)
	inc	hl
	ld	d,(hl)
	push	de
	ld	hl,_baddies
	push	hl
	ld	hl,(_enoffsmasi)
	ld	h,0
	add	hl,hl
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	ld	bc,6
	add	hl,bc
	ld	l,(hl)
	ld	h,0
	pop	de
	call	l_eq
	jp	nc,i_218
	ld	hl,_baddies
	push	hl
	ld	hl,(_enoffsmasi)
	ld	h,0
	add	hl,hl
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	ld	bc,9
	add	hl,bc
	push	hl
	ld	hl,0	;const
	ld	a,l
	call	l_sxt
	pop	de
	ld	a,l
	ld	(de),a
.i_218
	jp	i_219
.i_215
	ld	hl,_en_an_n_f
	push	hl
	ld	hl,(_gpit)
	ld	h,0
	add	hl,hl
	pop	de
	add	hl,de
	push	hl
	ld	hl,_sprite_18_a
	pop	de
	call	l_pint
	ld	hl,(_enemy_shoots)
	ld	h,0
	ld	de,0
	call	l_eq
	jp	c,i_221
	ld	hl,(_gpy)
	ld	h,0
	push	hl
	ld	hl,_baddies
	push	hl
	ld	hl,(_enoffsmasi)
	ld	h,0
	add	hl,hl
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	ld	bc,5
	add	hl,bc
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,_baddies
	push	hl
	ld	hl,(_enoffsmasi)
	ld	h,0
	add	hl,hl
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	ld	bc,5
	add	hl,bc
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,15 % 256	;const
	push	hl
	push	hl
	call	_addons_between
	pop	bc
	pop	bc
	pop	bc
	pop	bc
	pop	bc
	ld	a,h
	or	l
	jp	z,i_222
	ld	hl,(_gpx)
	ld	h,0
	push	hl
	ld	hl,_baddies
	push	hl
	ld	hl,(_enoffsmasi)
	ld	h,0
	add	hl,hl
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	ld	bc,4
	add	hl,bc
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,_baddies
	push	hl
	ld	hl,(_enoffsmasi)
	ld	h,0
	add	hl,hl
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	ld	bc,6
	add	hl,bc
	ld	l,(hl)
	ld	h,0
	push	hl
	ld	hl,15 % 256	;const
	push	hl
	ld	hl,31 % 256	;const
	push	hl
	call	_addons_between
	pop	bc
	pop	bc
	pop	bc
	pop	bc
	pop	bc
	ld	a,h
	or	l
	jp	z,i_222
	ld	hl,1	;const
	jr	i_223
.i_222
	ld	hl,0	;const
.i_223
	ld	a,h
	or	l
	jp	nz,i_221
	jr	i_224
.i_221
	ld	hl,1	;const
.i_224
	ld	a,h
	or	l
	jp	z,i_220
	ld	hl,_baddies
	push	hl
	ld	hl,(_enoffsmasi)
	ld	h,0
	add	hl,hl
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	ld	bc,7
	add	hl,bc
	ld	(hl),#(1 % 256 % 256)
	ld	l,(hl)
	ld	h,0
.i_220
.i_219
	ld	hl,_baddies
	push	hl
	ld	hl,(_enoffsmasi)
	ld	h,0
	add	hl,hl
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	ld	bc,7
	add	hl,bc
	ld	a,(hl)
	and	a
	jp	z,i_225
	ld	hl,_baddies
	push	hl
	ld	hl,(_enoffsmasi)
	ld	h,0
	add	hl,hl
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	ld	bc,9
	add	hl,bc
	push	hl
	pop	de
	ld	a,#(1 % 256)
	ld	(de),a
	ld	hl,_baddies
	push	hl
	ld	hl,(_enoffsmasi)
	ld	h,0
	add	hl,hl
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	push	hl
	ld	hl,_baddies
	push	hl
	ld	hl,(_enoffsmasi)
	ld	h,0
	add	hl,hl
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	ld	bc,4
	add	hl,bc
	ld	l,(hl)
	ld	h,0
	pop	de
	call	l_pint
	ld	hl,7 % 256	;const
	push	hl
	call	_beep_fx
	pop	bc
.i_225
	ld	hl,_baddies
	push	hl
	ld	hl,(_enoffsmasi)
	ld	h,0
	add	hl,hl
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	call	l_gint	;
	ld	h,0
	ld	a,l
	ld	(_gpen_cx),a
	ld	hl,_baddies
	push	hl
	ld	hl,(_enoffsmasi)
	ld	h,0
	add	hl,hl
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	inc	hl
	inc	hl
	call	l_gint	;
	ld	h,0
	ld	a,l
	ld	(_gpen_cy),a
	ld	hl,1 % 256	;const
	ld	a,l
	ld	(_active),a
	jp	i_190
.i_226
	ld	a,(_gpt)
	cp	#(15 % 256)
	jp	z,i_228
	jp	c,i_228
	ld	de,_en_an_state
	ld	hl,(_gpit)
	ld	h,0
	add	hl,de
	ld	a,(hl)
	cp	#(4 % 256)
	jr	nz,i_229_i_228
.i_228
	jp	i_227
.i_229_i_228
	ld	hl,_en_an_n_f
	push	hl
	ld	hl,(_gpit)
	ld	h,0
	add	hl,hl
	pop	de
	add	hl,de
	push	hl
	ld	hl,_sprite_18_a
	pop	de
	call	l_pint
.i_227
.i_190
	ld	a,(_active)
	and	a
	jp	z,i_230
	ld	a,(_animate)
	and	a
	jp	z,i_231
	ld	hl,_baddies
	push	hl
	ld	hl,(_enoffsmasi)
	ld	h,0
	add	hl,hl
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	ld	bc,8
	add	hl,bc
	call	l_gchar
	ld	a,h
	or	l
	jp	z,i_232
	ld	hl,(_gpen_cx)
	ld	h,0
	ld	bc,4
	add	hl,bc
	ex	de,hl
	ld	l,#(3 % 256)
	call	l_asr_u
	ld	de,1	;const
	ex	de,hl
	call	l_and
	jp	i_233
.i_232
	ld	hl,(_gpen_cy)
	ld	h,0
	ld	bc,4
	add	hl,bc
	ex	de,hl
	ld	l,#(3 % 256)
	call	l_asr_u
	ld	de,1	;const
	ex	de,hl
	call	l_and
.i_233
	ld	h,0
	ld	a,l
	ld	(_gpjt),a
	ld	hl,_en_an_n_f
	push	hl
	ld	hl,(_gpit)
	ld	h,0
	add	hl,hl
	pop	de
	add	hl,de
	push	hl
	ld	hl,_enem_frames
	push	hl
	ld	de,_en_an_base_frame
	ld	hl,(_gpit)
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
.i_231
	ld	a,(_gpt)
	cp	#(8 % 256)
	jp	nz,i_234
	ld	a,(_pregotten)
	and	a
	jp	z,i_236
	ld	a,(_p_gotten)
	cp	#(0 % 256)
	jp	nz,i_236
	ld	a,(_p_jmp_on)
	cp	#(0 % 256)
	jr	z,i_237_i_236
.i_236
	jp	i_235
.i_237_i_236
	ld	hl,_baddies
	push	hl
	ld	hl,(_enoffsmasi)
	ld	h,0
	add	hl,hl
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	ld	bc,8
	add	hl,bc
	call	l_gchar
	ld	a,h
	or	l
	jp	z,i_238
	ld	hl,(_gpy)
	ld	h,0
	ld	bc,16
	add	hl,bc
	push	hl
	ld	hl,_baddies
	push	hl
	ld	hl,(_enoffsmasi)
	ld	h,0
	add	hl,hl
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	inc	hl
	inc	hl
	call	l_gint	;
	pop	de
	call	l_uge
	jp	nc,i_240
	ld	hl,(_gpy)
	ld	h,0
	ld	bc,10
	add	hl,bc
	push	hl
	ld	hl,_baddies
	push	hl
	ld	hl,(_enoffsmasi)
	ld	h,0
	add	hl,hl
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	inc	hl
	inc	hl
	call	l_gint	;
	pop	de
	call	l_ule
	jr	c,i_241_i_240
.i_240
	jp	i_239
.i_241_i_240
	ld	a,#(1 % 256 % 256)
	ld	(_p_gotten),a
	ld	hl,_baddies
	push	hl
	ld	hl,(_enoffsmasi)
	ld	h,0
	add	hl,hl
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	ld	bc,8
	add	hl,bc
	call	l_gchar
	ex	de,hl
	ld	l,#(6 % 256)
	call	l_asl
	ld	(_ptgmx),hl
	ld	hl,_baddies
	push	hl
	ld	hl,(_enoffsmasi)
	ld	h,0
	add	hl,hl
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	inc	hl
	inc	hl
	call	l_gint	;
	ld	bc,-16
	add	hl,bc
	ex	de,hl
	ld	l,#(6 % 256)
	call	l_asl
	ld	(_p_y),hl
	ex	de,hl
	ld	l,#(6 % 256)
	call	l_asr
	ld	h,0
	ld	a,l
	ld	(_gpy),a
.i_239
.i_238
	ld	hl,_baddies
	push	hl
	ld	hl,(_enoffsmasi)
	ld	h,0
	add	hl,hl
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	ld	bc,9
	add	hl,bc
	call	l_gchar
	ld	de,0	;const
	ex	de,hl
	call	l_lt
	jp	nc,i_243
	ld	hl,(_gpy)
	ld	h,0
	ld	bc,18
	add	hl,bc
	push	hl
	ld	hl,_baddies
	push	hl
	ld	hl,(_enoffsmasi)
	ld	h,0
	add	hl,hl
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	inc	hl
	inc	hl
	call	l_gint	;
	pop	de
	call	l_uge
	jp	nc,i_243
	ld	hl,(_gpy)
	ld	h,0
	ld	bc,10
	add	hl,bc
	push	hl
	ld	hl,_baddies
	push	hl
	ld	hl,(_enoffsmasi)
	ld	h,0
	add	hl,hl
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	inc	hl
	inc	hl
	call	l_gint	;
	pop	de
	call	l_ule
	jp	c,i_245
.i_243
	jr	i_243_i_244
.i_244
	ld	a,h
	or	l
	jp	nz,i_245
.i_243_i_244
	ld	hl,_baddies
	push	hl
	ld	hl,(_enoffsmasi)
	ld	h,0
	add	hl,hl
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	ld	bc,9
	add	hl,bc
	call	l_gchar
	ld	de,0	;const
	ex	de,hl
	call	l_gt
	jp	nc,i_246
	ld	hl,(_gpy)
	ld	h,0
	ld	bc,17
	add	hl,bc
	push	hl
	ld	hl,_baddies
	push	hl
	ld	hl,(_enoffsmasi)
	ld	h,0
	add	hl,hl
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	ld	bc,9
	add	hl,bc
	call	l_gchar
	pop	de
	add	hl,de
	push	hl
	ld	hl,_baddies
	push	hl
	ld	hl,(_enoffsmasi)
	ld	h,0
	add	hl,hl
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	inc	hl
	inc	hl
	call	l_gint	;
	pop	de
	call	l_uge
	jp	nc,i_246
	ld	hl,(_gpy)
	ld	h,0
	ld	bc,10
	add	hl,bc
	push	hl
	ld	hl,_baddies
	push	hl
	ld	hl,(_enoffsmasi)
	ld	h,0
	add	hl,hl
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	inc	hl
	inc	hl
	call	l_gint	;
	pop	de
	call	l_ule
	jp	nc,i_246
	ld	hl,1	;const
	jr	i_247
.i_246
	ld	hl,0	;const
.i_247
	ld	a,h
	or	l
	jp	nz,i_245
	jr	i_248
.i_245
	ld	hl,1	;const
.i_248
	ld	a,h
	or	l
	jp	z,i_242
	ld	a,#(1 % 256 % 256)
	ld	(_p_gotten),a
	ld	hl,_baddies
	push	hl
	ld	hl,(_enoffsmasi)
	ld	h,0
	add	hl,hl
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	ld	bc,9
	add	hl,bc
	call	l_gchar
	ex	de,hl
	ld	l,#(6 % 256)
	call	l_asl
	ld	(_ptgmy),hl
	ld	hl,_baddies
	push	hl
	ld	hl,(_enoffsmasi)
	ld	h,0
	add	hl,hl
	ld	b,h
	ld	c,l
	add	hl,bc
	add	hl,bc
	add	hl,hl
	pop	de
	add	hl,de
	inc	hl
	inc	hl
	call	l_gint	;
	ld	bc,-16
	add	hl,bc
	ex	de,hl
	ld	l,#(6 % 256)
	call	l_asl
	ld	(_p_y),hl
	ex	de,hl
	ld	l,#(6 % 256)
	call	l_asr
	ld	h,0
	ld	a,l
	ld	(_gpy),a
	ld	hl,0	;const
	ld	(_p_vy),hl
.i_242
.i_235
	jp	i_249
.i_234
	ld	a,(_tocado)
	cp	#(0 % 256)
	jp	nz,i_251
	ld	hl,(_gpx)
	ld	h,0
	push	hl
	ld	hl,(_gpy)
	ld	h,0
	push	hl
	ld	hl,(_gpen_cx)
	ld	h,0
	push	hl
	ld	hl,(_gpen_cy)
	ld	h,0
	push	hl
	call	_collide
	pop	bc
	pop	bc
	pop	bc
	pop	bc
	ld	a,h
	or	l
	jp	z,i_251
	ld	a,(_p_state)
	cp	#(0 % 256)
	jr	z,i_252_i_251
.i_251
	jp	i_250
.i_252_i_251
	ld	a,(_p_life)
	and	a
	jp	z,i_253
	ld	hl,1 % 256	;const
	ld	a,l
	ld	(_tocado),a
.i_253
	ld	hl,2 % 256	;const
	push	hl
	call	_kill_player
	pop	bc
.i_250
.i_249
	call	_enem_move_spr_abs
	jp	i_254
.i_230
	; enter: IX = sprite structure address
	; IY = clipping rectangle, set it to "ClipStruct" for full screen
	; BC = animate bitdef displacement (0 for no animation)
	; H = new row coord in chars
	; L = new col coord in chars
	; D = new horizontal rotation (0..7) ie horizontal pixel position
	; E = new vertical rotation (0..7) ie vertical pixel position
	ld a, (_gpit)
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
.i_254
	jp	i_180
.i_181
	ret



._active_sleep
.i_257
	ld	hl,250 % 256	;const
	ld	a,l
	ld	(_gpjt),a
.i_260
	ld	hl,1 % 256	;const
	ld	a,l
	ld	(_gpit),a
.i_258
	ld	hl,(_gpjt)
	ld	h,0
	dec	hl
	ld	a,l
	ld	(_gpjt),a
	ld	a,h
	or	l
	jp	nz,i_260
.i_259
	call	_button_pressed
	ld	a,h
	or	l
	jp	nz,i_256
.i_261
.i_255
	pop	de
	pop	hl
	dec	hl
	push	hl
	push	de
	ld	a,h
	or	l
	jp	nz,i_257
.i_256
	ld	hl,0 % 256	;const
	push	hl
	call	sp_Border
	pop	bc
	ret



._run_fire_script
	ld	hl,42 % 256	;const
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


;	SECTION	text

._keyscancodes
	defw	763,765,509,1277,383,0,507,509,735,479
	defw	383,0
;	SECTION	code



._select_joyfunc
	; Music generated by beepola
	call musicstart
.i_263
	call	sp_GetKey
	ld	h,0
	ld	a,l
	ld	(_gpit),a
	cp	#(49 % 256)
	jp	z,i_266
	ld	a,(_gpit)
	cp	#(50 % 256)
	jp	nz,i_265
.i_266
	ld	hl,sp_JoyKeyboard
	ld	(_joyfunc),hl
	ld	hl,(_gpit)
	ld	h,0
	ld	bc,-49
	add	hl,bc
	ld	a,h
	or	l
	jp	z,i_268
	ld	hl,6	;const
	jp	i_269
.i_268
	ld	hl,0	;const
.i_269
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
	jp	i_264
.i_265
	ld	a,(_gpit)
	cp	#(51 % 256)
	jp	nz,i_271
	ld	hl,sp_JoyKempston
	ld	(_joyfunc),hl
	jp	i_264
.i_271
	ld	a,(_gpit)
	cp	#(52 % 256)
	jp	nz,i_273
	ld	hl,sp_JoySinclair1
	ld	(_joyfunc),hl
	jp	i_264
.i_273
.i_272
.i_270
	jp	i_263
.i_264
	di
	ret



._update_hud
	ld	hl,(_p_life)
	ld	h,0
	ex	de,hl
	ld	hl,(_life_old)
	ld	h,0
	call	l_ne
	jp	nc,i_274
	ld	hl,1 % 256	;const
	push	hl
	ld	hl,23 % 256	;const
	push	hl
	ld	hl,(_p_life)
	ld	h,0
	push	hl
	call	_print_number2
	pop	bc
	pop	bc
	pop	bc
	ld	hl,(_p_life)
	ld	h,0
	ld	a,l
	ld	(_life_old),a
.i_274
	ld	hl,(_flags+1)
	ld	h,0
	ex	de,hl
	ld	hl,(_flag_old)
	ld	h,0
	call	l_ne
	jp	nc,i_275
	ld	hl,4 % 256	;const
	push	hl
	ld	hl,23 % 256	;const
	push	hl
	ld	hl,(_flags+1)
	ld	h,0
	push	hl
	call	_print_number2
	pop	bc
	pop	bc
	pop	bc
	ld	hl,(_flags+1)
	ld	h,0
	ld	a,l
	ld	(_flag_old),a
.i_275
	ret



._flick_screen
	ld	hl,(_p_x)
	ld	de,0	;const
	call	l_eq
	jp	nc,i_277
	ld	hl,(_p_vx)
	ld	de,0	;const
	ex	de,hl
	call	l_lt
	jp	nc,i_277
	ld	a,(_x_pant)
	cp	#(0 % 256)
	jp	z,i_277
	jp	c,i_277
	jr	i_278_i_277
.i_277
	jp	i_276
.i_278_i_277
	ld	hl,(_n_pant)
	ld	h,0
	dec	hl
	ld	h,0
	ld	a,l
	ld	(_n_pant),a
	ld	hl,14336	;const
	ld	(_p_x),hl
.i_276
	ld	hl,(_p_x)
	ld	de,14336	;const
	call	l_eq
	jp	nc,i_280
	ld	hl,(_p_vx)
	ld	de,0	;const
	ex	de,hl
	call	l_gt
	jp	nc,i_280
	ld	a,(_x_pant)
	cp	#(9 % 256)
	jp	z,i_280
	jr	c,i_281_i_280
.i_280
	jp	i_279
.i_281_i_280
	ld	hl,(_n_pant)
	ld	h,0
	inc	hl
	ld	h,0
	ld	a,l
	ld	(_n_pant),a
	ld	hl,0	;const
	ld	(_p_x),hl
.i_279
	ld	hl,(_p_y)
	ld	de,0	;const
	call	l_eq
	jp	nc,i_283
	ld	hl,(_p_vy)
	ld	de,0	;const
	ex	de,hl
	call	l_lt
	jp	nc,i_283
	ld	a,(_y_pant)
	cp	#(0 % 256)
	jp	z,i_283
	jp	c,i_283
	jr	i_284_i_283
.i_283
	jp	i_282
.i_284_i_283
	ld	hl,(_n_pant)
	ld	h,0
	ld	bc,-10
	add	hl,bc
	ld	h,0
	ld	a,l
	ld	(_n_pant),a
	ld	hl,9216	;const
	ld	(_p_y),hl
.i_282
	ld	hl,(_p_y)
	ld	de,9216	;const
	call	l_eq
	jp	nc,i_286
	ld	hl,(_p_vy)
	ld	de,0	;const
	ex	de,hl
	call	l_gt
	jp	nc,i_286
	ld	a,(_y_pant)
	cp	#(1 % 256)
	jp	z,i_286
	jr	c,i_287_i_286
.i_286
	jp	i_285
.i_287_i_286
	ld	hl,(_n_pant)
	ld	h,0
	ld	bc,10
	add	hl,bc
	ld	h,0
	ld	a,l
	ld	(_n_pant),a
	ld	hl,0	;const
	ld	(_p_y),hl
	ld	hl,(_p_vy)
	ld	de,256	;const
	ex	de,hl
	call	l_gt
	jp	nc,i_288
	ld	hl,256	;const
	ld	(_p_vy),hl
.i_288
.i_285
	ret



._hide_sprites
	ld	hl,2	;const
	add	hl,sp
	ld	l,(hl)
	ld	h,0
	ld	a,h
	or	l
	jp	nz,i_289
	ld ix, (_sp_player)
	ld iy, vpClipStruct
	ld bc, 0
	ld hl, 0xdede
	ld de, 0
	call SPMoveSprAbs
.i_289
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
	call	_cortina
	di
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
	ld	hl,60840	;const
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
.i_292
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
.i_290
	ld	hl,(_gpit)
	ld	h,0
	ld	a,h
	or	l
	jp	nz,i_292
.i_291
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
	jp	i_295
.i_293
	ld	hl,_gpit
	ld	a,(hl)
	inc	(hl)
.i_295
	ld	a,(_gpit)
	cp	#(3 % 256)
	jp	z,i_294
	jp	nc,i_294
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
	jp	i_293
.i_294
.i_296
	call	sp_UpdateNow
	ld	hl,_s_title
	push	hl
	ld	hl,16384	;const
	push	hl
	call	_unpack
	pop	bc
	pop	bc
	call	_select_joyfunc
	call	_msc_init_all
	ld	a,#(0 % 256 % 256)
	ld	(_script_result),a
	ld	a,#(1 % 256 % 256)
	ld	(_playing),a
	ld	hl,_main_script
	ld	(_main_script_offset),hl
	ld	hl,10 % 256	;const
	ld	a,l
	ld	(_n_pant),a
	call	_init_player
	ld	a,#(0 % 256 % 256)
	ld	(_maincounter),a
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_script_result),a
	call	_msc_init_all
	ld	hl,40 % 256	;const
	push	hl
	call	_run_script
	pop	bc
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
	ld	a,#(255 % 256 % 256)
	ld	(_o_pant),a
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_no_draw),a
.i_298
	ld	a,(_playing)
	and	a
	jp	z,i_299
	ld	hl,(_n_pant)
	ld	h,0
	ex	de,hl
	ld	hl,(_o_pant)
	ld	h,0
	call	l_ne
	jp	nc,i_300
	ld	hl,(_n_pant)
	ld	h,0
	ld	a,l
	ld	(_o_pant),a
	call	_draw_scr
.i_300
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
	call	_move
	call	_mueve_bicharracos
	ld	a,(_p_state)
	ld	e,a
	ld	d,0
	ld	hl,2	;const
	call	l_and
	call	l_lneg
	jp	c,i_302
	ld	a,(_half_life)
	cp	#(0 % 256)
	jp	nz,i_301
.i_302
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
	add 1
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
	jp	i_304
.i_301
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
.i_304
	ld	hl,(_p_n_f)
	ld	(_p_c_f),hl
	call	sp_UpdateNow
	ld	a,(_p_state)
	cp	#(2 % 256)
	jp	nz,i_305
	ld	hl,_p_state_ct
	ld	a,(hl)
	dec	(hl)
	ld	a,(_p_state_ct)
	and	a
	jp	nz,i_306
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_p_state),a
.i_306
.i_305
	ld	hl,(_joyfunc)
	push	hl
	ld	hl,_keys
	pop	de
	ld	bc,i_307
	push	hl
	push	bc
	push	de
	ld	a,1
	ret
.i_307
	pop	bc
	ld	h,0
	ld	a,l
	ld	(_gpit),a
	ld	hl,_gpit
	ld	a,(hl)
	and	#(2 % 256)
	jp	nz,i_308
	ld	a,(_action_pressed)
	and	a
	jp	nz,i_309
	ld	hl,1 % 256	;const
	ld	a,l
	ld	(_action_pressed),a
	call	_run_fire_script
.i_309
	jp	i_310
.i_308
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_action_pressed),a
.i_310
	ld	a,(_f_zone_ac)
	and	a
	jp	z,i_311
	ld	hl,(_gpx)
	ld	h,0
	ex	de,hl
	ld	hl,(_fzx1)
	ld	h,0
	call	l_uge
	jp	nc,i_313
	ld	hl,(_gpx)
	ld	h,0
	ex	de,hl
	ld	hl,(_fzx2)
	ld	h,0
	call	l_ule
	jp	nc,i_313
	ld	hl,(_gpy)
	ld	h,0
	ex	de,hl
	ld	hl,(_fzy1)
	ld	h,0
	call	l_uge
	jp	nc,i_313
	ld	hl,(_gpy)
	ld	h,0
	ex	de,hl
	ld	hl,(_fzy2)
	ld	h,0
	call	l_ule
	jr	c,i_314_i_313
.i_313
	jp	i_312
.i_314_i_313
	call	_run_fire_script
.i_312
.i_311
	ld	a,(_script_result)
	cp	#(1 % 256)
	jp	z,i_316
	ld	a,(_script_result)
	ld	e,a
	ld	d,0
	ld	hl,2	;const
	call	l_ugt
	jp	nc,i_315
.i_316
	ld	a,#(1 % 256 % 256)
	ld	(_success),a
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_playing),a
.i_315
	ld	a,(_p_life)
	cp	#(0 % 256)
	jp	z,i_319
	ld	a,(_script_result)
	cp	#(2 % 256)
	jp	nz,i_318
.i_319
	ld	hl,0 % 256	;const
	ld	a,l
	ld	(_playing),a
.i_318
	call	_flick_screen
	jp	i_298
.i_299
	ld	hl,0 % 256	;const
	push	hl
	call	_hide_sprites
	pop	bc
	call	sp_UpdateNow
	ld	hl,(_success)
	ld	h,0
	ld	a,h
	or	l
	jp	z,i_321
	call	_game_ending
	jp	i_322
.i_321
	call	_game_over
.i_322
	ld	hl,500	;const
	push	hl
	call	_active_sleep
	pop	bc
	call	_cortina
	jp	i_296
.i_297
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
	;DI
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
	;EI
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
	.MUSICDATA
	DEFB 0 ; Pattern loop begin * 2
	DEFB 26 ; Song length * 2
	DEFW 16 ; Offset to start of song (length of instrument table)
	DEFB 0 ; Multiple
	DEFW 20 ; Detune
	DEFB 0 ; Phase
	DEFB 1 ; Multiple
	DEFW 5 ; Detune
	DEFB 0 ; Phase
	DEFB 0 ; Multiple
	DEFW 10 ; Detune
	DEFB 1 ; Phase
	DEFB 1 ; Multiple
	DEFW 25 ; Detune
	DEFB 5 ; Phase
	.PATTERNDATA DEFW PAT0
	DEFW PAT1
	DEFW PAT2
	DEFW PAT3
	DEFW PAT8
	DEFW PAT4
	DEFW PAT5
	DEFW PAT6
	DEFW PAT7
	DEFW PAT4
	DEFW PAT5
	DEFW PAT10
	DEFW PAT9
	; *** Pattern data - $00 marks the end of a pattern ***
	.PAT0
	DEFB $BD,2
	DEFB 149
	DEFB 149
	DEFB 6
	DEFB 151
	DEFB 6
	DEFB 152
	DEFB 6
	DEFB 154
	DEFB 6
	DEFB 156
	DEFB 148
	DEFB 6
	DEFB 157
	DEFB 6
	DEFB 160
	DEFB 6
	DEFB 161
	DEFB 6
	DEFB $00
	.PAT1
	DEFB $BD,2
	DEFB 163
	DEFB 145
	DEFB 6
	DEFB 164
	DEFB 6
	DEFB 166
	DEFB 6
	DEFB 168
	DEFB 6
	DEFB 169
	DEFB 148
	DEFB 6
	DEFB 172
	DEFB 6
	DEFB 173
	DEFB 6
	DEFB 175
	DEFB 6
	DEFB $00
	.PAT2
	DEFB $BD,2
	DEFB 176
	DEFB 149
	DEFB 6
	DEFB 175
	DEFB 6
	DEFB 173
	DEFB 6
	DEFB 172
	DEFB 6
	DEFB 173
	DEFB 151
	DEFB 6
	DEFB 175
	DEFB 6
	DEFB 176
	DEFB 6
	DEFB 175
	DEFB 6
	DEFB $00
	.PAT3
	DEFB $BD,2
	DEFB 176
	DEFB 152
	DEFB 14
	DEFB 175
	DEFB 14
	DEFB 173
	DEFB 14
	DEFB 172
	DEFB 14
	DEFB $00
	.PAT4
	DEFB $BD,2
	DEFB 149
	DEFB 149
	DEFB 118
	DEFB 2
	DEFB 190
	DEFB 161
	DEFB 3
	DEFB 151
	DEFB 161
	DEFB 118
	DEFB 2
	DEFB 190
	DEFB 149
	DEFB 118
	DEFB 2
	DEFB 190
	DEFB 161
	DEFB 126
	DEFB 2
	DEFB 151
	DEFB 161
	DEFB 3
	DEFB 152
	DEFB 149
	DEFB 121
	DEFB 2
	DEFB 190
	DEFB 161
	DEFB 118
	DEFB 2
	DEFB 190
	DEFB 148
	DEFB 123
	DEFB 2
	DEFB 190
	DEFB 160
	DEFB 122
	DEFB 2
	DEFB 154
	DEFB 160
	DEFB 121
	DEFB 2
	DEFB 190
	DEFB 148
	DEFB 123
	DEFB 2
	DEFB 190
	DEFB 160
	DEFB 126
	DEFB 2
	DEFB 190
	DEFB 160
	DEFB 118
	DEFB 2
	DEFB 156
	DEFB 148
	DEFB 118
	DEFB 2
	DEFB 190
	DEFB 160
	DEFB 126
	DEFB 2
	DEFB $00
	.PAT5
	DEFB $BD,2
	DEFB 190
	DEFB 145
	DEFB 118
	DEFB 2
	DEFB 190
	DEFB 157
	DEFB 3
	DEFB 154
	DEFB 157
	DEFB 118
	DEFB 2
	DEFB 190
	DEFB 145
	DEFB 118
	DEFB 2
	DEFB 190
	DEFB 157
	DEFB 126
	DEFB 2
	DEFB 190
	DEFB 157
	DEFB 3
	DEFB 152
	DEFB 145
	DEFB 121
	DEFB 2
	DEFB 190
	DEFB 157
	DEFB 118
	DEFB 2
	DEFB 190
	DEFB 148
	DEFB 123
	DEFB 2
	DEFB 190
	DEFB 160
	DEFB 122
	DEFB 2
	DEFB 151
	DEFB 160
	DEFB 121
	DEFB 2
	DEFB 190
	DEFB 148
	DEFB 123
	DEFB 2
	DEFB 190
	DEFB 160
	DEFB 126
	DEFB 2
	DEFB 190
	DEFB 160
	DEFB 118
	DEFB 2
	DEFB $BD,0
	DEFB 152
	DEFB 149
	DEFB 118
	DEFB 2
	DEFB 154
	DEFB 163
	DEFB 126
	DEFB 2
	DEFB $00
	.PAT6
	DEFB $BD,0
	DEFB 156
	DEFB 149
	DEFB 118
	DEFB 2
	DEFB 190
	DEFB 161
	DEFB 3
	DEFB 190
	DEFB 161
	DEFB 118
	DEFB 2
	DEFB 157
	DEFB 149
	DEFB 118
	DEFB 2
	DEFB 190
	DEFB 161
	DEFB 126
	DEFB 2
	DEFB 190
	DEFB 161
	DEFB 3
	DEFB 156
	DEFB 149
	DEFB 121
	DEFB 2
	DEFB 190
	DEFB 161
	DEFB 118
	DEFB 2
	DEFB 190
	DEFB 151
	DEFB 123
	DEFB 2
	DEFB 190
	DEFB 163
	DEFB 122
	DEFB 2
	DEFB 152
	DEFB 163
	DEFB 126
	DEFB 2
	DEFB 190
	DEFB 151
	DEFB 126
	DEFB 2
	DEFB 190
	DEFB 163
	DEFB 126
	DEFB 2
	DEFB 190
	DEFB 163
	DEFB 126
	DEFB 2
	DEFB 190
	DEFB 151
	DEFB 126
	DEFB 2
	DEFB 190
	DEFB 163
	DEFB 126
	DEFB 2
	DEFB $00
	.PAT7
	DEFB $BD,6
	DEFB 164
	DEFB 152
	DEFB 118
	DEFB 2
	DEFB 190
	DEFB 164
	DEFB 3
	DEFB 190
	DEFB 164
	DEFB 118
	DEFB 2
	DEFB 176
	DEFB 152
	DEFB 118
	DEFB 2
	DEFB 188
	DEFB 164
	DEFB 126
	DEFB 2
	DEFB 176
	DEFB 164
	DEFB 3
	DEFB 188
	DEFB 152
	DEFB 121
	DEFB 2
	DEFB 164
	DEFB 164
	DEFB 118
	DEFB 2
	DEFB 166
	DEFB 154
	DEFB 123
	DEFB 2
	DEFB 190
	DEFB 154
	DEFB 122
	DEFB 2
	DEFB 190
	DEFB 166
	DEFB 126
	DEFB 2
	DEFB 178
	DEFB 154
	DEFB 126
	DEFB 2
	DEFB 188
	DEFB 154
	DEFB 126
	DEFB 2
	DEFB 178
	DEFB 166
	DEFB 126
	DEFB 2
	DEFB 188
	DEFB 156
	DEFB 126
	DEFB 2
	DEFB 166
	DEFB 157
	DEFB 126
	DEFB 2
	DEFB $00
	.PAT8
	DEFB $BD,0
	DEFB 176
	DEFB 154
	DEFB 8
	DEFB 175
	DEFB 152
	DEFB 8
	DEFB 173
	DEFB 151
	DEFB 8
	DEFB 172
	DEFB 149
	DEFB 8
	DEFB 169
	DEFB 148
	DEFB 8
	DEFB 168
	DEFB 145
	DEFB 8
	DEFB 166
	DEFB 144
	DEFB 8
	DEFB 164
	DEFB 142
	DEFB 8
	DEFB 163
	DEFB 140
	DEFB 32
	DEFB 161
	DEFB 149
	DEFB 32
	DEFB $00
	.PAT9
	DEFB $BD,0
	DEFB 171
	DEFB 152
	DEFB 118
	DEFB 2
	DEFB 190
	DEFB 164
	DEFB 3
	DEFB 169
	DEFB 164
	DEFB 118
	DEFB 2
	DEFB 190
	DEFB 152
	DEFB 118
	DEFB 2
	DEFB 168
	DEFB 164
	DEFB 126
	DEFB 2
	DEFB 190
	DEFB 164
	DEFB 3
	DEFB 166
	DEFB 152
	DEFB 121
	DEFB 2
	DEFB 190
	DEFB 164
	DEFB 118
	DEFB 2
	DEFB 190
	DEFB 154
	DEFB 123
	DEFB 2
	DEFB 190
	DEFB 154
	DEFB 122
	DEFB 2
	DEFB 168
	DEFB 166
	DEFB 126
	DEFB 2
	DEFB 190
	DEFB 154
	DEFB 126
	DEFB 2
	DEFB 169
	DEFB 154
	DEFB 126
	DEFB 2
	DEFB 190
	DEFB 166
	DEFB 126
	DEFB 2
	DEFB 190
	DEFB 156
	DEFB 126
	DEFB 2
	DEFB 190
	DEFB 157
	DEFB 126
	DEFB 2
	DEFB $00
	.PAT10
	DEFB $BD,0
	DEFB 156
	DEFB 149
	DEFB 118
	DEFB 2
	DEFB 190
	DEFB 161
	DEFB 3
	DEFB 190
	DEFB 161
	DEFB 118
	DEFB 2
	DEFB 157
	DEFB 149
	DEFB 118
	DEFB 2
	DEFB 190
	DEFB 161
	DEFB 126
	DEFB 2
	DEFB 190
	DEFB 161
	DEFB 3
	DEFB 159
	DEFB 149
	DEFB 121
	DEFB 2
	DEFB 190
	DEFB 161
	DEFB 118
	DEFB 2
	DEFB 190
	DEFB 151
	DEFB 123
	DEFB 2
	DEFB 190
	DEFB 163
	DEFB 122
	DEFB 2
	DEFB 190
	DEFB 163
	DEFB 126
	DEFB 2
	DEFB 190
	DEFB 151
	DEFB 126
	DEFB 2
	DEFB 190
	DEFB 163
	DEFB 126
	DEFB 2
	DEFB 190
	DEFB 163
	DEFB 126
	DEFB 2
	DEFB 171
	DEFB 151
	DEFB 126
	DEFB 2
	DEFB 169
	DEFB 163
	DEFB 126
	DEFB 2
	DEFB $00
;	SECTION	text

.i_1
	defm	"            "
	defb	0

	defm	" GAME OVER! "
	defb	0

;	SECTION	code



; --- Start of Static Variables ---

;	SECTION	bss

._sp_moviles	defs	6
._gpen_cx	defs	1
._gpen_cy	defs	1
._en_an_base_frame	defs	3
._hotspot_x	defs	1
._hotspot_y	defs	1
._en_an_c_f	defs	6
._gpen_xx	defs	1
._gpen_yy	defs	1
._map_pointer	defs	2
._en_an_state	defs	3
._flags	defs	32
._p_facing	defs	1
._p_frame	defs	1
._en_an_n_f	defs	6
._p_c_f	defs	2
._pregotten	defs	1
._hit_h	defs	1
._hit_v	defs	1
._killed_old	defs	1
._p_n_f	defs	2
._gpaux	defs	1
._map_attr	defs	150
._active	defs	1
.__n	defs	1
._do_respawn	defs	1
.__t	defs	1
.__x	defs	1
.__y	defs	1
._bs	defs	1
._life_old	defs	1
._p_engine	defs	1
._xx	defs	1
._yy	defs	1
._gen_pt	defs	2
._no_draw	defs	1
._p_state	defs	1
._ptgmx	defs	2
._ptgmy	defs	2
._warp_to_level	defs	1
._sp_player	defs	2
._killable	defs	1
._enoffs	defs	1
._silent_level	defs	1
._p_killed	defs	1
._gpen_x	defs	1
._gpen_y	defs	1
._p_jmp_ct	defs	1
._n_pant	defs	1
._p_jmp_on	defs	1
._o_pant	defs	1
._p_life	defs	1
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
._en_an_vx	defs	6
._p_keys	defs	1
._en_an_vy	defs	6
._gpjt	defs	1
._main_script_offset	defs	2
._sc_c	defs	1
._playing	defs	1
._sc_m	defs	1
._sc_n	defs	1
._keys	defs	10
._sc_x	defs	1
._sc_y	defs	1
._asm_int_2	defs	2
._p_vx	defs	2
._p_vy	defs	2
._gpxx	defs	1
._gpyy	defs	1
._objs_old	defs	1
._maincounter	defs	1
._ptx1	defs	1
._ptx2	defs	1
._pty1	defs	1
._pty2	defs	1
._pty3	defs	1
._flag_old	defs	1
._f_zone_ac	defs	1
._action_pressed	defs	1
._enemy_shoots	defs	1
._p_subframe	defs	1
._p_state_ct	defs	1
._animate	defs	1
._next_script	defs	2
._pt1	defs	1
._pt2	defs	1
._gpc	defs	1
._gpd	defs	1
._p_g	defs	1
._en_an_x	defs	6
._en_an_y	defs	6
._hit	defs	1
._gps	defs	1
._gpt	defs	1
._p_x	defs	2
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
._asm_int	defs	2
._p_facing_h	defs	1
._y_pant	defs	1
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
	XDEF	_read_vbyte
	LIB	sp_ScreenStr
	XDEF	_draw_scr
	LIB	sp_PixelUp
	XDEF	_enem_move_spr_abs
	LIB	sp_JoyFuller
	LIB	sp_MouseAMXInit
	LIB	sp_MouseAMX
	XDEF	_sp_moviles
	XDEF	_gpen_cx
	XDEF	_gpen_cy
	LIB	sp_SetMousePosAMX
	XDEF	_u_malloc
	LIB	sp_Validate
	LIB	sp_HashAdd
	XDEF	_cortina
	LIB	sp_Border
	LIB	sp_Inkey
	XDEF	_en_an_base_frame
	XDEF	_hotspot_x
	XDEF	_hotspot_y
	LIB	sp_CreateSpr
	LIB	sp_MoveSprAbs
	LIB	sp_BlockCount
	LIB	sp_AddMemory
	XDEF	_half_life
	XDEF	_en_an_c_f
	XDEF	_gpen_xx
	XDEF	_gpen_yy
	XDEF	_map_pointer
	XDEF	_en_an_state
	XDEF	_flags
	LIB	sp_PrintAt
	LIB	sp_Pause
	XDEF	_mueve_bicharracos
	LIB	sp_ListFirst
	LIB	sp_HeapSiftUp
	LIB	sp_ListCount
	XDEF	_p_facing
	XDEF	_p_frame
	XDEF	_en_an_n_f
	LIB	sp_Heapify
	XDEF	_sprite_e
	XDEF	_p_c_f
	LIB	sp_MoveSprRel
	XDEF	_hide_sprites
	XDEF	_arrow_sprites
	XDEF	_pregotten
	XDEF	_hit_h
	LIB	sp_TileArray
	LIB	sp_MouseSim
	LIB	sp_BlockFit
	XDEF	_map_buff
	XDEF	_hit_v
	LIB	sp_HeapExtract
	LIB	sp_HuffExtract
	XDEF	_killed_old
	LIB	sp_SetMousePosSim
	XDEF	_p_n_f
	XDEF	_gpaux
	XDEF	_main_script
	LIB	sp_ClearRect
	XDEF	_print_message
	LIB	sp_HuffGetState
	XDEF	_map_attr
	XDEF	_baddies
	XDEF	_active
	XDEF	_seed1
	XDEF	_seed2
	LIB	sp_ListAppend
	XDEF	_keyscancodes
	XDEF	_level
	LIB	sp_ListCreate
	LIB	sp_ListConcat
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
	LIB	sp_JoyTimexEither
	XDEF	__n
	XDEF	_flick_screen
	XDEF	_do_respawn
	XDEF	__t
	XDEF	__x
	XDEF	__y
	XDEF	_bs
	XDEF	_life_old
	LIB	sp_Invalidate
	LIB	sp_CreateGenericISR
	LIB	sp_JoyKeyboard
	LIB	sp_FreeBlock
	LIB	sp_PrintAtDiff
	XDEF	_run_fire_script
	XDEF	_p_engine
	XDEF	_addons_between
	XDEF	_xx
	XDEF	_yy
	XDEF	_gen_pt
	XDEF	_no_draw
	XDEF	_read_byte
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
	XDEF	_warp_to_level
	XDEF	_sprite_16_a
	XDEF	_sprite_16_b
	XDEF	_sprite_16_c
	XDEF	_sprite_18_a
	XDEF	_qtile
	XDEF	_player_frames
	LIB	sp_MoveSprRelC
	LIB	sp_InitIM2
	XDEF	_randres
	XDEF	_sp_player
	XDEF	_stop_player
	XDEF	_init_player
	XDEF	_beep_fx
	LIB	sp_GetTiles
	LIB	sp_Pallette
	LIB	sp_WaitForNoKey
	XDEF	_killable
	XDEF	_enoffs
	XDEF	_silent_level
	XDEF	_utaux
	LIB	sp_JoySinclair1
	LIB	sp_JoySinclair2
	LIB	sp_ListPrepend
	XDEF	_behs
	XDEF	_p_killed
	LIB	sp_GetAttrAddr
	XDEF	_gpen_x
	XDEF	_gpen_y
	LIB	sp_HashCreate
	LIB	sp_Random32
	LIB	sp_ListInsert
	XDEF	_p_jmp_ct
	LIB	sp_ListFree
	XDEF	_n_pant
	XDEF	_p_jmp_on
	LIB	sp_IntRect
	LIB	sp_ListLast
	LIB	sp_ListCurr
	XDEF	_o_pant
	XDEF	_p_life
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
	XDEF	_main_script_offset
	XDEF	_sc_c
	XDEF	_s_title
	XDEF	_attr
	LIB	sp_ListNext
	XDEF	_playing
	XDEF	_sc_m
	XDEF	_sc_n
	LIB	sp_HuffDecode
	XDEF	_keys
	XDEF	_rand
	LIB	sp_Swap
	XDEF	_run_entering_script
	XDEF	_sc_x
	XDEF	_sc_y
	XDEF	_print_str
	XDEF	_asm_int_2
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
	XDEF	_pty3
	XDEF	_move
	XDEF	_active_sleep
	XDEF	_flag_old
	LIB	sp_RegisterHook
	LIB	sp_ListRemove
	LIB	sp_ListTrim
	XDEF	_f_zone_ac
	LIB	sp_MoveSprAbsNC
	LIB	sp_HuffDelete
	XDEF	_update_tile
	XDEF	_readxy
	LIB	sp_ListAdd
	LIB	sp_KeyPressed
	XDEF	_button_pressed
	XDEF	_step
	XDEF	_action_pressed
	LIB	sp_PrintAtInv
	XDEF	_kill_player
	XDEF	_draw_coloured_tile_gamearea
	XDEF	_enemy_shoots
	LIB	sp_CompDListAddr
	XDEF	_p_subframe
	XDEF	_u_free
	XDEF	_abs
	XDEF	_p_state_ct
	XDEF	_s_ending
	LIB	sp_CharRight
	XDEF	_animate
	XDEF	_game_ending
	XDEF	_next_script
	XDEF	_run_script
	XDEF	_pt1
	XDEF	_pt2
	LIB	sp_InstallISR
	XDEF	_gpc
	XDEF	_gpd
	LIB	sp_HuffAccumulate
	LIB	sp_HuffSetState
	XDEF	_p_g
	XDEF	_en_an_x
	XDEF	_en_an_y
	XDEF	_hit
	XDEF	_map
	XDEF	_sprite_1_a
	XDEF	_sprite_1_b
	XDEF	_sprite_1_c
	XDEF	_gps
	XDEF	_gpt
	XDEF	_sprite_2_a
	XDEF	_sprite_2_b
	XDEF	_sprite_2_c
	LIB	sp_SwapEndian
	LIB	sp_CharLeft
	XDEF	_p_x
	XDEF	_p_y
	LIB	sp_CharDown
	LIB	sp_HeapSiftDown
	LIB	sp_HuffCreate
	XDEF	_gpx
	XDEF	_gpy
	XDEF	_update_hud
	XDEF	_sprite_3_a
	XDEF	_sprite_3_b
	XDEF	_sprite_3_c
	LIB	sp_HuffEncode
	XDEF	_sprite_4_a
	XDEF	_sprite_4_b
	XDEF	_sprite_4_c
	XDEF	_sprite_5_a
	XDEF	_sprite_5_b
	LIB	sp_JoyTimexRight
	LIB	sp_PixelRight
	XDEF	_rdx
	XDEF	_rdy
	XDEF	_script_result
	LIB	sp_Initialize
	XDEF	_sprite_5_c
	XDEF	_sprite_6_a
	XDEF	_sprite_6_b
	XDEF	_sprite_6_c
	XDEF	_tileset
	XDEF	_sprite_7_a
	LIB	sp_JoyTimexLeft
	LIB	sp_SetMousePosKempston
	XDEF	_sprite_7_b
	XDEF	_sprite_7_c
	XDEF	_script
	LIB	sp_ComputePos
	XDEF	_sprite_8_a
	XDEF	_sprite_8_b
	XDEF	_sprite_8_c
	XDEF	_sprite_9_a
	XDEF	_sprite_9_b
	XDEF	_sprite_9_c
	XDEF	_msc_init_all
	XDEF	_keys_old
	XDEF	_wall_h
	XDEF	_reloc_player
	XDEF	_enoffsmasi
	XDEF	_spacer
	XDEF	_wall_v
	LIB	sp_IntIntervals
	XDEF	_my_malloc
	XDEF	_tocado
	XDEF	_x_pant
	XDEF	_do_gravity
	LIB	sp_inp
	LIB	sp_IterateSprChar
	LIB	sp_AddColSpr
	LIB	sp_outp
	XDEF	_sc_terminado
	XDEF	_asm_int
	XDEF	_p_facing_h
	XDEF	_y_pant
	LIB	sp_IntPtInterval
	LIB	sp_RegisterHookFirst
	LIB	sp_HashLookup
	XDEF	_p_facing_v
	LIB	sp_PFill
	XDEF	_possee
	LIB	sp_HashRemove
	XDEF	_sc_continuar
	LIB	sp_CharUp
	XDEF	_orig_tile
	XDEF	_collide
	XDEF	_success
	LIB	sp_MoveSprRelNC
	XDEF	_ram_destination
	XDEF	_en_an_count
	XDEF	_select_joyfunc
	XDEF	_unpack
	XDEF	_p_disparando
	LIB	sp_IterateDList
	XDEF	_distance
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
