// msc.h
// Generated by Mojon Script Compiler v3.97 20191202 fromMT Engine MK2 v1.0+
// Copyleft 2015 The Mojon Twins

#ifdef CLEAR_FLAGS
void msc_init_all (void) {
    for (sc_c = 0; sc_c < MAX_FLAGS; ++ sc_c)
        flags [sc_c] = 0;
}
#endif

unsigned char read_byte (void) {
    #asm
        #ifdef MODE_128K
            di
            ld b, SCRIPT_PAGE
            call SetRAMBank
        #endif

            ld  hl, (_script)
            ld  a, (hl)
            ld  (_safe_byte), a
            inc hl
            ld  (_script), hl

        #ifdef MODE_128K
            ld b, 0
            call SetRAMBank
            ei
        #endif
    #endasm
    return safe_byte;
}

unsigned char read_vbyte (void) {
    #asm
        call _read_byte
        ld  a, l
        and 128
        ret z
        ld  a, l
        and 127
        ld  c, a
        ld  b, 0
        ld  hl, _flags
        add hl, bc
        ld  l, (hl)
        ld  h, 0
        ret
    #endasm
}

void readxy (void) {
    sc_x = read_vbyte ();
    sc_y = read_vbyte ();
}

#if !(defined (PHANTOMAS_ENGINE) || defined (HANNA_ENGINE))
void stop_player (void) {
    p_vx = p_vy = 0;
}
#endif

void reloc_player (void) {
#if defined (PHANTOMAS_ENGINE) || defined (HANNA_ENGINE)
    p_x = read_vbyte () << 4;
    p_y = read_vbyte () << 4;
#else
    p_x = read_vbyte () << (4+FIXBITS);
    p_y = read_vbyte () << (4+FIXBITS);
    stop_player ();
#endif
}

