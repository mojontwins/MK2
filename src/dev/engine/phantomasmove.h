// MT Engine MK2 v0.90b
// Copyleft 2016 the Mojon Twins

// phantomasmove.h
// Player movement for Phantomas/Abu Simbel games

unsigned char canmove = 1;
unsigned char falling = 0;
unsigned char check_to_v, check_to_h;
int ptx1, ptx2, pty1, pty2, pty3, ptm;
char mx, my;
#ifdef RESET_TO_WHEN_STOPPED
unsigned char d_pressed;
#endif

// Bounding boxes pre-calc defines ;-)
#ifdef BOUNDING_BOX_8_BOTTOM
// Small 8x8 bounding box
#define LIMIT_LEFT 		(p_x + 4) >> 4
#define LIMIT_RIGHT 	(p_x + 11) >> 4
#define LIMIT_TOP 		(p_y + 8) >> 4
#define LIMIT_BOTTOM 	(p_y + 15) >> 4
#define ADJUST_LEFT		((ptx1 + 1) << 4) - 4
#define ADJUST_RIGHT	((ptx2 - 1) << 4) + 4
#define ADJUST_TOP 		((pty1 + 1) << 4) - 8
#define ADJUST_BOTTOM 	(pty2 - 1) << 4
#else
// Big 16x16 bounding box
#define LIMIT_LEFT 		p_x >> 4
#define LIMIT_RIGHT 	(p_x + 15) >> 4
#define LIMIT_TOP 		p_y >> 4
#define LIMIT_BOTTOM 	(p_y + 15) >> 4
#define ADJUST_LEFT		(ptx1 + 1) << 4
#define ADJUST_RIGHT	(ptx2 - 1) << 4
#define ADJUST_TOP 		(pty1 + 1) << 4
#define ADJUST_BOTTOM 	(pty2 - 1) << 4
#endif

#define BUTTON_FIRE	((gpit & sp_FIRE) == 0)

#if ADVANCE_FRAME_COUNTER != 1
void __FASTCALL__ advance_frame (void) {
	p_subframe ++; 
	if (p_subframe == ADVANCE_FRAME_COUNTER) {
		p_subframe = 0;
		p_frame = (p_frame + 1) & 3;
	}
}
#endif

#if PHANTOMAS_ENGINE == 4
unsigned char p_jump_max_steps;
#endif

unsigned char move () {
	gpit = (joyfunc) (&keys);
	wall_h = 0;
	check_to_v = check_to_h = 0;
	mx = my = 0;

	if (p_jmp_on == 0) {
		p_y += PHANTOMAS_FALLING;
		pty2 = LIMIT_BOTTOM;
		
		// Make fall?
		ptx1 = LIMIT_LEFT; ptx2 = LIMIT_RIGHT;
		if ((attr (ptx1, pty2) & 12) || (attr (ptx2, pty2) & 12)) {
			p_y = ADJUST_BOTTOM;
			falling = 0;
#ifdef DIE_AND_RESPAWN
#ifndef DISABLE_AUTO_SAFE_SPOT
			p_safe_pant = n_pant;
			p_safe_x = p_x >> 4;
			p_safe_y = p_y >> 4;
#endif			
#endif
#ifdef DISABLE_PLATFORMS
		} else {
#else
		} else if (0 == p_gotten) {
#endif
			falling = 1;
			canmove = 0;
#if PHANTOMAS_ENGINE != 3
			goto keepontruckin;
#endif
#ifdef DISABLE_PLATFORMS
		}
#else
		} else falling = 0;
#endif
#if PHANTOMAS_ENGINE == 3
	}
#endif	
		// Moving platforms (1st attempt)
		if (p_gotten) {
			if (ptgmx < 0) check_to_h = WLEFT; else if (ptgmx > 0) check_to_h = WRIGHT;
			if (ptgmy < 0) check_to_v = WTOP; else if (ptgmy > 0) check_to_v = WBOTTOM;
		}

		// Read controller
		gpit = (joyfunc) (&keys);
	
		// Jump?
