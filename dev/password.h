// password.h
// Simple password generator & checker for Ninjajar!
// Originally works with hex values. Modified for 
// obscurity and to save a couple of (needed) bytes

#define PASSWORD_LENGTH	8
#define MENU_Y 			20
#define MENU_X			11
#define MENU_COLOR		48

char *password_text = "XXXXXXXX ";
unsigned char pass_a, pass_b, pass_c, pass_d;
/*
char digit2hex (unsigned char v) {
	return v < 10 ? '0' + v : 'A' + (v - 10);
}

unsigned char hex2digit (char v) {
	return (v >= '0' && v <= '9') ? (char) (v - 48) : (v >= 'A' && v <= 'F') ? (char) (v - 55) : 0;
}
*/
unsigned char makebyte (char v1, char v2) {
	//return (unsigned char) ((hex2digit (v1) << 4) + (hex2digit (v2) & 15));
	return ((v1 - 'A') << 4) + ((v2 - 'A') & 15);
}

void addchar (unsigned char i1, unsigned char i2, unsigned char v) {
	//password_text [i1] = digit2hex (v >> 4);
	//password_text [i2] = digit2hex (v & 15);
	password_text [i1] = (v >> 4) + 'A';
	password_text [i2] = (v & 15) + 'A';
}

void gen_password (void) {
	addchar (7, 0, p_life);
	addchar (1, 6, level);
	addchar (5, 2, flags [1]);
	addchar (3, 4, (p_life << 2) + (level << 1) + flags [1]);
	password_text [PASSWORD_LENGTH] = 0;
}

void do_password (void) {	
	print_str (MENU_X, MENU_Y, MENU_COLOR, " PASSWORD ");	
	print_str (MENU_X, MENU_Y + 2, MENU_COLOR, "          ");
	password_text [PASSWORD_LENGTH] = ' ';
	gpit = PASSWORD_LENGTH; while (--gpit) password_text [gpit] = '.';
	sp_WaitForNoKey ();
	while (1) {
		password_text [gpit] = '+';
		print_str (16 - PASSWORD_LENGTH / 2, MENU_Y + 2, MENU_COLOR, password_text);
		sp_UpdateNow ();
		do {
			gpjt = sp_GetKey ();
		} while (!gpjt);
		if (gpjt == 12) {
			if (gpit > 0) {
				password_text [gpit] = gpit == PASSWORD_LENGTH ? ' ' : '.';
				gpit --;
			}
		} else if (gpjt == 13) {
			break;
		} else if (gpit < PASSWORD_LENGTH) {
			password_text [gpit] = (gpjt > 'Z') ? gpjt - 32 : gpjt;
			gpit ++;
		}
		wyz_play_sound (0);
		sp_WaitForNoKey ();
	}
	
	sp_WaitForNoKey ();
	wyz_stop_sound ();
	wyz_play_sound (1);
	password_text [PASSWORD_LENGTH] = ' ';
	
	// Check password...
	pass_a = makebyte (password_text [7], password_text [0]);
	pass_b = makebyte (password_text [1], password_text [6]);
	pass_c = makebyte (password_text [5], password_text [2]);
	pass_d = makebyte (password_text [3], password_text [4]);
	if (pass_d == ((pass_a << 2) + (pass_b << 1) + pass_c)) {
		p_life = pass_a;
		level = pass_b;
		flags [1] = pass_c;
	} 
}

void simple_menu (void) {
	p_life = PLAYER_LIFE;
	level = 0;
	flags [1] = 0;
	print_str (MENU_X - 6, MENU_Y, MENU_COLOR, "      1 PLAY          ");
	print_str (MENU_X - 6, MENU_Y + 1, MENU_COLOR, "                      ");
	print_str (MENU_X - 6, MENU_Y + 2, MENU_COLOR, "      2 PASSWORD      ");
	sp_UpdateNow ();
	while (1) {
		switch (sp_GetKey ()) {
			case '1':
				wyz_stop_sound ();
				wyz_play_sound (1);
				return;
			case '2':
				wyz_play_sound (0);
				do_password ();
				return;
		}
	}
}
