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

