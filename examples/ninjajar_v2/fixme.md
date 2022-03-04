Things not working properly:

#### [X] defining `MIN_FAPS_PER_FRAME` makes the game behave weirdly (and too slow). Check ISRC. Let's use the `NO_SOUND` engine.

It's odd. It doens't work at all in 128K mode no matter which ISR I'm using. When I play a bit it seems to start working after a while. Maybe a buffer overrun? 

Nope. The problem (may) be that isrc ends up lying very high in memory and gets paged out? But whenever it's incremented, RAM0 should be paged in...

I'm gonna try to force it existing lower in mem to see what happens.

Yup - that was it. It seems that I forgot a DI when some page was paged in. I could track it down or I could just put the isrc variable in a fixed position such as 23296 and that's what I will do.

#### [X] when `WALLS_STOP_ENEMIES` enemies seem to change direction based upon main player position (!). - a `cm_two_points` call was missing1

#### [ ] Clouds are not implemented!

#### [X] explosion sprite frame management is off

Completely replaced the enemies engine.

#### [X] Scripting is off ?!

Needed to place some vars in non-bankable memory

#### [X] Broken tiles not persistent

Needed to define `PERSISTENT_BREAKABLE`

#### [X] Safe spot should be pixel perfect!

Otherwise it reappears in bad places sometimes. Could [re]apply a simple fix. Gotta think about it. Did it but did it better

#### [X] TILE_GET is bugged, infinite get!

#### [X] Can't jump off vertical platforms.

#### [X] Horz platforms not right.

`p_vx` and `p_vy` are 16 bit integer. No good. Time to change to FIXBITS = 4 and use signed chars. Do this next.

#### [X] `drawscr` in `PACKED` / `UNPACKED` mode - rewrite in assembly

#### [X] Moving platforms kill

What's up with that `else` which should invalidate the collision check?

#### [X] Fix different animation for fanties

I mean, Ninjajar's should not animate but face left / right. Added `FANTIES_WITH_FACING`.

#### [X] Fanties don't respawn!

I had broken respawning code for all enemies, but still...

#### [X] Fanties don't reposition!

When reentering they don't seem to be in their original position (if they were killed ?).

#### [X] You can leave "jump" pressed

Implement "pad_this_frame" as in MK3

#### [X] Fanties (enemies?) are repositioned after showing text in the cave and other places.

Study why this happens and how to fix it. I think it has to do with "REENTER".

#### [X] Killing tiles not working

I just changed the collision detection, so I must've messed it somehow.

#### [X] Faster fanties in assembly

Not that they should move faster, but take less cycles to update. Will be performed in two stages:
[X] Rehash the code and extract copies of array values to plain vars.
[X] Translate into assembly.

Remember how you quickly add an 8 bit number to a 16 bit number (dumb mode on)

```
	ld  hl, (_var16)
	ld  bc, (_var8)
	ld  b, 0
	add hl, bc
	ld  (_result), hl
```

Signed:

```
	ld  e, a
	add a, a ; Carry if A < 0
	sbc a    ; Set all bits to C
	ld  d, a
	add hl, de
```

To compare two 16 bits numbers you can just do a 16 bit substraction and check the carry flag

```c
	ld  hl, (_A)
	ld  bc, (_B)
	sbc hl, bc
	jr  nc, A_was_bigger_or_equal_than_B
	jr  c, A_was_smaller_than_B
```

Or

```c
	or  a
	sbc hl, bc 	; Sets C 
	add hl, bc  ; Restore hl
	jr  nc, HL_was_bigger_or_equal_than_BC
	jr  c, HL_was_smaller_than_BC
```

I always say I prefer the 6502, but this is one of the situations Z80s are actually more powerful.

#### [X] Rewrite `distance` in assembly, 

Undo `abs` calls maybe.

#### [X] game almost freezes after exiting shops

Maybe it got stuck in an (unattended) fire zone? All main screens (0, 2, 4, 6, 8) define a fire zone at 224, 0, 239, 159, which is the right side of the screen, to trigger the level exit.

There's a strange scripting related to flag 6, which is noted in the comments as "Entering/exitting shop cheat". Maybe there was a cheat where you could get infinite lives? I can't remember, of course.

On entering screen 0 there's a `REPOSTN 8, 7` if `FLAG 6 = 1`. Flag 6 is set to 1 as soon as you enter the shop, but it's reset if you read any sign.

I bet there's something which is not being parsed quite right in this script which causes this endless loop.

The slowness is 'cause the game is reentering the screen continuously. `run_fire_script` is not being executed so I guess it doesn't have anything to do with the fire zone. Maybe the `WARP` is broken?

`WARP` sets `n_pant` to the value read in the script and `o_pant` to 99 (which should be unnecessary?), then relocates player and `return`s, which effectively ends the script.

At the moment the screen is about to be drawn, `n_pant = 0` (which is correct), `o_pant = 99`. So somebody is acting boldly.

Let's see what this does upon entering screen. Maybe the `run_entering_script` is in charge? First it calls `run_script` with 0x2B as a parameter, which happens to be 2*21+1, this is, `ENTERING ANY`. After this, `n_pant` and `o_pant` are still 0. So it's not there.

Then it calls again with 0x00, which happens to be `n_pant + n_pant` (`ENTERING SCREEN 0`). After this, `o_pant` = 99! WTF?

So there is something wrong with the scripting parsing as obviously there's nothing wrong with `ENTERING SCREEN 0`, at least nothing which should set `o_pant` to 99. There's a `script overflow` which is making this run into the `PRESS_FIRE AT SCREEN 0` script, hitting the `IF PLAYER_TOUCHES 8,7`. So let's debug `msc` *once again*.

But everything seems correct? Maybe the `msc.h` parser is wrong? Let's check `REPOSTN`.

```c
    case 0x6C:
        // REPOSTN sc_x sc_y
        // Opcode: 6C sc_x sc_y
        do_respawn = 0;
        reloc_player ();
        o_pant = 99;
        sc_terminado = 1;
        break;
```

WTF? Why does `REPOSTN` force a reenter?! Obviously this behaviour was added after `Ninjajar!`. Let's check what the docs have to say about `REPOSTN`...

No mention to `REPOSTN` in the docs. I guess I repurposed the command while making Leovigildo or whatever. Let's examine the script and change for `SETX`/`SETY`.

#### [X] No sprite for clouds (but they work)

#### [ ] Make cocos collision with bg selectable as per coco basis

So I can have monococos having laser cocos but nubes having solid cocos so you can take cover.

#### [ ] Why doesn't `cocos_destroy` clear the coco sprite?




