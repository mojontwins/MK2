// MT Engine MK2 v0.90b
// Copyleft 2016 the Mojon Twins

// phantomasmove.h
// Player movement for Phantomas/Abu Simbel games

void player_init (void) {
	// Inicializa player con los valores iniciales
	// (de ahí lo de inicializar).

	#ifndef COMPRESSED_LEVELS
		p_x = PLAYER_INI_X << 4;
		p_y = PLAYER_INI_Y << 4;;
	#endif

	p_vy = 0;
	p_vx = 0;

	#ifdef PLAYER_HAS_JUMP
		p_jmp_ct = 1;
		p_jmp_on = 0;
	#endif

	p_frame = 0;
	p_subframe = 0;

	#ifndef EXTENDED_LEVELS
		p_facing = 4;
	#endif
	
	p_facing_v = p_facing_h = 0xff;
	p_state = EST_NORMAL;
	p_state_ct = 0;

	#if !defined (COMPRESSED_LEVELS) || defined (REFILL_ME)
		p_life = PLAYER_LIFE;
	#endif

	p_objs = 0;
	p_keys = 0;

	#ifdef BODY_COUNT_ON
		flags [BODY_COUNT_ON] = 0;
	#else	
		p_killed = 0;
	#endif	

	p_disparando = 0;

	#ifdef MAX_AMMO
		#ifdef INITIAL_AMMO
			p_ammo = INITIAL_AMMO;
		#else
			p_ammo = MAX_AMMO;
		#endif
	#endif

	#if defined (PLAYER_CAN_PUNCH) || defined (PLAYER_HAZ_SWORD)
		p_hitting = 0;
		hitter_on = 0;
	#endif

	#ifdef TIMER_ENABLE
		ctimer.count = 0;
		ctimer.zero = 0;
		#ifdef TIMER_LAPSE
			ctimer.frames = TIMER_LAPSE;
		#endif
		#ifdef TIMER_INITIAL
			ctimer.t = TIMER_INITIAL;
		#endif
		#ifdef TIMER_START
			ctimer.on = 1;
		#else
			ctimer.on = 0;
		#endif
	#endif

	#ifdef DIE_AND_RESPAWN
		p_killme = 0;
		p_safe_pant = n_pant;
		p_safe_x = p_x >> 10;
		p_safe_y = p_y >> 10;
	#endif

	#if defined (BREAKABLE_WALLS) || defined (BREAKABLE_WALLS_SIMPLE)
		#ifdef BREAKABLE_ANIM
			breaking_idx = 0;	
		#endif	
	#endif

	#ifdef ENABLE_KILL_SLOWLY
		p_ks_gauge = p_ks_fc = 0;
	#endif
}

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
void advance_frame (void) {
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

unsigned char player_move () {
	gpit = (joyfunc) (&keys);
	wall_h = 0;
	check_to_v = check_to_h = 0;
	mx = my = 0;

	if (p_jmp_on == 0) {
		p_y += PHANTOMAS_FALLING;
		pty2 = LIMIT_BOTTOM;
		
		// Make fall?
		ptx1 = LIMIT_LEFT; ptx2 = LIMIT_RIGHT;
		cx1 = ptx1; cx2 = ptx2; cy1 = cy2 = pty2; cm_two_points ();
		if ((at1 & 12) || (at2 & 12)) {
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
		cy1 = cy2 = 1 + (p_y + 16);
		cx1 = p_x >> 4; cx2 = (p_x + 15) >> 4;
		cm_two_points ();
		
		if (at1 & 32) {
			mx += (pt1 & 1) ? 1 : -1;
		}
		if (at1 & 32) {
			mx += (pt1 & 1) ? 1 : -1;
		}
#endif

	// Collisions
	p_y += my;
	ptx1 = LIMIT_LEFT; ptx2 = LIMIT_RIGHT;
	
	cx1 = ptx1; cx2 = ptx2;
	if (check_to_v == WTOP) {
		cy1 = cy2 = LIMIT_TOP;
		cm_two_points ();
		if ((at1 & 8) || (at2 & 8)) {
			p_y = ADJUST_TOP;
		}
	} else if (check_to_v == WBOTTOM) {
		cy1 = cy2 = LIMIT_BOTTOM;
		cm_two_points ();
		if ((at1 & 12) || (at2 & 12)) {
			p_y = ADJUST_BOTTOM;
			p_jmp_on = 0;
		}
	}
	
	p_x += mx;	
	if (check_to_h == WLEFT) {		
		#if defined (PLAYER_PUSH_BOXES) || !defined (DEACTIVATE_KEYS)
			cx1 = LIMIT_LEFT; cy1 = (p_y + 8) >> 4;
			if (attr () == 10) process_tile (cx1, cy1, cx1 - 1, cy1);
		#endif

		cx1 = cx2 = LIMIT_LEFT; cy1 = LIMIT_TOP; cy2 = LIMIT_BOTTOM;
		cm_two_points ();
		if ((at1 & 8) || (at2 & 8)) {
			p_x = ADJUST_LEFT;
			wall_h = WLEFT;
		}
	} else if (check_to_h == WRIGHT) {
		
		#if defined (PLAYER_PUSH_BOXES) || !defined (DEACTIVATE_KEYS)
			cx1 = LIMIT_LEFT; cy1 = (p_y + 8) >> 4;
			if (attr () == 10) process_tile (cx1, cy1, cx1 + 1, cy1);
		#endif

		cx1 = cx2 = LIMIT_RIGHT; cy1 = LIMIT_TOP; cy2 = LIMIT_BOTTOM;
		cm_two_points ();
		if ((at1 & 8) || (at2 & 8)) {
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
	
	cx1 = (p_x + 8) >> 4;
	cy1 = (p_y + 8) >> 4;

#ifndef DEACTIVATE_EVIL_TILE	
	// Killing tile
	if (attr () & 1) {
		kill_player (SFX_PLAYER_DEATH_SPIKE);
	}
#endif

	// Tile get
#ifdef TILE_GET
	if (qtile () == TILE_GET) {
		gpaux = ptx2 + (pty2 << 4) - pty2;
		map_buff [gpaux] = 0;
		map_attr [gpaux] = 0;
		_x = ptx2; _y = pty2; _t = 0
		draw_invalidate_coloured_tile_gamearea ();
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
