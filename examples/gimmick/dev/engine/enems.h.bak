// MT Engine MK2 v0.90b
// Copyleft 2016 the Mojon Twins

// enems.h
// Enemy management, new style

// Ninjajar Clouds not supported, sorry!
// Type 5 "random respawn" not supported sorry! (but easily punchable!)

// There are new, more suitable defines now.
// ENABLE_FANTIES
// ENABLE_LINEAR_ENEMIES
// ENABLE_PURSUE_ENEMIES
// ENABLE_SHOOTERS

#include "engine/enemmods/helper_funcs.h"

#if WAYS_TO_DIE > 1
	#include "engine/enemmods/kill_enemy_multiple.h"
#elif defined ENEMS_MAY_DIE
	#include "engine/enemmods/kill_enemy.h"
#endif

void enems_init (void) {
	
	// Enemies' "t" is now slightly more complex:
	// XTTTTDNN where
	// X = dead
	// TTTT = type       1000 = platform
	//                   0001 = linear
	//                   0010 = flying
	//                   0011 = pursuing

	// Reserved (addons)
	//                   1001 = drops
	//                   1010 = arrows
	//                   1011 = Hanna Type 11
	//                   1100 = Hanna Punchos

	// 01001000

	#ifdef COUNT_SCR_ENEMS_ON_FLAG
		flags [COUNT_SCR_ENEMS_ON_FLAG]	= 0;
	#endif

	#ifndef RESPAWN_ON_REENTER
		if (do_respawn)
	#endif
	for (gpit = 0; gpit < 3; gpit ++) {
		//en_an_frame [gpit] = 0;
		en_an_count [gpit] = 3;
		en_an_state [gpit] = 0;
		enoffsmasi = enoffs + gpit;
		
		#ifdef RESPAWN_ON_ENTER
			// Back to life!
			{		
				baddies [enoffsmasi].t &= 0x7f;
				en_an_state [gpit] = 0;
				#if defined (PLAYER_CAN_FIRE) || defined (PLAYER_CAN_PUNCH) || defined (PLAYER_HAZ_SWORD)
					#ifdef COMPRESSED_LEVELS
						baddies [enoffsmasi].life = level_data.enems_life;
					#else
						baddies [enoffsmasi].life = ENEMS_LIFE_GAUGE;
					#endif
				#endif
			}
		#endif

		// Init enems:
		// - Asign "base frame"
		// - Init coordinates for flying people
		// Remember XTTTTDNN, TTTT = type, D = fires balls, NN = sprite number

		_en_t = baddies [enoffsmasi].t;
		gpt = _en_t >> 3;
		if (gpt && gpt < 16) {
			en_an_base_frame [gpit] = (_en_t & 3) << 1;

			switch (gpt) {
				#ifdef ENABLE_FANTIES
					case 2:
						// Flying
						#ifdef FANTIES_FIXED_CELL
							en_an_base_frame [gpit] = FANTIES_FIXED_CELL << 1;
						#endif
						en_an_x [gpit] = baddies [enoffsmasi].x1 << FIXBITS;
						baddies [enoffsmasi].x = baddies [enoffsmasi].x1;
						en_an_y [gpit] = baddies [enoffsmasi].y1 << FIXBITS;
						baddies [enoffsmasi].y = baddies [enoffsmasi].y1;
						
						en_an_vx [gpit] = en_an_vy [gpit] = 0;
						#ifdef FANTIES_SIGHT_DISTANCE					
							en_an_state [gpit] = FANTIES_IDLE;
						#endif					
						break;
				#endif
				#ifdef ENABLE_PURSUE_ENEMIES
					case 3:
						// Pursuing
						en_an_alive [gpit] = 0;
						en_an_dead_row [gpit] = 0;//DEATH_COUNT_EXPRESSION;
						break;
				#endif
				#ifdef ENABLE_CLOUDS
					case 4:
						// Make sure mx is positive!
						baddies [enoffsmasi].mx = abs (baddies [enoffsmasi].mx);
						break;
				#endif
				#ifdef ENABLE_DROPS
					case 9:
						#include "addons/drops/init.h"
						break;
				#endif
				#ifdef ENABLE_HANNA_MONSTERS_11
					case 11:
						en_an_state [gpit] = 0;
						break;
				#endif
				#include "my/extra_enems_init.h"
				default:
					break;
			}

			#ifdef COUNT_SCR_ENEMS_ON_FLAG
				#if defined (DISABLE_PLATFORMS) || defined (PLAYER_GENITAL)
					flags [COUNT_SCR_ENEMS_ON_FLAG] ++;
				#else
					if (16 != gpt) flags [COUNT_SCR_ENEMS_ON_FLAG] ++;
				#endif
			#endif
		} 
	}
}

