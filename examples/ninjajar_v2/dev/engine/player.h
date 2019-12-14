// MT Engine MK2 v0.90b
// Copyleft 2016 the Mojon Twins

// playermove.h
// Player movement v5.1 : half-box/point collision
// Copyleft 2013 by The Mojon Twins

// Predefine button detection
#ifdef USE_TWO_BUTTONS
	#define BUTTON_FIRE			((pad0 & sp_FIRE) == 0 || sp_KeyPressed (key_fire))
	#define BUTTON_JUMP 		(sp_KeyPressed (key_jump))
	#define BUTTON_JUMP_START	(sp_KeyPressed (key_jump))
#else
	#if defined (PLAYER_CAN_FIRE) || defined (PLAYER_CAN_PUNCH) || defined (PLAYER_HAZ_SWORD) || defined (CARRIABLE_BOXES_THROWABLE)
		#define BUTTON_FIRE			((pad0 & sp_FIRE) == 0)
		#define BUTTON_JUMP			((pad0 & sp_UP) == 0)
		#define BUTTON_JUMP_START	((pad_this_frame & sp_UP) == 0)
	#else
		#define BUTTON_FIRE			(0)
		#define BUTTON_JUMP			((pad0 & sp_FIRE) == 0)
		#define BUTTON_JUMP_START	((pad_this_frame & sp_FIRE) == 0)
	#endif
#endif

void player_init (void) {
	// Inicializa player con los valores iniciales
	// (de ahí lo de inicializar).

	#ifndef COMPRESSED_LEVELS
		#if defined (HANNA_ENGINE)
			p_x = PLAYER_INI_X << 4;
			p_y = PLAYER_INI_Y << 4;;
		#else
			gpx = PLAYER_INI_X << 4;
			gpy = PLAYER_INI_Y << 4;
			p_x = gpx << FIXBITS;
			p_y = gpy << FIXBITS;
		#endif
	#endif

	#if defined (PLAYER_GENITAL) && defined (PLAYER_HAS_JUMP)
		p_z = p_vz = 0;
		p_jmp_facing = 0;
	#endif

	#ifdef HANNA_ENGINE
		p_v = HANNA_WALK;
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
		#ifdef PLAYER_GENITAL
			p_facing = FACING_DOWN;
		#elif defined (HANNA_ENGINE)
			p_facing = 6;
		#else
			p_facing = 1;
		#endif
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
		p_safe_x = gpx >> 4;
		p_safe_y = gpy >> 4;
	#endif

	#if defined (BREAKABLE_WALLS) || defined (BREAKABLE_WALLS_SIMPLE)
		#ifdef BREAKABLE_ANIM
			breaking_idx = 0;	
		#endif	
	#endif

	#ifdef PLAYER_VARIABLE_JUMP
		PLAYER_JMP_VY_MAX = PLAYER_JMP_VY_MAX;
	#endif

	#ifdef JETPAC_DEPLETES
		p_fuel = JETPAC_FUEL_INITIAL;
	#endif
		
	#ifdef ENABLE_KILL_SLOWLY
		p_ks_gauge = p_ks_fc = 0;
	#endif
}

