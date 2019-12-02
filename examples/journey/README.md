# Journey to the Centre of the Nose MK2 version
### Ported to MK2 as an excercise, illustration and example

This game was created with the first revision of the original version of MK1, so it's a rather simple game. My intention when porting it is adding map RLE compression to the engine. RLE compression for maps was developed for our NES engines and divides each byte in "tile number" and "run length". There are three flavours: RLE44, RLE53 and RLE62, with 4 bits for tile number / 4 bits for run length (16 tiles max., runs of 16 identic tiles max.), 5 bits for tile number / 3 bits for run length (32 tiles max., runs of 8 identic tiles max.) and 6 bits for tile number / 2 bits for run length (64 tiles max., runs of 4 identic tiles max.), respectively.

Choosing which combination of tile count / max. run length depends on the project. Classic unpacked maps which allowed for 48 different tiles are forced to use RLE62, but packed maps with 16 tiles plus decorations may benefit greatly from the RLE53 version (as long as you can keep the total tile count under 32). For **Journey to the Centre of the Nose** we'll be choosing the RLE44 which should give the best results as this game uses just 16 different tiles with no decorations.

This game also has two different levels featuring different tilesets which will demonstrate the `level.h` 48K level manager.

This document is a walk through the process of taking the base project and building a new game.

## Copy the base project

I just copied the base project to a new folder and changed the name of the game. Edit `compile.bat`

1. Set `SET game=journey` at the top. 
2. Also change the name of the loader in the tap file towards the end, at line 162:

```
    ..\utils\bas2tap -a10 -sJOURNEY loader\loader.bas work\loader.tap
```

## Prepare main assets: graphics

Next is replacing all the graphics assets in the `gfx` folder:

- Ending screen: `ending.png`
- Loading screen: `loading.png`
- Title / frame: `title.png`
- Font: `font.png`
- Spriteset: `sprites.png`
- Tileset for level 1: `tileset0.png`
- Tileset for level 2: `tileset1.png`

Now let's modify `compile.bat` to properly convert *and compress* both tilesets. Notice how we generate the font and the metatilesets separately, as we will be compressing just the tilesets to save space.



