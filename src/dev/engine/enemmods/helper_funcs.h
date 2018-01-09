#if defined (ENABLE_FANTIES) || defined (ENABLE_SHOOTERS) || defined (ENABLE_HANNA_MONSTERS_11)
unsigned char distance (unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2) {
	unsigned char dx = abs (x2 - x1);
	unsigned char dy = abs (y2 - y1);
	unsigned char mn = dx < dy ? dx : dy;
	return (dx + dy - (mn >> 1) - (mn >> 2) + (mn >> 4));
}
#endif

#if defined (ENABLE_HANNA_MONSTERS_11)
// TODO: add light/torch stuff here!
unsigned char i_can_see_you (void) {
	return (distance (gpx, gpy, gpen_cx, gpen_cy) <= HANNA_MONSTERS_11_SIGHT);
}
#endif

#ifdef ENABLE_SHOOTERS
unsigned char coco_x [MAX_COCOS], coco_y [MAX_COCOS], coco_s [MAX_COCOS], ctx, cty;
signed char coco_vx [MAX_COCOS], coco_vy [MAX_COCOS];
void __FASTCALL__ init_cocos (void) {
	for (gpit = 0; gpit < MAX_COCOS;) coco_s [gpit++] = 0;
}

unsigned char coco_it, coco_d, coco_x0;
void __FASTCALL__ shoot_coco (void) {
	coco_x0 = gpen_cx + 4;
#ifdef SHOOTER_FIRE_ONE
	coco_it = gpit;
	{
#else
	for (coco_it = 0; coco_it < MAX_COCOS; coco_it ++) {
#endif
		if (coco_s [coco_it] == 0) {
			coco_d = distance (coco_x0, gpen_cy, gpx, gpy);
			if (coco_d >= SHOOTER_SAFE_DISTANCE) {
#ifdef MODE_128K
				_AY_PL_SND (3);
#endif
				coco_s [coco_it] = 1;
				coco_x [coco_it] = coco_x0;
				coco_y [coco_it] = gpen_cy;

				coco_vx [coco_it] = (ENEMY_SHOOT_SPEED * (gpx - coco_x0) / coco_d);
				coco_vy [coco_it] = (ENEMY_SHOOT_SPEED * (gpy - gpen_cy) / coco_d);
			}
		}
	}
}

void __FASTCALL__ move_cocos (void) {
	for (coco_it = 0; coco_it < MAX_COCOS; coco_it ++) {
		if (coco_s [coco_it]) {
			coco_x [coco_it] += coco_vx [coco_it];
			coco_y [coco_it] += coco_vy [coco_it];

			if (coco_x [coco_it] >= 240 || coco_y [coco_it] >= 160) coco_s [coco_it] = 0;
			// Collide player
			ctx = coco_x [coco_it] + 3;
			cty = coco_y [coco_it] + 3;
			if (p_state == EST_NORMAL) {
				if (collide_pixel (ctx, cty, gpx, gpy)) {
					coco_s [coco_it] = 0;
						kill_player (SFX_PLAYER_DEATH_COCO);
				}
			}
		}
	}
}
#endif

#ifdef ENABLE_RANDOM_RESPAWN
char player_hidden (void) {
	gpxx = gpx >> 4;
	gpyy = gpy >> 4;
	if ( (gpy & 15) == 0 && p_vx == 0 ) {
		if (attr (gpxx, gpyy) == 2 || (attr (1 + gpxx, gpyy) == 2 && (gpx & 15)) ) {
			return 1;
		}
	}
	return 0;
}
#endif

#if defined (ENABLE_HANNA_MONSTERS_11)
unsigned char player_hidden (void) {
	gpxx = (gpx + 8) >> 4; gpyy = (gpy + 8) >> 4;
	return (attr (gpxx, gpyy) & 2);
}
#endif

#ifdef WALLS_STOP_ENEMIES
unsigned char __FASTCALL__ mons_col_sc_x (void) {
	gpaux = gpen_xx + (baddies [enoffsmasi].mx > 0);
#ifdef EVERYTHING_IS_A_WALL
	return (attr (gpaux, gpen_yy) || ((baddies [enoffsmasi].y & 15) && attr (gpaux, gpen_yy + 1)));
#else
	return (attr (gpaux, gpen_yy) & 8 || ((baddies [enoffsmasi].y & 15) && attr (gpaux, gpen_yy + 1) & 8));
#endif
}

unsigned char __FASTCALL__ mons_col_sc_y (void) {
	gpaux = gpen_yy + (baddies [enoffsmasi].my > 0);
#ifdef EVERYTHING_IS_A_WALL
	return (attr (gpen_xx, gpaux) || ((baddies [enoffsmasi].x & 15) && attr (gpen_xx + 1, gpaux)));
#else
	return (attr (gpen_xx, gpaux) & 8 || ((baddies [enoffsmasi].x & 15) && attr (gpen_xx + 1, gpaux) & 8));
#endif
}
#endif

#if defined (SLOW_DRAIN) && defined (PLAYER_BOUNCES)
unsigned char lasttimehit;
#endif

#if defined (ENABLE_FANTIES) || defined (ENABLE_RANDOM_RESPAWN)
int limit (int val, int min, int max) {
	if (val < min) return min;
	if (val > max) return max;
	return val;
}
#endif
