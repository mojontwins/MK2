// msc.h
// Generado por Mojon Script Compiler 3 de la MT Engine MK2
// Copyleft 2015 The Mojon Twins

#ifdef CLEAR_FLAGS
void msc_init_all (void) {
    for (sc_c = 0; sc_c < MAX_FLAGS; sc_c ++)
        flags [sc_c] = 0;
}
#endif

unsigned char read_byte (void) {
    unsigned char sc_b;
#ifdef MODE_128K
    #asm
        di
        ld b, SCRIPT_PAGE
        call SetRAMBank
    #endasm
#endif
    sc_b = *script ++;
#ifdef MODE_128K
    #asm
        ld b, 0
        call SetRAMBank
        ei
    #endasm
#endif
    return sc_b;
}

unsigned char read_vbyte (void) {
    sc_c = read_byte ();
    return (sc_c & 128) ? flags [sc_c & 127] : sc_c;
}

void readxy (void) {
    sc_x = read_vbyte ();
    sc_y = read_vbyte ();
}

#if !(defined (PHANTOMAS_ENGINE) || defined (HANNA_ENGINE))
void __FASTCALL__ stop_player (void) {
    p_vx = p_vy = 0;
}
#endif

void __FASTCALL__ reloc_player (void) {
#if defined (PHANTOMAS_ENGINE) || defined (HANNA_ENGINE)
    p_x = read_vbyte () << 4;
    p_y = read_vbyte () << 4;
#else
    p_x = read_vbyte () << 10;
    p_y = read_vbyte () << 10;
    stop_player ();
#endif
}

unsigned char *next_script;
void run_script (unsigned char whichs) {

    // main_script_offset contains the address of scripts for current level
    asm_int [0] = main_script_offset + whichs + whichs;
#ifdef DEBUG
    debug_print_16bits (0, 0, asm_int [0]);
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
        ld (_asm_int_2), a
        inc hl
        ld a, (hl)
        ld (_asm_int_2 + 1), a
    #endasm

    script = (unsigned char *) (asm_int_2 [0]);

#ifdef MODE_128K
    #asm
        ld b, 0
        call SetRAMBank
        ei
    #endasm
#endif

    if (script == 0)
        return;

    script += main_script_offset;
#ifdef DEBUG
    debug_print_16bits (5, 0, script);
#endif


    while ((sc_c = read_byte ()) != 0xFF) {
        next_script = script + sc_c;
        sc_terminado = sc_continuar = 0;
        while (!sc_terminado) {
            switch (read_byte ()) {
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
                    case 0xF4:
                        // DECORATIONS
                        while (0xff != (sc_x = read_byte ())) {
                            sc_n = read_byte ();
                            update_tile (sc_x >> 4, sc_x & 15, behs [sc_n], sc_n);
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
