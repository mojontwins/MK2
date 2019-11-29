// CUSTOM {
/*
			en_an_count [gpit] ++;
#ifdef ENABLE_FANTIES
			if (gpt != 2) {
#endif
				if (en_an_count [gpit] == 4) {
					en_an_count [gpit] = 0;
					en_an_frame [gpit] = !en_an_frame [gpit];
					en_an_n_f [gpit] = enem_frames [en_an_base_frame [gpit] + en_an_frame [gpit]];
				}
#ifdef ENABLE_FANTIES 
			} else {
				en_an_n_f [gpit] = enem_frames [en_an_base_frame [gpit] + (en_an_vx [gpit] > 0)];
			}
#endif
*/

			// Ramiro is way more simple...
			gpjt = baddies [enoffsmasi].mx ? ((gpen_cx + 4) >> 3) & 1 : ((gpen_cy + 4) >> 3) & 1;
			en_an_n_f [gpit] = enem_frames [en_an_base_frame [gpit] + gpjt];
// } END_OF_CUSTOM
