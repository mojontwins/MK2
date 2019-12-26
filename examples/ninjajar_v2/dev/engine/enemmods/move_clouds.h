	// Move Clouds

	#asm
			ld 	a, 1
			ld  (_active), a
			ld  (_animate), a
	#endasm

	if (gpx != _en_x) {
		_en_x += addsign (gpx - _en_x, _en_mx);
	}

	// Shoot a coco
	if ((rand () & CLOUDS_SHOOT_FREQ) == 1) {
		cocos_shoot ();
	}
