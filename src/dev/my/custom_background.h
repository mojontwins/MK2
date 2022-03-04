// custom_background.h
// This data & code is used to substitute tile 0 when rendering the screen.
// Use this as an example.

void custom_bg (void) {
	// Changes gpd on the fly.

	// Un bonito fondo de cielo aleatorio.
	// En la lina 5 esta la linea de nubes.
	// 42: blanco, 43-45: nubes, 46: azul
	if (0 == gpd) {
		if (_y < (5*2+VIEWPORT_Y)) gpd = 46;
		else if (_y == (5*2+VIEWPORT_Y)) gpd = 42 + (rand () & 3);
		else gpd = 41;
	}
}