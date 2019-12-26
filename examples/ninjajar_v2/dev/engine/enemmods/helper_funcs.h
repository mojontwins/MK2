#if defined (ENABLE_FANTIES) || defined (ENABLE_SHOOTERS) || defined (ENABLE_HANNA_MONSTERS_11) || defined (ENABLE_CLOUDS)
	unsigned char distance (void) {
		/*
		unsigned char dx = abs (cx2 - cx1);
		unsigned char dy = abs (cy2 - cy1);
		unsigned char mn = dx < dy ? dx : dy;
		return (dx + dy - (mn >> 1) - (mn >> 2) + (mn >> 4));
		*/
		
		#asm
				// Calculate dx
				ld  a, (_cx1)
				ld  c, a
				ld  a, (_cx2)
				sub c
				bit 7, a 	// Negative?
				jr  z, _distance_dx_set
				neg
			._distance_dx_set
				ld  (__x), a

				// Calculate dy
				ld  a, (_cy1)
				ld  c, a
				ld  a, (_cy2)
				sub c
				bit 7, a 	// Negative?
				jr  z, _distance_dy_set
				neg
			._distance_dy_set
				ld  (__y), a

				// Calculate mn
				ld  c, a 			; c = _y
				ld  a, (__x)        ; a = _x
				cp  c 				; _x < _y ?
				jr  c, _distance_mn_set
			._distance_dy_min
				ld  a, c
			._distance_mn_set
				ld  (__n), a

				// Calculate distance
				// return (dx + dy - (mn >> 1) - (mn >> 2) + (mn >> 4));
				ld  a, (__x)
				ld  c, a
				ld  a, (__y)
				add c
				ld  b, a 	// dx + dy

				ld  a, (__n)
				srl a
				ld  c, a 			; c = (mn >> 1)
				srl a
				ld  d, a 			; d = (mn >> 2)
				srl a
				srl a
				ld  e, a 			; e = (mn >> 4)

				ld  a, b 	// dx + dy
				sub c  		// dx + dy - (mn >> 1)
				sub d 		// dx + dy - (mn >> 1) - (mn >> 2)
				add e 		// dx + dy - (mn >> 1) - (mn >> 2) + (mn >> 4)

				ld  l, a
				ld  h, 0
		#endasm		
	}
#endif

#if defined (ENABLE_HANNA_MONSTERS_11)
	// TODO: add light/torch stuff here!
	unsigned char i_can_see_you (void) {
		cx1 = gpx; cy1 = gpy; cx2 = _en_x; cy2 = _en_y;
		return (distance () <= HANNA_MONSTERS_11_SIGHT);
	}
#endif

