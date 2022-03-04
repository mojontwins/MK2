	// Move Clouds

	active = 1;
	if (gpx != _en_x) {
		_en_x += addsign (gpx - _en_x, _en_mx);
	}

	// Shoot a coco
	if ((rand () & CLOUDS_SHOOT_FREQ) == 1) {
		shoot_coco ();
	}
