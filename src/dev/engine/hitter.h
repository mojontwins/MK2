// MT Engine MK2 v0.90b
// Copyleft 2016 the Mojon Twins

// hitter_h
// Hitter (punch/sword/whip) helper functions

#ifdef PLAYER_CAN_PUNCH
	//								H   H   H
	unsigned char hoffs_x [] = {12, 14, 16, 16, 12};
	#define HITTER_MAX_FRAME 5
#endif
#ifdef PLAYER_HAZ_SWORD
	//                                     H   H   H   H
	unsigned char hoffs_x [] = {8, 10, 12, 14, 15, 15, 14, 13, 10};
	unsigned char hoffs_y [] = {2,  2,  2, 3,  4,  4,  5,  6,  7};
	#define HITTER_MAX_FRAME 9
#endif
#ifdef PLAYER_HAZ_WHIP
	//                          H  H   H
	unsigned char hoffs_x [] = {8, 16, 16, 12, 8,  4, 0};
	unsigned char hoffs_y [] = {4, 4,  4,  6,  8, 10, 12};
	#define HITTER_MAX_FRAME 7
#endif

void __FASTCALL__ render_hitter (void) {
#if defined (PHANTOMAS_ENGINE) || defined (HANNA_ENGINE)
	gpy = p_y;
	gpx = p_x;
#else
	gpy = (p_y >> 6);
	gpx = (p_x >> 6);
#endif

// Punching main code

#ifdef PLAYER_CAN_PUNCH
	hitter_y = gpy + 6;
	if (p_facing) {
		hitter_x = gpx + hoffs_x [hitter_frame];
		hitter_n_f = sprite_20_a;
#if (defined (BREAKABLE_WALLS) || defined (BREAKABLE_WALLS_SIMPLE)) && defined (HITTER_BREAKS_WALLS)
		gpxx = (hitter_x + 7) >> 4; gpyy = (hitter_y + 3) >> 4;
#endif
	} else {
		hitter_x = gpx + 8 - hoffs_x [hitter_frame];
		hitter_n_f = sprite_21_a;
#if (defined (BREAKABLE_WALLS) || defined (BREAKABLE_WALLS_SIMPLE)) && defined (HITTER_BREAKS_WALLS)
		gpxx = (hitter_x) >> 4; gpyy = (hitter_y + 3) >> 4;
#endif
	}
#if (defined (BREAKABLE_WALLS) || defined (BREAKABLE_WALLS_SIMPLE)) && defined (HITTER_BREAKS_WALLS)
	if (hitter_frame >= 1 && hitter_frame <= 3)
		break_wall (gpxx, gpyy);
#endif		
#endif

// Sword main code

#ifdef PLAYER_HAZ_SWORD
	if (p_up) {
		hitter_x = gpx + hoffs_y [hitter_frame];
		hitter_y = gpy + 6 - hoffs_x [hitter_frame];
		hitter_n_f = sprite_sword_u;
#if (defined (BREAKABLE_WALLS) || defined (BREAKABLE_WALLS_SIMPLE)) && defined (HITTER_BREAKS_WALLS)
		gpxx = (hitter_x + 4) >> 4; gpyy = (hitter_y) >> 4;
#endif		
	} else {
		hitter_y = gpy + hoffs_y [hitter_frame];
#if (defined (BREAKABLE_WALLS) || defined (BREAKABLE_WALLS_SIMPLE)) && defined (HITTER_BREAKS_WALLS)
		gpyy = (hitter_y + 4) >> 4;
#endif
		if (p_facing) {
			hitter_x = gpx + hoffs_x [hitter_frame];
			hitter_n_f = sprite_sword_r;
#if (defined (BREAKABLE_WALLS) || defined (BREAKABLE_WALLS_SIMPLE)) && defined (HITTER_BREAKS_WALLS)
			gpxx = (hitter_x + 7) >> 4; 
#endif
		} else {
			hitter_x = gpx + 8 - hoffs_x [hitter_frame];
			hitter_n_f = sprite_sword_l;
#if (defined (BREAKABLE_WALLS) || defined (BREAKABLE_WALLS_SIMPLE)) && defined (HITTER_BREAKS_WALLS)
			gpxx = (hitter_x) >> 4; 
#endif			
		}
	}
#if defined (BREAKABLE_WALLS) || defined (BREAKABLE_WALLS_SIMPLE)
	if (hitter_frame > 2 && hitter_frame < 7)
		break_wall (gpxx, gpyy);
#endif
#endif

// Whippo main code

#ifdef PLAYER_HAZ_WHIP
	hitter_y = gpy + hoffs_y [hitter_frame];
#if (defined (BREAKABLE_WALLS) || defined (BREAKABLE_WALLS_SIMPLE)) && defined (HITTER_BREAKS_WALLS)
	gpyy = (hitter_y + 3) >> 4;
#endif
	if (p_facing) {
		hitter_x = gpx + hoffs_x [hitter_frame];
#if (defined (BREAKABLE_WALLS) || defined (BREAKABLE_WALLS_SIMPLE)) && defined (HITTER_BREAKS_WALLS)
		gpxx = (hitter_x + 15) >> 4; 
#endif
	} else {
		hitter_x = gpx - hoffs_x [hitter_frame];
#if (defined (BREAKABLE_WALLS) || defined (BREAKABLE_WALLS_SIMPLE)) && defined (HITTER_BREAKS_WALLS)
		gpxx = (hitter_x) >> 4; 
#endif			
	}
#if (defined (BREAKABLE_WALLS) || defined (BREAKABLE_WALLS_SIMPLE)) && defined (HITTER_BREAKS_WALLS)
if (hitter_frame < 3)
	break_wall (gpxx, gpyy);
#endif
#endif

// End of main codes.

	sp_MoveSprAbs (sp_hitter, spritesClip,
		hitter_n_f - hitter_c_f,
		VIEWPORT_Y + (hitter_y >> 3), VIEWPORT_X + (hitter_x >> 3),
		hitter_x & 7, hitter_y & 7);
	hitter_c_f = hitter_n_f;

	hitter_frame ++;
	if (hitter_frame == HITTER_MAX_FRAME) {
		hitter_on = 0;
		sp_MoveSprAbs (sp_hitter, spritesClip, 0, -2, -2, 0, 0);
		p_hitting = 0;
	}
}
