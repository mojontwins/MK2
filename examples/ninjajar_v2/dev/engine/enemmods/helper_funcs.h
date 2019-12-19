#if defined (ENABLE_FANTIES) || defined (ENABLE_SHOOTERS) || defined (ENABLE_HANNA_MONSTERS_11) || defined (ENABLE_CLOUDS)
	unsigned char distance (void) {
		unsigned char dx = abs (cx2 - cx1);
		unsigned char dy = abs (cy2 - cy1);
		unsigned char mn = dx < dy ? dx : dy;
		return (dx + dy - (mn >> 1) - (mn >> 2) + (mn >> 4));
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
	void init_cocos (void) {
		for (gpit = 0; gpit < MAX_COCOS;) coco_s [gpit++] = 0;
	}

	void shoot_coco (void) {
		coco_x0 = _en_x + 4;
		#ifdef SHOOTER_FIRE_ONE
			coco_it = enit;	
		#else
			for (coco_it = 0; coco_it < MAX_COCOS; coco_it ++) 
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

	void move_cocos (void) {
		for (coco_it = 0; coco_it < MAX_COCOS; coco_it ++) {
			if (coco_s [coco_it]) {
				ctx = coco_x [coco_it] + coco_vx [coco_it];
				cty = coco_y [coco_it] + coco_vy [coco_it];

				if (ctx >= 240 || cty >= 160) coco_s [coco_it] = 0;
				// Collide player
				if (p_state == EST_NORMAL) {
					ctx = cx1 = ctx + 3; cty = cy1 = cty + 3; cx2 = gpx; cy2 = gpy;
					if (collide_pixel ()) {
						coco_s [coco_it] = 0;
						p_killme = SFX_PLAYER_DEATH_COCO;
					}
				}
				// Collide cocos
				#ifdef COCOS_COLLIDE
					cx1 = ctx >> 4; cy1 = cty >> 4;
					if (attr () > 7) coco_s [coco_it] = 0;
				#endif			

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