void player_calc_bounding_box (void) {
	#if defined (BOUNDING_BOX_8_BOTTOM)
		#asm
			ld  a, (_gpx)
			add 4
			srl a
			srl a
			srl a
			srl a
			ld  (_ptx1), a
			ld  a, (_gpx)
			add 11
			srl a
			srl a
			srl a
			srl a
			ld  (_ptx2), a
			ld  a, (_gpy)
			add 8
			srl a
			srl a
			srl a
			srl a
			ld  (_pty1), a
			ld  a, (_gpy)
			add 15
			srl a
			srl a
			srl a
			srl a
			ld  (_pty2), a
		#endasm
	#elif defined (BOUNDING_BOX_8_CENTERED)
		#asm
			ld  a, (_gpx)
			add 4
			srl a
			srl a
			srl a
			srl a
			ld  (_ptx1), a
			ld  a, (_gpx)
			add 11
			srl a
			srl a
			srl a
			srl a
			ld  (_ptx2), a
			ld  a, (_gpy)
			add 4
			srl a
			srl a
			srl a
			srl a
			ld  (_pty1), a
			ld  a, (_gpy)
			add 11
			srl a
			srl a
			srl a
			srl a
			ld  (_pty2), a
		#endasm
	#elif defined (BOUNDING_BOX_TINY_BOTTOM)		
		#asm
			ld  a, (_gpx)
			add 4
			srl a
			srl a
			srl a
			srl a
			ld  (_ptx1), a
			ld  a, (_gpx)
			add 11
			srl a
			srl a
			srl a
			srl a
			ld  (_ptx2), a
			ld  a, (_gpy)
			add 14
			srl a
			srl a
			srl a
			srl a
			ld  (_pty1), a
			ld  a, (_gpy)
			add 15
			srl a
			srl a
			srl a
			srl a
			ld  (_pty2), a
		#endasm
	#else
		#asm
			ld  a, (_gpx)
			srl a
			srl a
			srl a
			srl a
			ld  (_ptx1), a
			ld  a, (_gpx)
			add 15
			srl a
			srl a
			srl a
			srl a
			ld  (_ptx2), a
			ld  a, (_gpy)
			srl a
			srl a
			srl a
			srl a
			ld  (_pty1), a
			ld  a, (_gpy)
			add 15
			srl a
			srl a
			srl a
			srl a
			ld  (_pty2), a
		#endasm
	#endif
}

#if defined (ENABLE_FLOATING_OBJECTS) && defined (ENABLE_FO_CARRIABLE_BOXES) && defined (CARRIABLE_BOXES_CORCHONETA)
signed int p_vlhit;
#endif

void player_kill (void) {
	#ifdef CUSTOM_HIT
		if (was_hit_by_type == 0xff) {
			gpd = CUSTOM_HIT_DEFAULT;
		}
		#ifdef FANTIES_HIT
			else if (was_hit_by_type == 2) {
				gpd = FANTIES_HIT;
			}
		#endif
		#ifdef PATROLLERS_HIT
			else if (was_hit_by_type == 1) {
				gpd = PATROLLERS_HIT;
			}
		#endif
		else gpd = CUSTOM_HIT_DEFAULT;
		was_hit_by_type = 0xff;

		if (p_life > CUSTOM_HIT_DEFAULT) p_life -= CUSTOM_HIT_DEFAULT; else p_life = 0;
	#else
		p_life --;
	#endif

	#ifdef MODE_128K
		#ifdef PLAY_SAMPLE_ON_DEATH
			_AY_ST_ALL ();
		#else
			_AY_PL_SND (p_killme);
		#endif
	#else
		beep_fx (p_killme);
	#endif

	#ifdef DIE_AND_RESPAWN
		#ifdef ENABLE_HOLES
			if (p_ct_hole >= 2)
		#endif
		{
			half_life = 0;
		}
	#endif
	#ifdef PLAYER_FLICKERS
		p_state = EST_PARP;
		p_state_ct = 50;
	#endif
	#ifdef REENTER_ON_DEATH
		o_pant = 99;
		hide_sprites (0);
	#endif

	#ifdef DIE_AND_RESPAWN
		#ifdef PLAY_SAMPLE_ON_DEATH
			wyz_play_sample (PLAY_SAMPLE_ON_DEATH);
		#endif

		active_sleep (50);
		#ifdef PLAYER_HAS_SWIM
			if (p_engine != SENG_SWIM)
		#endif	
		{
			n_pant = p_safe_pant;
			
			#if !defined (DISABLE_AUTO_SAFE_SPOT) && !defined (PLAYER_GENITAL)
			
				gpjt = p_safe_x; gpit = 15; while (	gpit -- ) {
					cx1 = gpjt;
					cy1 = p_safe_y + 1;
					at1 = attr ();
					cx1 = gpjt;
					cy1 = p_safe_y;
					at2 = attr ();
					if ((at1 & 12) && !(at2 & 8)) break;
					gpjt ++; if (gpjt == 15) gpjt = 0; 
				}
				p_safe_x = gpjt;
			
			#endif

			#if defined (PHANTOMAS_ENGINE) || defined (HANNA_ENGINE)
				p_x = p_safe_x << 4;
				p_y = p_safe_y << 4;
			#elif defined (PLAYER_GENITAL)
				gpx = p_safe_x; gpy = p_safe_y;
				p_x = gpx << FIXBITS;
				p_y = gpy << FIXBITS;
			#else
				gpx = p_safe_x << 4; gpy = p_safe_y << 4;
				p_x = gpx << FIXBITS;
				p_y = gpy << FIXBITS;
			#endif
			
			p_vx = p_vy = p_jmp_on = 0;
		}

		#ifdef MODE_128K
			// Play music
			#ifdef COMPRESSED_LEVELS
				_AY_PL_MUS (level_data->music_id);
			#else
				_AY_PL_MUS (1);
			#endif
			//_AY_PL_SND (18);
		#endif
	#endif
}

