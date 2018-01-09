// MT Engine MK2 v0.90b
// Copyleft 2016 the Mojon Twins

// bullets.h
// Bullets helper functions

void fire_bullet (void) {
#ifdef PLAYER_CAN_FIRE_FLAG 
	if (flags [PLAYER_CAN_FIRE_FLAG] == 0) return;
#endif
#ifdef MAX_AMMO
	if (!p_ammo) return;
	p_ammo --;
#endif
	// Buscamos una bala libre
	for (gpit = 0; gpit < MAX_BULLETS; gpit ++) {
		if (bullets_estado [gpit] == 0) {
			bullets_estado [gpit] = 1;
#ifdef PLAYER_GENITAL
			switch (p_facing) {
				case FACING_LEFT:
#if defined (PHANTOMAS_ENGINE) || defined (HANNA_ENGINE)
					bullets_x [gpit] = p_x - 4;
					bullets_mx [gpit] = -PLAYER_BULLET_SPEED;
					bullets_y [gpit] = p_y + PLAYER_BULLET_Y_OFFSET;
					bullets_my [gpit] = 0;
#else
					bullets_x [gpit] = (p_x >> 6) - 4;
					bullets_mx [gpit] = -PLAYER_BULLET_SPEED;
					bullets_y [gpit] = (p_y >> 6) + PLAYER_BULLET_Y_OFFSET;
					bullets_my [gpit] = 0;
#endif
					break;
				case FACING_RIGHT:
#if defined (PHANTOMAS_ENGINE) || defined (HANNA_ENGINE)
					bullets_x [gpit] = p_x + 12;
					bullets_mx [gpit] = PLAYER_BULLET_SPEED;
					bullets_y [gpit] = p_y + PLAYER_BULLET_Y_OFFSET;
					bullets_my [gpit] = 0;
#else
					bullets_x [gpit] = (p_x >> 6) + 12;
					bullets_mx [gpit] = PLAYER_BULLET_SPEED;
					bullets_y [gpit] = (p_y >> 6) + PLAYER_BULLET_Y_OFFSET;
					bullets_my [gpit] = 0;
#endif
					break;
				case FACING_DOWN:
#if defined (PHANTOMAS_ENGINE) || defined (HANNA_ENGINE)
					bullets_x [gpit] = p_x + PLAYER_BULLET_X_OFFSET;
					bullets_y [gpit] = p_y + 12;
					bullets_my [gpit] = PLAYER_BULLET_SPEED;
					bullets_mx [gpit] = 0;
#else
					bullets_x [gpit] = (p_x >> 6) + PLAYER_BULLET_X_OFFSET;
					bullets_y [gpit] = (p_y >> 6) + 12;
					bullets_my [gpit] = PLAYER_BULLET_SPEED;
					bullets_mx [gpit] = 0;
#endif
					break;
				case FACING_UP:
#if defined (PHANTOMAS_ENGINE) || defined (HANNA_ENGINE)
					bullets_x [gpit] = p_x + 8 - PLAYER_BULLET_X_OFFSET;
					bullets_y [gpit] = p_y - 4;
					bullets_my [gpit] = -PLAYER_BULLET_SPEED;
					bullets_mx [gpit] = 0;
#else
					bullets_x [gpit] = (p_x >> 6) + 8 - PLAYER_BULLET_X_OFFSET;
					bullets_y [gpit] = (p_y >> 6) - 4;
					bullets_my [gpit] = -PLAYER_BULLET_SPEED;
					bullets_mx [gpit] = 0;
#endif
					break;
			}
#else

#ifdef CAN_FIRE_UP
			gpjt = (joyfunc) (&keys);
			if (!(gpjt & sp_UP)) {
#if defined (PHANTOMAS_ENGINE) || defined (HANNA_ENGINE)
				bullets_y [gpit] = p_y;
#else
				bullets_y [gpit] = (p_y >> 6);
#endif
				bullets_my [gpit] = -PLAYER_BULLET_SPEED;
			} else if (!(gpjt & sp_DOWN)) {
#if defined (PHANTOMAS_ENGINE) || defined (HANNA_ENGINE)
				bullets_y [gpit] = 8 + p_y;
#else
				bullets_y [gpit] = 8 + (p_y >> 6);
#endif
				bullets_my [gpit] = PLAYER_BULLET_SPEED;		
			} else {
#endif
#if defined (PHANTOMAS_ENGINE) || defined (HANNA_ENGINE)
				bullets_y [gpit] = p_y + PLAYER_BULLET_Y_OFFSET;
#else
				bullets_y [gpit] = (p_y >> 6) + PLAYER_BULLET_Y_OFFSET;
#endif
				bullets_my [gpit] = 0;
#ifdef CAN_FIRE_UP			
			}
#endif

#ifdef CAN_FIRE_UP
			if (!(gpjt & sp_LEFT) || !(gpjt & sp_RIGHT) || ((gpjt & sp_UP) && (gpjt & sp_DOWN))) {
#endif				
				if (p_facing == 0) {
#if defined (PHANTOMAS_ENGINE) || defined (HANNA_ENGINE)
					bullets_x [gpit] = p_x - 4;
#else
					bullets_x [gpit] = (p_x >> 6) - 4;
#endif
					bullets_mx [gpit] = -PLAYER_BULLET_SPEED;
				} else {
#if defined (PHANTOMAS_ENGINE) || defined (HANNA_ENGINE)
					bullets_x [gpit] = p_x + 12;
#else
					bullets_x [gpit] = (p_x >> 6) + 12;
#endif
					bullets_mx [gpit] = PLAYER_BULLET_SPEED;
				}
#ifdef CAN_FIRE_UP				
			} else {
#if defined (PHANTOMAS_ENGINE) || defined (HANNA_ENGINE)
				bullets_x [gpit] = p_x + 4;
#else
				bullets_x [gpit] = (p_x >> 6) + 4;
#endif
				bullets_mx [gpit] = 0;
			}
#endif			
#endif
#ifdef MODE_128K
			_AY_PL_SND (SFX_SHOOT);
#else
			beep_fx (SFX_SHOOT);
#endif

#ifdef LIMITED_BULLETS
#if defined (LB_FRAMES) || !defined (ACTIVATE_SCRIPTING)
			bullets_life [gpit] = LB_FRAMES;
#else
			bullets_life [gpit] = flags [LB_FRAMES_FLAG];
#endif
#endif
			break;
		}
	}
}

