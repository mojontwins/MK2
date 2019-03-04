
#ifdef PLAYER_GENITAL
	#include "engine/playermods/va_genital.h"
#endif

	// Gravity
#if defined (PLAYER_HAS_JUMP) || defined (PLAYER_HAS_JETPAC) || defined (PLAYER_BOOTEE) || defined (PLAYER_CUMULATIVE_JUMP)
	#include "engine/playermods/va_gravity.h"
#endif

	// Jetpac boost
#ifdef PLAYER_HAS_JETPAC
	#include "engine/playermods/va_jetpac.h"
#endif

	// Swimming vertical thrust
#ifdef PLAYER_HAS_SWIM
	#include "engine/playermods/va_swimming.h"
#endif
	
	// Move
	p_y += p_vy;
#if defined (PLAYER_GENITAL) && (!defined (DISABLE_PLATFORMS) || defined (ENABLE_CONVEYORS))
	if (p_gotten) p_y += ptgmy;
#endif

#if defined (PLAYER_GENITAL) && defined (PLAYER_HAS_JUMP)
	p_z += p_vz;
	if (p_z > 0) {
		p_z = 0;
		p_vz = 0;
	}
#endif

	// Safe
	if (p_y < 0) p_y = 0;
	if (p_y > 9216) p_y = 9216;

	// Handle collision
#ifdef PLAYER_NEW_GENITAL
	// "New genital" top-down games need slightly different vertical collision
	#include "engine/playermods/va_collision_25d.h"
#else
	#include "engine/playermods/va_collision.h"
#endif
	
	// Possee - player is on solid floor.
#if !defined(PLAYER_GENITAL) || defined (PLAYER_HAS_JUMP)
	#include "engine/playermods/possee.h"
#endif	

	// Jumping Jack!
#ifdef PLAYER_HAS_JUMP
#ifdef PLAYER_GENITAL
	#include "engine/playermods/jump_genital.h"
#else
	#include "engine/playermods/jump_sideview.h"
#endif
#endif
