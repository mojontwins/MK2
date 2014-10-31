// breakable-s.h
// Simple breakable tiles helper functions

void wall_broken (unsigned char x, unsigned char y) {
	gpd = 0;
	gpaux = (y << 4) - y + x;
#ifdef BREAKABLE_TILE_GET
	if (map_buff [gpaux] == BREAKABLE_TILE_GET &&
		(rand () & BREAKABLE_TILE_FREQ) <= BREAKABLE_TILE_FREQ_T) gpd = TILE_GET;
#endif
	update_tile (x, y, 0, gpd);
	
	// Persistent maps:
#ifdef PERSISTENT_BREAKABLE
	// Modify map
#ifdef UNPACKED_MAP
	mapa [n_pant * 150 + gpaux] = 0;
#else
	map_pointer = mapa + n_pant * 75 + (gpaux >> 1);
	*map_pointer = (gpaux & 1) ? ((*map_pointer) & 0xf0) : ((*map_pointer) & 0x0f);		
#endif				
#endif	
}

#ifdef BREAKABLE_ANIM
void process_breakable () {
	unsigned char brkit;

	do_process_breakable = 0;
	
	for (brkit = 0; brkit < MAX_BREAKABLE; brkit ++) {
		if (breaking_f [brkit]) {
			if (! --breaking_f [brkit]) {
#ifdef MODE_128K				
				wyz_play_sound (3);
#endif	
				wall_broken (breaking_x [brkit], breaking_y [brkit]);
			} else {
				do_process_breakable = 1;
			}
		}	
	}
}
#endif

void break_wall (unsigned char x, unsigned char y) {
	gpaux = (y << 4) - y + x;
	map_attr [gpaux] &= 0xEF; // 11101111, remove "breakable" bit.	
#ifdef BREAKABLE_ANIM
	// add this block to the "breaking" tile list
	breaking_f [breaking_idx] = MAX_BREAKABLE_FRAMES;
	breaking_x [breaking_idx] = x;
	breaking_y [breaking_idx] = y;
	draw_coloured_tile_gamearea (x, y, BREAKABLE_TILE);
	breaking_idx ++; if (breaking_idx == MAX_BREAKABLE) breaking_idx = 0;	
	do_process_breakable = 1;
#else
	// break this block.
	wall_broken (x, y);
#endif
	
#ifdef MODE_128K
	wyz_play_sound (7);
#else			
	peta_el_beeper (7);
#endif
}