void enems_move_spr_abs (void) {
	//sp_MoveSprAbs (sp_moviles [enit], spritesClip, en_an_n_f [enit] - en_an_c_f [enit], VIEWPORT_Y + (_en_y >> 3), VIEWPORT_X + (_en_x >> 3), _en_x & 7, _en_y & 7);
	
	#asm
		; enter: IX = sprite structure address 
		;        IY = clipping rectangle, set it to "ClipStruct" for full screen 
		;        BC = animate bitdef displacement (0 for no animation) 
		;         H = new row coord in chars 
		;         L = new col coord in chars 
		;         D = new horizontal rotation (0..7) ie horizontal pixel position 
		;         E = new vertical rotation (0..7) ie vertical pixel position 

		// sp_moviles [enit] = sp_moviles + enit*2
		ld  a, (_enit)
		sla a
		ld  c, a
		ld  b, 0 				// BC = offset to [enit] in 16bit arrays
		ld  hl, _sp_moviles
		add hl, bc
		ld  e, (hl)
		inc hl 
		ld  d, (hl)
		push de						
		pop ix

		// Clipping rectangle
		ld  iy, vpClipStruct

		// Animation
		// en_an_n_f [enit] - en_an_c_f [enit]
		ld  hl, _en_an_c_f
		add hl, bc 				// HL -> en_an_current_frame [enit]
		ld  e, (hl)
		inc hl 
		ld  d, (hl) 			// DE = en_an_current_frame [enit]

		ld  hl, _en_an_n_f
		add hl, bc 				// HL -> en_an_next_frame [enit]
		ld  a, (hl)
		inc hl
		ld  h, (hl)
		ld  l, a 				// HL = en_an_next_frame [enit]

		or  a 					// clear carry
		sbc hl, de 				// en_an_next_frame [enit] - en_an_current_frame [enit]

		push bc 				// Save for later

		ld  b, h
		ld  c, l 				// ** BC = animate bitdef **

		//VIEWPORT_Y + (_en_y >> 3), VIEWPORT_X + (_en_x >> 3)
		ld  a, (__en_y)					
		srl a
		srl a
		srl a
		add VIEWPORT_Y
		ld h, a

		ld  a, (__en_x)
		srl a
		srl a
		srl a
		add VIEWPORT_X
		ld  l, a

		// _en_x & 7, _en_y & 7
		ld  a, (__en_x)
		and 7
		ld  d, a

		ld  a, (__en_y)
		and 7
		ld  e, a

		call SPMoveSprAbs

		// en_an_c_f [enit] = en_an_n_f [enit];

		pop bc 					// Retrieve index

		ld  hl, _en_an_c_f
		add hl, bc
		ex  de, hl 				// DE -> en_an_c_f [enit]	

		ld  hl, _en_an_n_f
		add hl, bc 				// HL -> en_an_n_f [enit]
		
		ldi
		ldi
	#endasm
}

