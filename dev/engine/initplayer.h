// initp_h
// Player initialization

void init_player (void) {
	// Inicializa player con los valores iniciales
	// (de ahí lo de inicializar).

#ifndef COMPRESSED_LEVELS
	p_x = PLAYER_INI_X << 10;
	p_y = PLAYER_INI_Y << 10;
#endif
	p_vy = 0;
	p_vx = 0;
	p_cont_salto = 1;
	p_saltando = 0;
	p_frame = 0;
	p_subframe = 0;
#ifndef EXTENDED_LEVELS
#ifdef PLAYER_MOGGY_STYLE
	p_facing = FACING_DOWN;
#else
	p_facing = 1;
#endif
#endif
	p_facing_v = p_facing_h = 0xff;
	p_estado = EST_NORMAL;
	p_ct_estado = 0;
#if !defined(COMPRESSED_LEVELS) || defined(REFILL_ME)
	p_life = PLAYER_LIFE;
#endif
	p_objs = 0;
	p_keys = 0;
	p_killed = 0;
	p_disparando = 0;
#ifdef MAX_AMMO
#ifdef INITIAL_AMMO
	p_ammo = INITIAL_AMMO
#else
	p_ammo = MAX_AMMO;
#endif
#endif
#if defined(PLAYER_CAN_PUNCH) || defined(PLAYER_CAN_SWORD)
	p_hitting = 0;
	hitter_on = 0;
#endif
	pant_final = SCR_FIN;
#ifdef TIMER_ENABLE
	ctimer.count = 0;
	ctimer.zero = 0;
#ifdef TIMER_LAPSE
	ctimer.frames = TIMER_LAPSE;
#endif
#ifdef TIMER_INITIAL
	ctimer.t = TIMER_INITIAL;
#endif
#ifdef TIMER_START
	ctimer.on = 1;
#else
	ctimer.on = 0;
#endif
#endif
#ifdef DIE_AND_RESPAWN
	p_killme = 0;
	p_safe_pant = n_pant;
	p_safe_x = p_x >> 10;
	p_safe_y = p_y >> 10;
#endif
#if defined (BREAKABLE_WALLS) || defined (BREAKABLE_WALLS_SIMPLE)
#ifdef BREAKABLE_ANIM
	breaking_idx = 0;	
#endif	
#endif
}