#if PHANTOMAS_ENGINE == 3
		if (0 == p_jmp_on && 0 == falling && (gpit & sp_UP) == 0) {
#else
		if ((gpit & sp_UP) == 0) {
#endif
			p_jmp_ct = 0;
			p_jmp_on = 1;
#ifdef MODE_128K
			_AY_PL_SND (SFX_JUMP);
#else
			beep_fx (SFX_JUMP);
#endif
#if PHANTOMAS_ENGINE == 1
			// Phantomas 1 - TALL jump
			p_vx = PHANTOMAS_INCR_1;
			p_vy = PHANTOMAS_INCR_2;
#elif PHANTOMAS_ENGINE == 2
			// Phantomas 2 - LONG jump
			p_vx = p_vy = PHANTOMAS_INCR_2;
#elif PHANTOMAS_ENGINE == 3
			// Phantomas LOKOsoft - thrust jump
			p_vy = PHANTOMAS_INCR_2;
#elif PHANTOMAS_ENGINE == 4
			// Abu Simbel Profanation - LONG jump
			p_vy = PHANTOMAS_INCR_1;
			p_jump_max_steps = PHANTOMAS_JUMP_CTR + PHANTOMAS_JUMP_CTR;
			if ((gpit & sp_LEFT) == 0) {
				p_vx = PHANTOMAS_INCR_1;
				p_facing = 0;
			} else if ((gpit & sp_RIGHT) == 0) {
				p_vx = PHANTOMAS_INCR_1;
				p_facing = 4;
			} else {
				p_vx = 0;
			}
#endif
#if PHANTOMAS_ENGINE == 3
		}
#else
		} else if ((gpit & sp_DOWN) == 0) {
			p_jmp_ct = 0;
			p_jmp_on = 1;
#ifdef MODE_128K
			_AY_PL_SND (SFX_JUMP_ALT);
#else
			beep_fx (SFX_JUMP_ALT);
#endif
#if PHANTOMAS_ENGINE == 1
			// Phantomas 1 - WIDE jump
			p_vx = PHANTOMAS_INCR_2;
			p_vy = PHANTOMAS_INCR_1;
#elif PHANTOMAS_ENGINE == 2
			// Phantomas 2 - SHORT jump
			p_vx = p_vy = PHANTOMAS_INCR_1;
#elif PHANTOMAS_ENGINE == 4
			// Abu Simbel Profanation - SHORT jump
			p_vy = PHANTOMAS_INCR_1;
			p_jump_max_steps = PHANTOMAS_JUMP_CTR;
			if ((gpit & sp_LEFT) == 0) {
				p_vx = PHANTOMAS_INCR_1;
				p_facing = 0;
			} else if ((gpit & sp_RIGHT) == 0) {
				p_vx = PHANTOMAS_INCR_1;
				p_facing = 4;
			} else {
				p_vx = 0;
			}
#endif
		}
#endif

		// Left/right
		
#ifdef RESET_TO_WHEN_STOPPED
		d_pressed = 0;
#endif		
			
		if ((gpit & sp_LEFT) == 0) {			
			if (p_facing == 4) {
				p_facing = 0;
			} else {
				mx += -PHANTOMAS_WALK;
#if ADVANCE_FRAME_COUNTER == 1				
				p_frame = (p_frame + 1) & 3;
#else
				advance_frame ();
#endif
				check_to_h = WLEFT;
#ifdef PLAYER_STEP_SOUND
				step ();
#endif
#ifdef RESET_TO_WHEN_STOPPED
				d_pressed = 1;
#endif
			}
		}
		
		if ((gpit & sp_RIGHT) == 0) {
			if (p_facing == 0) {
				p_facing = 4;
			} else {
				mx += PHANTOMAS_WALK;
#if ADVANCE_FRAME_COUNTER == 1				
				p_frame = (p_frame + 1) & 3;
#else
				advance_frame ();
#endif
				check_to_h = WRIGHT;
#ifdef PLAYER_STEP_SOUND
				step ();
#endif
#ifdef RESET_TO_WHEN_STOPPED
				d_pressed = 1;
#endif
			}
		}

