// Collide with thrownable

if (fo_fly && killable) {
	if (f_o_xp + 15 >= _en_x && f_o_xp <= _en_x + 15 &&
		f_o_yp + 15 >= _en_y && f_o_yp <= _en_y + 15) {
		en_an_n_f [enit] = sprite_17_a;
		en_an_state [enit] = GENERAL_DYING;
		en_an_count [enit] = 8;
		#ifdef CARRIABLE_BOXES_COUNT_KILLS
			flags [CARRIABLE_BOXES_COUNT_KILLS] ++;
		#endif
		_en_t |= 128;
		#ifdef BODY_COUNT_ON
			flags [BODY_COUNT_ON] ++;
		#else					
			p_killed ++;
		#endif					
		#ifdef MODE_128K
		#else
			sp_UpdateNow ();
			beep_fx (SFX_EXPLOSION);
		#endif

		#ifdef ACTIVATE_SCRIPTING
			#ifdef RUN_SCRIPT_ON_KILL
				run_script (2 * MAP_W * MAP_H + 5);
			#endif
		#endif
		goto enems_loop_continue;
	}
}
