// MT Engine MK2 v0.90b
// Copyleft 2016 the Mojon Twins

// clevels.h
// Compressed levels loading

#ifdef MODE_128K
#ifdef EXTENDED_LEVELS
unsigned char level_ac;
void prepare_level (void) {
#ifdef LEVEL_SEQUENCE
	level_ac = level_sequence [level];
#else
	level_ac = level;
#endif

	get_resource (levels [level_ac].map_res, (unsigned int) (map));
#ifndef DEACTIVATE_KEYS
	get_resource (levels [level_ac].bolts_res, (unsigned int) (bolts));
#endif
	get_resource (levels [level_ac].ts_res, (unsigned int) (tileset + 512));
	get_resource (levels [level_ac].ss_res, (unsigned int) (spriteset));
	get_resource (levels [level_ac].enems_res, (unsigned int) (baddies));
#ifndef DISABLE_HOTSPOTS
	get_resource (levels [level_ac].hotspots_res, (unsigned int) (hotspots));
#endif
	get_resource (levels [level_ac].behs_res, (unsigned int) (behs));

	if (script_result != 3) {
		n_pant = levels [level_ac].scr_ini;
#ifdef PHANTOMAS_ENGINE
		p_x = levels [level_ac].ini_x << 4;
		p_y = levels [level_ac].ini_y << 4;
#else			
		p_x = levels [level_ac].ini_x << 10;
		p_y = levels [level_ac].ini_y << 10;
#endif		
		p_facing = levels [level_ac].facing;
	}

	level_data->map_w = levels [level_ac].map_w;
	level_data->map_h = levels [level_ac].map_h;
	level_data->max_objs = levels [level_ac].max_objs;
	level_data->enems_life = levels [level_ac].enems_life;
	level_data->win_condition = levels [level_ac].win_condition;
	level_data->scr_fin = levels [level_ac].scr_fin;
	level_data->activate_scripting = levels [level_ac].activate_scripting;
	level_data->music_id = levels [level_ac].music_id;

	p_engine = levels [level_ac].switchable_engine_type;
	do_gravity = !(p_engine == SENG_SWIM);

	main_script_offset = levels [level_ac].script_offset;
}
#else
void prepare_level (void) {
	get_resource (levels [level].resource, (unsigned int) (level_data));
#ifdef MAP_ATTRIBUTES
	cur_map_attr = 99; 	// Force load of subts just in case.
#endif	
	n_pant = level_data.scr_ini;
#ifdef PHANTOMAS_ENGINE
	p_x = level_data->ini_x << 4;
	p_y = level_data->ini_y << 4;
#else	
	p_x = level_data->ini_x << 10;
	p_y = level_data->ini_y << 10;
#endif	
	
	main_script_offset = levels [level].script_offset;

}
#endif
#else
void prepare_level (void) {
	unpack ((unsigned int) levelset [level].leveldata_c, MAP_DATA);
	unpack ((unsigned int) levelset [level].tileset_c, (unsigned int) (tileset));
	unpack ((unsigned int) levelset [level].spriteset_c, (unsigned int) (sprite_1_a - 16));
	n_pant = levelset [level].ini_pant;
	p_x = levelset [level].ini_x << 10;
	p_y = levelset [level].ini_y << 10;
	n_bolts = *((unsigned char *) (NBOLTS_PEEK));
	win_condition = levelset [level].win_condition;
}
#endif
