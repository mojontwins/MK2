	// Conveyors
#ifdef ENABLE_CONVEYORS	
	#include "engine/playermods/ha_conveyors.h"
#endif
	
	// Controller
	#include "engine/playermods/ha_controller.h"

	// Move
	p_x = p_x + p_vx;
#if !defined (DISABLE_PLATFORMS) || defined (ENABLE_CONVEYORS)
	if (p_gotten) p_x += ptgmx;
#endif

	// Safe
	if (p_x < 0) p_x = 0;
	if (p_x > 14336) p_x = 14336;

	// Handle collision
#ifdef PLAYER_NEW_GENITAL
	// "New genital" top-down games need slightly different vertical collision
	#include "engine/playermods/ha_collision_25d.h"
#else
	#include "engine/playermods/ha_collision.h"
#endif