#if PHANTOMAS_ENGINE != 3
	} else {
#endif
		// Jump
#if PHANTOMAS_ENGINE == 4
		if (p_jmp_ct < (p_jump_max_steps >> 1)) {
#else
		if (p_jmp_ct < (PHANTOMAS_JUMP_CTR >> 1)) {
#endif
			// Up
			my = -p_vy;
			check_to_v = WTOP;
		} else {
#if PHANTOMAS_ENGINE == 3
			// Off
			p_jmp_on = 0;
#else
			// Down
			my = p_vy;
			check_to_v = WBOTTOM;
#endif
		}
		
#if PHANTOMAS_ENGINE != 3
		// Horizontal
		
#if PHANTOMAS_ENGINE == 2
		// Change direction?
		if ((gpit & sp_LEFT) == 0) {
			p_facing = 0;
		} else if ((gpit & sp_RIGHT) == 0) {
			p_facing = 4;
		}
#endif

		// Advance
		if (p_facing) {
			mx = p_vx; check_to_h = WRIGHT;
		} else {
			mx = -p_vx; check_to_h = WLEFT;
		}
#endif

#if PHANTOMAS_ENGINE == 4
		if (p_jmp_ct < p_jump_max_steps) {
#else
		if (p_jmp_ct < PHANTOMAS_JUMP_CTR) {
#endif			
			p_jmp_ct ++;
		} else {
			p_jmp_on = 0;
		}
#if PHANTOMAS_ENGINE != 3
	}
#endif

		// Conveyors
#ifdef ENABLE_CONVEYORS	
		pty3 = 1 + (p_y + 16);
		ptx1 = p_x >> 4; ptx2 = (p_x + 15) >> 4;
		pt1 = attr (ptx1, pty3);
		pt2 = attr (ptx2, pty3);
		if (pt1 & 32) {
			mx += (pt1 & 1) ? 1 : -1;
		}
		if (pt1 & 32) {
			mx += (pt1 & 1) ? 1 : -1;
		}
#endif

	// Collisions
	p_y += my;
	ptx1 = LIMIT_LEFT; ptx2 = LIMIT_RIGHT;
	
	if (check_to_v == WTOP) {
		pty1 = LIMIT_TOP;
		if ((attr (ptx1, pty1) & 8) || (attr (ptx2, pty1) & 8)) {
			p_y = ADJUST_TOP;
		}
	} else if (check_to_v == WBOTTOM) {
		pty2 = LIMIT_BOTTOM;
		if ((attr (ptx1, pty2) & 12) || (attr (ptx2, pty2) & 12)) {
			p_y = ADJUST_BOTTOM;
			p_jmp_on = 0;
		}
	}
	
	p_x += mx;
	pty1 = LIMIT_TOP; pty2 = LIMIT_BOTTOM; ptm = (p_y + 8) >> 4;
	if (check_to_h == WLEFT) {
		ptx1 = LIMIT_LEFT;
#if defined (PLAYER_PUSH_BOXES) || !defined (DEACTIVATE_KEYS)
		if (attr (ptx1, ptm) == 10) process_tile (ptx1, ptm, ptx1 - 1, ptm);
#endif
		if ((attr (ptx1, pty1) & 8) || (attr (ptx1, pty2) & 8)) {
			p_x = ADJUST_LEFT;
			wall_h = WLEFT;
		}
	} else if (check_to_h == WRIGHT) {
		ptx2 = LIMIT_RIGHT;
#if defined (PLAYER_PUSH_BOXES) || !defined (DEACTIVATE_KEYS)
		if (attr (ptx2, ptm) == 10) process_tile (ptx2, ptm, ptx2 + 1, ptm);
#endif
		if ((attr (ptx2, pty1) & 8) || (attr (ptx2, pty2) & 8)) {
			p_x = ADJUST_RIGHT;
			wall_h = WRIGHT;
		}
	}
	
keepontruckin:
	// Further checks
	
	// Fire bullets
#include "engine/playermods/fire.h"
	
	// Hitters
#include "engine/playermods/hitter.h"
	
	// Bombs
#include "engine/playermods/bombs.h"

	// Done with the fire button...
#include "engine/playermods/fire_button.h"	
	
	ptx2 = (p_x + 8) >> 4;
	pty2 = (p_y + 8) >> 4;

#ifndef DEACTIVATE_EVIL_TILE	
	// Killing tile
	if (attr (ptx2, pty2) & 1) {
		kill_player (SFX_PLAYER_DEATH_SPIKE);
	}
#endif

	// Tile get
#ifdef TILE_GET
	if (qtile (ptx2, pty2) == TILE_GET) {
		gpaux = ptx2 + (pty2 << 4) - pty2;
		map_buff [gpaux] = 0;
		map_attr [gpaux] = 0;
		draw_coloured_tile_gamearea (ptx2, pty2, 0);
		flags [TILE_GET_FLAG] ++;
#ifdef MODE_128K
			_AY_PL_SND (SFX_TILE_GET);
#else
			beep_fx (SFX_TILE_GET);
#endif

#ifdef TILE_GET_SCRIPT
		run_script run_script (2 * MAP_W * MAP_H + 4);
#endif
	}
#endif
	
	// Calculate frame
	if (p_jmp_on || falling) {
		p_n_f = player_frames [p_facing ? 9 : 8];
	} else {
#ifdef RESET_TO_WHEN_STOPPED
		if (d_pressed) {
			p_n_f = player_frames [p_facing + p_frame];
		} else {
			p_n_f = player_frames [p_facing + RESET_TO_WHEN_STOPPED];
		}
#else		
		p_n_f = player_frames [p_facing + p_frame];
#endif		
	}
	
	// possee
	possee = (0 == p_jmp_on && 0 == falling && 0 == p_gotten);
		
}
