Things not working properly:

#### [X] defining MIN_FAPS_PER_FRAME makes the game behave weirdly (and too slow). Check ISRC. Let's use the NO_SOUND engine.

It's odd. It doens't work at all in 128K mode no matter which ISR I'm using. When I play a bit it seems to start working after a while. Maybe a buffer overrun? 

Nope. The problem (may) be that isrc ends up lying very high in memory and gets paged out? But whenever it's incremented, RAM0 should be paged in...

I'm gonna try to force it existing lower in mem to see what happens.

Yup - that was it. It seems that I forgot a DI when some page was paged in. I could track it down or I could just put the isrc variable in a fixed position such as 23296 and that's what I will do.

#### [X] when WALLS_STOP_ENEMIES enemies seem to change direction based upon main player position (!). - a `cm_two_points` call was missing1

#### [ ] Clouds are not implemented!

#### [X] explosion sprite frame management is off

Completely replaced the enemies engine.

#### [X] Scripting is off ?!

Needed to place some vars in non-bankable memory

#### [X] Broken tiles not persistent

Needed to define `PERSISTENT_BREAKABLE`

#### [X] Safe spot should be pixel perfect!

Otherwise it reappears in bad places sometimes. Could [re]apply a simple fix. Gotta think about it.

#### [X] TILE_GET is bugged, infinite get!

#### [X] Can't jump off vertical platforms.

#### [X] Horz platforms not right.

`p_vx` and `p_vy` are 16 bit integer. No good. Time to change to FIXBITS = 4 and use signed chars. Do this next.

#### [X] `drawscr` in `PACKED` / `UNPACKED` mode - rewrite in assembly

