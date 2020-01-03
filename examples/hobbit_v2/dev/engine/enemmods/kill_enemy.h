//

void enems_kill (unsigned char amount) {
	
	#if PLAYER_BULLETS_STRENGTH > 0 || PLAYER_HITTER_STRENGTH > 0 || PLAYER_BOMBS_STRENGTH > 0)
		en_an_n_f [enit] = sprite_17_a;

		// Trajectory modification?
		#if defined ENABLE_FANTIES && FANTIES_LIFE_GAUGE > 1
			if (gpt == 2) {
				en_an_vx [enit] += -en_an_vx [enit];
				en_an_x [enit] += en_an_vx [enit];
			}
		#endif

		#if ENEMS_LIFE_GAUGE > 1 || FANTIES_LIFE_GAUGE > 1
			// Lose life
			if (killable) _en_life -= amount;

			// No life left?
			if (_en_life == 0)
		#else
			if (killable)
		#endif								
		{
			en_an_state [enit] = GENERAL_DYING;
			#ifdef MODE_128K
				en_an_count [enit] = ENEMS_DYING_FRAMES;
				_AY_PL_SND (SFX_KILL_ENEMY);
			#else
				en_an_count [enit] = 1;
			#endif
				
			// Mark as enemy dead																
			#ifdef ENABLE_PURSUERS
				if (gpt != 7) _en_t |= 128;
			#else
				_en_t |= 128;
			#endif

			// Count kills								
			#ifdef BODY_COUNT_ON								
				flags [BODY_COUNT_ON] ++;
			#else
				p_killed ++;
			#endif

			// Special for pursuers...	
			#ifdef ENABLE_PURSUERS
				en_an_alive [enit] = 0;
				en_an_dead_row [enit] = DEATH_COUNT_EXPRESSION;
			#endif

			enemy_was_killed = 1;
		}
		#if ENEMS_LIFE_GAUGE > 1 || FANTIES_LIFE_GAUGE > 1
			else {
				_en_mx = -_en_mx;
				_en_my = -_en_my;
			}
		#endif

	#else

		// Trajectory modification?
		#ifdef ENABLE_FANTIES
			if (gpt == 2) {
				en_an_vx [enit] =- en_an_vx [enit];
			}
		#endif

		#ifdef ENABLE_PATROLLERS
			_en_mx = -_en_mx;
			_en_my = -_en_my;
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
