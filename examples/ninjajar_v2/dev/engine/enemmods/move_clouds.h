				// Move Clouds

				active = 1;
				gpen_cx = baddies [enoffsmasi].x;
				gpen_cy = baddies [enoffsmasi].y;
				if (gpx != gpen_cx) {
					baddies [enoffsmasi].x += addsign (gpx - gpen_cx, baddies [enoffsmasi].mx);
				}

				// Shoot a coco
				if ((rand () & TYPE_9_SHOOT_FREQ) == 1) {
					shoot_coco ();
				}