void read_two_bytes_D_E (void) {
    #asm
            // Read two bytes: flag #, number

            #ifdef MODE_128K
                di
                ld  b, SCRIPT_PAGE
                call SetRAMBank
            #endif

                ld  hl, (_script)
                ld  d, (hl)         // flag #
                inc hl
                ld  e, (hl)         // number
                inc hl
                ld  (_script), hl

            #ifdef MODE_128K
                ld  b, 0
                call SetRAMBank
                ei
            #endif
    #endasm
}
unsigned char *next_script;
void run_script (unsigned char whichs) {

    // main_script_offset contains the address of scripts for current level
    asm_int = main_script_offset + whichs + whichs;
#ifdef DEBUG
    debug_print_16bits (0, 23, asm_int);
#endif

#ifdef MODE_128K
    #asm
        di
        ld b, SCRIPT_PAGE
        call SetRAMBank
    #endasm
#endif

    #asm
        ld hl, (_asm_int)
        ld a, (hl)
        inc hl
        ld h, (hl)
        ld l, a
        ld  (_script), hl
    #endasm

#ifdef MODE_128K
    #asm
        ld b, 0
        call SetRAMBank
        ei
    #endasm
#endif

#ifdef DEBUG
    debug_print_16bits (5, 23, (unsigned int) script);
#endif

    if (script == 0)
        return;

    script += main_script_offset;
#ifdef DEBUG
    debug_print_16bits (10, 23, (unsigned int) script);
#endif


    while ((sc_c = read_byte ()) != 0xFF) {
        next_script = script + sc_c;
        sc_terminado = sc_continuar = 0;
        while (!sc_terminado) {
            switch (read_byte ()) {
                case 0x10:
                    // IF FLAG sc_x = sc_n
                    // Opcode: 10 sc_x sc_n
                    // readxy ();
                    // sc_terminado = (flags [sc_x] != sc_y);
                    #asm
                            call _read_two_bytes_d_e
                            // Set sc_terminado if flags [C] != E
                            ld  b, 0
                            ld  c, d
                            ld  hl, _flags
                            add hl, bc
                            ld  a, (hl)
                            cp  e
                            jr  z, _flag_equal_val_ok
                            ld  a, 1
                            ld  (_sc_terminado), a
                        ._flag_equal_val_ok
                    #endasm
                    break;
                case 0x11:
                    // IF FLAG sc_x < sc_n
                    // Opcode: 11 sc_x sc_n
                    // readxy ();
                    // sc_terminado = (flags [sc_x] >= sc_y);
                    #asm
                            call _read_two_bytes_d_e
                            // Set sc_terminado if flags [C] >= E
                            ld  b, 0
                            ld  c, d
                            ld  hl, _flags
                            add hl, bc
                            ld  a, (hl)
                            cp  e
                            jr  c, _flag_minor_val_ok ; branch if A < E
                            ld  a, 1
                            ld  (_sc_terminado), a
                        ._flag_minor_val_ok
                    #endasm
                    break;
                case 0x12:
                    // IF FLAG sc_x > sc_n
                    // Opcode: 12 sc_x sc_n
                    // readxy ();
                    // sc_terminado = (flags [sc_x] <= sc_y);
                    #asm
                            call _read_two_bytes_d_e
                            // Set sc_terminado if flags [C] <= E
                            // or...            if E >= flags [C]
                            ld  b, 0
                            ld  c, d
                            ld  hl, _flags
                            add hl, bc
                            ld  a, e     ; A = E (second byte)
                            ld  e, (hl)  ; E = flags [C]
                            cp  e
                            jr  c, _flag_equal_greater_ok ; branch if A < E
                            ld  a, 1
                            ld  (_sc_terminado), a
                        ._flag_equal_greater_ok
                    #endasm
                    break;
                case 0x13:
                    // IF FLAG sc_x <> sc_n
                    // Opcode: 13 sc_x sc_n
                    // readxy ();
                    // sc_terminado = (flags [sc_x] == sc_y);
                    #asm
                            call _read_two_bytes_d_e
                            // Set sc_terminado if flags [C] == E
                            ld  b, 0
                            ld  c, d
                            ld  hl, _flags
                            add hl, bc
                            ld  a, (hl)
                            cp  e
                            jr  nz, _flag_different_val_ok
                            ld  a, 1
                            ld  (_sc_terminado), a
                        ._flag_different_val_ok
                    #endasm
                    break;
                case 0x20:
                    // IF PLAYER_TOUCHES sc_x, sc_y
                    // Opcode: 20 sc_x sc_y
                    readxy ();
                    sc_x <<= 4; sc_y <<= 4;
#if defined (PHANTOMAS_ENGINE) || defined (HANNA_ENGINE)
                    sc_terminado = (!(p_x >= sc_x - 15 && p_x <= sc_x + 15 && p_y >= sc_y - 15 && p_y <= sc_y + 15));
#elif defined (PLAYER_NEW_GENITAL)
                    //sc_terminado = (0 == (gpx + 8 >= sc_x && gpx + 8 <= sc_x + 15 && gpy + 14 >= sc_y - 15 && gpy + 14 <= sc_y + 15));
                    sc_terminado = (0 == (gpx + 8 >= sc_x && gpx <= sc_x + 7 && gpy + 29 >= sc_y && gpy <= sc_y + 1));
#else
                    sc_terminado = (!(gpx + 15 >= sc_x && gpx <= sc_x + 15 && gpy + 15 >= sc_y && gpy <= sc_y + 15));
#endif
                    break;
                case 0x21:
                    // IF PLAYER_IN_X x1, x2
                    // Opcode: 21 x1 x2
                    sc_x = read_byte ();
                    sc_y = read_byte ();
#if defined (PHANTOMAS_ENGINE) || defined (HANNA_ENGINE)
                    sc_terminado = (!(p_x >= sc_x && p_x <= sc_y));
#else
                    sc_terminado = (!((p_x >> FIXBITS) >= sc_x && (p_x >> FIXBITS) <= sc_y));
#endif
                    break;
                case 0x23:
                    // IF POSSEE
                    sc_terminado = (possee == 0);
                    break;
                case 0x80:
                     // IF LEVEL = sc_n
                     // Opcode: 80 sc_n
                     sc_terminado = (read_vbyte () != level);
                     break;
                case 0xF0:
                     // IF TRUE
                     // Opcode: F0
                     break;
                case 0xFF:
                    // THEN
                    // Opcode: FF
                    sc_terminado = 1;
                    sc_continuar = 1;
                    break;
            }
        }
        if (sc_continuar) {
            sc_terminado = 0;
            while (!sc_terminado) {
                switch (read_byte ()) {
                    case 0x01:
                        // SET FLAG sc_x = sc_n
                        // Opcode: 01 sc_x sc_n
                        #asm
                                call _readxy
                                ld  de, (_sc_x)
                                ld  d, 0
                                ld  hl, _flags
                                add hl, de
                                ld  a, (_sc_y)
                                ld  (hl), a
                        #endasm
                        break;
                    case 0x10:
                        // INC FLAG sc_x, sc_n
                        // Opcode: 10 sc_x sc_n
                        #asm
                                call _readxy
                                ld  de, (_sc_x)
                                ld  d, 0
                                ld  hl, _flags
                                add hl, de
                                ld  c, (hl)
                                ld  a, (_sc_y)
                                add c
                                ld  (hl), a
                        #endasm
                        break;
                    case 0x11:
                        // DEC FLAG sc_x, sc_n
                        // Opcode: 11 sc_x sc_n
                        #asm
                                call _readxy
                                ld  de, (_sc_x)
                                ld  d, 0
                                ld  hl, _flags
                                add hl, de
                                ld  a, (_sc_y)
                                ld  c, a
                                ld  a, (hl)
                                sub c
                                ld  (hl), a
                        #endasm
                        break;
                    case 0x15:
                        // FLIPFLOP sc_x
                        // Opcode: 15 sc_x
                        sc_x = read_vbyte ();
                        flags [sc_x] = 1 - flags [sc_x];
                        break;
                    case 0x20:
                        // SET TILE (sc_x, sc_y) = sc_n
                        // Opcode: 20 sc_x sc_y sc_n
                        readxy ();
                        sc_n = read_vbyte ();
                        _x = sc_x; _y = sc_y; _n = behs [sc_n]; _t = sc_n; update_tile ();
                        break;
                    case 0x30:
                        // INC LIFE sc_n
                        // Opcode: 30 sc_n
                        p_life += read_vbyte ();
                        break;
                    case 0x31:
                        // DEC LIFE sc_n
                        // Opcode: 31 sc_n
                        p_life -= read_vbyte ();
                        break;
                    case 0x50:
                        // PRINT_TILE_AT (sc_x, sc_y) = sc_n
                        // Opcode: 50 sc_x sc_y sc_n
                        readxy ();
                        _x = sc_x; _y = sc_y; _t = read_vbyte (); 
                        draw_coloured_tile ();
                        invalidate_tile ();
                        break;
                    case 0x51:
                        // SET_FIRE_ZONE x1, y1, x2, y2
                        // Opcode: 51 x1 y1 x2 y2
                        fzx1 = read_byte ();
                        fzy1 = read_byte ();
                        fzx2 = read_byte ();
                        fzy2 = read_byte ();
                        f_zone_ac = 1;
                        break;
                    case 0x52:
                        // INVALIDATE
                        enems_move ();
                        update_sprites ();
                        invalidate_viewport ();
                        break;
                    case 0x69:
                        // WARP_TO_LEVEL
                        // Opcode: 69 l n_pant x y silent
                        warp_to_level = read_vbyte ();
                        n_pant = read_vbyte ();
                        o_pant = 99;
                        reloc_player ();
                        silent_level = read_vbyte ();
                        sc_terminado = 1;
                        script_result = 3;
                        return;
                    case 0x6A:
                        // SETY sc_y
                        // Opcode: 6B sc_y
#if defined (PHANTOMAS_ENGINE) || defined (HANNA_ENGINE)
                        gpy = p_y = read_vbyte () << 4;
#else
                        gpy = read_vbyte () << 4; p_y = gpy << FIXBITS;
                        stop_player ();
#endif
                        break;
                    case 0x6B:
                        // SETX sc_x
                        // Opcode: 6B sc_x
#if defined (PHANTOMAS_ENGINE) || defined (HANNA_ENGINE)
                        gpx = p_x = read_vbyte () << 4;
#else
                        gpx = read_vbyte () << 4; p_x = gpx << FIXBITS;
                        stop_player ();
#endif
                        break;
                    case 0x6D:
                        // WARP_TO sc_n
                        // Opcode: 6D sc_n
                        n_pant = read_vbyte ();
                        o_pant = 99;
                        reloc_player ();
                        return;
                    case 0x6E:
                        // REDRAW
                        // Opcode: 6E
                        sc_x = sc_y = 0;
                        for (sc_c = 0; sc_c < 150; sc_c ++) {
                            _x = sc_x; _y = sc_y; _n = map_attr [sc_c]; _t = map_buff [sc_c]; update_tile ();
                            sc_x ++; if (sc_x == 15) { sc_x = 0; sc_y ++; }
						}
#ifdef ENABLE_FLOATING_OBJECTS
                        FO_paint_all ();
#endif
						break;
                    case 0x6F:
                        // REENTER
                        // Opcode: 6F
                        do_respawn = 0;
                        o_pant = 99; 
                        return;
                    case 0x80:
                        // ENEM n ON
                        // Opcode: 0x80 n
                        baddies [enoffs + read_vbyte ()].t &= 0x7F;
                        break;
                    case 0x81:
                        // ENEM n OFF
                        // Opcode: 0x81 n
                        baddies [enoffs + read_vbyte ()].t |= 0x80;
                        break;
                    case 0xE0:
                        // SOUND sc_n
                        // Opcode: E0 sc_n
#ifdef MODE_128K
                        _AY_PL_SND (read_vbyte ());
#else
                        beep_fx (read_vbyte ());
#endif
                        break;
                    case 0xE1:
                        // SHOW
                        // Opcode: E1
                        sp_UpdateNow ();
                        break;
                    case 0xE4:
                        // EXTERN sc_n
                        // Opcode: 0xE4 sc_n
                        do_extern_action (read_byte ());
                        break;
                    case 0xE5:
                        // PAUSE sc_n
#ifdef MODE_128K
                        sc_n = read_byte ();
                        while (sc_n --) {
                            #asm
                                halt
                            #endasm
                        }
#else
						active_sleep (read_byte ());
#endif
                        break;
                    case 0xE6:
                        // MUSIC n
                        sc_n = read_vbyte ();
                        if (sc_n == 0xff) {
                            _AY_ST_ALL ();
                        } else {
#ifdef COMPRESSED_LEVELS
                            level_data->music_id = sc_n;
                            _AY_PL_MUS (level_data->music_id);
#else
                            _AY_PL_MUS (sc_n);
#endif
                        }
                        break;
                    case 0xF1:
                        // WIN
                        script_result = 1;
                        return;
                    case 0xF3:
                        // Final del todo
                        script_result = 4;
                        return;
                        break;
                    case 0xF4:
                        // DECORATIONS
                        while (0xff != (sc_x = read_byte ())) {
                            sc_n = read_byte ();
                            _x = sc_x >> 4; _y = sc_x & 15; _n = behs [sc_n]; _t = sc_n; update_tile ();
                        }
                        break;
                    case 0xFF:
                        sc_terminado = 1;
                        break;
                }
            }
        }
        script = next_script;
    }
}
