// MT Engine MK2 v0.90b
// Copyleft 2016 the Mojon Twins

// initplayer.h
// Player initialization

void init_player (void) {
	// Inicializa player con los valores iniciales
	// (de ahí lo de inicializar).

#ifndef COMPRESSED_LEVELS
#if defined (PHANTOMAS_ENGINE) || defined (HANNA_ENGINE)
	p_x = PLAYER_INI_X << 4;
	p_y = PLAYER_INI_Y << 4;;
#else
	p_x = PLAYER_INI_X << 10;
	p_y = PLAYER_INI_Y << 10;
#endif
#endif
#if defined (PLAYER_GENITAL) && defined (PLAYER_HAS_JUMP)
	p_z = p_vz = 0;
	p_jmp_facing = 0;
#endif
#ifdef HANNA_ENGINE
	p_v = HANNA_WALK;
#endif
	p_vy = 0;
	p_vx = 0;
#ifdef PLAYER_HAS_JUMP
	p_jmp_ct = 1;
	p_jmp_on = 0;
#endif
	p_frame = 0;
	p_subframe = 0;
#ifndef EXTENDED_LEVELS
#ifdef PLAYER_GENITAL
	p_facing = FACING_DOWN;
#elif defined (PHANTOMAS_ENGINE)
	p_facing = 4;
#elif defined (HANNA_ENGINE)
	p_facing = 6;
#else
	p_facing = 1;
#endif
#endif
	p_facing_v = p_facing_h = 0xff;
	p_state = EST_NORMAL;
	p_state_ct = 0;
#if !defined (COMPRESSED_LEVELS) || defined (REFILL_ME)
	p_life = PLAYER_LIFE;
#endif
	p_objs = 0;
	p_keys = 0;
#ifdef BODY_COUNT_ON
	flags [BODY_COUNT_ON] = 0;
#else	
	p_killed = 0;
#endif	
	p_disparando = 0;
#ifdef MAX_AMMO
#ifdef INITIAL_AMMO
	p_ammo = INITIAL_AMMO;
#else
	p_ammo = MAX_AMMO;
#endif
#endif
#if defined (PLAYER_CAN_PUNCH) || defined (PLAYER_HAZ_SWORD)
	p_hitting = 0;
	hitter_on = 0;
#endif
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
#ifdef PLAYER_VARIABLE_JUMP
	PLAYER_JMP_VY_MAX = PLAYER_JMP_VY_MAX;
#endif
#ifdef JETPAC_DEPLETES
	p_fuel = JETPAC_FUEL_INITIAL;
#endif
#ifdef ENABLE_KILL_SLOWLY
	p_ks_gauge = p_ks_fc = 0;
#endif
}
