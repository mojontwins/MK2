// MT MK2 ZX v1.0 
// Copyleft 2010-2015, 2019 by The Mojon Twins

// New level screen.
// You can add here your own code. Just comment the original and add yours.

/*
if (!silent_level) {
	blackout_area ();
	
	_x = 12; _y = 12; _t = 71; gp_gen = (unsigned char *) ("LEVEL"); print_str ();
	_x = 18; _y = 12; _t = level + 1; print_number2 ();
	
	sp_UpdateNow ();

	#ifdef MODE_128K
		_AY_PL_SND (8);
	#endif

	active_sleep (250);
}
silent_level = 1;
*/

if (!silent_level) {
	blackout_area ();	
	_x = 5; _y = 5; _t = 71; gp_gen = (unsigned char *) ("GRACIAS ANDY Y NATHAN ;_"); print_str ();
	sp_UpdateNow ();
	active_sleep (150);

	blackout_area ();
	_x = 6; _y = 11; _t = 71; gp_gen = (unsigned char *) ("LA AVENTURA COMIENZA"); print_str ();
	sp_UpdateNow ();
	active_sleep (250);
} 
silent_level = 1;
