#ifdef ACTIVATE_SCRIPTING
#ifdef CLEAR_FLAGS
		msc_init_all ();
#endif
#endif

#ifdef COMPRESSED_LEVELS
		mlplaying = 1;
		silent_level = 0;
		level = 0;

#ifndef REFILL_ME
		p_life = PLAYER_LIFE;

#endif
#endif

#ifndef DIRECT_TO_PLAY
		// Clear screen and show game frame
		cortina ();
		sp_UpdateNow();
#ifdef MODE_128K
		// Resource 1 = marco.bin
		get_resource (1, 16384);
#else
		unpack ((unsigned int) (s_marco), 16384);
#endif
#endif

#ifdef ACTIVATE_SCRIPTING
		script_result = 0;
#endif

#ifdef DIE_AND_RESPAWN
		p_killme = 0;
#endif

/*
// CUSTOM {
		// This runs the special script "level" called INIT_GAME
		main_script_offset = SCRIPT_INIT + INIT_GAME;
		run_script (MAP_W * MAP_H * 2);
// } END_OF_CUSTOM
*/
