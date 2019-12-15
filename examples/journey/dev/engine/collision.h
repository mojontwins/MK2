// MT Engine MK2 v0.90b
// Copyleft 2016 the Mojon Twins

// collision.h
// Collision functions

unsigned char collide_pixel (void) {
	#asm
			// return (cx1 >= cx2 + 1 && cx1 <= cx2 + 14 && cy1 >= cy2 + 1 && cy1 <= cy2 + 14);
			ld  hl, 0

			// cx1 >= cx2 + 1
			ld  a, (_cx2)
			inc a
			ld  c, a
			ld  a, (_cx1)
			cp  c 
			jr  c, _collide_pixel_return

			// cx1 <= cx2 + 14 -> cx2 + 14 >= cx1
			ld  a, (_cx1)
			ld  c, a
			ld  a, (_cx2)
			add 14
			cp  c
			jr  c, _collide_pixel_return

			// cy1 >= cy2 + 1
			ld  a, (_cy2)
			inc a
			ld  c, a
			ld  a, (_cy1)
			cp  c 
			jr  c, _collide_pixel_return

			// cy1 <= cy2 + 14 -> cy2 + 14 >= cy1
			ld  a, (_cy1)
			ld  c, a
			ld  a, (_cy2)
			add 14
			cp  c
			jr  c, _collide_pixel_return

			ld  l, 1
		._collide_pixel_return
			ret
	#endasm
}

unsigned char cm_two_points (void) {
	/*
	if (cx1 > 14 || cy1 > 9) at1 = 0; 
	else at1 = map_attr [cx1 + (cy1 << 4) - cy1];

	if (cx2 > 14 || cy2 > 9) at2 = 0; 
	else at2 = map_attr [cx2 + (cy2 << 4) - cy2];
	*/
	#asm
			ld  a, (_cx1)
			cp  15
			jr  nc, _cm_two_points_at1_reset

			ld  a, (_cy1)
			cp  10
			jr  c, _cm_two_points_at1_do

		._cm_two_points_at1_reset
			xor a
			jr  _cm_two_points_at1_done

		._cm_two_points_at1_do
			ld  a, (_cy1)
			ld  b, a
			sla a
			sla a
			sla a
			sla a
			sub b
			ld  b, a
			ld  a, (_cx1)
			add b
			ld  e, a
			ld  d, 0
			ld  hl, _map_attr
			add hl, de
			ld  a, (hl)

		._cm_two_points_at1_done
			ld (_at1), a

			ld  a, (_cx2)
			cp  15
			jr  nc, _cm_two_points_at2_reset

			ld  a, (_cy2)
			cp  10
			jr  c, _cm_two_points_at2_do

		._cm_two_points_at2_reset
			xor a
			jr  _cm_two_points_at2_done

		._cm_two_points_at2_do
			ld  a, (_cy2)
			ld  b, a
			sla a
			sla a
			sla a
			sla a
			sub b
			ld  b, a
			ld  a, (_cx2)
			add b
			ld  e, a
			ld  d, 0
			ld  hl, _map_attr
			add hl, de
			ld  a, (hl)

		._cm_two_points_at2_done
			ld (_at2), a
	#endasm
}

unsigned char attr (void) {
	// x + 15 * y = x + (16 - 1) * y = x + 16 * y - y = x + (y << 4) - y.
	// if (cx1 < 0 || cy1 < 0 || cx1 > 14 || cy1 > 9) return 0;
	// return map_attr [cx1 + (cy1 << 4) - cy1];
	#asm
			ld  a, (_cx1)
			cp  15
			jr  nc, _attr_reset

			ld  a, (_cy1)
			cp  10
			jr  c, _attr_do

		._attr_reset
			ld  hl, 0
			ret

		._attr_do
			ld  a, (_cy1)
			ld  b, a
			sla a
			sla a
			sla a
			sla a
			sub b
			ld  b, a
			ld  a, (_cx1)
			add b
			ld  e, a
			ld  d, 0
			ld  hl, _map_attr
			add hl, de
			ld  a, (hl)

			ld  h, 0
			ld  l, a
			ret
	#endasm
}

unsigned char qtile (void) {
	// x + 15 * y = x + (16 - 1) * y = x + 16 * y - y = x + (y << 4) - y.
	// return map_buff [cx1 + (cy1 << 4) - cy1];
		#asm
			ld  a, (_cx1)
			cp  15
			jr  nc, _qtile_reset

			ld  a, (_cy1)
			cp  10
			jr  c, _qtile_do

		._qtile_reset
			ld  hl, 0
			ret

		._qtile_do
			ld  a, (_cy1)
			ld  b, a
			sla a
			sla a
			sla a
			sla a
			sub b
			ld  b, a
			ld  a, (_cx1)
			add b
			ld  e, a
			ld  d, 0
			ld  hl, _map_buff
			add hl, de
			ld  a, (hl)

			ld  h, 0
			ld  l, a
			ret
	#endasm
}