#if defined (ENABLE_SHOOTERS) || defined (ENABLE_CLOUDS)	

	void cocos_shoot (void) {
		coco_x0 = _en_x + 4;
		#ifdef SHOOTER_FIRE_ONE
			coco_it = enit;	
		#else
			for (coco_it = 0; coco_it < MAX_COCOS; ++ coco_it) 
		#endif
		{
			if (coco_s [coco_it] == 0) {
				cx1 = coco_x0; cy1 = _en_y; cx2 = gpx; cy2 = gpy;
				coco_d = distance ();
				if (coco_d >= SHOOTER_SAFE_DISTANCE) {
					#ifdef MODE_128K
						_AY_PL_SND (3);
					#endif

					coco_s [coco_it] = 1;
					coco_x [coco_it] = coco_x0;
					coco_y [coco_it] = _en_y;

					#ifdef ENABLE_CLOUDS
						if (gpt == 4) {
							coco_vx [coco_it] = 0;
							coco_vy [coco_it] = CLOUD_SHOOT_SPEED;
						} else
					#endif
					{
						coco_vx [coco_it] = (ENEMY_SHOOT_SPEED * (gpx - coco_x0) / coco_d);
						coco_vy [coco_it] = (ENEMY_SHOOT_SPEED * (gpy - _en_y) / coco_d);
					}
				}
			}
		}
	}

	void cocos_destroy (void) {
		coco_s [coco_it] = 0;
		//sp_MoveSprAbs (sp_cocos [coco_it], spritesClip, 0, -2, -2, 0, 0);
		#asm
				ld  a, (_coco_it)
				sla a
				ld  c, a
				ld  b, 0 				// BC = offset to [gpit] in 16bit arrays
				ld  hl, _sp_cocos
				add hl, bc
				ld  e, (hl)
				inc hl 
				ld  d, (hl)
				push de						
				pop ix

				ld  iy, vpClipStruct
				ld  bc, 0

				ld  hl, 0xfefe
				ld  de, 0 
				
				call SPMoveSprAbs
		#endasm
	}

	void cocos_init (void) {
		for (coco_it = 0; coco_it < MAX_COCOS; ++ coco_it) cocos_destroy ();
	}
	
	void cocos_move (void) {
		for (coco_it = 0; coco_it < MAX_COCOS; coco_it ++) {
			if (coco_s [coco_it]) {
				ctx = coco_x [coco_it] + coco_vx [coco_it];
				cty = coco_y [coco_it] + coco_vy [coco_it];

				if (ctx >= 240 || cty >= 160) cocos_destroy ();
				// Collide player
				if (p_state == EST_NORMAL) {
					cx1 = ctx + 3; cy1 = cty + 3; cx2 = gpx; cy2 = gpy;
					if (collide_pixel ()) {
						cocos_destroy ();
						p_killme = SFX_PLAYER_DEATH_COCO;
					}
				}
				// Collide cocos
				#ifdef COCOS_COLLIDE
					cx1 = (ctx + 3) >> 4; cy1 = (cty + 3) >> 4;
					if (attr () > 7) cocos_destroy ();
				#endif

				// Render
				//sp_MoveSprAbs (sp_cocos [coco_it], spritesClip, 0, VIEWPORT_Y + (coco_y [coco_it] >> 3), VIEWPORT_X + (coco_x [coco_it] >> 3), coco_x [coco_it] & 7, coco_y [coco_it] & 7);
				#asm
						ld  a, (_coco_it)
						sla a
						ld  c, a
						ld  b, 0 				// BC = offset to [gpit] in 16bit arrays
						ld  hl, _sp_cocos
						add hl, bc
						ld  e, (hl)
						inc hl 
						ld  d, (hl)
						push de						
						pop ix

						ld  iy, vpClipStruct
						ld  bc, 0

						ld  a, (_cty)
						srl a
						srl a
						srl a
						add VIEWPORT_Y
						ld  h, a

						ld  a, (_ctx)
						srl a
						srl a
						srl a
						add VIEWPORT_X
						ld  l, a

						ld  a, (_ctx)
						and 7
						ld  d, a 

						ld  a, (_cty)
						and 7
						ld  e, a 
						
						call SPMoveSprAbs
				#endasm	

				coco_x [coco_it] = ctx;
				coco_y [coco_it] = cty;
			}
		}
	}
#endif

#ifdef ENABLE_RANDOM_RESPAWN
	char player_hidden (void) {
		cx1 = gpx >> 4; cx2 = (gpx + 15) >> 4; 
		cy1 = cy2 = gpy >> 4;
		cm_two_points ();

		if ( (gpy & 15) == 0 && p_vx == 0 ) {
			if (at1 == 2 || at2 == 2) {
				return 1;
			}
		}
		return 0;
	}
#endif

#if defined (ENABLE_HANNA_MONSTERS_11)
	unsigned char player_hidden (void) {
		cx1 = (gpx + 8) >> 4; cy1 = (gpy + 8) >> 4;
		return (attr () & 2);
	}
#endif

#ifdef WALLS_STOP_ENEMIES
	unsigned char mons_col_sc_x (void) {
		cx1 = cx2 = (_en_mx > 0 ? _en_x + 15 : _en_x) >> 4;
		cy1 = _en_y >> 4; cy2 = (_en_y + 15) >> 4;
		cm_two_points ();
		#ifdef EVERYTHING_IS_A_WALL
			return (at1 || at2);
		#else
			return ((at1 & 8) || (at2 & 8));
		#endif

	}

	unsigned char mons_col_sc_y (void) {
		cy1 = cy2 = (_en_my > 0 ? _en_y + 15 : _en_y) >> 4;
		cx1 = _en_x >> 4; cx2 = (_en_x + 15) >> 4;
		cm_two_points ();
		#ifdef EVERYTHING_IS_A_WALL
			return (at1 || at2);
		#else
			return ((at1 & 8) || (at2 & 8));
		#endif
	}
#endif

#if defined (SLOW_DRAIN) && defined (PLAYER_BOUNCES)
	unsigned char lasttimehit;
#endif
