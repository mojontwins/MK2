
#ifdef NO_MASKS
	sp_player = sp_CreateSpr (sp_OR_SPRITE, 3, sprite_2_a);
	sp_AddColSpr (sp_player, sprite_2_b);
	sp_AddColSpr (sp_player, sprite_2_c);
	p_c_f = p_n_f = sprite_2_a;

	for (gpit = 0; gpit < 3; gpit ++) {
		sp_moviles [gpit] = sp_CreateSpr(sp_OR_SPRITE, 3, sprite_9_a);
		sp_AddColSpr (sp_moviles [gpit], sprite_9_b);
		sp_AddColSpr (sp_moviles [gpit], sprite_9_c);
		en_an_c_f [gpit] = en_an_n_f [gpit] = sprite_9_a;
	}
#else
	sp_player = sp_CreateSpr (sp_MASK_SPRITE, 3, sprite_2_a);
	sp_AddColSpr (sp_player, sprite_2_b);
	sp_AddColSpr (sp_player, sprite_2_c);
	p_c_f = p_n_f = sprite_2_a;

	for (gpit = 0; gpit < 3; gpit ++) {
		sp_moviles [gpit] = sp_CreateSpr(sp_MASK_SPRITE, 3, sprite_9_a);
		sp_AddColSpr (sp_moviles [gpit], sprite_9_b);
		sp_AddColSpr (sp_moviles [gpit], sprite_9_c);
		en_an_c_f [gpit] = en_an_n_f [gpit] = sprite_9_a;
	}
#endif

#ifdef PLAYER_CAN_FIRE
	for (gpit = 0; gpit < MAX_BULLETS; gpit ++) {
#ifdef MASKED_BULLETS
		sp_bullets [gpit] = sp_CreateSpr (sp_MASK_SPRITE, 2, sprite_19_a);
#else
		sp_bullets [gpit] = sp_CreateSpr (sp_OR_SPRITE, 2, sprite_19_a);
#endif
		sp_AddColSpr (sp_bullets [gpit], sprite_19_a + 32);
	}
#endif

#ifdef ENABLE_FLOATING_OBJECTS
#ifdef ENABLE_FO_CARRIABLE_BOXES
	sp_carriable = sp_CreateSpr (sp_MASK_SPRITE, 3, carriable_a);
	sp_AddColSpr (sp_carriable, carriable_b);
	sp_AddColSpr (sp_carriable, carriable_c);
#endif
#endif

#if defined (PLAYER_CAN_PUNCH)
	sp_hitter = sp_CreateSpr (sp_MASK_SPRITE, 2, sprite_20_a);
	sp_AddColSpr (sp_hitter, sprite_20_a + 32);
	hitter_c_f = sprite_20_a;
#endif

#if defined (PLAYER_HAZ_SWORD)
	sp_hitter = sp_CreateSpr (sp_MASK_SPRITE, 2, sprite_sword_l);
	sp_AddColSpr (sp_hitter, sprite_sword_l + 32);
	hitter_c_f = sprite_sword_l;
#endif

#if defined (PLAYER_HAZ_WHIP)
	sp_hitter = sp_CreateSpr (sp_MASK_SPRITE, 2, sprite_whip);
	sp_AddColSpr (sp_hitter, sprite_whip + 32);
	sp_AddColSpr (sp_hitter, sprite_whip + 64);
	hitter_n_f = hitter_c_f = sprite_whip;
#endif

#ifdef ENABLE_SHOOTERS
	for (gpit = 0; gpit < MAX_COCOS; gpit ++) {
#ifdef MASKED_BULLETS
		sp_cocos [gpit] = sp_CreateSpr (sp_MASK_SPRITE, 2, sprite_19_a);
#else
		sp_cocos [gpit] = sp_CreateSpr (sp_OR_SPRITE, 2, sprite_19_a);
#endif
		sp_AddColSpr (sp_cocos [gpit], sprite_19_a + 32);
	}
#endif

#if defined (PLAYER_GENITAL) && defined (PLAYER_HAS_JUMP)
	sp_shadow = sp_CreateSpr (sp_MASK_SPRITE, 2, sprite_shadow);
	sp_AddColSpr (sp_shadow, sprite_shadow + 32);
	sp_AddColSpr (sp_shadow, sprite_shadow + 64);
#endif
