// Collide with bombs

if (bomb_state == 2) {
	if (_en_x + 15 >= bomb_px && _en_x <= bomb_px + 47 &&
		_en_y + 15 >= bomb_py && _en_y <= bomb_py + 47) {
		enems_kill (PLAYER_BOMBS_STRENGTH);
		goto enems_loop_continue;
	}
}
