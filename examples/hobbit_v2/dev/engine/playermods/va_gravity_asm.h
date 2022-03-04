#asm
	#ifdef PLAYER_GENITAL
			; Signed comparisons are hard
			; p_vz <= PLAYER_FALL_VY_MAX - PLAYER_G

			ld  a, (_p_vz)
			bit 7, a
			jr  nz, _player_gravity_add 	; < 0

			cp  PLAYER_FALL_VY_MAX - PLAYER_G
			jr  nc, _player_gravity_maximum

		._player_gravity_add
			add PLAYER_G
			jr  _player_gravity_vy_set

		._player_gravity_maximum
			ld  a, PLAYER_FALL_VY_MAX

		._player_gravity_vy_set
			ld  (_p_vz), a
	#else
			ld  a, (_do_gravity)
			or  a
			jr  z, _player_gravity_done

			; Signed comparisons are hard
			; p_vy <= PLAYER_FALL_VY_MAX - PLAYER_G

			; We are going to take a shortcut.
			; If p_vy < 0, just add PLAYER_G.
			; If p_vy > 0, we can use unsigned comparition anyway.

			ld  a, (_p_vy)
			bit 7, a
			jr  nz, _player_gravity_add 	; < 0

			cp  PLAYER_FALL_VY_MAX - PLAYER_G
			jr  nc, _player_gravity_maximum

		._player_gravity_add
			add PLAYER_G
			jr  _player_gravity_vy_set

		._player_gravity_maximum
			ld  a, PLAYER_FALL_VY_MAX

		._player_gravity_vy_set
			ld  (_p_vy), a

		._player_gravity_done

		#ifdef PLAYER_CUMULATIVE_JUMP
			ld  a, (_p_jmp_on)
			or  a
			jr  nz, _player_gravity_p_gotten_done
		#endif

			ld  a, (_p_gotten)
			or  a
			jr  z, _player_gravity_p_gotten_done

			xor a
			ld  (_p_vy), a

		._player_gravity_p_gotten_done
	#endif
#endasm
