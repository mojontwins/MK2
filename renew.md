Empezamos con leves mejoras para acelerar un poco MK2 y luego ya nos iremos metiendo en cosas más mejores y menos peores.

Empezamos con la demo de greenweb tal cual

32194 bytes

1.- Deshacer spritesClip, sp_MoveSprAbs y relacionados.

31918 bytes

2.- Nueva version de drawColouredTile e invalidate por separado.

Primero tengo que modificar todas las instancias para que usen `_x`, `_y`, ... y esto incluye a msc. Ya modifiqué msc para key2time, voy a hacer un diff para ver si estamos actualizados.

En el interim he cambiado también asm_int_2 y asm_int.

Recordar optimizar las ristras de decoraciones no llamando a invalidar y haciéndolo después con toda la pantalla

31868 bytes - antes de pasar a asm, solo deshaciendo parámetros.

TODO: Ver las llamadas a `draw_coloured_tile` que podrían abreviarse con `draw_coloured_tile_gamearea`. [ ]

31649 bytes

~~

He metido la estructura para la memoria dinámica como un array fijo que engorda el binario pero hace que todo esté mucho más controlado y delimitado (el binario es más gordo, pero el limite superior es ahora una constante: 61440).

32458 bytes

Things to test:

[X] Sprites extra: disparos, cocos, hitter, explosión.
[X] Enemigos que se mueren.

32264 bytes

~~

Built The Hobbit (Vaka's Cut) to test more stuff.

1.- Collisions are not as nice (downwards or so it seems).
2.- Dizzy state is not dizzy at all.

~~

Años sin apuntar nada, pero pongo aqui un todo:

[ ] Revisar toda la lógica de `SHOOTER_FIRE_ONE`
[ ] Poner que sea fácil importar otro gráfico para los proyectiles y configurar el tamaño. Idem para el puf de morirse. De hecho, hacer que los extra_sprites sean fácilmente modificables. Poner los que ya hay de placeholders y dejar hacer al programador.

~~

[X] Recordar qué música estaba sonando para poder reanudar LA MISMA

~~

Volvemos, esta vez con fecha, porque quiero terminar Ninjajar y en el proceso arreglar cosas.

20220303
========

Antes siquiera de ver el estado de las cosas, quiero actualizar splib2 y recompilar esto con el z88dk moderno. Lo voy a hacer TODO en Ninjajar y luego si eso paso los cambios.

## splib2

Usamos la última versión que tiene MK1 v5.10 (unreleased) que lleva el modo bg/fg y tal. De paso compruebo que las modificaciones son compatibles y si no, cambiaré el motor.

Sip, todo estaba más o menos igual, salvo un par de mierdas para z88dk nuevo y tal. Recompilo y lo dejo así.

## MK2

Voy a ver si tengo diario en MK1 para ver qué pequeños cambios tuve que hacer en esta versión para que compilase con z88dk nuevo. El tema es que me da un poco de jiña porque Greenweb me dijo que MK2 no iba ni para atrás, y jamás encontramos la causa. Espero que fuera algún custom suyo porque no me apetece tener problemas - me apetece tan poco que si los tengo me vuelvo al z88dk10 de siempre, lo cual me daría bastante por saquer.

Nada apuntado. Bien pichis. Bueno, a la aventura ^_^u

Empezamos:

```
	engine/enemmods/kill_enemy.h: line 5: trailing garbage in constant integral expression
        included from engine/enems.h:21
        included from mk2.c:195
```

Esta era fácil, había un ")" al final que no era :)

```
	engine/general.h:17:21: warning: Calling via non-function pointer [-Wincompatible-pointer-types]
	engine/general.h:17:28: warning: Assigning from a void expression [-Wvoid]
```

Esta la recuerdo, es el struct de los controles, se cambia en `definitions.h`:

```c
	//void *joyfunc = sp_JoyKeyboard;		// Puntero a la función de manejo seleccionada.
	unsigned char (*joyfunc)(struct sp_UDK *) = sp_JoyKeyboard;
```

Y esta ristra de cadenas que hay que *castear*:

```
	my/extern.h:176:64: warning: Assigning 'gp_gen', type: unsigned char * gp_gen from char *  [-Wincompatible-pointer-types]
	my/extern.h:177:56: warning: Assigning 'gp_gen', type: unsigned char * gp_gen from char *  [-Wincompatible-pointer-types]
	my/extern.h:179:67: warning: Assigning 'gp_gen', type: unsigned char * gp_gen from char *  [-Wincompatible-pointer-types]
```

Y ahora tenemos este:

```
	my/msc.h:478:48: fatal error: Non struct type can't take member
```

```c
	level_data.music_id = sc_n;
```

Probablemente tenga que cambiar msc, voy a ver MK1 cómo cuece esto - pues directamente no lo cuece :*) Así que voy a ver qué tripa se le ha roto. Oh, probablemente tenga que poner `->` porque es un puntero del demonio. Arreglemos msc...

