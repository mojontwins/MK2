// MT Engine MK2 v0.90b
// Copyleft 2016 the Mojon Twins

// bombs-s.h
// Simple bomb implementation

// This simple bomb implementation is quite simple (yeah!).
// You can drop just one bomb. You must be on solid floor.

// Bomb will explode after a countdown. It will make tiles with beh|16 explode
// and disappear.

// This uses a simple FSM to work.
// 0 -> idle, bomb not set.
// 1 -> bomb set and counting down.
// 2 -> bomb exploding -> will trigger breaking blocks at the end.

// REQUIRES BREAKABLE-S.H!!

#define CMD_EXPLODE 0
#define CMD_FINISH 1

unsigned char bomb_state;
unsigned char bomb_ctr;
unsigned char bomb_x, bomb_y;
unsigned char bomb_px, bomb_py; // two extra bytes to save tons of bytes elsewhere. And cycles.

void bomb_init (void) {
	bomb_state = 0;
}

void bomb_set (void) {
	bomb_x = (gpx + 8) >> 4;
	bomb_y = gpy >> 4;
	bomb_px = bomb_x << 4;
	bomb_py = bomb_y << 4;
	bomb_ctr = 32;
	bomb_state = 1;
	_x = bomb_x; _y = bomb_y; _t = PLAYER_BOMBS_TILE;
	draw_coloured_tile_gamearea ();
	invalidate_tile  ();
}

void bomb_racime (unsigned char cmd) {
	gpyy = bomb_y - 1;
	gpit = 3; while (gpit --) {
		gpxx = bomb_x - 1;
		gpjt = 3; while (gpjt --) {
			_x = gpxx; _y = gpyy; 
			switch (cmd) {
				case CMD_EXPLODE:
					_t = BOMBS_EXPLOSION_TILE;
					draw_coloured_tile_gamearea (); 
					break;
				case CMD_FINISH:
					#ifdef BREAKABLE_WALLS
						break_wall ();
					#endif
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
					_t = map_buff [gpaux];
					draw_coloured_tile_gamearea ();					
			}
			invalidate_tile ();
			gpxx ++;
		}
		gpyy ++;
	}
}

void bomb_run (void) {
	switch (bomb_state) {
		case 1:
			bomb_ctr --;
			if (bomb_ctr == 0) {
				bomb_ctr = 8;
				bomb_state = 2;
				// Paint explosions!
				bomb_racime (CMD_EXPLODE);
				_AY_PL_SND (17);
			}
			break;
		case 2:
			bomb_ctr --;
			if (bomb_ctr == 0) {
				bomb_state = 0;
				// Restore backdrop.
				// Trigger breakables.
				bomb_racime (CMD_FINISH);	
				#ifdef ENABLE_FLOATING_OBJECTS
					FO_paint_all ();
				#endif
			} else {
				// Collisions ?
				// W/player-> here
				if (gpx + 15 >= bomb_px && gpx <= bomb_px + 47 &&
					gpy + 15 >= bomb_py && gpy <= bomb_py + 47) {
					p_killme = SFX_PLAYER_DEATH_BOMB;
				}
				// W/enemies-> enems.h
			}
			break;
	}
}
