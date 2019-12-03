// MT Engine MK2 v0.90b
// Copyleft 2016 the Mojon Twins

// Needed prototypes

#ifdef ACTIVATE_SCRIPTING
	void draw_scr_background (void);
	void draw_scr (void);
#endif

#ifdef MODE_128K
	void blackout_area (void);
	void get_resource (unsigned char res, unsigned int dest);

	void __FASTCALL__ _AY_PL_SND (unsigned char fx_number);
	void __FASTCALL__ _AY_PL_MUS (unsigned char song_number);
#endif

#ifdef ENABLE_FLOATING_OBJECTS
	unsigned char FO_add (unsigned char x, unsigned char y, unsigned char t);
	void FO_paint (unsigned char idx);
	void FO_paint_all (void);
#endif

#ifdef ENABLE_TILANIMS
	void tilanims_add (void);
	void tilanims_do (void);
	void tilanim_reset (void);
#endif

void active_sleep (int espera);
void run_fire_script (void);

void cortina (void);
unsigned char rand (void);
void hide_sprites (unsigned char which_ones);
void draw_coloured_tile (void);
void draw_coloured_tile_gamearea (void);
unsigned char collide (unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2);
unsigned char collide_pixel (unsigned char x, unsigned char y, unsigned char x1, unsigned char y1);
unsigned char attr (void);
void print_number2 (void);