Vale, por ahora se ha callao la boca, pero dice que:

```
	engine/general.h:148:28: warning: Assigning 'joyfunc', type: unsigned int (struct sp_UDK * )* joyfunc from unsigned char ucharsp_JoyKeyboard(struct sp_UDK * keys)*  [-Wincompatible-pointer-types]
	engine/general.h:166:29: warning: Assigning 'joyfunc', type: unsigned int (struct sp_UDK * )* joyfunc from unsigned char ucharsp_JoyKempston()*  [-Wincompatible-pointer-types]
	engine/general.h:169:30: warning: Assigning 'joyfunc', type: unsigned int (struct sp_UDK * )* joyfunc from unsigned char ucharsp_JoySinclair1()*  [-Wincompatible-pointer-types]
```

Es al asignar las funciones de control. Esto en MK1 está muy apañao, tengo 

```c 
	const void *joyfuncs [] = {
		sp_JoyKeyboard, sp_JoyKempston, sp_JoySinclair1
	};
```

Y asigno según eso. Como es `void *` se lo traga con salsita. Voy a por un apañete, así:

```c
	// definitions.h @ 64

	const void *joyfuncs [] = {
		sp_JoyKeyboard, sp_JoyKeyboard, sp_JoyKempston, sp_JoySinclair1
	};
```

Y 

```c
	// general.h @ 144

	while (1) {
		gpit = sp_GetKey ();
		if (gpit >= '1' && gpit <= '4') {
			joyfunc = joyfuncs [gpit - '1'];

			if (gpit == '1' || gpit == '2') {
				gpjt = (gpit - '1') ? 6 : 0;
				#ifdef USE_TWO_BUTTONS
					keys.up = keyscancodes [gpjt ++];
					keys.down = keyscancodes [gpjt ++];
					keys.left = keyscancodes [gpjt ++];
					keys.right = keyscancodes [gpjt ++];
					key_fire = keys.fire = keyscancodes [gpjt ++];
					key_jump = keyscancodes [gpjt];
				#else
					keys.up = keyscancodes [gpjt ++];		// UP
					keys.down = keyscancodes [gpjt ++];		// DOWN
					keys.left = keyscancodes [gpjt ++];		// LEFT
					keys.right = keyscancodes [gpjt ++];	// RIGHT
					keys.fire = keyscancodes [gpjt ++];		// FIRE				
				#endif
			}

			break;
		}
	}
```

Y luego la diversión. En el msc.h se quejaba por lo contrario, y aquí:

```
	my/msc.h:478:49: fatal error: Member reference to 'music_id' via 'struct 0__anonstruct_4 LEVELHEADER level_data[0]' is not a pointer; did you mean to use '.'?
	Compilation aborted
	my/msc.h:478:49: fatal error: Member reference to 'music_id' via 'struct 0__anonstruct_4 LEVELHEADER level_data[0]' is not a pointer; did you mean to use '.'?
```

Esto sí que me suena de haberlo apañado en MK1. A ver si es verdad... Pues en MK1 va todo con punto. ¿Por qué @#!! se quejaba en el msc? Voy a ver la definición.

Vale, parece que es el [0] de mierda que le puse en MK2. Fuera, y veo si hay más cosas así... Si pero meh. A deshacer el cambio en msc...

Y ahora otro:

```
	engine/scripting.h:4:37: fatal error: Member reference to 'activate_scripting' via 'struct 0__anonstruct_4 level_data' is not a pointer; did you mean to use '.'?
```

Otro ->, vamos a buscar y remplazar y abreviamos. Un millón de sitios. Apañated.

Ahora más strings:

```
	engine/messages.h:33:25: warning: Assigning 'gp_gen', type: unsigned char * gp_gen from char *  [-Wincompatible-pointer-types]
	./my/new_level.h:10:45: warning: Assigning 'gp_gen', type: unsigned char * gp_gen from char *  [-Wincompatible-pointer-types]
	mainloop/mainloop.h:274:30: warning: Assigning 'gp_gen', type: unsigned char * gp_gen from char *  [-Wincompatible-pointer-types]
	mainloop/mainloop.h:282:29: warning: Assigning 'gp_gen', type: unsigned char * gp_gen from char *  [-Wincompatible-pointer-types]
```

Y con esto, y un bizcocho... Compiló. Otra cosa es que funcione :*)

Pues no va la lectura del teclado en los "pause N frames". Revisamos `active_sleep`, que llama a `button_pressed`, que hace:

```c
	unsigned char button_pressed (void) {
		read_controller (); return (pad_this_frame != 0xff);
	}
```

