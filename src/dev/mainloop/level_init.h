	#if defined (ENEMY_BACKUP) && defined (COMPRESSED_LEVELS)
		backup_baddies ();
	#endif

	playing = 1;

	#ifdef ENABLE_SIM
		sim_init ();
	#endif

	#ifndef COMPRESSED_LEVELS
		#ifndef DISABLE_HOTSPOTS
			init_hotspots ();
		#endif

		#ifdef ACTIVATE_SCRIPTING
			#ifdef MODE_128K
				main_script_offset = (unsigned int) (SCRIPT_INIT);
			#else
				main_script_offset = (unsigned int) (main_script);
			#endif		
		#endif
		#ifndef DEACTIVATE_KEYS
			init_bolts ();
		#endif
		#ifdef RESTORE_ON_INIT
			restore_baddies ();
		#endif
		#if defined (PLAYER_KILLS_ENEMIES) || defined (PLAYER_CAN_FIRE)
			init_baddies ();
		#endif
	#endif

	#ifdef PLAYER_CAN_FIRE
		init_bullets ();
	#endif

	#ifdef ENABLE_SHOOTERS
		init_cocos ();
	#endif

	#ifndef COMPRESSED_LEVELS
		n_pant = SCR_INI;
	#endif

	player_init ();
	maincounter = 0;

	#ifdef ACTIVATE_SCRIPTING
		script_result = 0;
		#ifdef CLEAR_FLAGS
			msc_init_all ();
		#endif

		#ifdef EXTENDED_LEVELS
			if (level_data.activate_scripting)
		#endif
		{
			// Entering game script
			run_script (MAP_W * MAP_H * 2);
		}
	#endif
	#ifdef ENABLE_LAVA
		init_lava ();
	#endif

	do_respawn = 1;

	#ifdef PLAYER_KILLS_ENEMIES
		#ifdef SHOW_TOTAL
			// Show total of enemies next to the killed amount.

			//sp_PrintAtInv (KILLED_Y, 2 + KILLED_X, 71, 15);
			//sp_PrintAtInv (KILLED_Y, 3 + KILLED_X, 71, 16 + BADDIES_COUNT / 10);
			//sp_PrintAtInv (KILLED_Y, 4 + KILLED_X, 71, 16 + BADDIES_COUNT % 10);
			rda = 16 + (BADDIES_COUNT / 10); rdb = 16 + (BADDIES_COUNT % 10);
			#asm
				ld  a, KILLED_Y
				ld  c, KILLED_X + 2
				ld  d, 71
				ld  e, 15
				call SPPrintAtInv

				ld  a, (_rda)
				ld  e, a
				ld  a, KILLED_Y
				ld  c, KILLED_X + 3
				ld  d, 71				
				call SPPrintAtInv
				
				ld  a, (_rdb)
				ld  e, a
				ld  a, KILLED_Y
				ld  c, KILLED_X + 4
				ld  d, 71				
				call SPPrintAtInv
			#endasm
		#endif
	#endif

	objs_old = keys_old = life_old = killed_old = 0xff;

	#ifdef MAX_AMMO
		ammo_old = 0xff;
	#endif
	#if defined (TIMER_ENABLE) && defined (PLAYER_SHOW_TIMER)
		timer_old = 0;
	#endif
	#ifdef PLAYER_SHOW_FLAG
		flag_old = 99;
	#endif
	#if defined (PLAYER_HAS_JETPAC) && defined (JETPAC_DEPLETES) && defined (PLAYER_SHOW_FUEL)
		fuel_old = 99;
	#endif
	#if defined (ENABLE_KILL_SLOWLY) && defined (PLAYER_SHOW_KILL_SLOWLY_GAUGE)
		ks_gauge_old = 99;
	#endif
	success = 0;

	#if defined (BREAKABLE_WALLS) || defined (BREAKABLE_WALLS_SIMPLE)
		#ifdef BREAKABLE_ANIM
				do_process_breakable = 0;
				gen_pt = breaking_f;
				for (gpit = 0; gpit < MAX_BREAKABLE; gpit ++) *gen_pt ++ = 0;
		#endif
	#endif

	#ifdef MODE_128K
		// Play music
		#if !defined (HANNA_LEVEL_MANAGER) && !defined (SIMPLE_LEVEL_MANAGER)
			#ifdef COMPRESSED_LEVELS
				#ifdef EXTENDED_LEVELS
					_AY_PL_MUS (level_data.music_id);
				#else
					_AY_PL_MUS (levels [level].music_id);
				#endif		
			#else
				//_AY_PL_MUS (0);
			#endif
		#endif
	#endif
	o_pant = 0xff;

	#if defined (MSC_MAXITEMS) || defined (ENABLE_SIM)
		display_items ();
	#endif

	no_draw = 0;

	#ifdef CUSTOM_HIT
		was_hit_by_type = 0xff;
	#endif
