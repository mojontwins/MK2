// MT Engine MK2 v0.90b
// Copyleft 2016 the Mojon Twins

// flickscreen.h
// Flicking screen logic... REHASH!

#ifdef ENABLE_CUSTOM_CONNECTIONS
	#define SCREEN_LEFT custom_connections [n_pant].left;
	#define SCREEN_RIGHT custom_connections [n_pant].right;
	#define SCREEN_UP custom_connections [n_pant].up;
	#define SCREEN_DOWN custom_connections [n_pant].down;
#elif defined (PLAYER_CYCLIC_MAP)
	#if defined (MDOE_128K) && defined (COMPRESSED_LEVELS)
		#define SCREEN_LEFT x_pant > 0 ? n_pant - 1 : n_pant + (level_data->map_w - 1);
		#define SCREEN_RIGHT x_pant < (level_data->map_w - 1) ? n_pant + 1 : n_pant - (level_data->map_w - 1);
		#define SCREEN_UP y_pant > 0 ? n_pant - level_data->map_w : n_pant + (level_data->map_w * (level_data->map_h - 1));
		#define SCREEN_DOWN y_pant < (level_data->map_h - 1) ? n_pant + level_data->map_w : n_pant - (level_data->map_w * (level_data->map_h - 1));
	#else
		#define SCREEN_LEFT x_pant > 0 ? n_pant - 1 : n_pant + (MAP_W - 1);
		#define SCREEN_RIGHT x_pant < (MAP_W - 1) ? n_pant + 1 : n_pant - (MAP_W - 1);
		#define SCREEN_UP y_pant > 0 ? n_pant - MAP_W : n_pant + (MAP_W * (MAP_H - 1));
		#define SCREEN_DOWN y_pant < (MAP_H - 1) ? n_pant + MAP_W : n_pant - (MAP_W * (MAP_H - 1));
	#endif
#else
	#define SCREEN_LEFT	n_pant - 1
	#define SCREEN_RIGHT n_pant + 1
	#if defined (MODE_128K) && defined (COMPRESSED_LEVELS)
		#define SCREEN_UP n_pant - level_data->map_w
		#define SCREEN_DOWN n_pant + level_data->map_w
	#else
		#define SCREEN_UP n_pant - MAP_W
		#define SCREEN_DOWN n_pant + MAP_W
	#endif
#endif

#ifdef PLAYER_CHECK_MAP_BOUNDARIES
	#define MAP_BOUNDARY_LEFT && x_pant > 0
	#define MAP_BOUNDARY_TOP && y_pant > 0
	#if defined (MODE_128K) && defined (COMPRESSED_LEVELS)
		#define MAP_BOUNDARY_RIGHT && (x_pant < (level_data->map_w - 1))
		#define MAP_BOUNDARY_BOTTOM && (y_pant < (level_data->map_h - 1))
	#else
		#define MAP_BOUNDARY_RIGHT && (x_pant < (MAP_W - 1))
		#define MAP_BOUNDARY_BOTTOM && (y_pant < (MAP_H - 1))
	#endif
#else
	#define MAP_BOUNDARY_LEFT
	#define MAP_BOUNDARY_RIGHT
	#define MAP_BOUNDARY_TOP
	#define MAP_BOUNDARY_BOTTOM
#endif

void flick_screen (void) {
#if defined (PHANTOMAS_ENGINE) || defined (HANNA_ENGINE)	
	gpit = (joyfunc) (&keys);
#endif
	
#if defined (PHANTOMAS_ENGINE)
	// Phantomas engine edge screen detection
	if (p_x <= 0 && ((gpit & sp_LEFT) == 0 || (p_jmp_on && p_facing == 0)) MAP_BOUNDARY_LEFT) {
		n_pant = SCREEN_LEFT; p_x = 224;
	}
	if (p_x >= 224 && ((gpit & sp_RIGHT) == 0 || (p_jmp_on && p_facing)) MAP_BOUNDARY_RIGHT) {
		n_pant = SCREEN_RIGHT; p_x = 0;
	}
	if (p_y <= 0 && p_jmp_on MAP_BOUNDARY_TOP) {
		n_pant = SCREEN_UP; p_y = 144;
	}
	if (p_y >= 144 && (0 == p_jmp_on || p_jmp_ct >= (PHANTOMAS_JUMP_CTR >> 1)) MAP_BOUNDARY_BOTTOM) {
		n_pant = SCREEN_DOWN; p_y = 0;
	}
#elif defined (HANNA_ENGINE)
	// Hanna engine edge screen detection
	if (p_x <= 0 && (gpit & sp_LEFT) == 0 MAP_BOUNDARY_LEFT) {
		n_pant = SCREEN_LEFT; p_x = 224;
	}
	if (p_x >= 224 && (gpit & sp_RIGHT) == 0 MAP_BOUNDARY_RIGHT) {
		n_pant = SCREEN_RIGHT; p_x = 0;
	}
	if (p_y <= 0 && (gpit & sp_UP) == 0 MAP_BOUNDARY_TOP) {
		n_pant = SCREEN_UP; p_y = 144;
	}
	if (p_y >= 144 && (gpit & sp_DOWN) == 0 MAP_BOUNDARY_BOTTOM) {
		n_pant = SCREEN_DOWN; p_y = 0;
	}
#else
	// Momentum engine edge screen detection
	if (p_x == 0 && p_vx < 0 MAP_BOUNDARY_LEFT) {
		n_pant = SCREEN_LEFT; p_x = 14336;
	}
	if (p_x == 14336 && p_vx > 0 MAP_BOUNDARY_RIGHT) {
		n_pant = SCREEN_RIGHT; p_x = 0;
	}
	if (p_y == 0 && p_vy < 0 MAP_BOUNDARY_TOP) {
		n_pant = SCREEN_UP; p_y = 9216;
	}
	if (p_y == 9216 && p_vy > 0 MAP_BOUNDARY_BOTTOM) {
		n_pant = SCREEN_DOWN; p_y = 0;
		if (p_vy > 256) p_vy = 256;
	}
#endif	
}
