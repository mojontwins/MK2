			// Let's move this somewhere else...
/*
			for (gpit = 0; gpit < 3; gpit ++) {
				enoffsmasi = enoffs + gpit;

#if defined (ENABLE_CUSTOM_FANTIES)
				if (
					(baddies [enoffsmasi].t & 0x78) == 16
				) {
					gpen_x = en_an_x [gpit] >> 6;
					gpen_y = en_an_y [gpit] >> 6;
				} else {
#endif
					gpen_x = baddies [enoffsmasi].x;
					gpen_y = baddies [enoffsmasi].y;
#if defined (ENABLE_CUSTOM_FANTIES)
				}
#endif

#ifdef PIXEL_SHIFT
				if ((baddies [enoffsmasi].t & 0x78) == 8) gpen_y -= PIXEL_SHIFT;
#endif				
				sp_MoveSprAbs (sp_moviles [gpit], spritesClip, en_an_n_f [gpit] - en_an_c_f [gpit], VIEWPORT_Y + (gpen_y >> 3), VIEWPORT_X + (gpen_x >> 3),gpen_x & 7, gpen_y & 7);
				en_an_c_f [gpit] = en_an_n_f [gpit];
			}
*/

#if defined (PLAYER_GENITAL) && defined (PLAYER_HAS_JUMP)	
			if (0 == p_killme && ( !(p_state & EST_PARP) || half_life == 0) ) {
				sp_MoveSprAbs (sp_shadow, spritesClip, 0, VIEWPORT_Y + (gpy >> 3) + 1, VIEWPORT_X + (gpx >> 3), gpx & 7, gpy & 7);
				gpz = gpy - ((-p_z) >> 6);
				sp_MoveSprAbs (sp_player, spritesClip, p_n_f - p_c_f, VIEWPORT_Y + (gpz >> 3), VIEWPORT_X + (gpx >> 3), gpx & 7, gpz & 7);
			} else {
				sp_MoveSprAbs (sp_shadow, spritesClip, 0, -2, -2, 0, 0);
				sp_MoveSprAbs (sp_player, spritesClip, p_n_f - p_c_f, -2, -2, 0, 0);
			}
#else
#ifdef DIE_AND_RESPAWN
			if (0 == p_killme && ( !(p_state & EST_PARP) || half_life == 0) ) 
#else
			if (!(p_state & EST_PARP) || half_life == 0)				
#endif				
			{
				sp_MoveSprAbs (sp_player, spritesClip, p_n_f - p_c_f, VIEWPORT_Y + (gpy >> 3), VIEWPORT_X + (gpx >> 3), gpx & 7, gpy & 7);
			} else {
				sp_MoveSprAbs (sp_player, spritesClip, p_n_f - p_c_f, -2, -2, 0, 0);
			}
#endif
			p_c_f = p_n_f;


#ifdef PLAYER_CAN_FIRE
			for (gpit = 0; gpit < MAX_BULLETS; gpit ++) {
				if (bullets_estado [gpit] == 1) {
					sp_MoveSprAbs (sp_bullets [gpit], spritesClip, 0, VIEWPORT_Y + (bullets_y [gpit] >> 3), VIEWPORT_X + (bullets_x [gpit] >> 3), bullets_x [gpit] & 7, bullets_y [gpit] & 7);
				} else {
					sp_MoveSprAbs (sp_bullets [gpit], spritesClip, 0, -2, -2, 0, 0);
				}
			}
#endif

#ifdef ENABLE_SHOOTERS
			for (gpit = 0; gpit < MAX_COCOS; gpit ++) {
				if (coco_s [gpit] == 1) {
					sp_MoveSprAbs (sp_cocos [gpit], spritesClip, 0, VIEWPORT_Y + (coco_y [gpit] >> 3), VIEWPORT_X + (coco_x [gpit] >> 3), coco_x [gpit] & 7, coco_y [gpit] & 7);
				} else {
					sp_MoveSprAbs (sp_cocos [gpit], spritesClip, 0, -2, -2, 0, 0);
				}
			}
#endif

