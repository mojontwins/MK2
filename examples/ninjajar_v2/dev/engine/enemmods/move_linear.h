// linear movement

active = animate = 1;
_en_x += _en_mx;
_en_y += _en_my;				
	
#ifdef WALLS_STOP_ENEMIES
	if (_en_x == _en_x1 || _en_x == _en_x2 || mons_col_sc_x ())	_en_mx = -_en_mx;
	if (_en_y == _en_y1 || _en_y == _en_y2 || mons_col_sc_y ())	_en_my = -_en_my;
#else
	if (_en_x == _en_x1 || _en_x == _en_x2)	_en_mx = -_en_mx;
	if (_en_y == _en_y1 || _en_y == _en_y2)	_en_my = -_en_my;
#endif

#ifdef ENABLE_SHOOTERS
	// Shoot a coco
	if (enemy_shoots && (rand () & SHOOTER_SHOOT_FREQ) == 1) shoot_coco ();
#endif
