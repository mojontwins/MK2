MT Engine MK2
=============

MT Engine MK2 is a framework composed by a modular engine coded in C and a powerful toolchain to make games for the ZX Spectrum. MK2 is the sucessor to Churrera (MK1). 

MK2 needs z88dk v1.10 to compile and uses a modified version of splib2 by Alvin Albrecht.

We "abandoned" MK2 in 2018, but continued support by some developers has resurrected the proyect, which will eventually get more enhancements and additions.

Installation
============

There's a couple of things you have to do to get this working.

1. Download or clone this repository.
2. Install the stripped-down, minimal version of z88dk10 in C:. Just decompress the file `env/z88dk10-stripped.zip` to `C:/`. You shouls get a `C:\z88dk10\` folder.
3. Compile and install the modified **splib2** library. To do that, just run `lib/splib2/Makefile.bat`.

How to Build
============

The engine / framework resides in `src`. The code, as is, features a placeholder game you are supposed to *replace* with your own. You can compile it as-is, of course, to test the environment. To do so:

1. Open a command line console.
2. Navigate to the `src/dev` folder
3. Execute `setenv.bat` to set up some environment variables.
4. Run `compile.bat`.

If everything went OK, you'll get a tape image `mk2.tap` you can play in your favourite ZX Spectrum emulator. 

Documentation
=============

There isn't a proper tutorial yet, but you can check the one we wrote for MK1 [here](http://www.elmundodelspectrum.com/taller.php) (Spanish) or [here]() (English, thanks Andy Dansby).

Most of the features are documented in the ever growing but a bit confusing ['whats's new' document](https://github.com/mojontwins/MK2/blob/master/docs/whatsnew.md).

There's also a bunch of interesting docs in [the `docs` folder](https://github.com/mojontwins/MK2/tree/master/docs).

Credits
=======

* Engine & toolchain by na_th_an copyleft 2013-2015, 2019. Like it? [buy me a coffee](https://ko-fi.com/I2I0JUJ9)
* Placeholder game by **Greenweb**.
* **splib2** by Alvin Albrecth.
* Sound FX and *Phaser 1* music player by Shiru.
* **Appack decompresor** by dwedit, adapted by Utopian and optimized by Metalbrain.
* **WYZ Player** by WYZ. 

Important
=========

* The included `splib2` library is not the original. You can get the original `splib2` [here](http://www.mojontwins.com/churrera/mt-splib2.zip). There's a backup of the original Spritepack site with the docs [here](http://www.oocities.org/aralbrec/spritepack/programmer-intro.htm).
* The z88dk 1.10 package in the `env` folder is not complete as it just includes the files needed to compile MK2 projects. You can get the full version [here](http://www.mojontwins.com/churrera/mt-z88dk10.zip).

License
=======

**MT Engine MK2 ZX** is copyleft The Mojon Twins and is distributed under a [LGPL license](https://github.com/mojontwins/MK2/blob/master/LICENSE).

You are *required* to add the Mojon Twins logo to the cover art and/or the loading screen of your games.

**But** if you make a game with the engine we understand you'll want to make it into a tape and sell it. **In such case, just tell us!** Write to mojontwins@gmail.com - just as a matter of courtesy. If you don't we'll get sad and rather disappointed.

The **game assets** included in the testers and examples (graphics, music, etc.) are [donationware](https://en.wikipedia.org/wiki/Donationware). 

If you like this, you can [buy me a coffee](https://ko-fi.com/I2I0JUJ9).

Have fun.


Logo for game arts
------------------

![MK2 logo](https://raw.githubusercontent.com/mojontwins/MK2/master/mk2_logo.png)

Logo for ZX Spectrum
--------------------

![MK2 logo spectrum](https://raw.githubusercontent.com/mojontwins/MK2/master/mk2_logo_orig.png)
