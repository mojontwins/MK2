// MT Engine MK2 v0.90b
// Copyleft 2016 the Mojon Twins

// hud.h
// Heads-up display (shows your life, keys, etc...)

unsigned char objs_old, keys_old, life_old, killed_old;

#ifdef MAX_AMMO
unsigned char ammo_old;
#endif

#if defined (TIMER_ENABLE) && defined (PLAYER_SHOW_TIMER)
unsigned char timer_old;
#endif

#ifdef PLAYER_SHOW_FLAG
unsigned char flag_old;
#endif

#if defined (PLAYER_HAS_JETPAC) && defined (JETPAC_DEPLETES) && defined (PLAYER_SHOW_FUEL)
unsigned char fuel_old;
#endif

#if defined (ENABLE_KILL_SLOWLY) && defined (PLAYER_SHOW_KILL_SLOWLY_GAUGE)
unsigned char ks_gauge_old;
#endif

void update_hud (void) {
#ifndef DEACTIVATE_OBJECTS
	if (p_objs != objs_old) {
		draw_objs ();
		objs_old = p_objs;
	}
#endif

	if (p_life != life_old) {
		print_number2 (LIFE_X, LIFE_Y, p_life);
		life_old = p_life;
	}

#ifndef DEACTIVATE_KEYS
	if (p_keys != keys_old) {
		print_number2 (KEYS_X, KEYS_Y, p_keys);
		keys_old = p_keys;
	}
#endif

#if defined (PLAYER_KILLS_ENEMIES) || defined (PLAYER_CAN_FIRE)
#ifdef PLAYER_SHOW_KILLS
#ifdef BODY_COUNT_ON
	if (flags [BODY_COUNT_ON] != killed_old) {
		print_number2 (KILLED_X, KILLED_Y, flags [BODY_COUNT_ON]);
		killed_old = flags [BODY_COUNT_ON];
	}
#else
	if (p_killed != killed_old) {
		print_number2 (KILLED_X, KILLED_Y, p_killed);
		killed_old = p_killed;
	}
#endif
#endif
#endif

#ifdef MAX_AMMO
	if (p_ammo != ammo_old) {
		print_number2 (AMMO_X, AMMO_Y, p_ammo);
		ammo_old = p_ammo;
	}
#endif

#if defined (TIMER_ENABLE) && defined (PLAYER_SHOW_TIMER)
	if (ctimer.t != timer_old) {
		print_number2 (TIMER_X, TIMER_Y, ctimer.t);
		timer_old = ctimer.t;
	}
#endif

#ifdef PLAYER_SHOW_FLAG
	if (flags [PLAYER_SHOW_FLAG] != flag_old) {
		print_number2 (FLAG_X, FLAG_Y, flags [PLAYER_SHOW_FLAG]);
		flag_old = flags [PLAYER_SHOW_FLAG];
	}
#endif

#if defined (PLAYER_HAS_JETPAC) && defined (JETPAC_DEPLETES) && defined (PLAYER_SHOW_FUEL)
	if (p_fuel != fuel_old) {
		print_number2 (FUEL_X, FUEL_Y, p_fuel);
		fuel_old = p_fuel;
	}
#endif

#if defined (ENABLE_KILL_SLOWLY) && defined (PLAYER_SHOW_KILL_SLOWLY_GAUGE)
	if (p_ks_gauge != ks_gauge_old) {
		print_number2 (KILL_SLOWLY_GAUGE_X, KILL_SLOWLY_GAUGE_Y, p_ks_gauge);
		ks_gauge_old = p_ks_gauge;
	}
#endif	

}

