// hitter_h
// Hitter (punch/sword) helper functions

#ifdef PLAYER_CAN_PUNCH
unsigned char hitter_offs [] = {12, 14, 16, 16, 12};
#endif
void __FASTCALL__ render_hitter (void) {
	gpy = (p_y >> 6);
	gpx = (p_x >> 6);
#ifdef PLAYER_CAN_PUNCH
	hitter_y = gpy + 6;
	if (p_facing) {
		hitter_x = gpx + hitter_offs [hitter_frame];
		hitter_next_frame = sprite_20_a;
#if defined (BREAKABLE_WALLS) || defined (BREAKABLE_WALLS_SIMPLE)
		gpxx = (hitter_x + 7) >> 4; gpyy = (hitter_y + 3) >> 4;
#endif
	} else {
		hitter_x = gpx + 8 - hitter_offs [hitter_frame];
		hitter_next_frame = sprite_21_a;
#if defined (BREAKABLE_WALLS) || defined (BREAKABLE_WALLS_SIMPLE)
		gpxx = (hitter_x) >> 4; gpyy = (hitter_y + 3) >> 4;
#endif
	}
#if defined (BREAKABLE_WALLS) || defined (BREAKABLE_WALLS_SIMPLE)
	if ((attr (gpxx, gpyy) & 16) && (hitter_frame >= 1 && hitter_frame <= 3))
		break_wall (gpxx, gpyy);
#endif		
#endif
#ifdef PLAYER_CAN_SWORD
	// TODO
#endif

	sp_MoveSprAbs (sp_hitter, spritesClip,
		hitter_next_frame - hitter_current_frame,
		VIEWPORT_Y + (hitter_y >> 3), VIEWPORT_X + (hitter_x >> 3),
		hitter_x & 7, hitter_y & 7);
	hitter_current_frame = hitter_next_frame;

	hitter_frame ++;
#ifdef PLAYER_CAN_PUNCH
	if (hitter_frame == 5) {
#endif
#ifdef PLAYER_CAN_SWORD
	if (hitter_frame == 9) {
#endif
		hitter_on = 0;
		sp_MoveSprAbs (sp_hitter, spritesClip, 0, -2, -2, 0, 0);
		p_hitting = 0;
	}
}
