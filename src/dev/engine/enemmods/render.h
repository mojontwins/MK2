#ifdef PIXEL_SHIFT
				if ((baddies [enoffsmasi].t & 0x78) == 8) gpen_y -= PIXEL_SHIFT;
#endif				
				sp_MoveSprAbs (sp_moviles [gpit], spritesClip, en_an_n_f [gpit] - en_an_c_f [gpit], VIEWPORT_Y + (gpen_cy >> 3), VIEWPORT_X + (gpen_cx >> 3),gpen_cx & 7, gpen_cy & 7);
				en_an_c_f [gpit] = en_an_n_f [gpit];
