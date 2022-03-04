# Espadewr - Juego ilustrativo

Este juego fue creado como demo / showcase / tutorial para la versión 0.88 de MK2 y ha sido actualizado para la versión actual.

En Espadewr se utiliza un script bastante complejo para ilustrar de forma didáctica las cosas que se pueden hacer con el motor sin modificar ni una linea de código.

## El juego

Meghan, nuestra time lady favorita, se permite cometer la excentricidad de ir a comprar huevos a Hexon-4, el planeta de los hombres-cebolla multiformes y calvos. Sin embargo, una colilla que en vez de en el cenicero de su TARDIS terminó cayendo por una rendija de ventilación al mismo centro de lo que es el motowr, la hizo desviarse unos parsecs (y otros tanto siglos). Cuando se quiso dar cuenta, estaba varada en un planeta desconocido. Cuando salió a investigar un poco, se cayó por un terraplen y perdió el conocimiento.

Cuando se despertó, comprobó que estaba en unas misteriosas ruinas. Un montón de amazonas furiosas pululaban por allí - ¡pero estaban malditas! Al poco tiempo se convertían en unos murciélagos feos de cojones.

Armada con una espada que se encontró por ahí, Meghan debe avanzar por las ruinas hasta encontrar su TARDIS.

En esta demo hay 9 pantallas. El juego completo saldrá en una fecha indeterminada comprendida entre el momento en el que leas esta frase y el futuro.

## Implementación

Empezaremos haciendo una lista de lo que queremos conseguir y proponiendo cómo:

### Control del final del juego custom

Queremos manejarlo desde el script, por lo que activaremos `SCRIPTED_GAME_ENDING` y establecer `WIN_CONDITION` a 2 en `my/config.h`.

### Salto y espadazo

Necesitamos dos botones de acción, uno para saltar y otro para golpear, además de las cuatro direcciones, por lo que activamos `USE_TWO_BUTTONS`. 

### Pantalla por pantalla, con wrap-around

Para ello tendremos que activar en `my/config.h` las macros:
* `PLAYER_CANNOT_FLICK_SCREEN` para no cambiar de pantalla en el mapa al tocar los bordes,
* `PLAYER_WRAP_AROUND` para salir por un lateral y entrar por el otro,
* `SHOW_LEVEL_ON_SCREEN` para que se muestre el número de pantalla al entrar en una nueva, 
* `REENTER_ON_DEATH` para que al morir se vuelva a entrar en la pantalla actual y 
* `RESPAWN_ON_ENTER` para que los enemigos revivan al volver a entrar en la pantalla.

### Espada para matal

Activamos `PLAYER_HAZ_SWORD` y establecemos `PLAYER_HITTER_STRENGTH` a 1, además de poner `ENEMS_LIFE_GAUGE` a 1 también, para que un golpe elimine a los enemigos.

### No hay plataformas, llaves ni objetos, pero sí recargas

Por lo tanto, establecemos:

* `DEACTIVATE_KEYS` para desactivar llaves,
* `DEACTIVATE_OBJECTS` para desactivar objetos,
* `PLAYER_REFILL` a 5 para que las recargas recarguen 5.
* `USE_HOTSPOTS_TYPE_3` para que las recargas se pongan en el ponedor.
* `DISABLE_PLATFORMS` para quitar las plataformas móviles.

### Tiempo

Debe haber un temporizador que lance el script cuando llega a 0:

```c
	#define TIMER_ENABLE					// Enable timer
	#define TIMER_INITIAL				99	// For unscripted games, initial value.
	#define TIMER_REFILL				30	// Timer refill, using tile 21 (hotspot #5)
	#define TIMER_LAPSE 				32	// # of frames between decrements
	#define TIMER_START 					// If defined, start timer from the beginning
	#define TIMER_SCRIPT_0					// If defined, timer = 0 runs "ON_TIMER_OFF" in the script
```

### La lógica dura

La lógica "dura" es la que no se puede simplemente configurar, sino que hay que implementar. Lo suyo sería tocar el código C. En MK2 esto es guarreras porque hay que tocar el core del engine, no es como en MK1 que es amor. Sin embargo, aquí lo haremos todo por scripting. Esto es lo que queremos conseguir:

* Cuando el temporizador llega a 0, los enemigos se convierten en fantis.
* Cuando te matan, todo debe reiniciarse: los fantis deben volver a ser enemigos.
* Que cuando se mate todo lo que hay en la pantalla se avance la fase.

Consulta el script para más información. En los comentarios se explica qué hace cada cosa.

## Ya

Documentación de mierda TM.
