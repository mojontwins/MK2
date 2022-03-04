// MT MK2 ZX v1.0 
// Copyleft 2010-2015, 2019 by The Mojon Twins

// Title screen code. Replace this simple placeholder with something more fancy
// if you need that (i.e. passwords, etc)

sp_UpdateNow();

#ifdef MODE_128K
	get_resource (0, 16384); // Resource 0 = title.bin
#else
	unpack ((unsigned int) (s_title), 16384);
#endif

#ifdef MODE_128K
	_AY_PL_MUS (0);
#endif

select_joyfunc ();

#ifdef MODE_128K
	_AY_ST_ALL ();
#endif
