Cosas que he hecho:

1. Lo he metido en examples con lo que he cambiado todas las rutas de `../utils/` a `../../../src/utils`.

2. Me he follao el `levels/buildlevels.bat` y lo he metido en `/dev/build_levels.bat` como en Ninjajar (buscando un poco de homogeinidad). No se llama desde `compile.bat` cada vez, hay que hacerlo a mano cuando se quieran regenerar los niveles (para poder depurar más rápidamente).

3. He quitado el juntamiento de scripts de `buildlevels.bat` y lo he puesto en `compile.bat` justo antes de llamar a msc. Además, he puesto bien el nombre: ahora el script debe llamarse `script.spt`.

4. He quitado la generación de pantallas fijas de `compile.bat` y la he puesto en `build_fixed.bat`, por las mismas razones.

5. Por alguna razón `buildtzx` termina su ejecución con "Cannot read file", pero parece funcionar (?)

6. A `msc` hay que decirle `rampage` para que genere código preparado para RAM extendida: `..\..\..\src\utils\msc3_mk2_1.exe script.spt 20 rampage > nul`.

7. TODO - Empezar a añadir puntos de inyección de código para todos los customs!

	- [X] Hay un mensaje al comenzar el juego y luego se establece `silent_level` para todos los niveles. Se puede sustituir por un custom level screen o algo así.

	- [X] Tipos de enemigos
