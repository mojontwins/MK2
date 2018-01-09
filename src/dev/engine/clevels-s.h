// MT Engine MK2 v0.90b
// Copyleft 2016 the Mojon Twins

// clevels.h
// Compressed levels loading (use with simplelevels.h)

void prepare_level (void) {
	get_resource (levels [level_ac].map_res, (unsigned int) (map));
	get_resource (levels [level_ac].enems_res, (unsigned int) (baddies));
#ifndef DISABLE_HOTSPOTS
	get_resource (levels [level_ac].hotspots_res, (unsigned int) (hotspots));
#endif
	get_resource (levels [level_ac].behs_res, (unsigned int) (behs));
}
