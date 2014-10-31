// inits.h
// Initialization functions

#ifndef COMPRESSED_LEVELS
#ifndef DEACTIVATE_KEYS
void init_cerrojos (void) {
	// Activa todos los cerrojos	
	for (gpit = 0; gpit < MAX_CERROJOS; gpit ++)
		cerrojos [gpit].st = 1;	
}
#endif
#endif

#ifdef PLAYER_CAN_FIRE
void init_bullets (void) {
	// Inicializa las balas
	gpit = 0;
	while (gpit < MAX_BULLETS) {
		bullets [gpit ++].estado = 0;
	}
}
#endif

#ifndef COMPRESSED_LEVELS
#if defined(PLAYER_KILLS_ENEMIES) || defined (PLAYER_CAN_FIRE)
void init_malotes (void) {
	gpit = 0;
	while (gpit < MAP_W * MAP_H * 3) {
		malotes [gpit].t = malotes [gpit].t & 15;	
#ifdef PLAYER_CAN_FIRE
		malotes [gpit].life = ENEMIES_LIFE_GAUGE;
#ifdef ENABLE_RANDOM_RESPAWN
		if (malotes [gpit].t == 5)
			malotes [gpit].t |= 16;
#endif
#endif
		gpit ++;
	}
}
#endif
#endif

#ifndef COMPRESSED_LEVELS
void init_hotspots (void) {
	gpit = 0;
	while (gpit < MAP_W * MAP_H) {
		hotspots [gpit ++].act = 1;
	}
}
#endif
