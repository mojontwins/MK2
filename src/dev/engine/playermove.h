// MT Engine MK2 v0.90b
// Copyleft 2016 the Mojon Twins

// playermove.h
// Player movement v5.0 : half-box/point collision
// Copyleft 2013 by The Mojon Twins

// Predefine button detection
#ifdef USE_TWO_BUTTONS
	#define BUTTON_FIRE	((gpit & sp_FIRE) == 0 || sp_KeyPressed (key_fire))
	#define BUTTON_JUMP	(sp_KeyPressed (key_jump))
#else
	#if defined (PLAYER_CAN_FIRE) || defined (PLAYER_CAN_PUNCH) || defined (PLAYER_HAZ_SWORD) || defined (CARRIABLE_BOXES_THROWABLE)
		#define BUTTON_FIRE	((gpit & sp_FIRE) == 0)
		#define BUTTON_JUMP	((gpit & sp_UP) == 0)
	#else
		#define BUTTON_FIRE	(0)
		#define BUTTON_JUMP	((gpit & sp_FIRE) == 0)
	#endif
#endif

#if defined (ENABLE_FLOATING_OBJECTS) && defined (ENABLE_FO_CARRIABLE_BOXES) && defined (CARRIABLE_BOXES_CORCHONETA)
signed int p_vlhit;
#endif
unsigned char ptx1, ptx2, pty1, pty2, pty3, pt1, pt2;
unsigned char move (void) {

	wall_v = wall_h = 0;
	gpit = (joyfunc) (&keys);

	// Get bottom-center pixel tile behaviour for several NEW_GENITAL stuff
#if defined (PLAYER_GENITAL)
	p_thrust = 0;
#if defined (ENABLE_CONVEYORS) || defined (ENABLE_BEH_64)
	gpx = p_x >> 6;	gpy = p_y >> 6;
	pt1 = attr ((gpx + 8) >> 4, (gpy + 15) >> 4);	
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
		pty1 = (gpy + 16) >> 4;
		ptx1 = (gpx + 8) >> 4;
		if (attr (ptx1, pty1) & 64) p_vy = -(abs (p_vlhit)) << 1;	 // CHECK FORMULA!
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
	gpx = p_x >> 6;
	pty1 = (gpy + 15) >> 4;
	ptx1 = (gpx + 4) >> 4;
	ptx2 = (gpx + 12) >> 4;
	if (
		#if defined (PLAYER_GENITAL) && defined (PLAYER_HAS_JUMP)
			p_z == 0 && 
		#endif
		p_gotten == 0 && attr (ptx1, pty1) == 3 && attr (ptx2, pty1) == 3 && p_state == EST_NORMAL
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
			kill_player (SFX_PLAYER_DEATH_HOLE);
		}
	} else p_ct_hole = 0;
#endif

#if defined (TILE_GET) || defined (ENABLE_KILL_SLOWLY)
	gpxx = (gpx + 8) >> 4;
	gpyy = (gpy + 8) >> 4;
#endif

	// ********************
	// Killing slowly tiles
	// ********************
#ifdef ENABLE_KILL_SLOWLY	
	if (attr (gpxx, gpyy) == 3) {
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
	if (qtile (gpxx, gpyy) == TILE_GET) {
		gpaux = gpxx + (gpyy << 4) - gpyy;
		map_buff [gpaux] = 0;
		map_attr [gpaux] = 0;
		draw_coloured_tile_gamearea (gpxx, gpyy, 0);
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
		p_y = (p_y >> 10) << 10;
// } END_OF_CUSTOM
#ifdef PLAYER_FLICKERS
		if (p_life > 0 && p_state == EST_NORMAL)
#else
		if (p_life > 0)
#endif
		{
			kill_player (SFX_PLAYER_DEATH_SPIKE);
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
			kill_player (SFX_PLAYER_DEATH_SPIKE);
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