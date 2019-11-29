			// Platforms: 2013 rewrite!
			// This time coded in a SMARTER way...!
			if (gpt == 8) {
#if defined (PHANTOMAS_ENGINE) || defined (HANNA_ENGINE)
				if (pregotten && (p_gotten == 0) && (p_jmp_on == 0 || p_jmp_ct > 2))
#else
				if (pregotten && (p_gotten == 0) && (p_jmp_on == 0))
#endif
				{
					// Horizontal moving platforms
					if (baddies [enoffsmasi].mx) {
						if (gpy + 16 >= baddies [enoffsmasi].y && gpy + 10 <= baddies [enoffsmasi].y) {
							p_gotten = 1;
#if defined (PHANTOMAS_ENGINE) || defined (HANNA_ENGINE)
							ptgmx = baddies [enoffsmasi].mx;
							p_x += ptgmx;
							p_y = (baddies [enoffsmasi].y - 16); gpy = p_y;
							p_jmp_on = 0;
#else
							ptgmx = baddies [enoffsmasi].mx << 6;
							p_y = (baddies [enoffsmasi].y - 16) << 6; gpy = p_y >> 6;
#endif
						}
					}

					// Vertical moving platforms
					if (
						(baddies [enoffsmasi].my < 0 && gpy + 18 >= baddies [enoffsmasi].y && gpy + 10 <= baddies [enoffsmasi].y) ||
						(baddies [enoffsmasi].my > 0 && gpy + 17 + baddies [enoffsmasi].my >= baddies [enoffsmasi].y && gpy + 10 <= baddies [enoffsmasi].y)
					) {
						p_gotten = 1;
#if defined (PHANTOMAS_ENGINE) || defined (HANNA_ENGINE)
						ptgmy = baddies [enoffsmasi].my;
						p_y = baddies [enoffsmasi].y - 16; gpy = p_y;
						p_jmp_on = 0;
#else
						ptgmy = baddies [enoffsmasi].my << 6;
						p_y = (baddies [enoffsmasi].y - 16) << 6; gpy = p_y >> 6;
						p_vy = 0;
#endif
					}
				}
			} else 
