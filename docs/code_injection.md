# Code injection points

I've added (and will keep adding) a bunch of `.h` files in `my/` where you can add code which is `#include`d in key positions of the engine which will help you do useful customizations.

This list will keep growing. Everytime you need to do something custom check if there's a code injection point that suits your needs or just contact me and I'll add a new one for you. Don't forget that [I love coffee](https://ko-fi.com/I2I0JUJ9).

## before_flick.h

The code you add here will be executed everytime the player changes to a new room, just after the transition in detected. At this point, `n_pant` contains the number of the room the player is about to move to, and `o_pant` contains the number of the room the player is leaving. You can do all sorts of stuff here, keep in mind that `ENTERING SCREEN n` in the script is run after the new room has been drawn. `before_flick.h` happens right before the transition.

## Custom enemies

You can define custom enemy types adding code to `extra_enems_init.h` (initialization, if needed) and `extra_enems_move` (update). Enemies are added using new `case`s of an existing `switch`. For example, adding a new type '5' (0 0101 000) of enemy which just exists somewhere and doesn't move (but animates) and has a fixed base frame:

Code in `extra_enems_init.h`:

```c
    case 5:
        // This enemy type has a fixed base frame: 
        en_an_base_frame [gpit] = 4;
        break;
```

Code in `extra_enems_move.h`: 

```c
    case 5:
        // static, idle, dummy enemy
        active = animate = 1;
        break;
```

## `new_level.h`

If you are using a game with several levels, the default new level screen (which shows `LEVEL XX` on screen for a while) can be customized changing the code in this file. In the examples, **Ninjajar v2** and **ZX Gimmick** do this to various degrees.

## `title_screen.h`

By default, games show a fixed screen then prompt for controls. This can be customized changing the code in this file. 

Keep reviewing this file for new additions!
