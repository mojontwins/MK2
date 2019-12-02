#if defined (MSC_MAXITEMS) || defined (ENABLE_SIM)
			// Select object
			if (sp_KeyPressed (key_z)) {
				if (!key_z_pressed) {
#ifdef MODE_128K
					_AY_PL_SND (SFX_INVENTORY);
#else
					beep_fx (SFX_INVENTORY);
#endif
#ifdef MSC_MAXITEMS
					flags [FLAG_SLOT_SELECTED] = (flags [FLAG_SLOT_SELECTED] + 1) % MSC_MAXITEMS;
#else
					flags [FLAG_SLOT_SELECTED] = (flags [FLAG_SLOT_SELECTED] + 1) % SIM_DISPLAY_MAXITEMS;
#endif
					display_items ();
				}
				key_z_pressed = 1;
			} else {
				key_z_pressed = 0;
			}
#endif
			