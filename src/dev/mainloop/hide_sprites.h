void hide_sprites (unsigned char which_ones) {
	if (which_ones == 0) sp_MoveSprAbs (sp_player, spritesClip, 0, VIEWPORT_Y + 30, VIEWPORT_X + 20, 0, 0);
	for (gpit = 0; gpit < 3; gpit ++)
		sp_MoveSprAbs (sp_moviles [gpit], spritesClip, 0, VIEWPORT_Y + 30, VIEWPORT_X + 20, 0, 0);
#ifdef PLAYER_CAN_FIRE
	for (gpit = 0; gpit < MAX_BULLETS; gpit ++)
		sp_MoveSprAbs (sp_bullets [gpit], spritesClip, 0, -2, -2, 0, 0);
#endif
#ifdef ENABLE_SHOOTERS
	for (gpit = 0; gpit < MAX_COCOS; gpit ++)
		sp_MoveSprAbs (sp_cocos [gpit], spritesClip, 0, -2, -2, 0, 0);
#endif
#if defined (PLAYER_CAN_PUNCH) || defined (PLAYER_HAZ_SWORD) || defined (PLAYER_HAZ_WHIP)
	sp_MoveSprAbs (sp_hitter, spritesClip, 0, -2, -2, 0, 0);
#endif
#ifdef ENABLE_FO_CARRIABLE_BOXES
	sp_MoveSprAbs (sp_carriable, spritesClip, 0, -2, -2, 0, 0);
#endif
#if defined (PLAYER_GENITAL) && defined (PLAYER_HAS_JUMP)
	sp_MoveSprAbs (sp_shadow, spritesClip, 0, -2, -2, 0, 0);
#endif
}
