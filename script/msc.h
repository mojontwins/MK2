// msc.h
// Generado por Mojon Script Compiler de la Churrera 5
// Copyleft 2014 The Mojon Twins

void msc_init_all (void) {
    for (sc_c = 0; sc_c < MAX_FLAGS; sc_c ++)
        flags [sc_c] = 0;
}

unsigned char read_byte (void) {
    unsigned char sc_b;
    #asm
        di
        ld b, SCRIPT_PAGE
        call SetRAMBank
    #endasm
    sc_b = *script ++;
    #asm
        ld b, 0
        call SetRAMBank
        ei
    #endasm
    return sc_b;
}

unsigned char __FASTCALL__ read_vbyte (void) {
    sc_c = read_byte ();
    return (sc_c & 128) ? flags [sc_c & 127] : sc_c;
}

void __FASTCALL__ readxy (void) {
	sc_x = read_vbyte ();
    sc_y = read_vbyte ();
}

void __FASTCALL__ stop_player (void) {
    p_vx = p_vy = 0;
}

void __FASTCALL__ reloc_player (void) {
	p_x = read_vbyte () << 10;
    p_y = read_vbyte () << 10;
    stop_player ();
}

void run_script (unsigned char whichs) {
    unsigned char *next_script;

    asm_int [0] = main_script_offset + whichs + whichs;

    #asm
        di
        ld b, SCRIPT_PAGE
        call SetRAMBank
        ld hl, (_asm_int)
        ld a, (hl)
        ld (_asm_int_2), a
        inc hl
        ld a, (hl)
        ld (_asm_int_2 + 1), a
    #endasm

    script = (unsigned char *) (asm_int_2 [0]);

    #asm
        ld b, 0
        call SetRAMBank
        ei
    #endasm

    if (script == 0)
        return;

    script += main_script_offset;

    while ((sc_c = read_byte ()) != 0xFF) {
        next_script = script + sc_c;
        sc_terminado = sc_continuar = 0;
        while (!sc_terminado) {
            switch (read_byte ()) {
                case 0x10:
                    // IF FLAG sc_x = sc_n
                    // Opcode: 10 sc_x sc_n
                    readxy ();
                    sc_terminado = (flags [sc_x] != sc_y);
                    break;
                case 0x11:
                    // IF FLAG sc_x < sc_n
                    // Opcode: 11 sc_x sc_n
                    readxy ();
                    sc_terminado = (flags [sc_x] >= sc_y);
                    break;
                case 0x12:
                    // IF FLAG sc_x > sc_n
                    // Opcode: 12 sc_x sc_n
                    readxy ();
                    sc_terminado = (flags [sc_x] <= sc_y);
                    break;
                case 0x13:
                    // IF FLAG sc_x <> sc_n
                    // Opcode: 13 sc_x sc_n
                    readxy ();
                    sc_terminado = (flags [sc_x] == sc_y);
                    break;
                case 0x20:
                    // IF PLAYER_TOUCHES sc_x, sc_y
                    // Opcode: 20 sc_x sc_y
                    readxy ();
                    sc_terminado = (!((p_x >> 6) >= (sc_x << 4) - 15 && (p_x >> 6) <= (sc_x << 4) + 15 && (p_y >> 6) >= (sc_y << 4) - 15 && (p_y >> 6) <= (sc_y << 4) + 15));
                    break;
                case 0x21:
                    // IF PLAYER_IN_X x1, x2
                    // Opcode: 21 x1 x2
                    sc_x = read_byte ();
                    sc_y = read_byte ();
                    sc_terminado = (!((p_x >> 6) >= sc_x && (p_x >> 6) <= sc_y));
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
                        readxy ();
                        flags [sc_x] = sc_y;
                        break;
                    case 0x10:
                        // INC FLAG sc_x, sc_n
                        // Opcode: 10 sc_x sc_n
                        readxy ();
                        flags [sc_x] += sc_y;
                        break;
                    case 0x11:
                        // DEC FLAG sc_x, sc_n
                        // Opcode: 11 sc_x sc_n
                        readxy ();
                        flags [sc_x] -= sc_y;
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
                        update_tile (sc_x, sc_y, comportamiento_tiles [sc_n], sc_n);
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
                        draw_coloured_tile (sc_x, sc_y, read_vbyte ());
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
                        break;
                    case 0x6A:
                        // SETY sc_y
                        // Opcode: 6B sc_y
						p_y = read_vbyte () << 10;
                        stop_player ();
                        break;
                    case 0x6B:
                        // SETX sc_x
                        // Opcode: 6B sc_x
						p_x = read_vbyte () << 10;
                        stop_player ();
                        break;
                    case 0x6C:
                        // REPOSTN sc_x sc_y
                        // Opcode: 6C sc_x sc_y
                        do_respawn = 0;
                        reloc_player ();
                        o_pant = 99;
                        sc_terminado = 1;
                        break;
                    case 0x6D:
                        // WARP_TO sc_n
                        // Opcode: 6D sc_n
                        n_pant = read_vbyte ();
                        o_pant = 99;
                        reloc_player ();
                        sc_terminado = 1;
                        break;
                    case 0x6E:
                        // REDRAW
                        // Opcode: 6E
                        draw_scr_background ();
                        break;
                    case 0x6F:
                        // REENTER
                        // Opcode: 6F
                        do_respawn = 0;
                        o_pant = 99; 
                        sc_terminado = 1;
                        break;
                    case 0x80:
                        // ENEM n ON
                        // Opcode: 0x80 n
                        malotes [enoffs + read_vbyte ()].t &= 0xEF;
                        break;
                    case 0x81:
                        // ENEM n OFF
                        // Opcode: 0x81 n
                        malotes [enoffs + read_vbyte ()].t |= 0x10;
                        break;
                    case 0xE0:
                        // SOUND sc_n
                        // Opcode: E0 sc_n
#ifdef MODE_128K
                        wyz_play_sound (read_vbyte ());
#else
                        peta_el_beeper (read_vbyte ());
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
                        sc_n = read_vbyte ();
                        while (sc_n --) {
                            #asm
                                halt
                            #endasm
                        }
                        break;
                    case 0xE6:
                        // MUSIC n
#ifdef COMPRESSED_LEVELS
                        level_data->music_id = read_vbyte ();
						wyz_play_music (level_data->music_id);
#else
                        wyz_play_music (read_vbyte ());
#endif
                        break;
                    case 0xF1:
                        script_result = 1;
                        sc_terminado = 1;
                        break;
                    case 0xF3:
                        // Final del todo
                        script_result = 4;
                        sc_terminado = 1;
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