unsigned char player_move (void) {

	wall_v = wall_h = 0;

	// Get bottom-center pixel tile behaviour for several NEW_GENITAL stuff
	#if defined (PLAYER_GENITAL)
		p_thrust = 0;
		#if defined (ENABLE_CONVEYORS) || defined (ENABLE_BEH_64)
			cx1 = (gpx + 8) >> 4; cy1 = (gpy + 15) >> 4; at1 = attr ();	
		#endif
	#endif

	#if defined (PLAYER_GENITAL)
		// Pre-detect conveyors. Needs attr @ bottom-center pixel in pt1!
		#if defined (ENABLE_CONVEYORS)
			#include "engine/playermods/ng_conveyors.h"
		#endif

		// Pre-detect behaviour 64. Needs attr @ bottom-center pixel in pt1!
		#if defined (ENABLE_BEH_64)
			#include "engine/playermods/ng_beh64.h"
		#endif
	#endif

	// ***************************************************************************
	//  MOVEMENT IN THE VERTICAL AXIS
	// ***************************************************************************

	#include "engine/playermods/va.h"

	// ***************************************************************************
	//  MOVEMENT IN THE HORIZONTAL AXIS
	// ***************************************************************************

	#include "engine/playermods/ha.h"

	// **********
	// MORE STUFF
	// **********

	#ifdef PLAYER_GENITAL
		// Priority to decide facing
		#ifdef TOP_OVER_SIDE
			if (p_facing_v != 0xff) {
				p_facing = p_facing_v;
			} else if (p_facing_h != 0xff) {
				p_facing = p_facing_h;
			}
		#else
			if (p_facing_h != 0xff) {
				p_facing = p_facing_h;
			} else if (p_facing_v != 0xff) {
				p_facing = p_facing_v;
			}
		#endif
	#endif

	#ifdef FIRE_TO_PUSH
		pushed_any = 0;
	#endif

	// ********************
	// Hail the corchoneta!
	// ********************
	
	#if defined (ENABLE_FLOATING_OBJECTS) && defined (ENABLE_FO_CARRIABLE_BOXES) && defined (CARRIABLE_BOXES_CORCHONETA)
		// With special carriable boxes
		if (wall_v == WBOTTOM) {
			
			gpx = p_x >> 6;
			cy1 = (gpy + 16) >> 4;
			cx1 = (gpx + 8) >> 4;
			if (attr () & 64) p_vy = -(abs (p_vlhit)) << 1;	 // CHECK FORMULA!
			if (p_vy < -CARRIABLE_BOXES_MAX_C_VY) p_vy = -CARRIABLE_BOXES_MAX_C_VY;
		}
	#endif

	// Other ways soon!

	// ************************************************
	// Tile type 10 operations (push boxes, open locks)
	// ************************************************
	
	#include "engine/playermods/type10.h"

	// ************
	// Fire bullets
	// ************
	
	#include "engine/playermods/fire.h"

	// *******
	// Hitters
	// *******
	
	#include "engine/playermods/hitter.h"

	// *****
	// Bombs
	// *****
	
	#include "engine/playermods/bombs.h"

	// Done with the fire button...
	#include "engine/playermods/fire_button.h"	

	// **********
	// Hole tiles
	// **********

	#ifdef ENABLE_HOLES
		gpx = p_x >> FIXBITS;
		cy1 = cy2 = (gpy + 15) >> 4;
		cx1 = (gpx + 4) >> 4;
		cx2 = (gpx + 12) >> 4;
		cm_two_points ();

		if (
			#if defined (PLAYER_GENITAL) && defined (PLAYER_HAS_JUMP)
				p_z == 0 && 
			#endif
			p_gotten == 0 && at1 == 3 && at2 == 3 && p_state == EST_NORMAL
		) {
			if (p_ct_hole < 2) {
				p_ct_hole ++;
			} else {
				p_n_f = FALLING_FRAME;
				main_spr_frame (gpx, gpy);
				#ifdef MODE_128K
					_AY_PL_SND (SFX_FALL_HOLE);
					active_sleep (25);
				#else			
					beep_fx (SFX_FALL_HOLE);
				#endif
				p_n_f = FALLING_FRAME + 144;
				main_spr_frame (gpx, gpy);
				#ifdef MODE_128K			
					active_sleep (25);
				#endif			
				p_killme = SFX_PLAYER_DEATH_HOLE;
			}
		} else p_ct_hole = 0;
	#endif

	#if defined (TILE_GET) || defined (ENABLE_KILL_SLOWLY)
		cx1 = (gpx + 8) >> 4;
		cy1 = (gpy + 8) >> 4;

	#endif

	// ********************
	// Killing slowly tiles
	// ********************
	#ifdef ENABLE_KILL_SLOWLY	
		if (attr () == 3) {
			#ifdef KILL_SLOWLY_ON_FLAG
				if (p_ks_gauge && flags [KILL_SLOWLY_ON_FLAG])
			#else		
				if (p_ks_gauge) 
			#endif			
			{
				if (p_ks_fc) {
					p_ks_fc --;
				} else {
					p_ks_fc = KILL_SLOWLY_FRAMES;
					p_ks_gauge --;
					#ifdef MODE_128K
						_AY_PL_SND (SFX_KS_TICK);
					#else
						sp_Border (2);
						beep_fx (SFX_KS_TICK);
						sp_Border (0);
					#endif				
				}
			} else {
				p_life --;
				p_ks_fc = (p_ks_fc + 1) & 3;			
				if (0 == p_ks_fc) 
					#ifdef MODE_128K
						_AY_PL_SND (SFX_KS_DRAIN);
					#else
						beep_fx (SFX_KS_DRAIN);
					#endif				
			}
		} else {
			#ifdef KILL_SLOWLY_ON_FLAG		
				if (p_ks_gauge < KILL_SLOWLY_GAUGE && flags [KILL_SLOWLY_ON_FLAG]) p_ks_gauge ++;		
			#else
				if (p_ks_gauge < KILL_SLOWLY_GAUGE) p_ks_gauge ++;
			#endif		
		}
	#endif	

	// ********
	// Tile get 
	// ********
	
	#ifdef TILE_GET
		if (qtile () == TILE_GET) {
			_x = cx1; _y = cy1; _t = TILE_GET_REPLACE; _n = behs [TILE_GET_REPLACE];
			update_tile ();
			#if defined (PLAYER_SHOW_FLAG) && PLAYER_SHOW_FLAG == TILE_GET_FLAG
				if (flags [TILE_GET_FLAG] < 99)
			#endif
			flags [TILE_GET_FLAG] ++;
			#ifdef MODE_128K
				_AY_PL_SND (SFX_TILE_GET);
			#else
				beep_fx (SFX_TILE_GET);
			#endif

			#ifdef TILE_GET_SCRIPT
				run_script (2 * MAP_W * MAP_H + 4);
			#endif
		}
	#endif

	// **********
	// Evil tiles
	// **********

	#ifndef DEACTIVATE_EVIL_TILE
		#ifdef ONLY_VERTICAL_EVIL_TILE
			if (hit_v) {
				p_vy = addsign (-p_vy, PLAYER_V_BOUNCE);
				// CUSTOM {
					//p_y = (p_y >> 10) << 10;
					#if FIXBITS == 6
						p_y &= 0xfc00; 
					#else
						p_y &= 0xff00; 
					#endif
					gpy &= 0xf0;
				// } END_OF_CUSTOM
				#ifdef PLAYER_FLICKERS
					if (p_life > 0 && p_state == EST_NORMAL)
				#else
					if (p_life > 0)
				#endif
				{
					p_killme = SFX_PLAYER_DEATH_SPIKE;
				}
			}
		#else
			// hit_v tiene preferencia sobre hit_h
			hit = 0;
			if (hit_v == TILE_EVIL) {
				hit = 1;
				#ifdef FULL_BOUNCE
					p_vy = addsign (-p_vy, PLAYER_V_BOUNCE);
				#else
					p_vy = -p_vy;
				#endif
			} else if (hit_h == TILE_EVIL) {
				hit = 1;
				#ifdef FULL_BOUNCE
					p_vx = addsign (-p_vx, PLAYER_V_BOUNCE);
				#else
					p_vx = -p_vx;
				#endif
			}

			if (hit) {
				#ifdef PLAYER_FLICKERS
					if (p_life > 0 && p_state == EST_NORMAL)
				#else
					if (p_life > 0)
				#endif
				{
					p_killme = SFX_PLAYER_DEATH_SPIKE;
				}
			}
		#endif
	#endif

	// **********************
	// Select animation frame
	// **********************

	#ifndef PLAYER_GENITAL
		#ifdef PLAYER_BOOTEE
			gpit = p_facing << 2;
			if (p_vy == 0) {
				p_n_f = player_frames [gpit];
			} else if (p_vy < 0) {
				p_n_f = player_frames [gpit + 1];
			} else {
				p_n_f = player_frames [gpit + 2];
			}
		#else
			if (!possee && !p_gotten) {
				p_n_f = player_frames [8 + p_facing];
			} else {
				gpit = p_facing << 2;
				if (p_vx == 0) {
					#ifdef PLAYER_ALTERNATE_ANIMATION
						p_n_f = player_frames [gpit];
					#else
						p_n_f = player_frames [gpit + 1];
					#endif
				} else {
					p_subframe ++;
					if (p_subframe == 4) {
						p_subframe = 0;
						#ifdef PLAYER_ALTERNATE_ANIMATION
							p_frame ++; if (p_frame == 3) p_frame = 0;
						#else
							p_frame = (p_frame + 1) & 3;
						#endif
						#ifdef PLAYER_STEP_SOUND
							step ();
						#endif
					}
					p_n_f = player_frames [gpit + p_frame];
				}
			}
		#endif
	#else
		#if defined (PLAYER_GENITAL) && defined (PLAYER_HAS_JUMP)
			if (p_z != 0) {
				p_n_f = player_frames [1 + p_jmp_facing];
			} else 
		#endif		
		{
			if (p_vx == 0 && p_vy == 0) {
				p_n_f = player_frames [p_facing];
			} else if (p_thrust) {
				p_subframe ++;
				if (p_subframe == 4) {
					p_subframe = 0;
					p_frame = !p_frame;
					#ifdef PLAYER_STEP_SOUND
						step ();
					#endif
				}
				p_n_f = player_frames [p_facing + p_frame];
			}		
		}
	#endif

}