void mueve_bullets (void) {
	for (gpit = 0; gpit < MAX_BULLETS; gpit ++) {
		if (bullets_estado [gpit]) {
			if (bullets_mx [gpit]) {
				bullets_x [gpit] += bullets_mx [gpit];
				if (bullets_x [gpit] > 240) {
					bullets_estado [gpit] = 0;
				}
			}
#if defined (PLAYER_GENITAL) || defined (CAN_FIRE_UP)
			if (bullets_my [gpit]) {
				bullets_y [gpit] += bullets_my [gpit];
				if (bullets_y [gpit] < 8 || bullets_y [gpit] > 160) {
					bullets_estado [gpit] = 0;
				}
			}
#endif
			gpxx = (bullets_x [gpit] + 3) >> 4;
			gpyy = (bullets_y [gpit] + 3) >> 4;
#if (defined (BREAKABLE_WALLS) || defined (BREAKABLE_WALLS_SIMPLE)) && defined (BULLETS_BREAK_WALLS)
			break_wall (gpxx, gpyy);
#endif
			if (attr (gpxx, gpyy) > 7) bullets_estado [gpit] = 0;
			
#ifdef LIMITED_BULLETS
			if (bullets_life [gpit] > 0) {
				bullets_life [gpit] --;
			} else {
				bullets_estado [gpit]= 0;
			}
#endif
		}
	}
}