void enems_move (void) {
	#if !defined (PLAYER_GENITAL) || defined (PLAYER_NEW_GENITAL)
		p_gotten = ptgmy = ptgmx = 0;
	#endif

	tocado = 0;

	for (enit = 0; enit < 3; ++ enit) {
		active = killable = animate = 0;
		enoffsmasi = enoffs + enit;

		// Copy array values to temporary variables as fast as possible
		
		#asm
				// Those values are stores in this order:
				// x, y, x1, y1, x2, y2, mx, my, t, life
				// Point HL to baddies [enoffsmasi]. The struct is 10 bytes long
				// so this is baddies + enoffsmasi*10
				ld 	hl, (_enoffsmasi)
				ld  h, 0
				add hl, hl 				// x2
				ld  d, h
				ld  e, l 				// DE = x2
				add hl, hl 				// x4
				add hl, hl 				// x8
				
				add hl, de 				// HL = x8 + x2 = x10

				ld  de, _baddies
				add hl, de

				ld  (__baddies_pointer), hl 		// Save address for later

				ld  a, (hl)
				ld  (__en_x), a
				inc hl 

				ld  a, (hl)
				ld  (__en_y), a
				inc hl 

				ld  a, (hl)
				ld  (__en_x1), a
				inc hl 

				ld  a, (hl)
				ld  (__en_y1), a
				inc hl 

				ld  a, (hl)
				ld  (__en_x2), a
				inc hl 

				ld  a, (hl)
				ld  (__en_y2), a
				inc hl 

				ld  a, (hl)
				ld  (__en_mx), a
				inc hl 

				ld  a, (hl)
				ld  (__en_my), a
				inc hl 

				ld  a, (hl)
				ld  (__en_t), a
				inc hl 

				ld  a, (hl)
				ld  (__en_life), a
		#endasm

		if (_en_t == 0) {
			en_an_n_f [enit] = sprite_18_a;
		} 
		#ifdef ENEMS_MAY_DIE
			else if (en_an_state [enit] == GENERAL_DYING) {
				if (en_an_count [enit]) {
					-- en_an_count [enit];
					en_an_n_f [enit] = sprite_17_a;
				} else {
					#ifndef MODE_128K
						beep_fx (SFX_KILL_ENEMY);
					#endif
					en_an_state [enit] = 0;
					en_an_n_f [enit] = sprite_18_a;
				}	
			} 
		#endif
		else {

			#if defined (ENABLE_SHOOTERS) || defined (ENABLE_ARROWS)
				if (_en_t & 4) {
					enemy_shoots = 1;
				} else enemy_shoots = 0;
			#endif
			gpt = _en_t >> 3;

			// Gotten preliminary:	
			if (gpt == 8) {
				#ifdef PLAYER_NEW_GENITAL	
					/*
					pregotten =	(gpx + 12 >= _en_x && gpx <= _en_x + 12) &&
								(gpy + 15 >= _en_y && gpy <= _en_y);
					*/
					#asm
							// gpx + 12 >= _en_x
							ld  a, (__en_x)
							ld  c, a
							ld  a, (_gpx)
							add 12
							cp  c
							jp  c, _enems_move_pregotten_not 	// branch if <

							// gpx <= _en_x + 12; _en_x + 12 >= gpx
							ld  a, (_gpx)
							ld  c, a
							ld  a, (__en_x)
							add 12
							cp  c 
							jp  c, _enems_move_pregotten_not 	// branch if <

							// gpy + 15 >= _en_y
							ld  a, (__en_y)
							ld  c, a
							ld  a, (_gpy)
							add 15
							cp  c
							jp  c, _enems_move_pregotten_not	// branch if <

							// gpy <= _en_y; _en_y >= gpy
							ld  a, (_gpy)
							ld  c, a
							ld  a, (__en_y)
							cp  c
							jp  c, _enems_move_pregotten_not	// branch if <

							ld  a, 1
							jr  _enems_move_pregotten_set

						._enems_move_pregotten_not
							xor a

						._enems_move_pregotten_set
							ld  (_pregotten), a
					
						// enemy_shoots = (_en_t & 4);
						// gpt = _en_t >> 3;

							ld  a, (__en_t)
							ld  c, a
							and 4
							ld  (_enemy_shoots), a
							ld  a, c
							srl a
							srl a
							srl a
							ld  (_gpt), a
					#endasm

				#elif !defined (PLAYER_GENITAL)
					
					#if defined (BOUNDING_BOX_8_CENTERED) || defined (BOUNDING_BOX_8_BOTTOM)
						// pregotten = (gpx + 12 >= _en_x && gpx <= _en_x + 12);
						#asm
								// gpx + 12 >= _en_x
								ld  a, (__en_x)
								ld  c, a
								ld  a, (_gpx)
								add 12
								cp  c
								jp  c, _enems_move_pregotten_not 	// branch if <

								// gpx <= _en_x + 12; _en_x + 12 >= gpx
								ld  a, (_gpx)
								ld  c, a
								ld  a, (__en_x)
								add 12
								cp  c 
								jp  c, _enems_move_pregotten_not 	// branch if <

								ld  a, 1
								jr  _enems_move_pregotten_set

							._enems_move_pregotten_not
								xor a

							._enems_move_pregotten_set
								ld  (_pregotten), a			
						#endasm
					#else
						// pregotten = (gpx + 12 >= _en_x && gpx <= _en_x + 12);
						#asm
								// gpx + 15 >= _en_x
								ld  a, (__en_x)
								ld  c, a
								ld  a, (_gpx)
								add 12
								cp  c
								jp  c, _enems_move_pregotten_not 	// branch if <

								// gpx <= _en_x + 15; _en_x + 12 >= gpx
								ld  a, (_gpx)
								ld  c, a
								ld  a, (__en_x)
								add 12
								cp  c 
								jp  c, _enems_move_pregotten_not 	// branch if <

								ld  a, 1
								jr  _enems_move_pregotten_set

							._enems_move_pregotten_not
								xor a

							._enems_move_pregotten_set
								ld  (_pregotten), a			
						#endasm
					#endif

				#endif
			}

			switch (gpt) {
				#ifdef ENABLE_PATROLLERS
					case 1:			// linear
						killable = 1;
					case 8:			// moving platforms
						#include "engine/enemmods/move_linear.h"
						break;
				#endif
				#ifdef ENABLE_FANTIES
					case 2:			// flying
						#include "engine/enemmods/move_fanty_asm.h"
						break;
				#endif
				#ifdef ENABLE_PURSUERS
					case 3:			// pursuers
						#include "engine/enemmods/move_pursuers.h"
						break;
				#endif
				#ifdef ENABLE_CLOUDS
					case 4:
						#include "engine/enemmods/move_clouds.h"
						break;
				#endif
				#ifdef ENABLE_DROPS
					case 9:			// drops
						#ifdef DROPS_KILLABLE
							killable = 1;
						#endif
						#include "addons/drops/move.h"
						break;
				#endif
				#ifdef ENABLE_ARROWS
					case 10:		// arrows
						#ifdef ARROWS_KILLABLE
							killable = 1;
						#endif
						#include "addons/arrows/move.h"
						break;
				#endif
				#ifdef ENABLE_HANNA_MONSTERS_11
					case 11:		// Hanna monsters type 11
						#include "engine/enemmods/move_hanna_11.h"
						break;
				#endif
				#include "my/extra_enems_move.h"
				default:
					en_an_n_f [enit] = sprite_18_a;
			}

			if (active) {
				if (animate) {
					#ifdef FANTIES_WITH_FACING
						if (gpt == 2) {
							gpjt = (gpx > _en_x);
						} else
					#endif
					{
						gpjt = _en_mx ? ((_en_x + 4) >> 3) & 1 : ((_en_y + 4) >> 3) & 1;
					}
					en_an_n_f [enit] = enem_frames [en_an_base_frame [enit] + gpjt];
				}

				// Carriable box launched and hit...
				#ifdef ENABLE_FO_CARRIABLE_BOXES
					#ifdef CARRIABLE_BOXES_THROWABLE
						#include "engine/enemmods/throwable.h"
					#endif
				#endif	
				
				// Hitter
				#if defined (PLAYER_CAN_PUNCH) || defined (PLAYER_HAZ_SWORD) || defined (PLAYER_HAZ_WHIP)
					#include "engine/enemmods/hitter.h"
				#endif		

				// Bombs
				#if defined (PLAYER_SIMPLE_BOMBS)
					#include "engine/enemmods/bombs.h"
				#endif

				// Bullets
				#ifdef PLAYER_CAN_FIRE
					#include "engine/enemmods/bullets.h"
				#endif

				// Collide with player
				#if !defined (DISABLE_PLATFORMS)
					#ifdef PLAYER_NEW_GENITAL
						#include "engine/enemmods/platforms_25d.h"
					#elif !defined (PLAYER_GENITAL)
						#include "engine/enemmods/platforms.h"
					#endif
				#endif 	// ends with  } else
				//if ((tocado == 0) && collide (gpx, gpy, _en_x, _en_y) && p_state == EST_NORMAL) 
				#asm
					ld  a, (_tocado)
					or  a
					jp  nz, _enems_collision_skip

					ld  a, (_p_state)
					or  a
					jp  nz, _enems_collision_skip

					// (gpx + 8 >= _en_x && gpx <= _en_x + 8 && gpy + 8 >= _en_y && gpy <= _en_y + 8)

					// gpx + 8 >= _en_x
					ld  a, (__en_x)
					ld  c, a
					ld  a, (_gpx)
					#ifdef SMALL_COLLISION
						add 8
					#else
						add 12
					#endif
					cp  c
					jp  c, _enems_collision_skip

					// gpx <= _en_x + 8; _en_x + 8 >= gpx
					ld  a, (_gpx)
					ld  c, a
					ld  a, (__en_x)
					#ifdef SMALL_COLLISION
						add 8
					#else
						add 12
					#endif
					cp  c
					jp  c, _enems_collision_skip

					// gpy + 8 >= _en_y
					ld  a, (__en_y)
					ld  c, a
					ld  a, (_gpy)
					#ifdef SMALL_COLLISION
						add 8
					#else
						add 12
					#endif
					cp  c
					jp  c, _enems_collision_skip

					// gpy <= _en_y + 8; _en_y + 8 >= gpy
					ld  a, (_gpy)
					ld  c, a
					ld  a, (__en_y)
					#ifdef SMALL_COLLISION
						add 8
					#else
						add 12
					#endif
					cp  c
					jp  c, _enems_collision_skip			
				#endasm
				{
					#ifdef PLAYER_KILLS_ENEMIES
						#include "engine/enemmods/step_on.h"
					#endif
					if (p_life) {
						tocado = 1;
					}

					#if defined (SLOW_DRAIN) && defined (PLAYER_BOUNCES)
						if ((lasttimehit == 0) || ((maincounter & 3) == 0)) {
							p_killme = SFX_PLAYER_DEATH_ENEMY;
							#ifdef CUSTOM_HIT
								was_hit_by_type = gpt;
							#endif
						}
					#else
						p_killme = SFX_PLAYER_DEATH_ENEMY;
						#ifdef CUSTOM_HIT
							was_hit_by_type = gpt;
						#endif
					#endif

					#ifdef FANTIES_KILL_ON_TOUCH
						if (gpt == 2) enems_kill (FANTIES_LIFE_GAUGE);
					#endif

					#ifdef PLAYER_BOUNCES
						#ifndef PLAYER_GENITAL

							p_vx = addsign (_en_mx, PLAYER_VX_MAX << 1);
							p_vy = addsign (_en_my, PLAYER_VX_MAX << 1);

						#else
							if (_en_mx) {
								p_vx = addsign (gpx - _en_x, abs (_en_mx) << (2+FIXBITS));
							}
							if (_en_my) {
								p_vy = addsign (gpy - _en_y, abs (_en_my) << (2+FIXBITS));
							}
						#endif
					#endif
				}

				#asm
					._enems_collision_skip
				#endasm
			}			
		}

		enems_loop_continue:
		#asm
			.enems_loop_continue_a
		#endasm

		// Render
		#ifdef PIXEL_SHIFT
			if ((_en_t & 0x78) == 8) gpen_y -= PIXEL_SHIFT;
		#endif

		enems_move_spr_abs ();

		#asm		
				// Those values are stores in this order:
				// x, y, x1, y1, x2, y2, mx, my, t, life

				ld  hl, (__baddies_pointer) 		// Restore pointer

				ld  a, (__en_x)
				ld  (hl), a
				inc hl

				ld  a, (__en_y)
				ld  (hl), a
				inc hl

				ld  a, (__en_x1)
				ld  (hl), a
				inc hl

				ld  a, (__en_y1)
				ld  (hl), a
				inc hl

				ld  a, (__en_x2)
				ld  (hl), a
				inc hl

				ld  a, (__en_y2)
				ld  (hl), a
				inc hl

				ld  a, (__en_mx)
				ld  (hl), a
				inc hl

				ld  a, (__en_my)
				ld  (hl), a
				inc hl

				ld  a, (__en_t)
				ld  (hl), a
				inc hl

				ld  a, (__en_life)
				ld  (hl), a
		#endasm	
	}

	#if defined (SLOW_DRAIN) && defined (PLAYER_BOUNCES)
		lasttimehit = tocado;
	#endif
}