Y que voy a irme a comparar con MK1 :-/ Aunque quizá lo que he roto es la función de seleccionar controles - aún así ...  No aplica, porque en MK1 v5 todo esto es super rudimentario. Voy a probar a seleccionar joystick sinclair y así voy descartando cosas...

Joder, no me eches cuenta. Funciona, sólo que esto sólo reacciona a los botones del joyfunc. Yo es que estoy muy acostumbrado a darle a SPACE, ¿podría pinchearlo vilmente?

Si esto fuera un universo alternativo en el que yo me currase MK2 pues mira, haría una super función virgosa que lo metiese todo en el byte devuelto y meeeeh.

```c
	void read_controller (void) {
		// Thanks for this, Nicole & nesdev!
		// https://forums.nesdev.com/viewtopic.php?p=179315#p179315
		// This version is the same but with negative logic
		// as splib2's functions are active low
		pad_this_frame = pad0;
		pad0 = ((joyfunc) (&keys));			// Read pads here.

		// Pinch, raise/lower bit 6 with SPACE
		if (sp_KeyPressed (0x017f)) pad0 &= 0xbf; 	// 1011 1111
		else 						pad0 |= 0x40; 	// 0100 0000

		pad_this_frame = ((~(pad_this_frame ^ pad0)) | pad0) | 0x30; // Always raise 00110000
	}
```

Me cago y me queda. El ensamble de esto tiene que ser el terror:

```asm
	._read_controller
		ld	a,(_pad0)
		ld	(_pad_this_frame),a
		ld	hl,(_joyfunc)
		push	hl
		ld	hl,_keys
		ex	(sp),hl
		call	l_jphl
		pop	bc
		ld	a,l
		ld	(_pad0),a
		ld	hl,383	;const
		push	hl
		call	sp_KeyPressed
		pop	bc
		ld	a,h
		or	l
		jp	z,i_20	;
		ld	hl,(_pad0)
		ld	h,0
		ld	a,191
		and	l
		ld	l,a
		ld	a,l
		ld	(_pad0),a
		jp	i_21	;EOS
	.i_20
		ld	hl,(_pad0)
		ld	h,0
		set	6,l
		ld	h,0
		ld	a,l
		ld	(_pad0),a
	.i_21
		ld	hl,(_pad_this_frame)
		ld	h,0
		ld	a,(_pad0)
		xor	l
		ld	l,a
		call	l_com
		ex	de,hl
		ld	hl,(_pad0)
		ld	h,0
		call	l_or
		ld	a,l
		or	48
		ld	l,a
		ld	h,0
		ld	(_pad_this_frame),a
		ret
```

Maemía... Así que la paso yo a manita:

```c
	#asm
			ld  a, (_pad0)
			ld  (_pad_this_frame), a

			// Read pads here:

			ld	hl, (_joyfunc)
			push hl
			ld	hl,_keys
			ex	(sp), hl
			call l_jphl
			pop	bc
			ld	a, l
			ld	(_pad0), a

			// Pinch, raise / lower bit 6 with SPACE.
			// You may want to remove this in your game...

			ld  hl, 0x017f
			push hl
			call sp_KeyPressed
			pop bc
			xor a
			or  l
			
			ld  a, (_pad0)
			jp  z, space_not_pressed

		.space_pressed
			and 0xbf
			jr  space_read_update_pad0

		.space_not_pressed
			or 0x40

		.space_read_update_pad0
			ld  (_pad0), a

			// Now "compare"
			
			ld  c, a
			ld  a, (_pad_this_frame)
			xor c
			neg
			or  c
			or  0x30

			ld  (_pad_this_frame), a
	#endasm
```

Esto parece funcionar bastante bien... Voy a pasar los cambios a los otros ejemplos y ver si sigue compilando.

### Gimmick

Corregí una miseria en las balas, que tiene mx, my como `unsigned char` porque soy tonto y un guarro y z88dk nuevo es refinado y fino y ya lo he corregido.

### Hobbit v2

Faltaba `my/before_flick.h`, y parece que `music.h` no le gusta ni mijitis. Es como si no encontrase ni un solo identificador y es que creo que esto es case sensitive... Con este find and replace: `\.([a-z0-9_]+)` por `.\U$1` en modo regexp parece arreglarse... veamos. Sip, pero `.musicstart` tiene que estar en minúsculas.

### Journey

El apaño de la definición de `level_data` había que hacerlo también en modo 48 Kas Naranja. También tenía la misma miseria de `music.h`.

## Ahora Khe

Ahora, a preparar un release de MK2. Habría que sacar Ninjajar y meter un juego por defecto, para luego hacer el merge, crear una nueva rama, y meter Ninjajar en esa rama.

Como ejemplo voy a poner algún ejemplo chulo que haya hecho a lo largo del tiempo. Por ejemplo **Espadewr!**.

## Espadewr!

