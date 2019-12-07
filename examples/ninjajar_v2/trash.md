### The loader

The thing is, this game uses RAM7 and this page is used a some sort of scratchpad by the ROM if IM1 is on, so we can't use a BASIC loader. Thankfully, thanks to some explanations by the almighty Antonio Villena, I've crafted a little loader in assembly which loads every asset (aplib compressed) and decompresses everything in place.

This may bit a bit advanced as the original `loaderzx.asm-orig` file has to be patched in real time with the actual sizes of the binaries. I hate doing things by hand, that's why I use `imanol.exe`, which performs simple textual substitutions. If you don't get this but you are interested in assembly loaders you can drop me a line. You should know that [I love coffee](https://ko-fi.com/I2I0JUJ9).

First of all we must compress every binary: loading screen, all 5 extra RAM pages, and the main binary. But once we do and try, we notice that two of the RAMx.bin files actually get bigger when compressed, as the data in them is already compressed: RAM3.bin and RAM4.bin. So we compress the rest and leave these uncompressed.

```
    echo ### COMPRESSING ###
    ..\..\..\src\utils\apack.exe ..\bin\loading.bin work\loading_c.bin > nul
    ..\..\..\src\utils\apack.exe work\RAM1.bin work\RAM1c.bin > nul
    ..\..\..\src\utils\apack.exe work\RAM6.bin work\RAM6c.bin > nul
    ..\..\..\src\utils\apack.exe work\RAM7.bin work\RAM7c.bin > nul
    ..\..\..\src\utils\apack.exe work\%game%.bin work\MAINc.bin > nul
```

The loader starts with a bit of magic by A.Villena that, to be honest, I don't really understand, but makes this code auto-executable:

```
        org $5ccb
        ld  sp, $ffff
        di
        db  $de, $c0, $37, $0e, $8f, $39, $96 ;OVER USR 7 ($5ccb)
```

First thing is loading the compressed loading screen, then decompressing it to 16384. We'll be using the ROM loading routine on a headerless block, so we must know the exact length as we have to pass it to the routine. As I said before, I like to automate things, so for this parameter I'll use a constant and later on I'll inject the actual length of the bin file using my utility `imanol.exe`:

```
    ; load screen
        scf
        ld  a, $ff
        ld  ix, $8000
        ld  de, %%%ls_length%%%
        call $0556
        di

    ; Decompress
        ld  hl, $8000
        ld  de, $4000
        call depack 
```

The ROM loading routine which resides in $0556 needs the loading address in IX and the number of bytes to oad in DE, and the carry flag set. It also enables interrupts at the end, so a DI is needed right after. We'll be loading the compressed screen to $8000. For the length we use the constant %%%ls_length%%%, which will be replaced by the actual length using `imanol.exe` from `compile.bat`.

Aplib's depacker needs the compressed binary address in HL and the destination address in DE. This is a loading screen so it has to be decompressed to 16384 ($4000).

Next block is the compressed RAM1. To load the block, we page in RAM1, load the compressed block to $8000, then decompress it to $C000 (where RAM1 is mapped once it is paged in). Again, the block length will be injected later using `imanol.exe`.

```
    ; RAM1
        ld  a, $11      ; ROM 1, RAM 1
        ld  bc, $7ffd
        out (C), a

        scf
        ld  a, $ff
        ld  ix, $8000
        ld  de, %%%ram1_length%%%
        call $0556
        di

    ; Decompress
        ld  hl, $8000
        ld  de, $C000
        call depack
```

The next two blocks are RAM3 and RAM4 which were not compressed, so what we do is paging the correct RAM page and load the binaries directly to $C000:

```
    ; RAM3
        ld  a, $13      ; ROM 1, RAM 3
        ld  bc, $7ffd
        out (C), a

        scf
        ld  a, $ff
        ld  ix, $C000
        ld  de, %%%ram3_length%%%
        call $0556
        di

    ; RAM4
        ld  a, $14      ; ROM 1, RAM 4
        ld  bc, $7ffd
        out (C), a

        scf
        ld  a, $ff
        ld  ix, $C000
        ld  de, %%%ram4_length%%%
        call $0556
        di
```

Next come RAM6 and RAM7 which, like RAM1, are compressed:

```
    ; RAM6
        ld  a, $16      ; ROM 1, RAM 6
        ld  bc, $7ffd
        out (C), a

        scf
        ld  a, $ff
        ld  ix, $8000
        ld  de, %%%ram6_length%%%
        call $0556
        di

    ; Decompress
        ld  hl, $8000
        ld  de, $C000
        call depack 

    ; RAM7
        ld  a, $17      ; ROM 1, RAM 7
        ld  bc, $7ffd
        out (C), a

        scf
        ld  a, $ff
        ld  ix, $8000
        ld  de, %%%ram7_length%%%
        call $0556
        di

    ; Decompress
        ld  hl, $8000
        ld  de, $C000
        call depack
```

The last block is the main binary. It currently compresses to a bit over 11K so we could load it safely to $C000 and then decompress it to 24200. But I prefer, for the main binary, to load it as high as I can. imanol can do some calculations, so this time I'll use a constant for the base address as well, and will later substituite it for 65536-256-binary_length (256 to make room for the stack). Oh, and dont' forget to put RAM0 back in!:

```
; Main binary
    ld  a, $10      ; ROM 1, RAM 0
    ld  bc, $7ffd
    out (C), a

    scf
    ld  a, $ff
    ld  ix, %%%mb_start%%%
    ld  de, %%%mb_length%%%
    call $0556
    di

; Decompress
    ld  hl, %%%mb_start%%%
    ld  de, 24200
    call depack 
```

And now everything is in place, run the game:

```
    ; run game!
    jp 24200
```

What follows in the `loaderzx.asm-orig` file is the aplib decompressor.

Now is when we put `imanol.exe` to use. This simple command line tool just takes a text file, makes some substitutions, and writes a new file with the changes. Substitutions are passed as parameters in the format `constant=expression`, where expression may be a literal, a file length, or a simple aritmetic expression (addition and substraction).

Those are the constants we have to substitute:

```
    ls_length
    ram1_length
    ram3_length
    ram4_length
    ram6_length
    ram7_length
    mb_start
    mb_length
```

And this is how `imanol.exe` is called (I've broken the command line into several lines using `^` for clarity - this is a feature of Windows' .cmd and .bat files):

```
    ..\utils\imanol.exe ^
        in=loader\loaderzx.asm-orig ^
        out=loader\loader.asm ^
        ls_length=?work\loading_c.bin ^
        ram1_length=?work\RAM1c.bin ^
        ram3_length=?work\RAM3.bin ^
        ram4_length=?work\RAM4.bin ^
        ram6_length=?work\RAM6c.bin ^
        ram7_length=?work\RAM7c.bin ^
        mb_start=?65200-MAINc.bin ^
        mb_length=?MAINc.bin
```

If the value of a substitution begins with `?` that means "expression". A file name here equals its file length.

Next step is using `pasmo.exe` to assemble the loader:

```
    ..\utils\pasmo.exe loader\loader.asm work\loader.bin loader.txt
```

And now we have all the pieces of the puzzle, we have to build the tape using Antonio Villena's `GenTape.exe`:

```
    ..\utils\GenTape.exe %game%.tap ^
        basic 'NINJAJAR' 10 work\loader.bin ^
        data                work\loading_c.bin ^
        data                work\RAM1c.bin ^
        data                work\RAM3.bin ^
        data                work\RAM4.bin ^
        data                work\RAM6c.bin ^
        data                work\RAM7c.bin ^
        data                work\MAINc.bin
```

And now - fingers crossed :D
