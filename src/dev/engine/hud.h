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
		_x = LIFE_X; _y = LIFE_Y; _t = p_life; print_number2 ();
		life_old = p_life;
	}

#ifndef DEACTIVATE_KEYS
	if (p_keys != keys_old) {
		_x = KEYS_X; _y = KEYS_Y; _t = p_keys; print_number2 ();
		keys_old = p_keys;
	}
#endif

#if defined (PLAYER_KILLS_ENEMIES) || defined (PLAYER_CAN_FIRE)
#ifdef PLAYER_SHOW_KILLS
#ifdef BODY_COUNT_ON
	if (flags [BODY_COUNT_ON] != killed_old) {
		_x = KILLED_X; _y = KILLED_Y; _t = flags [BODY_COUNT_ON]; print_number2 ();
		killed_old = flags [BODY_COUNT_ON];
	}
#else
	if (p_killed != killed_old) {
		_x = KILLED_X; _y = KILLED_Y; _t = p_killed; print_number2 ();
		killed_old = p_killed;
	}
#endif
#endif
#endif

#ifdef MAX_AMMO
	if (p_ammo != ammo_old) {
		_x = AMMO_X; _y = AMMO_Y; _t = p_ammo; print_number2 ();
		ammo_old = p_ammo;
	}
#endif

#if defined (TIMER_ENABLE) && defined (PLAYER_SHOW_TIMER)
	if (ctimer.t != timer_old) {
		_x = TIMER_X; _y = TIMER_Y; _t = ctimer.t; print_number2 ();
		timer_old = ctimer.t;
	}
#endif

#ifdef PLAYER_SHOW_FLAG
	if (flags [PLAYER_SHOW_FLAG] != flag_old) {
		_x = FLAG_X; _y = FLAG_Y; _t = flags [PLAYER_SHOW_FLAG]; print_number2 ();
		flag_old = flags [PLAYER_SHOW_FLAG];
	}
#endif

#if defined (PLAYER_HAS_JETPAC) && defined (JETPAC_DEPLETES) && defined (PLAYER_SHOW_FUEL)
	if (p_fuel != fuel_old) {
		_x = FUEL_X; _y = FUEL_Y; _t = p_fuel; print_number2 ();
		fuel_old = p_fuel;
	}
#endif

#if defined (ENABLE_KILL_SLOWLY) && defined (PLAYER_SHOW_KILL_SLOWLY_GAUGE)
	if (p_ks_gauge != ks_gauge_old) {
		_x = KILL_SLOWLY_GAUGE_X; _y = KILL_SLOWLY_GAUGE_Y; _t = p_ks_gauge; print_number2 ();
		ks_gauge_old = p_ks_gauge;
	}
#endif	

}

