// MT Engine MK2 v0.90b
// Copyleft 2016 the Mojon Twins

// Simple Item Manager

// Lo m�s fuerte es que he programado esto para el juego oculto
// en la carga final del Leovigildo. Muy fuerte lo m�o.

// No se me ocurre ninguna raz�n para que tengas
// que tocar estos valores... As� que no los toques.
#define FLAG_SLOT_ALLDONE  29
#define FLAG_SLOT_SELECTED 30
#define FLAG_ITEM_SELECTED 31

typedef struct {
	unsigned char n_pant;
	unsigned char xy;
	unsigned char initial_object;
} SIM_CONTAINER;

// Initial state and location
SIM_CONTAINER sim_initial [SIM_MAXCONTAINERS] = {
	{1, 0x72, 22},
	{4, 0x76, 20},
	{7, 0x76, 17},
	{10, 0x64, 21},
	{15, 0x95, 18},
	{17, 0x65, 19}
};

// Final state
unsigned char sim_final [SIM_MAXCONTAINERS] = {17, 18, 19, 20, 21, 22};
unsigned char sim_it, sim_p;

// Call this at the beginning of the game/level
void sim_init (void) {
	// Copies items in flags
	for (sim_it = 0; sim_it < SIM_MAXCONTAINERS; sim_it ++) {
		flags [sim_it] = sim_initial [sim_it].initial_object;
	}
	for (sim_it = 0; sim_it < SIM_DISPLAY_MAXITEMS; sim_it ++)
        items [sim_it] = 0;
	flags [FLAG_SLOT_ALLDONE] = 0;
}

// Call this whenever the player flips a container
void sim_check (void) {
	flags [FLAG_SLOT_ALLDONE] = 1;
	for (sim_it = 0; sim_it < SIM_MAXCONTAINERS; sim_it ++) {
		if (flags [sim_it] != sim_final [sim_it]) {
			flags [FLAG_SLOT_ALLDONE] = 0;
			break;
		}
	}
}

// Call this whenever the player enters a screen
void sim_paint (void) {
	// Creates FOs
	for (sim_it = 0; sim_it < SIM_MAXCONTAINERS; sim_it ++) {
		if (sim_initial [sim_it].n_pant == n_pant) {
			sim_p = FO_add (sim_initial [sim_it].xy >> 4, sim_initial [sim_it].xy & 15, 128 + sim_it);
            FO_paint (sim_p);
		}
	}
}

#ifdef SIM_DISPLAY_HORIZONTAL
void display_items (void) {
	sim_p = SIM_DISPLAY_X;
	for (sim_it = 0; sim_it < SIM_DISPLAY_MAXITEMS; sim_it ++) {
		if (items [sim_it]) {
			_x = sim_p; _y = SIM_DISPLAY_Y; _t = items [sim_it]; 
			draw_coloured_tile ();
			invalidate_tile ();
		} else {
			_x = sim_p; _y = SIM_DISPLAY_Y; _t = SIM_DISPLAY_ITEM_EMPTY; 
			draw_coloured_tile ();
			invalidate_tile ();
		}
		if (sim_it != flags [FLAG_SLOT_SELECTED]) {
			// sp_PrintAtInv (SIM_DISPLAY_Y + 2, sim_p, 0, 0);
			// sp_PrintAtInv (SIM_DISPLAY_Y + 2, sim_p + 1, 0, 0);
			#asm
				ld  c, SIM_DISPLAY_Y + 2
				ld  a, (_sim_p)
				ld  de, 0
				call SPPrintAtInv
				ld  c, SIM_DISPLAY_Y + 2
				ld  a, (_sim_p)
				inc a
				ld  de, 0
				call SPPrintAtInv
			#endasm
		} else { 
			// sp_PrintAtInv (SIM_DISPLAY_Y + 2, sim_p, SIM_DISPLAY_SEL_C, SIM_DISPLAY_SEL_CHAR1);
			// sp_PrintAtInv (SIM_DISPLAY_Y + 2, sim_p + 1, SIM_DISPLAY_SEL_C, SIM_DISPLAY_SEL_CHAR2);
			#asm				
				ld  a, (_sim_p)
				ld  c, a
				ld  a, SIM_DISPLAY_Y + 2
				ld  d, SIM_DISPLAY_SEL_C
				ld  e, SIM_DISPLAY_SEL_CHAR1
				call SPPrintAtInv				
				ld  a, (_sim_p)
				inc a
				ld  c, a
				ld  a, SIM_DISPLAY_Y + 2
				ld  d, SIM_DISPLAY_SEL_C
				ld  e, SIM_DISPLAY_SEL_CHAR2
				call SPPrintAtInv
			#endasm
		}
		sim_p += SIM_DISPLAY_ITEM_STEP;
	}
}
#else
void display_items (void) {
	sim_p = SIM_DISPLAY_Y;
	for (sim_it = 0; sim_it < SIM_DISPLAY_MAXITEMS; sim_it ++) {
		if (items [sim_it]) {
			_x = SIM_DISPLAY_X; _y = sim_p; _t = items [sim_it]; 
			draw_coloured_tile ();
			invalidate_tile ();
		} else {
			_x = SIM_DISPLAY_X; _y = sim_p; _t = SIM_DISPLAY_ITEM_EMPTY; 
			draw_coloured_tile ();
			invalidate_tile ();
		}
		if (sim_it != flags [FLAG_SLOT_SELECTED]) {
			//sp_printatinv (sim_p + 2, SIM_DISPLAY_X, 0, 0);
			//sp_printatinv (sim_p + 2, SIM_DISPLAY_X + 1, 0, 0);
			#asm
				ld  a, (_sim_p)
				add 2
				ld  c, SIM_DISPLAY_X
				ld  de, 0
				call SPPrintAtInv
				ld  a, (_sim_p)
				add 2
				ld  c, SIM_DISPLAY_X+1
				ld  de, 0
				call SPPrintAtInv
			#endasm
		} else {
			//sp_printatinv (sim_p + 2, SIM_DISPLAY_X, SIM_DISPLAY_SEL_C, SIM_DISPLAY_SEL_CHAR1);
			//sp_printatinv (sim_p + 2, SIM_DISPLAY_X + 1, SIM_DISPLAY_SEL_C, SIM_DISPLAY_SEL_CHAR2);
			#asm
				ld  a, (_sim_p)
				add 2
				ld  c, SIM_DISPLAY_X
				ld  d, SIM_DISPLAY_SEL_C
				ld  e, SIM_DISPLAY_SEL_CHAR1
				call SPPrintAtInv
				ld  a, (_sim_p)
				add 2
				ld  c, SIM_DISPLAY_X+1
				ld  d, SIM_DISPLAY_SEL_C
				ld  e, SIM_DISPLAY_SEL_CHAR2
				call SPPrintAtInv
			#endasm
		}
		sim_p +=  SIM_DISPLAY_ITEM_STEP;
	}
}
#endif
