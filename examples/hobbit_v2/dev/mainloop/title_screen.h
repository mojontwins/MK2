		sp_UpdateNow();

		//blackout ();
#ifdef MODE_128K
		// Resource 0 = title.bin
		get_resource (0, 16384);
#else
		unpack ((unsigned int) (s_title), 16384);
#endif

#ifdef MODE_128K
		_AY_PL_MUS (0);
#endif
		select_joyfunc ();
#ifdef MODE_128K
		_AY_ST_ALL ();
#endif
		