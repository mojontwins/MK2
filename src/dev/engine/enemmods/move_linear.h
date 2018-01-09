				// linear movement

				active = animate = 1;
				baddies [enoffsmasi].x += baddies [enoffsmasi].mx;
				baddies [enoffsmasi].y += baddies [enoffsmasi].my;
				gpen_cx = baddies [enoffsmasi].x;
				gpen_cy = baddies [enoffsmasi].y;
				gpen_xx = gpen_cx >> 4;
				gpen_yy = gpen_cy >> 4;
#ifdef WALLS_STOP_ENEMIES
				if (gpen_cx == baddies [enoffsmasi].x1 || gpen_cx == baddies [enoffsmasi].x2 || mons_col_sc_x ())
					baddies [enoffsmasi].mx = -baddies [enoffsmasi].mx;
				if (gpen_cy == baddies [enoffsmasi].y1 || gpen_cy == baddies [enoffsmasi].y2 || mons_col_sc_y ())
					baddies [enoffsmasi].my = -baddies [enoffsmasi].my;
#else
				if (gpen_cx == baddies [enoffsmasi].x1 || gpen_cx == baddies [enoffsmasi].x2)
					baddies [enoffsmasi].mx = -baddies [enoffsmasi].mx;
				if (gpen_cy == baddies [enoffsmasi].y1 || gpen_cy == baddies [enoffsmasi].y2)
					baddies [enoffsmasi].my = -baddies [enoffsmasi].my;
#endif

#ifdef ENABLE_SHOOTERS
				// Shoot a coco
				if (enemy_shoots && (rand () & SHOOTER_SHOOT_FREQ) == 1) {
					shoot_coco ();
				}
#endif
