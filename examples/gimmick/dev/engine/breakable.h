// MT Engine MK2 v0.90b
// Copyleft 2016 the Mojon Twins

// breakable.h
// Breakable tiles helper functions
// Somewhat broken?

void wall_broken (void) {
	gpd = 0;
	
	// gpaux = (_y << 4) - _y + _x;
	#asm
			ld  a, (__y)
			ld  c, a
			sla a
			sla a
			sla a
			sla a
			sub c
			ld  c, a
			ld  a, (__x)
			add c
			ld  (_gpaux), a
	#endasm

	#ifdef BREAKABLE_TILE_GET
		if (map_buff [gpaux] == BREAKABLE_TILE_GET &&
			(rand () & BREAKABLE_TILE_FREQ) == 0) gpd = TILE_GET;
	#endif
	_n = 0; _t = gpd; update_tile ();

	// Persistent maps:
	#ifdef PERSISTENT_BREAKABLE
		// Modify map
		#ifdef UNPACKED_MAP
			map [n_pant * 150 + gpaux] = 0;
		#else
			map_pointer = map + n_pant * 75 + (gpaux >> 1);
			if (gpaux & 1) {
				*map_pointer = ((*map_pointer) & 0xf0);
			} else {
				*map_pointer = ((*map_pointer) & 0x0f);
			}
		#endif
	#endif
}

#ifdef BREAKABLE_ANIM
void process_breakable (void) {
	unsigned char brkit;

	do_process_breakable = 0;

	for (brkit = 0; brkit < MAX_BREAKABLE; brkit ++) {
		if (breaking_f [brkit]) {
			breaking_f [brkit] --;
			if (!breaking_f [brkit]) {
				#ifdef MODE_128K
					_AY_PL_SND (3);
				#endif
				_x = breaking_x [brkit]; _y = breaking_y [brkit]; wall_broken ();
			} else {
				do_process_breakable = 1;
			}
		}
	}
}

void add_to_breakable (void) {
	breaking_f [breaking_idx] = MAX_BREAKABLE_FRAMES;
	breaking_x [breaking_idx] = _x;
	breaking_y [breaking_idx] = _y;
	_t = BREAKABLE_TILE; draw_invalidate_coloured_tile_gamearea ();
	breaking_idx ++; if (breaking_idx == MAX_BREAKABLE) breaking_idx = 0;
	do_process_breakable = 1;
}
#endif

void break_wall (void) {
	
	// gpaux = (_y << 4) - _y + _x;
	#asm
			ld  a, (__y)
			ld  c, a
			sla a
			sla a
			sla a
			sla a
			sub c
			ld  c, a
			ld  a, (__x)
			add c
			ld  (_gpaux), a
	#endasm
	
	// Increment buffer
	brk_buff [gpaux] ++;
	if (brk_buff [gpaux] < BREAKABLE_WALLS_LIFE) {
		// Play this sound
		gpaux = 6;
	} else {
		map_attr [gpaux] &= 0xEF; // 11101111, remove "breakable" bit.

		#ifdef BREAKABLE_ANIM
			// add this block to the "breaking" tile list
			add_to_breakable ();
		#else
			// break this block.
			wall_broken ();
		#endif

		// Play this sound
		gpaux = 7;
	}

	#ifdef MODE_128K
		_AY_PL_SND (gpaux);
	#else
		beep_fx (gpaux);
	#endif
}
