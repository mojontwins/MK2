# Tilanims (v3)

Animated tiles are great but they've always been a mess in MK2. Let's try for the third time to make them usable. Thanks Greenweb for the ideas.

Animated tiles are just pairs of tiles in your tileset which are swapped every N frames, this is, if tile A is found in the map, tile A or tile A+1 are displayed alternatively every N frames. That's what we call a *tilanim*. Which tiles are *tilanims* and when the graphics are swapped is defined by a simple yet powerful (!) system.

*Tilanims* behavious is configured by this section in `my/config.h`:

```c
    #define ENABLE_TILANIMS                 // If defined, animated tiles are enabled and will alternate between t and t+1

    #define TILANIMS_PERIOD             16  // Update tilanims every N frames. 1 = every frame

    #define TILANIMS_TYPE_ONE               // Only one animated tile changes each time, or
    #define TILANIMS_TYPE_ALL               // All animated tiles change at once.
                                            // If you enable both types you need to set tilanims_type_select
                                            // to 0 (TYPE_ALL) or 1 (TYPE_ONE) to choose
    #define TILANIMS_TYPE_SELECT_FLAG   5   // Or use this flag instead, if defined

    #define IS_TILANIM(t)       ((t)==20)   // Condition to detect if a tile is animated
```

If `ENABLE_TILANIMS` is set, tiles which meet the condition `IS_TILANIM(t)` are added to the *tilanims* arrays. The size of these arrays should not be very big and is configured in `definitions.h` as `MAX_TILANIMS`.

In the main loop, the *tilanims* update function is called every `TILANIMS_PERIOD` frames, so setting this to `1` makes the function run every frame. Which *tilanims* are updated every time the update function is called depends on the following set of defines:

- If `TILANIMS_TYPE_ONE` is defined, only one of the tilanims is updated each time the function is called (in reality, the function has a counter which is incremented by `TILANIMS_PRIME` modulus `MAX_TILANIMS` so it iterates for every possible tilanim and updates it if it is active - I know this sounds a bit confusing but you end up with every active tilanim being updated every `MAX_TILANIMS * TILANIMS_PERIOD` frames).

- If `TILANIMS_TYPE_ALL` is defined, all active tilanims are updated at once. So be careful not to have many *and* have a low value in `TILANIMS_PERIOD`.

You can define both but then must select which is active at a given moment using `tilanims_type_select` or `flags [TILANIMS_TYPE_SELECT_FLAG]`.

The `IS_TILANIM(t)` condition can be configured in a number of ways to fit your needs. For example, the default `((t)==20)` will make every tile 20 found in the map a *tilanim*. Using something like `((t)>15)` will make every tile with index > 15 a *tilanim*. You can use flags even, `(flags [3]==(t))` for example will make a *tilanim* every tile found in the map which equals to flag 3, and so on.

You can use the `my/before_flick.h` to add code which is run before changing to a new room to select the type of the *tilanims*, changing flags, etc.
