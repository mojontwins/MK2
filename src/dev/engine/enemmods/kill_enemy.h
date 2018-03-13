//

void enemy_kill (unsigned char amount) {
	baddies [enoffsmasi].x = gpen_x;
	baddies [enoffsmasi].y = gpen_y;

#if PLAYER_BULLETS_STRENGTH > 0 || PLAYER_HITTER_STRENGTH > 0 || PLAYER_BOMBS_STRENGTH > 0)
	en_an_n_f [gpit] = sprite_17_a;

// Trajectory modification?
#ifdef ENABLE_FANTIES
	if (gpt == 2) {
		en_an_vx [gpit] += -en_an_vx [gpit];
		en_an_x [gpit] += en_an_vx [gpit];
	}
#endif

#if ENEMIES_LIFE_GAUGE > 1 || FANTIES_LIFE_GAUGE > 1
// Lose life
	if (killable) baddies [enoffsmasi].life -= amount;

// No life left?
	if (baddies [enoffsmasi].life == 0) {
#else
	if (killable) {
#endif								

// Play sound								
#ifdef MODE_128K
		en_an_state [gpit] = GENERAL_DYING;
		en_an_count [gpit] = 8;
		_AY_PL_SND (SFX_KILL_ENEMY);
#else
		sp_MoveSprAbs (sp_moviles [gpit], spritesClip, en_an_n_f [gpit] - en_an_c_f [gpit], VIEWPORT_Y + (gpen_cy >> 3), VIEWPORT_X + (gpen_cx >> 3), gpen_cx & 7, gpen_cy & 7);
		en_an_c_f [gpit] = en_an_n_f [gpit];
		sp_UpdateNow ();
		beep_fx (SFX_KILL_ENEMY);
		en_an_n_f [gpit] = sprite_18_a;
#endif								
		
// Mark as enemy dead																
#ifdef ENABLE_PURSUERS
		if (gpt != 7) baddies [enoffsmasi].t |= 128;
#else
		baddies [enoffsmasi].t |= 128;
#endif

// Count kills								
#ifdef BODY_COUNT_ON								
		flags [BODY_COUNT_ON] ++;
#else
		p_killed ++;
#endif

// Special for pursuers...	
#ifdef ENABLE_PURSUERS
		en_an_alive [gpit] = 0;
		en_an_dead_row [gpit] = DEATH_COUNT_EXPRESSION;
#endif

// Run script on kill
#ifdef ACTIVATE_SCRIPTING
#ifdef RUN_SCRIPT_ON_KILL
		run_script (2 * MAP_W * MAP_H + 5);
#endif
#endif

#if ENEMIES_LIFE_GAUGE > 1 || FANTIES_LIFE_GAUGE > 1
	} else {
		baddies [enoffsmasi].mx = -baddies [enoffsmasi].mx;
		baddies [enoffsmasi].my = -baddies [enoffsmasi].my;
	}
#else
	}
#endif

#else

// Trajectory modification?
#ifdef ENABLE_FANTIES
	if (gpt == 2) {
		en_an_vx [gpit] =- en_an_vx [gpit];
	}
#endif

#ifdef ENABLE_PATROLLERS
	baddies [enoffsmasi].mx = -baddies [enoffsmasi].mx;
	baddies [enoffsmasi].my = -baddies [enoffsmasi].my;
#endif

// Play sound
#ifdef MODE_128K
		_AY_PL_SND (SFX_ENEMY_HIT);
#else
		beep_fx (SFX_ENEMY_HIT);
#endif
	
#endif		
////	
}