Primero copio los assets y luego monto la historia con el config.h y compilo. A ver. Tengo que parchear el enems.ene, probablemente. Hay que comprobar "2b" y que el formato de los enemigos esté bien. Y parece que está bien. Veamos el config...

Remember que tiene un extern *y scripting* *y textos* (WTF?) Bueno, está bien todo el despliegue.

Compilando esto han salido más miserias (¡normal! qué bien he elegido el ejemplo):

```
	engine/drawscr.h:569:47: warning: Assigning 'gp_gen', type: unsigned char * gp_gen from char *  [-Wincompatible-pointer-types]
```

Típico de cadenas, y este: 

```
	engine/hud.h:79:28: fatal error: Unknown symbol: timer_old
```

Porque cambié la forma en que se controla si se dibuja algo o no en el hud.

También hay miserias en los fanties, seguramente porque estos son más complejos o algo. La putez es que esta versión de z88dk no sabe enseñar bien donde está el fallo en ensamble, o yo no sé interpretarlo...

```
	Warning at file './engine/enemmods/move_fanty_asm.h::enems_move::5::136': integer '356' out of range
	Warning at file './engine/enemmods/move_fanty_asm.h::enems_move::5::136': integer '356' out of range
	Warning at file './engine/enemmods/move_fanty_asm.h::enems_move::5::136': integer '356' out of range
	Warning at file './engine/enemmods/move_fanty_asm.h::enems_move::5::136': integer '-356' out of range
	Warning at file './engine/enemmods/move_fanty_asm.h::enems_move::5::136': integer '356' out of range
	Warning at file './engine/enemmods/move_fanty_asm.h::enems_move::5::136': integer '356' out of range
	Warning at file './engine/enemmods/move_fanty_asm.h::enems_move::5::136': integer '356' out of range
	Warning at file './engine/enemmods/move_fanty_asm.h::enems_move::5::136': integer '-356' out of range
```

Lo miraré en el ensamble generado, quizá esté haciendo el tonto con alguna constante porque ahora esto es 4 bits de precisión y siempre se me olvida... Parece ser `FANTIES_MAX_V`... Que debería ser 64.

Y esto ¡huy!:

```
	Error at file 'engine/hitter_asm.h::hitter_render::0::92' line 25: syntax error
```

Esta es inexplicable... Aunque es posible que sea algo del ensamble, tal y como veo que está generando el código...  Exacto, y ahora encontrarlo va a ser un dolor :D Aunque si esto iba en Ninjajar!, debe ser en la sección específica para la espada.

Te encontrarew - vale, ponía "Or z". Espero que no haya más.

Listo. Hay que ver si funciona, y si eso, ya tendría para hacer el release.

Sale raro y no furula casi na, tendré que arreglarlo. Además me da que este es de los juegos estos que usaban los planos para hacer el fondo, como Leovigildo, y no me acuerdo cómo se obraba el milagro... Voy a ver. OK - esto era con un custom en `draw_scr_background`, que voy a "guardar" tras un define para que se pueda desactivar sin tocar mucho.

```c
	#define CUSTOM_BACKGROUND
```

Y luego pones código en una función `custom_bg ()` dentro de `my/custom_background.h`. Debería documentar esto, o quizá actualizar el PDF mierdoso que hay que no sé cómo hice.

Luego hay miserias:

1.- Supuestamente los enemigos deberían convertirse en murciélagos, pero estos aparecen en (0,0) y no donde deberían.
2.- Habría que usar un gráfico fijo.
3.- Al acabar el nivel hay que sacar los sprites de pantalla.

Ya estamos con las mierdas... Al inicializar los fantis se establece su posición a (x1, y1), en lugar de a (x, y). Debería poner esto configurable con to sus muertos tho.

Más miserias: ahora resulta que hay un backup de enemigos que guarda los tipos y nada más. Cuando te matan los fantis vuelven a ser lineales, pero no se recolocan en su sitio. Y esto es por la mierda de lógica de entrar y salir de pantalla que está hecha con el puto ojete.

Qué me enerva este motor, qué bien que lo abandoné.

Veamos, se hace esto:

- `player_kill`: Como `REENTER_ON_DEATH`, `o_pant` se pone a 99. Esto provoca un reenter. 
- `draw_scr`: Si se ha puesto `no_draw` a 1, no se pinta. Pero no es el caso.
- Se pinta LEVEL XX y se dibuja la pantalla
- Se llama a enems_init, en cualquier caso.

`do_respawn` se pone cuando hay que revivir a los enemigos si `RESPAWN_ON_ENTER` está definido. Supuestamente se pone a 1 siempre, tras salir de `enems_init`, pero se puede poner a 0 desde el script con un "REDRAW".

El tema entonces es, ¿por qué no se reinicializan los lineales a x1? Porque no habrá código para ello. Me queda pendiente mirar cómo se obra el milagro en la versión vieja y ver cómo reintegrarlo.