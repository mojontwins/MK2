MT Engine MK2 v 0.92 (Godkiller Edition 1)
==========================================

Correcciones para volver a hacer funcionar el modo genital normal, arreglos en los controles, y una [pequeña documentación al respecto](https://github.com/mojontwins/MK2/blob/master/docs/settingUpControls.md).

MT Engine MK2 v 0.91 (Greenweb Edition 1)
=========================================

Un millón de arreglos a bugs reportados por Antonio Greenweb y algunas mejoras que no recuerdo.

MT Engine MK2 v 0.90b (Ramiro R Edition)
========================================

Pensaba rehacer Ramiro con lo mínimo, pero estoy haciendo algunas adiciones bastante interesantes. Serán pocas y no es un juego nuevo, así que lo pongo como 0.90b en vez de 0.91. Además, más que nada estoy corrigiendo tela de pequeñas cagadas que he introducido mientras hacía la 0.90 (es genial tener un juego de motor diferente para probar qué has roto con lo que has metido para otro motor), que son un montón.

Cambiar el comportamiento de una posición del mapa desde scripting
------------------------------------------------------------------

A veces pongo títulos tan largos que casi no hace falta descripción... Pues eso mismo. Cambiarle el comportamiento al vuelo a un tile:

```
	SET BEH (x, y) = b
```

#define ENABLE_KILL_SLOWLY
--------------------------

Reintroduce esta característica que metimos en la v4.5 para Ramiro y que desapareció cuando reiniciamos a la 3.1 y ampliamos para sacar la 3.99 [de MK1].

Se trata de que los tiles de tipo 3 quitan energía tras cierto tiempo. Este tiempo se controla con un número de ticks y cuántos frames dura cada tick:

```c
	#define KILL_SLOWLY_GAUGE		T 		// # of ticks before kill
	#define KILL_SLOWLY_FRAMES		F 		// # of frames per tick
```

Además podemos activar o desactivar esto durante la ejecución del juego. Cuando la característica está desactivada, OJETE, los tiles 3 quitan vida al instante. Lo podemos controlar usando el flag que definamos con:

```c
	#define KILL_SLOWLY_ON_FLAG 	N
```

Mejoras para juegos que usen energía en vez de vidas
----------------------------------------------------

Llevamos años tratándolos igual pero cada uno tiene su castaña. Esto lo tengo que pensar bastante mejor porque seguro que puedo refactorizar el código y conseguir ahorros: por lo general, si tu juego va por vidas y cuando te matan sólo pierdes una vida el código es más sencillo.

De todos modos he tenido que meter de forma rápida una pequeña modificación que consideraremos temporal, porque está cogida un poco con pinzas. 

Para Ramiro necesitaba tener la posibilidad de que los enemigos lineales quitasen una cantidad de vida y los voladores una diferente, así que me he limitado a definir eso mismo...

```c
	#define CUSTOM_HIT	
```

Activa la característica de que cada tipo de enemigo quite una cantidad diferente de vida.

```c
	#define PATROLLERS_HIT			X
```

Define cuántos puntos de vida quitan los enemigos lineales.

```c
	#define FANTIES_HIT 			X
```

Define cuántos puntos de vida quitan los enemigos voladores.

Por ahora el resto de los tipos de enemigo (y los pinchos) no están controlados y quitan los puntos de vida que diga `CUSTOM_HIT_DEFAULT`

Adormecer a los fantys
----------------------

Ramiro podía "desactivar" (más bien, "paralizar") a los fantys a golpe de comando de script. Para trasladar la funcionalidad he preferido mapear la bandera a un flag, de forma que no hay que ampliar nada y el intérprete del script no crece.

```c
	#define FANTIES_NUMB_ON_FLAG	F
```

Definiendo esto, el valor del flag F determinará si los fantys se mueven o no. Si vale 0, los fantys no se mueven.

Mejora en la configuración de los efectos de sonido
---------------------------------------------------

El tema del sonido en MK1 / MK2 siempre ha sido un poco coñazo: o te tragabas los sonidos por defecto, o cambiarlos era un puto dolor porque te tenías que hartar de recorrer código arriba y abajo para modificar NÚMEROS. Muy mal. No sé por qué no he cambiado esto antes.

Ahora sólo hay que irse a definitions.h y cambiar esta lista de constantes por los numeritos de tu set de sonidos (los que apliquen, obviamente):

```c
	// Sound effects. Alter here and you are done!
	#define SFX_PUSH_BOX	2
	#define SFX_LOCK		8
	#define SFX_BREAK_WALL	10
	#define SFX_BREAK_WALL_ANIM 10
	#define SFX_SHOOT		9
	#define SFX_KILL_ENEMY	2
	#define SFX_ENEMY_HIT	2
	#define SFX_EXPLOSION	10
	#define SFX_CONTAINER	6
	#define SFX_FO_DRAIN	2
	#define SFX_FO_DESTROY	10
	#define SFX_FO_DROP		2
	#define SFX_FO_GET		2
	#define SFX_JUMP 		1
	#define SFX_JUMP_ALT 	1
	#define SFX_TILE_GET 	5
	#define SFX_HITTER_HIT 	2
	#define SFX_FALL_HOLE 	9
	#define SFX_KS_TICK 	4
	#define SFX_KS_DRAIN 	3
	#define SFX_REFILL 		7
	#define SFX_OBJECT 		6
	#define SFX_KEY 		6
	#define SFX_AMMO		6
	#define SFX_TIME		6
	#define SFX_FUEL		6
	#define SFX_WRONG 		2
	#define SFX_INVENTORY 	2
	#define SFX_PLAYER_DEATH_BOMB 2
	#define SFX_PLAYER_DEATH_COCO 2
	#define SFX_PLAYER_DEATH_ENEMY 2
	#define SFX_PLAYER_DEATH_SPIKE 3
	#define SFX_PLAYER_DEATH_HOLE 10
	#define SFX_PLAYER_DEATH_TIME 2
	#define SFX_PLAYER_DEATH_LAVA 10
	#define SFX_ENDING_LAME_1 2
	#define SFX_ENDING_LAME_2 3
	#define SFX_ENDING_LAME_WIN 6
	#define SFX_ENDING_LAME_LOSE 10
```

Script para pasar de .ene formato antiguo a .ene formato nuevo
--------------------------------------------------------------

Por ahora es muy (demasiado) básico, pero los que me conocéis sabéis que no me suelo rayar más de la cuenta. Ahora mismo hace lo que necesitaba: cambiar los enemigos de tipo (viejo) 1, 2, 3, 4, y 6 en enemigos con el formato nuevo. Los que salían en Ramiro, vaya.

Lo tenéis en /utils/enemsupdater.exe. El código fuente está, como siempre, en  /utils/src, para que lo ampliéis si queréis y lo necesitáis.

MT Engine MK2 v 0.90 (Key To Time Edition)
==========================================

El motor de vista genital está vergonzósamente abandonado en MK2, y nos hemos propuesto ampliarlo y completarlo para que las cosas que hay en el
de vista lateral que hemos ido añadiendo poco a poco desde Ninjajar funcionen también en vista genital. Son muchas cosas, así que:

#define DISABLE_HOTSPOTS
------------------------

Elimina todo el código que inicializa, dibuja y comprueba los hotspots. Se puede liberar entre 600 y 700 bytes así. Si no los usas, es un win.

New Genital
-----------

La vieja vista genital no está demasiado preparada para juegos con perspectiva diédrica (aunque no hemos parado de hacerlos), y ahora que
queremos tener plataformas móviles y saltos necesitamos otro tipo de detección de colisiones diferente.

Tenemos dos cambios:

El viejo "PLAYER_MOGGY_STYLE" es ahora "PLAYER_GENITAL". Usando esta directiva la vista genital será como siempre.

Para activar además la nueva colisión y toda la gaita es  necesario, además, activar

```c
#define PLAYER_NEW_GENITAL
```

Con esta directiva la vista genital se considerará en perspectiva diédrica y será el "cimiento" sobre el que se construirá el motor 2.5D en un futuro.

BOUNDING_BOX_TINY_BOTTOM
------------------------

La caja que controla la colisión con el escenario es de 8x2 si se define esta directiva en lugar de las demás. Funciona mejor con PLAYER_NEW_GENITAL si hay caídas al vacío y cosas así.

USE_TWO_BUTTONS
---------------

Esta directiva se activará automáticamente si el jugador elige vista genital y poder saltar.

Die & Respawn
-------------

Esta función no tiene ningún sentido por sí misma en el motor de vista genital, así que por lo general se ignorará.

Sin embargo, se activará de forma automática si se activa el motor de salto en la vista genital, ya que si se cae a un agujero habrá que reposicionar al personaje.

En vista genital, la posición "segura" se almacenará en dos supuestos:

- El jugador pulsa la tecla de salto.
- El jugador entra en una nueva pantalla *y* está "posado"

Conveyors
---------

En la vista lateral, levantar el bit 5 (OR 32) de un behaviour hacía que el tile fuese una cinta transportadora. La dirección de la cinta la controlaba el bit 1.

En vista genital, esto es algo diferente. El bit 5 sigue activando el comportamiento de cinta transportadora, pero la dirección la controlan los bits 1 y 2, de modo que:

```c
	// C  DD
	// 100000 = 32 = conveyor up
	// 100010 = 34 = conveyor down
	// 100100 = 36 = conveyor left
	// 100110 = 38 = conveyor right
```

La detección de las plataformas móviles se realiza con el pixel central de la fila inferior del cuadro del sprite del protagonista, por lo que
funciona sólo con `PLAYER_NEW_GENITAL`.

Se activan igual que los de vista lateral: 

```c
	#define ENABLE_CONVEYORS
```

Plataformas móviles
-------------------

También para `PLAYER_NEW_GENITAL`. Arrastran igual que los conveyors (por el mismo punto). Las plataformas pueden tener cualquier velocidad y ser verticales, horizontales o incluso diagonales.

Hay que tener cuidado porque si no quieres plataformas en la vista genital hay que #define DISABLE_PLATFORMS ! Esto es diferente a como era antes.

sprite_e
--------

Se añade soporte para ampliar el spriteset a partir de los 16 de siempre. Lo he hecho de forma muy sencilla para dar mucha flexibilidad, pero eso siempre implica algo de trabajo sucio. 

Por lo pronto los voy a emplear para las caídas al vacío y tal.

En 48K: No hay que hacer nada, simplemente tenerlos en sprites.png (debe ser de 256 pixels de ancho, pero ahora puede tener más de 32 de alto para hacer sitio a más sprites) y pasar el número correcto a sprcnv.exe para convertir. Los sprites extra (todas sus columnas y su mierda) se colocan a partir de una etiqueta sprite_e, habrá que calcular a pelo las direcciones reales (cada columna son 48 bytes, cada sprite 144).

En 128K: [aún hay que definir la conversión y ampliar los conversores] se hace sitio tras el spriteset principal en la memoria baja, pero para que el motor sepa cuanto sitio tiene que dejar hay que definir en config.h la nueva directiva

```c
	#define EXTRA_SPRITES 2
```

Donde decimos cuántos hay. Si no vamos a usar, no definimos la directiva.

Caídas al vacío
---------------

Un tile con behaviour 3 en PLAYER_NEW_GENITAL se considera un "vacío" por el que se puede caer (y perder una vida).

Para que el engine los soporte, hay que definir 

```c
	#define ENABLE_HOLES
```

La detección no es inmediata, ocurre con un par de frames de retraso para que el jugador pueda cambiar de plataforma móvil sin morir y sin tener  que saltar.

Se usa dos prames extra que deben estar, en principio, en la dirección apuntada por `FALLING_FRAME` (por ejemplo, `sprite_e`) y `FALLING_FRAME + 144` (o sea, el sprite siguiente)

Saltos genitales
----------------

Si se emplea el modo `PLAYER_NEW_GENITAL` y se activa `PLAYER_HAS_JUMP` el jugador podrá saltar. Este modo activa automáticamente `USE_TWO_BUTTONS` por lo que la tecla de salto es N en el modo principal y [ya veré en el modo para siesos].

Los saltos genitales añaden automáticamente un sprite de 16x8 para la sombra del personaje y por tanto necesitan 7 bloques de sprites más.

La fuerza del salto se controla con las directivas para el salto que se usan en la vista lateral.

AX y RX modificables
--------------------

El Behaviour 64 (bit 6) define un tile como "modificador" de AX y RX. Si el jugador pisa este tile, AX y RX obtienen los valores de las directivas:

```c
	#define PLAYER_AX_ALT			16 
	#define PLAYER_RX_ALT			16 
```

Para que esto funcione hay que activar 

```c
	#define ENABLE_BEH_64
```

en modo `PLAYER_NEW_GENITAL`

Mapa cíclico
------------

`PLAYER_CYCLIC_MAP` invalida `PLAYER_CHECK_MAP_BOUNDARIES`. Ahora, al salirse del mapa, se aparece por el lado contrario. Genial para hacer desiertos como el de K2T :-D

"Subscripts" (o sea, los "niveles" en el script)
------------------------------------------------

Esto no es esencialmente nuevo ya que está disponible desde Ninjajar!, pero ahora es mucho mejor.

Como ya se sabe, en juegos multinivel puedes configurar un script para cada nivel de forma muy sencilla. Pones todos los scripts seguidos en tu archivo de scripts y los separas con `END_OF_LEVEL`.

Al generar el intérprete (en concreto, en el archivo msc-config.h), msc3 crea una serie de constantes con la dirección de inicio de cada uno de los scripts contenidos en el archivo fuente de scripts: SCRIPT_N para el script N-ésimo del archivo.

Esto funciona bien y tal y cual, pero a veces es mejor tener más control y más legibilidad, sobre todo porque los proyectos multi-nivel pueden ser un poco más complejos y es más fácil perder el norte y cometer errores.

Lo que hemos hecho es añadir la posibilidad de nombrar de forma "custom" cada subscript, de forma que controlamos desde el propio fuente del script cómo se llamará la constante que apunte al principio de dicho subscript en el binario. Esto se hace con el comando:

```
LEVELID xxxxx
```

Con "xxxxx" un literal alfanumérico, que colocaremos al principio de cada subscript de nivel (se puede colocar en cualquier sitio, pero mejor ser  ordenados - esto es para hacer más "legible" el tema, en general, así que no lo ofusquemos).

Subtilesets
-----------

Soporte inicial para subtilesets. Son bundles que contienen 16 tiles (64 chars, comprimidos), sus atributos (64 bytes, comprimidos) y su array de  comportamientos (16 bytes, comprimidos). Se usan para sustituir la primera, segunda o tercera tira de tiles de un tileset al vuelo. Pueden cargarse desde un EXTERN o usar el manejador de niveles, etc. 

Con la directiva

```c
	#define ENABLE_SUBTILESETS	
```

Se activa la función "load_subtileset" que podemos llamar desde donde queramos (desde nuestra función de EXTERN o desde modificaciones custom)para cargar un subtileset. Los parámetros son:

```c
	unsigned char load_subtileset (unsigned char res, unsigned char n)
```

Donde "res" es el número de recurso de librarian y "n" es 0, 1 o 2 dependiendo del subtileset que queramos sustituir.

Map Attributes
--------------

Aunque en un futuro se ampliará con más funcionalidades, por el momento se trata de un array de enteros que define qué subtileset se emplea en cada pantalla, con un número de 1 al nº de tilesets que haya. Por el momento, esto sólo puede usarse en juegos multinivel para 128K (la adaptación para juegos de un solo nivel es sencilla, pero habría que hacerla).

El subtileset empleado por esta funcionalidad es siempre el número 1, o sea, los tiles del 16 al 31.

Los arrays se crean en archivos de texto que se pasan a levelbuilder para que los incluya en el binario del juego. Se trata sencillamente de una lista con `MAP_W*MAP_H` valores separados por comas. Cada valor corresponde a una pantalla, en orden de fila. 

A la hora de construir tu juego, en el librarian, deberás añadir los subtilesets justo después del binario del nivel, ya que draw_scr lo que hace  es mirar si necesita un nuevo subtileset y carga el recurso BASE + N, donde BASE es el recurso donde está el nivel y N el número que aparece en el array de atributos.

Para ahorrar espacio, lo mejor es que el archivo png con los tiles que uses para crear el binario de tu fase tenga los tiles del 16 a 31 en negro. Así ahorrarás espacio porque comprimirá mejor y no estarás almacenando duplicados.

Si empleas esta funcionalidad, los niveles que no necesiten cambiar el subtileset 1 deberán estar organizados de la misma manera: binario del nivel y binario del único subtileset justo después.

nosoundplayer.h
---------------

Soy muy tonto y me da rabia usar temporalmente músicas y sonidos del juego anterior en el nuevo (hablo de 128K). He creado este nuevo "driver" que no hace nada, así el juego estará calladito hasta que el músico haga su trabajo.

Para activar, pon un #define NO_SOUND en config.h, esto invalida todo lo demás. (en modo 128K)

PIXEL_SHIFT
-----------

Sirve para los juegos de perspectina "New Genital". Hace que los sprites de los  enemigos lineales que no sean plataformas se pinten (y detecten) N pixels más arriba. Así podemos hacer, si nos conviene, que enemigos que se muevan siguiendo trayectorias horizontales caminen "por el centro" del tile y no alineados a  este, con lo que la "sensación de profundidad" es mucho mejor.

Por ejemplo...

```c
	#define PIXEL_SHIFT					8
```

SET_FIRE_ZONE_TILES
-------------------

Para que sea más coñazo programar el script, he introducido `SET_FIRE_ZONE_TILES`, donde los parámetros indican un rango en coordenadas de tiles en vez de en píxels. msc3 lo convertirá a un `SET_FIRE_ZONE` normal internamente para que no tengamos que estar haciendo cálculos.

PLAYER_IN_X_TILES / PLAYER_IN_Y_TILES
-------------------------------------

Como el anterior. Internamente se convierten en PLAYER_IN_X y PLAYER_IN_Y de forma automática, para no tener que andar calculando.

Macros tontos en msc3
---------------------

Básicamente consiste en definir alias para sustituir una linea completa de código que se use mucho. Se definen en la sección DEFALIAS y emplean el % como identificador. Por ejemplo, imagina que usas un motón

```
	EXTERN 0, 0
```

Para borrar la pantalla. Pero un montón. Pues es mejor (y queda más legible) hacer esto en tu DEFALIAS:

```
	DEFALIAS
	    ... (cosas)
	    %CLS EXTERN 0, 0
	END
```

Y entonces, en vez de EXTERN 0, 0, podrás poner en tu código, simplemente:

```
	%CLS
```

Y poco más. Esto puede venir genial porque así podemos darle nombre a los diferentes EXTERN que tengamos y que sean específicos. No es que sea demasiado potente, pero en un futuro intentaré ver cómo parametrizarlo para ya partir la pana del todo.

MT Engine MK2 v 0.89 (Nicanor Edition)
======================================

Esta versión corresponde al juego "Nicanor el Profanador". Incluye una nueva versión de msc3, la 3.92

Scripting más fácil con Alias
-----------------------------

A partir de la versión 3.92 de msc3, puedes obviar la palabra FLAG si usas alias. O sea, que el compilador aceptará

```
SET $LLAVE = 1
```

y también 

```
IF $LLAVE = 1
```

Safe Spot
---------

Si defines #define `DIE_AND_RESPAWN` en config.h, el jugador, al morir, va a reaparecer en el "último punto seguro". Si DIE_AND_RESPAWN está activo, el motor salva la posición (pantalla, x, y) cada vez que nos posamos sobre un tile no traspasable (que no sea un "floating object").

Podemos controlar la definición del "punto seguro" (safe spot) desde nuestro script. Si decidimos hacer esto (por ejemplo, para definir un "checkpoint" de forma manual), es conveniente desactivar que el motor almacene el safe spot de forma automática con:

```c
#define DISABLE_AUTO_SAFE_SPOT
```

Hagamos o no hagamos esto, podemos definir el safe spot desde el script con estos dos comandos:

```
SET SAFE HERE			Establece el "safe spot" a la posición actual del
						jugador.
						
SET SAFE n, x, y		Establece el "safe spot" a la pantalla n en las 
						coordenadas (de tile) (x, y).
```


MT Engine MK2 v 0.88c
=====================

OJO: A partir de esta versión el módulo clásico de manejo de enemigos (`#define USE_OLD_ENEMS`) dejará de estar soportado y dejará de mantenerse. Seguirá ahí, pero es probable que haya muchas cosas que dejen de funcionar. No debe usarse.

TODO: Escribir una aplicación que cambie un archivo .ene del formato viejo al formato nuevo, por si se quiere hacer algún otro rehash de un juego viejo de la Churrera.

Esta versión integra algunas mejoras en el scripting, como las cadenas de decoraciones (ver más abajo) o la espada de Sir Ababol como tipo de HITTER.

No hay juego con esto, pero sí la demo Espadewr.

Decoraciones
------------

Básicamente es hacer lo de engine/extraprints.h pero desde el script. Hasta ahora decorábamos las pantallas con tiles extra poniendo ristras de `SET TILE (x, y) = t`. Eso es un coñazo de escribir y mantener y además ocupaba 4 bytes por tile.

Ahora podemos definir ristras de tiles en las que todo el conjunto de tiles ocupará `2*n+2`, donde n es el número de tiles. Una buena mejora frente a la original, que ocupaba 4*n bytes.

El tema es así: basta con incluir esto en el `ENTERING_SCREEN` (o en cualquier sitio que admita comandos: esto sirve para cambiar buenos trozos de la pantalla desde el script y puede venir genial para implementar puzzles chulos que modifiquen el escenario:

```
	IF TRUE
	THEN
		DECORATIONS
			x, y, t
			x, y, t
			...
		END
	END
```

Cada linea x, y, t define la posición y el número de un tile extra de decoración. Podéis poner todos los que queráis. 

Esto sirve para ahorrar mucha memoria y tener pantallas bien decoradas. Generalmente NO necesitáis los 48 tiles de un tileset extendido a la vez. Siempre hay un grupo de tiles que se repite más. La idea es establecer ese set de tiles como tileset principal (0-15) y colocar los demás como decoraciones.

Además, el nuevo map2bin se encarga de detectarlos automáticamente y de generar las lineas de script necesarias.

REENTER, REDRAW, REHASH
-----------------------

REDRAW ha sido rediseñado para funcionar mejor y más rápidamente. Redibuja de nuevo la pantalla desde el buffer, y esto incluye todo lo que le hayamos colocado antes con SET TILE (x, y) = t.

REHASH vuelve a entrar en la pantalla para, entre otras cosas, inicializar los enemigos. Es necesario si se cambia un enemigo de tipo lineal a tipo volador, ya que hay que inicializar algunas variables.

REENTER, como siempre: es REDRAW + REHASH.

Cambiar enemigos y backup de enemigos
-------------------------------------

Además de apagarlos y encenderlos (Ninjajar!), ahora podemos cambiar el tipo de los enemigos. El tipo contiene si dispara o no, qué patrón de movimiento sigue, y qué sprite tiene. 

```
ENEMY n TYPE t			Establece el tipo "t" para el enemigo "n".
```

Sin embargo hay que tener en cuenta que esto es destructivo: si cambiarmos el tipo de un enemigo, el tipo original se perderá para siempre.

En juegos multinivel esto no es ningún problema porque con descomprimir de nuevo el nivel vamos listos.

Para juegos de un solo nivel, hemos introducido un "backup de enemigos" que podemos activar desde config.h usando:

```
	#define ENEMY_BACKUP
```

El backup ocupa 3 bytes por pantalla y guarda el tipo original de todos los enemigos. 

Desde scripting, podemos hacer:

```
ENEMIES RESTORE			Restablece a sus valores originales los enemigos de
						la pantalla actual.
	
ENEMIES RESTORE ALL		Restaura el tipo de TODOS los enemigos del nivel.
```

Si sólo necesitas restaurarlos al empezar cada partida, puedes pasar de usar `ENEMIES RESTORE ALL` en el script y activar la directiva `RESTORE_ON_INIT` en config.h


Espada
------

Hemos añadido la espada de Sir Ababol 2 como nuevo tipo de hitter (internamente). Por el momento, no es posible disponer de puño y espada en el mismo juego, aunque ya haremos algo para posibilitarlo en un futuro.

```c
	#define PLAYER_HAZ_SWORD
```

El gráfico de la pantalla se define donde todos los demás: en extrasprites.h


Más cosas
---------

Hemos cambiado de todo pero ahora me falla la memoria... A ver, cosas miscelaneas que sí recuerdo:

```c
	#define PLAYER_WRAP_AROUND
```

Hay que usarlo sólo si se ha definido `#define PLAYER_CANNOT_FLICK_SCREEN`. Con ambas activas, además de no poder salir de la pantalla, si nos acercamos a un extremo lateral saldremos por el contrario. COMO UWOL ILLO!


MT Engine MK2 v 0.88
====================

Edicioón Leovigildo F. WTF? Es un puto HUEVO DE PASCUA, pero he ampliado el motor en varias direcciones. Algunas pueden ser útiles para otros juegos, y otras no. A ver si me acuerdo de todo:


Cosas de scripting sin scripting
--------------------------------

Son cosas que se pueden hacer con scripting, pero al ser sencillas y poder almacenarse los tiestos en un array, si sólo ibas a usar scripting para esto, así te lo ahorras y te caben más cosas. A saber:

**engine/levelnames.h**

Permite ponerle un nombre a cada pantalla. Los nombres tienen que tener una longitud fija y definirse todos en una misma cadena, todos seguidos y en orden. Puedes verlo en el propio levelnames.h, donde también puedes configurar ubicación y color y tal. Para activarlo:

```c
	#define ENABLE_LEVEL_NAMES
```

**engine/extraprints.h**

Permite definir impresiones de tiles extra para cada pantalla. Hay mucha gente que ha usado scripting únicamente para esto (lo que me parece una  pena, si me preguntan). Ahora no hace falta activar el scripting, el  código ocupa muy poco y cada impresión únicamente 2 bytes. Para activarlo: 

```c
#define ENABLE_EXTRA_PRINTS
```

Para establecer qué se imprimirá, hay que editar extraprints.h. Ahí se define un array por cada pantalla con prints extra. Cada print extra se compone de 2 bytes: "xy" y "tile". "xy" usa 4 bits para X y 4 para Y. Es muy fácil de gestionar en hexadecimal, "x" va de 0 a F e "y" de 0 a 9. El byte "tile" es simplemente el número de tile. La lista se acaba con un  0xff (valor 255).

Por ejemplo, para imprimir un tile 17 en la posición X=10, Y=2, los dos bytes serían 0xA2, 17. Para imprimir un tile 33 en la posición X=5, Y=7 los dos bytes serían 0x57, 33.

Por último, hay otro array *prints con una entrada por cada pantalla del mapa. Si en una pantalla no hay prints extra, se pone un 0. Si sí que  los hay, se pone el array de prints de la pantalla correspondiente.

**engine/sim.h**

SIM significa "Simple Item Manager", y sirve para manejar items e inventario sin necesitar scripting para juegos sencillos en los que haya X objetos en Y contenedores por todo el mapa, y el juego se termine cuando los X objetos se han colocado en otros sitios. Sin más.

```c
	#define ENABLE_SIM
```

Activará el SIM. Esto meterá código redundante con el sistema de scripting, por lo que ambos sistemas NO SON COMPATIBLES. Si usas scripting, maneja tus objetos a mano.

El SIM tiene unas cuantas directivas para configurarlo:

```c
	// General
	#define SIM_MAXCONTAINERS		6
	#define SIM_DOWN
	//#define SIM_KEY_M
	//#define SIM_KEY_FIRE
```

La primera, `SIM_MAXCONTAINERS`, define el máximo número de contenedores (que no de objetos) que habrá en el juego. Un contenedor puede estar vacío o contener un objeto. Juegos en los que haya que poner tres  objetos en otros tres sitios diferentes, por ejemplo, necesitarán seis contenedores: los 3 que contendrán a los objetos, y 3 vacíos con el "destino final".

Las tres siguientes, definen qué tecla se usa para interactuar (coger/dejar objeto). Respectivamente, abajo, M o FIRE. Define sólo una, como con el scripting.

Un componente del SIM es el inventario. El inventario es exactamente el mismo que te sale cuando usas scripting y lo defines en tu script. Se configura con las siguientes directivas:

```c
	// Display:
	#define SIM_DISPLAY_HORIZONTAL
	#define SIM_DISPLAY_MAXITEMS	2
	#define SIM_DISPLAY_X			24
	#define SIM_DISPLAY_Y			21
	#define SIM_DISPLAY_ITEM_EMPTY	31
	#define SIM_DISPLAY_ITEM_STEP	3
	#define SIM_DISPLAY_SEL_C		66
	#define SIM_DISPLAY_SEL_CHAR1	62
	#define SIM_DISPLAY_SEL_CHAR2	63
```

Si se define `SIM_DISPLAY_HORIZONTAL`, el inventario se mostrará en una linea horizontal. Si no se define, se mostrará en una linea vertical.

`SIM_DISPLAY_MAXITEMS` define el número de slots del inventario.

`SIM_DISPLAY_X` y `SIM_DISPLAY_Y` indican la coordenada de la pantalla donde se mostrará el inventario. `SIM_DISPLAY_ITEM_STEP` define cada cuántas celdas de carácter se dibujará un nuevo slot a partir de las coordenadas iniciales.

`SIM_DISPLAY_ITEM_EMPTY` especifica qué tile representa el slot vacío.

`SIM_DISPLAY_SEL_C` especifica el color del selector, y `SIM_DISPLAY_SEL_CHAR1` y `SIM_DISPLAY_SEL_CHAR2` qué dos carácteres de tu charset utilizar para dibujarlo.

Una vez definido todo esto, tendremos que abrir engine/sim.h para terminar de configurar nuestro juego.

En sim.h se definen dos arrays: `sim_initial` y `sim_final`. El primero define la ubicación de los contenedores en el mapa y su contenido inicial; el  segundo define un estado final que hará que ganemos el juego si se alcanza.

`sim_initial` es un array de estructuras. Se define una entrada por cada container del juego (en total, `SIM_MAXCONTAINERS` entradas). Cada entrada tiene un formato `{n_pant, XY, tile}`, donde `n_pant` es la pantalla donde se encuentra, XY son las coordenadas (4 bits X, 4 bits Y, como en extraprints) y tile es el tile que representa al objeto contenido en el container al principio del juego.

Por ejemplo `{10, 0x54, 32}` hará que en la pantalla 10 haya un container en la posición X=5, Y=4, que tenga inicialmente el objeto 32.

`{3, 0xB3, 0}` hará que en la pantalla 3, en la posición X=11, Y=3, haya un container vacío.

`sim_final` es un array de números. Simplemente especifica qué item debe haber en cada container para terminar el juego. 

Por ejemplo, imaginemos un juego tonto donde hay un objeto en la pantalla 0 y otro en la pantalla 1, y hay que intercambiarlos para ganar. Los objetos aparecerán ambos en X=7, Y=4, y se representarán con los tiles 20 y 21.

En ese caso, `SIM_MAXCONTAINERS` valdría 2 y nuestros arrays serían:

```c
	SIM_CONTAINER sim_initial [SIM_MAXCONTAINERS] = {
		{0, 0x74, 20},
		{1, 0x74, 21}
	};

	unsigned char sim_final [SIM_MAXCONTAINERS] = {21, 20};
```

Tan sencillo como esto. Al principio, los contenedores contienen los objetos 20 y 21, y al final deben contener los objetos 21 y 20.

NOTA IMPORTANTE: SIM necesita que activemos los Floating Objects de tipo contenedor en config.h

```c
	#define ENABLE_FO_OBJECT_CONTAINERS
```

Además: si no has enredado debería estar igual, pero asegúrate de todos modos que el valor de `FT_FLAG_SLOT` en config.h y de `FLAG_SLOT_SELECTED` en sim.h se corresponden. Parece guarrero, pero está así para posibles futuras ampliaciones.


Mejoras en el JETPAC
--------------------

El Jetpac se nos ocurrió en la Churrera 1.0 y lo programamos, pero sin probar. No lo usamos hasta la Churrera 3.1, cuando hicimos Cheril the Goddess, y era muy rawro. Luego lo usamos en Jet Paco. 

Desde el principio habíamos pensado en darle chicha con recargas, fuel que se acaba, y cosas asín, pero hasta AHORA no se ha hecho.

```c
	#define PLAYER_HAS_JETPAC            	
	#define JETPAC_DEPLETES				4	
	#define JETPAC_FUEL_INITIAL			25	
	#define JETPAC_FUEL_MAX				25	
	#define JETPAC_AUTO_REFILLS			2
	//#define JETPAC_REFILLS				
	//#define JETPAC_FUEL_REFILL		25	
```

`PLAYER_HAS_JETPAC`, de toda la vida, activa este sistema. Si sólo defines esto, tendrás un jetpac como en jetpaco. Guay.

Si activas `JETPAC_DEPLETES` con valor "X", el jetpac tendrá fuel que se irá agotando cada X frames, con X una potencia de 2 (2, 4, 8, 16...).  Teniendo esto activo, podemos definir más comportamientos.

`JETPAC_FUEL_INITIAL` y `JETPAC_FUEL_MAX` son necesarias en todo caso si activas `JETPAC_DEPLETES`. Especifican el valor de fuel al principio del juego y el valor máximo que se puede alcanzar.

Con esto hemos conseguido que el fuel se gaste. Ahora hay que decidir cómo recuperarlo:

Si activas `JETPAC_AUTO_REFILLS` con valor "Y", el jetpac se recargará sólo cuando no se esté usando, cada Y frames, con Y una potencia de 2.

Si, en cambio, activas `JETPAC_REFILLS`, aparecerán recargas que se colocan como hotspots de tipo 6 en el colocador. Cada recarga recargará el número de unidades especificado en `JETPAC_FUEL_REFILL`.


Whoa
----

Sí, eso digo yo. Para un easter egg. Además he corregido unos cuantos bugs que he visto por ahí y he limpiado algunas cosillas.


MT Engine MK2 v 0.87
====================

Edición Leovigildo III. Tiene pocas cosas puramente nuevas, pero trae un porrón de mejoras internas, arreglos de bugs, optimizaciones...

El módulo nuevo de enemigos.
----------------------------

Para usarlo, asegúrate de comentar `#define USE_OLD_ENEMS`.

Ahora los enemigos son mucho más flexibles. Cada uno define varias cosas:

- Qué sprite usa, de 0 a 3.
- Qué tipo de movimiento lleva: lineal, volador...
- Si dispara o no.

Además está preparado para que sea muy fácil meter más comportamientos.

Todo se especifica en el tipo de enemigo, que se divide en varios campos a nivel de bits:

```
	76543210
	XBBBBFSS
```

Donde:

- X está reservado para marcar si un enemigo está muelto.
- BBBB es el tipo de movimiento. Por ahora hay implementados estos:

```
0001 (1) - lineal de ida y vuelta, como siempre.
0010 (2) - volador. Como los fantys tipo 6. 
0011 (3) - perseguidor. Los coñazo tipo 7 de siempre.
1000 (8) - plataforma móvil. Como "1" pero plataforma móvil.
```

Ojete! Si usas tipo 2, tienes que activar ENABLE_FLYING_ENEMIES. Si 
usas tipo 3, activa ENABLE_PURSUE_ENEMIES.

- F es si dispara (1) o no (0). Si lo activas para algún enemigo, acuérdate de que tienes que activar `ENABLE_SHOOTERS` y configurar `MAX_COCOS` y otras cosas.

- SS es el número de sprite, según spriteset, de 0 a 3 (00, 01, 10, 11).

El "tipo" de enemigo se calcula, por tanto, usando esta fórmula tonter:

S + 4 * F + 8 * B, donde S es el sprite, F si dispara, y B el comportamiento

Para colocarlos puedes calcular tú el valor del tipo de enemigo usando la fórmula de arriba (es binario) o usar el Colocador MK2 que hay  en /enems, donde puedes poner los valores por separado. Lo que te pete.

Modificaciones a los floating objects
-------------------------------------

- Ahora se puede controlar mejor su comportamiento con respecto a la gravedad - por si queremos usarlos en juegos de vista genital, más que nada:

```c
	#define FO_GRAVITY
	#define FO_SOLID_FLOOR	
```

Activando la primera, los FO se caen si no hay suelo debajo. Con la segunda, se pararán al llegar a la firla inferior de la pantalla en lugar de desaparecer.

- Los FO "matan" mientras los llevas a cuestas. Esto es por la tontería de este juego, no sé si servirá para algo más... De todos modos no me  costaba ponerlo en el config en vez de una paranoia custom...

```c
	#define CARRIABLE_BOXES_DRAIN		7
```

- Corchonetas. Los FO pueden ser corchonetas. Si caes sobre ellos, rebotarás. Puedes definir el máximo de velocidad rebotante.

```c
	#define CARRIABLE_BOXES_CORCHONETA	
	#define CARRIABLE_BOXES_MAX_C_VY	1024	
```

Para que esto funcione tienes que darle el comportamiento "rebotante" al tile que represente la corchoneta. Esto significa que en una futura versión podemos usar tiles rebotantes que no sean FO, sólo definiendo el comportamiento... Creo.

```c
	// 0 = Walkable (no action)
	// 1 = Walkable and kills.
	// 2 = Walkable and hides.
	// 4 = Platform (only stops player if falling on it)
	// 8 = Full obstacle (blocks player from all directions)
	// 10 = special obstacle (pushing blocks OR locks!)
	// 16 = Breakable (#ifdef BREAKABLE_WALLS)
	// 32 = Conveyor 
	// 64 = CUSTOM F.O. -> CORCHONETA!
```

- Scripting FO

Esto puede servir para muchas cosas pero hay que usarlo con cuidado. Se emplea en Leovigildo III para detectar que le tiramos una corchoneta en la cabeza al domador.

Básicamente, si se activa, cuando un FO "cae", se almacena su tipo y posición en tres flags (configurables) y se llama a PRESS_FIRE en el script de esa pantalla.

```c
	#define ENABLE_FO_SCRIPTING			
	#define FO_X_FLAG					1
	#define FO_Y_FLAG					2
	#define FO_T_FLAG					3	
```

Esto empieza a dar mucho miedo. Ya daba miedo en Ninjajar. Ahora es aterrador.


MT Engine MK2 v 0.86
====================

Edición "Phantomas Engine". Ahora se puede hacer juegos de Phantomas - esto abre la posibilidad de añadir muy fácilmente más motores de movimiento puramente lineales (sin inercia).

```c
	// Phantomas Engine
	// ----------------
	// Coment everything here for normal engine
	#define PHANTOMAS_ENGINE 		1		// Which phantomas engine:
											// 1 = Phantomas 1
											// 2 = Phantomas 2
											// 3 = LOKOsoft Phantomas
											// 4 = Abu Simbel Profanation
											
	#define PHANTOMAS_FALLING 		4		// Falling speed (pixels/frame)
	#define PHANTOMAS_WALK			2		// Walking speed

	#define PHANTOMAS_INCR_1		2		// Used for jumping
	#define PHANTOMAS_INCR_2		4
	#define PHANTOMAS_JUMP_CTR		16		// Total jumping steps up&down


	// Most things from now on won't apply if PHANTOMAS_ENGINE is on...
	// Try... And if you need something, just ask us... Maybe it's possible to add.

	// For example, BOUNDING_BOX_8_BOTTOM works for PHANTOMAS/PROFANANTION engines.
```

Es sencillo (o no). Hay cuatro tipos de motor, como se ve en el código. Luego hay parámetros de configuración.

Tal y como está, seleccionando el motor 1 el movimiento será como en Phantomas 1, el motor 2 lo hará como Phantomas 2, y el motor 4 como Abu Simbel Profanation... Pero jugando con los valores conseguirás otras cosas.

Los motores 1, 2 y 4 se basan en que hay dos tipos de saltos. En el motor 1 tenemos salto alto (2 tiles de alto, 1 de ancho) y salto largo (1 tile de alto, 4 de ancho). En el motor 2 tenemos salto largo (algo más de 2 tiles de alto, 2 tiles de ancho) y corto (1 tile x 1 tile), y además podemos cambiar la dirección del salto en medio del aire. En el motor 4 tenemos saltos igual que en el motor 2, pero no se puede cambiar la dirección y además si pulsamos sólo salto el muñeco saltará para arribá (es necesario pulsar salto + izq. o der. para saltar lateralmente).

Además hemos aprovechado para añadir soporte para enemigos 100% custom al módulo de enemigos, y hemos incluido un par como "addons": gotas y  flechas, que utilizan sus propios sprites. Además, hay una nueva utilidad para convertir sprites para estos tejemanejes. 

```c
	#define ENABLE_DROPS					// Enemy type 9 = drops
	#define ENABLE_ARROWS					// Enemy type 10 = arrows
```

Estos enemigos se colocan con el colocador. Mira los archivos

```
	\dev\addons\drops\move.h 
	\dev\addons\arros\move.h
```

para ver cómo se especifican sus valores. 

Lo mejor es que si quieres usar esto nos pongas un mensajito o algo pidiendo el microjuego de ejemplo donde se ve todo en acción. Es que no creo que lo vayamos a sacar así por las buenas, no tengo tiempo ni energías.


MT Engine MK2 v 0.85
====================

Cambios y añadidos para la segunda carga de Leovigildo. Son un montón, a ver si me acuerdo:

- Se puede lanzar las cajas CARRIABLE_BOXES pulsando FIRE. Las cajas matan los bichos y los cuentan en un flag:

```c
	#define CARRIABLE_BOXES_THROWABLE
	#define CARRIABLE_BOXES_COUNT_KILLS 2
```

- Modo mono-pantalla. Sólo se puede cambiar de pantalla por scripting, no se detecta el cambio de pantallas de toda la vida cuando el niño se pega al borde. Esto sirve para hacer juegos de pantalla en pantalla.

```c
	#define PLAYER_CANNOT_FLICK_SCREEN	
```

- Contar cuántos bichos hay en la pantalla y meterlos en un flag. Para hacer güegos de "mátalos todos para pasar" o cosas por el estilo, del palo "si matas todos los bichos pasa algo".

```c
	#define COUNT_SCR_ENEMS_ON_FLAG	1	
```

- Cada vez que se cambia de pantalla, mostrar el número de pantalla +1 en plan número de nivel. Para juegos pantalla-a-pantalla.

```c
	#define SHOW_LEVEL_ON_SCREEN		
```

- Vamos a cambiar el módulo de enemigos, así que nos vamos preparando. Como el módulo viejo no lo voy a borrar, puedes seguir usándolo si especificas

```c
	#define USE_OLD_ENEMS				
```

- Desactivar plataformas móviles en juegos de plataformas. Ahora puedes tener cuatro enemigos diferentes. 

```c
	#define DISABLE_PLATFORMS			
```

- Enemigos resucitan al entrar en la pantalla. Vale, esto ya estaba, pero ahora tiene algunos cambios:

```c
#define RESPAWN_ON_ENTER		
#define RESPAWN_ON_REENTER		
```

Si activas la primera, al entrar con el muñeco en una pantalla los enemigos volverán a la vida. 
	
Si activas, además, la segunda, los enemigos volverán a la vida también tras el comando REENTER en el script.

- Hemos mejorado un montón de cosas, entre ellas el timer, que estaba algo roto (todavía quedarán muchas cosas de la Churrera que estén rotas, vamos poco a poco).


MT Engine MK2 v 0.8
===================

Hemos reescrito el motor casi entero. Aún falta el módulo de enemigos, que queremos reorganizar. Por eso aún no estamos en la 1.0.

El nuevo motor funciona prácticamente igual que la Churrera 3.X, pero funciona más rápido y ocupa menos memoria. Además hay un montón de cosas nuevas, como los "hitters" de Ninjajar (por ahora para dar hostias, pero pronto para hacer espadas), mejor soporte multi-fase en el scripting, poder saltar de una fase a otra, motor de items mejorado...

Floating Objects
================

```c
	#define ENABLE_FLOATING_OBJECTS
```

Son tiles interactuables que no forman parte del mapa. Se colocan desde el script. Por ahora el motor puede manejar dos tipos.

Los floating objects se colocan en cada pantalla desde el script:

```
	ADD_FLOATING_OBJECT t, x, y
```

- Carriable boxes

```c
	#define ENABLE_FO_CARRIABLE_BOXES
	#define CARRIABLE_BOXES_ALTER_JUMP 180
	#define FT_CARRIABLE_BOXES			16
```

Son cajas que se pueden transportar. Necesita que reservemos 10 bloques de sprites más (ver main.c, al principio) para un sprite extra. Las cajas se cogen y depositan pulsando ABAJO. Las cajas se ven afectadas por la gravedad y se apilan unas a otras. 

Puedes definir el tile que usan con la directiva FT_CARRIABLE_BOXES. Los objetos emplean el comportamiento definido para este tile. Será el valor que hay que darle a "t" a la hora de colocarlos desde el script, por ejemplo para poner una de estas cajas en la posición 7, 8 habiendo definido que su tile es el 16 hacemos:

```
	ADD_FLOATING_OBJECT 16, 7, 8
```

Si defines `CARRIABLE_BOXES_ALTER_JUMP`, el valor máximo de la velocidad de salto se cambiará por el valor especificado cuando llevemos una caja.

- Item containers

```c
	#define ENABLE_FO_OBJECT_CONTAINERS		
	#define FT_FLAG_SLOT				30	
```

Estos están pensados para ser usados con el motor de inventario del scripting. Cada contenedor en realidad representa un flag del sistema de scripting. Al pintar la pantalla se pintará el tile cuyo número esté almacenado en el flag correspondiente.

Para crearlos desde el scripting:

```
	ADD_FLOATING_OBJECT 128 + f, x, y
```

Donde f es el flag que queremos representar. Por ejemplo, si vamos a usar el flag 10 para representar un contenedor en la posición 4, 4 de la pantalla, deberíamos crearlo así:

```
	ADD_FLOATING_OBJECT 138, 4, 4
```

Como esto es un poco confuso, hemos añadido un alias. Lo mismo puede hacerse
llamando a:

```
	ADD_CONTAINER f, x, y
```

El ejemplo anterior sería:

```
	ADD_CONTAINER 10, 4, 4
```

El motor reacciona a estos bloques intercambiando el objeto seleccionado del
inventario con el que haya en el contenedor.

Alias en el script
==================

Porque haciendo Ninjajar nos quisimos volver locos con tanto flag, hemos
añadido alias. Definimos un bloque al principio del script así:

```
	DEFALIAS
		$ALIAS N
		...
	END
```

A partir de entonces, podemos sustituir "N" por "$ALIAS". Por ejemplo, si
usamos el flag 2 para abrir una puerta verde y el flag 3 para ver si hemos
hablado con el ogro hacemos:

```
	DEFALIAS
		$PUERTA_VERDE 2
		$HABLA_OGRO 3
	END
```

En el script podemos usar los alias en vez del numerico:

```
	...
    IF FLAG $HABLA_OGRO = 0
    THEN
        EXTERN 10
        SET FLAG $HABLA_OGRO = 1
    END
	...
```


3.99.3c
=======

```c
#define PLAYER_CAN_FIRE_FLAG   1
```

Si se define, el flag indicado controla si el jugador puede (1) o no (0)  disparar.

MOTOR DE ITEMS
--------------

Queremos conseguir que pueda haber un pequeño inventario en pantalla y poder seleccionar un objeto de él, y además queremos que los objetos que compongan el inventario no sean fijos y que podamos saber, desde el script, qué objeto hay seleccionado.

- En una sección inicial del script, vamos a definir "el itemset" (hay que ponerle nombres a las cosas, aunque sean nombres tan chungos como este): cuantos espacios tiene, dónde se colocan, y como se distribuyen los objetos. Algo así:

```
	ITEMSET
	   # Número de huecos:
	   SIZE 3
	   
	   # Posición x, y
	   LOCATION 2, 21
	   
	   # Horizonta/vertical, espaciado
	   DISPOSITION HORZ, 3
	   
	   # Color y caracteres para pintar el selector
	   SELECTOR 66, 82, 83
	   
	   # (si se define) qué tile representa el tile vacío
	   EMPTY 31
	   
	   # Flag que contiene qué hueco está seleccionado
	   SLOT_FLAG 14
	   
	   # Flag que contiene qué objeto está en el hueco seleccionado
	   ITEM_FLAG 15
	END
```

- Un objeto se representa por su tile. Si tenemos una corona en el tile 10, el objeto corona será el 10. Si en un hueco del inventario está el 10, significa que en ese hueco está la corona. El valor 0 siempre representará un hueco vacío. Esto simplifica el código una barbaridad.

- En el script habrá cambios. ITEM n = t significa que en el hueco "n" está el objeto representado por el tile t. Definimos, pues, las siguientes condiciones:

```
	IF ITEM n = t
	IF ITEM n <> t
```

Comprueban que en el espacio "n" está o no el objeto de tile "t".

```
	IF SEL_ITEM = t
```

Comprueba que en el espacio seleccionado por el selector está el objeto de  tile "t"

Y los siguientes comandos:

```
	SET ITEM n = t
```

Establece en el hueco n el tile t. Obviamente, para quitar un objeto del hueco n, pondremos un 0.

Hay una limitación, por tanto, en el número de objetos que puede llevar el personaje a la vez. Con un poco de cabeza, como he dicho, se puede gestionar esto muy bien, y con un mínimo de código añadido al motor tenemos una herramienta bastante potente. Todo esto hay que combinarlo con los flags para tener funcionalidad completa. Con los ITEMs solo podemos saber si tenemos o no un ITEM en el inventario, pero no si se ha usado ya. Para eso necesitamos los flags.

¿Cómo se usa esto? Pongamos un ejemplo.

Imaginad que en la pantalla 6 tenemos un objeto "corona", representado por el tile 33, y lo tenemos en (7, 7). Además, el flag que indica su estado es el 3, que valdrá 0 cuando aún no lo hayamos cogido ni nada, para pintarlo en la pantalla.

```
	ENTERING SCREEN 6
	    IF FLAG 3 = 0
	    THEN
	        SET TILE (7, 7) = 33
	    END
	END
```

Vamos a gestionar el hecho de cogerlo. Podemos hacerlo en modo básico o en modo virguero. Veamos el modo básico primero. En el modo básico asignamos "a mano" un hueco fijo para cada item. La corona la colocaremos en el hueco 2:

```
	PRESS_FIRE AT SCREEN 6
	    IF PLAYER_TOUCHES (7, 7)
	    IF FLAG 3 = 0
	    THEN
	        SET FLAG 3 = 1
	        SET TILE (7, 7) = 0
	        SET ITEM 2 = 33
	    END
	END
```

El juego con el flag 3 es simplemente para que no vuelva a dibujarse. Cuando el flag 3 valga 1 no se volverá a pintar el objeto al volver a entrar en la pantalla, ni intentaremos cogerlo de nuevo. Por lo demás, lo que se hace es hacer que en el hueco 2 esté el objeto 33.

Imaginad que en la pantalla 12 tenemos que usarlo en la coordenada 5, 8. Pues habrá que comprobar que el item seleccionado es el 33:

```
	PRESS_FIRE AT SCREEN 12
	    IF SEL_ITEM = 33
	    THEN
	        SET ITEM 2 = 0
	        # mas cosas
	    END
	END
```

Si el objeto seleccionado es el 33 (que sólo podrá ocurrir si antes lo colocamos en el hueco 2), lo quitamos del inventario (poniendo un 0 en el slot 2) y luego hacemos más cosas.

El modo virugero es que el objeto vaya al hueco seleccionado. Para eso usamos la indirección que permite el motor de scripting con el operador #. Recordad que estamos usando el flag 10 para representar el hueco seleccionado. Juguemos con eso. Además, habrá que comprobar que el hueco está libre!

```
	PRESS_FIRE AT SCREEN 6
	    IF PLAYER_TOUCHES (7, 7)
	    IF FLAG 3 = 0
	    IF FLAG 10 <> 0
	    THEN
	        # Mal! el hueco no está libre!
	        SOUND 2
	    END

	    IF PLAYER_TOUCHES (7, 7)
	    IF FLAG 3 = 0
	    IF FLAG 10 = 0
	    THEN
	        SET FLAG 3 = 1
	        SET TILE (7, 7) = 0
	        SET ITEM #10 = 33
	    END
	END
```

¿Qué hacemos? Pues colocar el objeto de tile 33 (nuestra corona) en el espacio seleccionado, que no es más que el que está almacenado en el flag 10 (recordad que #10 significa "el valor del flag 10").

Para comprobar que lo tenemos, pues lo mismo.

¿Qué os parece? ¿Dudas? ¿Algo que comentar? Si mola, lo haré exactamente como he descrito.


3.99.3b
=======

Mínima revisión. Se arregla lo necesario para poder tener juegos de 128K con un sólo nivel (es decir, usar `MODE_128K` sin `COMPRESSED_LEVELS`).

Ahora mismo hay dos ejemplos que te pueden ayudar si quieres hacer un juego de 128K:

- Goku Mal: 128K con niveles comprimidos. Ver este doc y los fuentes del juego.
- Las nuevas aventuras de Dogmole Tuppowsky: 128K con un sólo nivel.

Además, en spare he añadido el archivo extern-textos.h cuyo contenido podéis usar en extern.h si queréis una forma sencilla de mostrar textos en pantalla mediante el comando EXTERN n del script.


3.99.3
======

Tiles animados
--------------

Si se define:

```c
	#define ENABLE_TILANIMS			32		
```

En config.h, los tiles >= que el índice especificado se consideran animados. En el tileset, vienen por parejas. Si se define, por ejemplo, "46", entonces la única pareja de tiles 46 y 47 estará animada. El motor los detectará y cada frame hará que uno de los tiles 46 cambie de estado.

Puede haber un máximo de 64 tiles animados en la misma pantalla. Si pones más, petará.

Modo 128K
---------

Tienes que hacer mucho trabajo manual con esto. Lo siento, pero es así. En primer lugar habrá que crear un make.bat que construya todo lo que necesitas. Para ello puedes basarte en el archivo spare/make128.bat y adecuarlo a tu proyecto.

El modo 128K es igual que el 48K pero usar WYZ Player y además soporta varios niveles. No podrás tener niveles más largos, pero sí podrás tener varios niveles. 

Para usarlo, necesitas activar tres cosas en config.h:

```c
	#define MODE_128K
	#define COMPRESSED_LEVELS
	#define MAX_LEVELS			4			
```

En MAX_LEVELS tienes que especificar el número de niveles que vas a usar.

En churromain.c hay que cambiar la posición de la pila y colocarla por debajo del binario principal:

```c
	#pragma output STACKPTR=24299
```

Luego hay que modificar levels128.h, que es donde se define la estructura de niveles y que se incluye en modo 128K. Ahí verás un array levels, con información sobre los niveles. En principio se incluye muy poca información:

```c
	// Level struct
	LEVEL levels [MAX_LEVELS] = {
		{3,2},
		{4,3},
		{5,4},
		{6,5}	
	};
```

El primer valor es el número de recurso (ver más adelante) que contiene el nivel. El segundo valor es el número de la canción en WYZ PLAYER que debe sonar mientras se juega al nivel.

Para preparar un nivel tienes que usar la nueva utilidad buildlevel.exe que hay en /utils. Esta utilidad toma los siguientes parámetros:

```
$ buildlevel 	mapa.map map_w map_h lock font.png work.png spriteset.png 
				extrasprites.bin enems.ene scr_ini x_ini y_ini max_objs 
				enems_life behs.txt level.bin
```

- mapa.map Es el mapa de mappy
- map_w, map_h Son las dimensiones del mapa en pantallas.
- lock 15 para autodetectar cerrojos, 99 si no hay cerrojos
- font.png es un archivo de 256x16 con 64 caracteres ascii 32-95
- work.png es un archivo de 256x48 con el tileset
- spriteset.png es un archivo de 256x32 con el spriteset
- extrasprites.bin lo encuentras en /levels
- enems.ene el archivo con los enemigos/hotspots de colocador.exe
- scr_ini, scr_x, scr_y, max_objs, enems_life valores del nivel
- behs.txt un archivo con los tipos de tiles, separados por comas
- level.bin es el nombre de archivo de salida.
   
Cuando tengamos todos los niveles construidos, hay que comprimirlos con apack:

```
$ /utils/apacke.exe level1.bin level1c.bin
```

Cuando tengamos todos los niveles comprimidos, habrá que crear las imagenes binarias que se cargarán en las páginas de RAM extra. Para eso usamos la utilidad librarian que hay en la carpeta /bin. De hecho, es buena idea trabajar en la carpeta /bin para esto.

La utilidad librarian utiliza una lista list.txt con los binarios comprimidos que debe ir metiendo en las imagenes binarias que irán en las páginas extra de RAM. Lo primero que tendremos que meter serán los archivos title.bin, marco.bin y ending.bin, en ese orden. Si no tienes marco.bin debes usar un archivo de longitud 0, pero debes especificarlo. Luego añadiremos nuestros niveles. Por ejemplo:

```
	title.bin
	marco.bin
	ending.bin
	level1c.bin
	level2c.bin
	level3c.bin
	level4c.bin
```

Ahí hemos añadido cuatro niveles comprimidos.

Al ejecutar librarian, irá rellenando imagenes de 16K destinadas para ir en la RAM extra. Primero creará ram3.bin, luego ram4.bin y finalmente ram6.bin, según vaya necesitando más espacio.

También generará el archivo librarian.h, que tendremos que copiar en /dev. Aquí podremos ver el número de recurso asociado a cada binario:

```c
	RESOURCE resources [] = {
	   {3, 49152},   // 0: title.bin
	   {3, 50680},   // 1: marco.bin
	   {3, 50680},   // 2: ending.bin
	   {3, 52449},   // 3: level1c.bin
	   {3, 55469},   // 4: level2c.bin
	   {3, 58148},   // 5: level3c.bin
	   {3, 60842}   // 6: level4c.bin
	};
```

Estos números de recurso son los que tendremos que especificar en el array levels que mencionamos más arriba. En concreto, los recursos 3, 4, 5 y 6 son los que contienen los cuatro niveles.

Con todo esto hecho y preparado, habrá que montar la cinta. Para ello hay que crear un loader.bas adecuado (puedes ver un ejemplo en /spare/loader.bas) y construir un .tap con cada bloque de RAM (de nuevo, el ejemplo en /spare/make.bat construye la cinta con binarios en RAM3 y RAM4).

También necesitarás RAM1.BIN para construir RAM1.TAP, conteniendo el player de WYZ con las canciones. Para ello tendrás que modificar /mus/WYZproPlay47aZX. ASM en /mus para que incluya tus canciones. Tienes un ejemplo en /spare.

Como ves, es un poco tedioso. Te recomiendo que construyas mini-proyectos en 48K según vas haciendo los niveles, y que al final montes una versión 128K con todo.

Además, puedes usar el espacio extra para meter más pantallas comprimidas, o incluso código para usar passwords para saltar directamente a los niveles. Puedes ver ejemplos de todo esto en Goku Mal 128.

Hotspots tipo 3
---------------

Hemos hecho esta modificación, propuesta en el foro, fija a golpe de directiva. Si defines

```c
	#define USE_HOTSPOTS_TYPE_3				// Alternate logic for recharges.
```

Las recargas aparecerán única y exclusivamente donde tú las coloques, usando el hotspot de tipo 3.

Pausa / Abortar
---------------

Si se define

```c
	#define PAUSE_ABORT						// Add h=PAUSE, y=ABORT
```

Se añade código para habilitar la tecla "h" para pausar el juego y la tecla "y" para interrumpir la partida. Si quieres cambiar la asignación tendrás que tocar el código en mainloop.h

Mensaje al coger objetos
------------------------

Se se define

```c
	#define GET_X_MORE						// Shows "get X more" 
```

Aparecerá un mensaje con los objetos que te quedan cada vez que coges uno.



3.99.2mod
=========

Esta fue una versión especial con una cosa que nos pidió Radastan, los...

Tiles animados
--------------

Todo se basa en tilanim.h. Este archivo se incluye si se define en config.h la directiva ENABLE_TILANIMS. Además, el valor de esta directiva es el que define el número de tile menor que se considera animado.

En tilanim.h hay, además de la definición de datos, dos funciones:

```c
	void add_tilanim (unsigned char x, unsigned char y, unsigned char t) 
```

se llama desde la función que pinta la pantalla actual si detecta que el tile que va a pintar es >= ENABLE_TILANIMS. Añade un tile animado a la lista de tiles.

```c
	void do_tilanims (void)
```

se llama desde el bucle principal. Básicamente selecciona un tile animado al azar entre todos los almacenados, le cambia el frame (de 0 a 1, de 1 a 0) y lo dibuja.

Para usarlo sólo tienes que definir en config.h la directiva ENABLE_TILANIMS con el tile animado menor. Por ejemplo, si tus cuatro últimas parejas de tiles (8 en total) son los animados, pon el valor 40. Luego, en el mapa, se tiene que poner el tile menor de la pareja, o sea, el tile 40 para 40-41, el 42 para 42-43... Si no lo haces así pasarán cosas divertidas. El código es (tiene que ser) minimal, no se comprueba nada, así que cuidao.

Por cierto, esto no se ha probado. Si lo pones en tu güego y se peta, mal.



3.99.2
======

Venga, las churreras van saliendo como churros. Estamos que lo rompemos, y se nos ocurren cosas nuevas todos los días. Las iremos metiendo a medida que se nos ocurran güegos que las lleven.

Estas son las cosas nuevas que hay en esta versión de la churrera:

Temporizadores
--------------

Se añade a la churrera un temporizador que podemos usar de forma automática o desde el script. El temporizador toma un valor inicial, va contando hacia abajo, puede recargarse, se puede configurar cada cuántos frames se decrementa o decidir qué hacer cuando se agota.

```c
	#define TIMER_ENABLE
```

Con `TIMER_ENABLE` se incluye el código necesario para manejar el temporizador. Este código necesitará algunas otras directivas que especifican la forma de funcionar:

```c 
	#define TIMER_INITIAL		99	
	#define TIMER_REFILL		25
	#define TIMER_LAPSE 		32
```

`TIMER_INITIAL` especifica el valor inicial del temporizador. Las recargas de tiempo, que se ponen con el colocador como hotspots de tipo 5, recargarán el valor especificado en `TIMER_REFILL`. El valor máximo del timer, tanto para el inicial como al recargar, es de 99. Para controlar el intervalo de tiempo que transcurre entre cada decremento del temporizador, especificamos en `TIMER_LAPSE` el número de frames que debe transcurrir.

```c
	#define TIMER_START
```

Si se define `TIMER_START`, el temporizador estará activo desde el principio.

Tenemos, además, algunas directivas que definen qué pasará cuando el temporizador llegue a cero. Hay que descomentar las que apliquen:

```c
	#define TIMER_SCRIPT_0	
```

Definiendo esta, cuando llegue a cero el temporizador se ejecutará una sección especial del script, ON_TIMER_OFF. Es ideal para llevar todo el control del temporizador por scripting, como ocurre en Cadàveriön.

```c
	//#define TIMER_GAMEOVER_0
```

Definiendo esta, el juego terminará cuando el temporizador llegue a cero.

```c
	//#define TIMER_KILL_0
	//#define TIMER_WARP_TO 0
	//#define TIMER_WARP_TO_X 	1
	//#define TIMER_WARP_TO_Y 	1
```

Si se define `TIMER_KILL_0`, se restará una vida cuando el temporizador llegue a cero. Si, además, se define `TIMER_WARP_TO`, además se cambiará a la pantalla espeficiada, apareciendo el jugador en las coordenadas `TIMER_WARP_TO_X` y `TIMER_WARP_TO_Y`.

```c
//#define TIMER_AUTO_RESET
```

Si se define esta opción, el temporizador volverá al máximo tras llegar a cero de forma automática. Si vas a realizar el control por scripting, mejor deja esta comentada.

```c
	#define SHOW_TIMER_OVER	
```

Si se define esta, en el caso de que hayamos definido o bien `TIMER_SCRIPT_0` o bien `TIMER_KILL_0`, se mostrará un cartel de "TIME'S UP!" cuando el temporizador llegue a cero.

Scripting:
----------

Como hemos dicho, el temporizador puede administrarse desde el script. Es interesante que, si decidimos hacer esto, activemos `TIMER_SCRIPT_0` para que cuando el temporizador llegue a cero se ejecute la sección `ON_TIMER_OFF` de nuestro script y que el control sea total. 

Además, se definen estas comprobaciones y comandos:

Comprobaciones:
---------------

```
	IF TIMER >= x
	IF TIMER <= x
```

Que se cumplirán si el valor del temporizador es mayor o igual o menor o igual que el valor especificado, respectivamente.

Comandos:
---------

```
	SET_TIMER a, b
```

Sirve para establecer los valores `TIMER_INITIAL` y `TIMER_LAPSE` desde el script.

```
	TIMER_START
```

Sirve para iniciar el temporizador.

```
	TIMER_STOP
```

Sirve para parar el temporizador.

---

Control de bloques empujables
=============================

Hemos mejorado el motor para que se pueda hacer más cosas con el tile 14 de tipo 10 (tile empujable) que simplemente empujarlo o que detenga la trayectoria de los enemigos. Ahora podemos decirle al motor que lance la sección `PRESS_FIRE` de la pantalla actual justo después de empujar un bloque empujable. Además, el número del tile que se "pisa" y las coordenadas finales se almacenan en tres flags que podemos configurar, para poderlas usar desde el script para hacer comprobaciones.

Este es el sistema que se emplea en el script de Cadàveriön para controlar que coloquemos las estatuas sobre los pedestales, por poner un ejemplo.

Recordemos lo que teníamos hasta ahora:

```c
	#define PLAYER_PUSH_BOXES 				
	#define FIRE_TO_PUSH					
```

La primera es necesaria para activar los tiles empujables. La segunda obliga al jugador a pulsar FIRE para empujar y, por tanto, no es obligatoria. Veamos  ahora las nuevas directivas:

```c
	#define ENABLE_PUSHED_SCRIPTING
	#define MOVED_TILE_FLAG 		1
	#define MOVED_X_FLAG 			2
	#define MOVED_Y_FLAG 			3
```

Activando ENABLE_PUSHED_SCRIPTING, el tile que se pisa y sus coordenadas se almacenarán en los flags especificados por las directivas `MOVED_TILE_FLAG`, `MOVED_X_FLAG` y `MOVED_Y_FLAG`. En el código que se muestra, el tile pisado se almacenará en el flag 1, y sus coordenadas en los flags 2 y 3.

```c
	#define PUSHING_ACTION
```

Si definimos esta, además, se ejecutarán los scripts `PRESS_FIRE AT ANY` y `PRESS_FIRE` de la pantalla actual.

Recomendamos estudiar el script de Cadàveriön, el cual, además de ser un buen ejemplo del uso del temporizador y del control del bloque empujable, resulta ser un script bastante complejo que emplea un montón de técnicas avanzadas.


Comprobar si nos salimos del mapa
---------------------------------

Es aconsejable poner límites en tu mapa para que el jugador no se pueda salir, pero si tu mapa es estrecho puede que quieras aprovechar toda la  pantalla. En ese caso, puedes activar:

```c
	#define PLAYER_CHECK_MAP_BOUNDARIES
```

Que añadirá comprobaciones y no dejará que el jugador se salga del mapa. ¡Ojo! Si puedes evitar usarlo, mejor: ahorrarás espacio.


Tipo de enemigo "custom" de regalo
----------------------------------

Hasta ahora habíamos dejado sin código los enemigos de tipo 6, pero hemos pensado que no nos cuesta poner uno, de ejemplo. Se comporta como los murciélagos de Cheril the Goddess. Para usarlos, ponlos en el colocador de enemigos como tipo 6 y usa estas directivas:

```c
	#define ENABLE_CUSTOM_TYPE_6			
	#define TYPE_6_FIXED_SPRITE 	2		
	#define SIGHT_DISTANCE			96
```

La primera los activa, la segunda define qué sprite va a usar (menos 1, si quieres el sprite del enemigo 3, pon un 2. Sorry por la guarrada,pero ahorro bytes). La tercera dice cuántos píxels ve de lejos el bicho. Si te ve, te persigue. Si no, vuelve a su sitio (donde lo hayas puesto con el colocador).

Esta implementación, además, utiliza dos directivas de los enemigos de tipo 5 para funcionar:

```c
	#define FANTY_MAX_V             256	
	#define FANTY_A                 12	
```

Define ahí la aceleración y la velocidad máxima de tus tipo 6. Si vas a usar también tipo 5 y quieres otros valores, sé un hombre y modifica el motor.


Configuración de teclado / joystick para dos botones
----------------------------------------------------

Hay güegos de vista lateral que se juegan mejor con dos botones. Si activas esta directiva:

```c
	#define USE_TWO_BUTTONS
```

El teclado será el siguiente, en vez del habitual:

```
	A izquierda
	D derecha
	W arriba
	S abajo
	N salto
	M disparo
```

Si se elige joystick, FIRE y M disparan, y N salta.


Disparos hacia arriba y en diagonal para vista lateral
------------------------------------------------------

Ahora podrás permitir que el jugador dispare hacia arriba o en diagonal. Para ello define esto:

```c
	#define CAN_FIRE_UP	
```

Esta configuración funciona mejor con `USE_TWO_BUTTONS`, ya que así separamos "arriba" del botón de salto.

Si no pulsas "arriba", el personaje disparará hacia donde esté mirando. Si pulsas "arriba" mientras disparas, el personaje disparará hacia arriba. Si, además, estás pulsando una dirección, el personaje disparará en la diagonal indicada.


Balas enmascaradas
------------------

Por velocidad, las balas no llevan máscaras. Esto funciona bien si el fondo sobre el que se mueven es oscuro (pocos pixels INK activos). Sin embargo,  hay situaciones en las que esto no ocurre y se ve mal. En ese caso, podemos activar máscaras para las balas:

```c
	#define MASKED_BULLETS
```
