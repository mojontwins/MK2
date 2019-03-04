# Configuración de los controles

Casi todo el mundo tiene problemas con esto, básicamente porque siempre ha estado roto y siempre he terminado apañándolo para todos los juegos. Existen dos modos: dos botones y un botón, que deberás elegir si quieres un solo botón de disparo/acción, o dos botones separados para salto y disparo (además de un botón de "arriba").

El menú de MK2 ofrece dos opciones para dos configuraciones de teclado. Tradicionalmente, estas han sido WASDNM y OPQASpace, con diferentes combinaciones y tonterías. Como esto nunca termina de valer para TODO, he decidido explicar como poner tus propias combinaciones de teclado. Todo se define en este array, que se encuentra en dev\engine.h:

```c
    unsigned int keyscancodes [] = {
    #ifdef USE_TWO_BUTTONS
        0x02fb, 0x02fd, 0x01fd, 0x04fd, 0x047f, 0x087f,     // WSADMN
        0x01fb, 0x01fd, 0x02df, 0x01df, 0x047f, 0x087f,     // QAOPMN
    #else
        0x02fb, 0x02fd, 0x01fd, 0x04fd, 0x017f, 0,          // WSADs-
        0x01fb, 0x01fd, 0x02df, 0x01df, 0x017f, 0,          // QAOPs-
    #endif
    };
```

Según hayas configurado `USE_TWO_BUTTONS` o no, los valores que valen son los de arriba o los de abajo. Para poner tus propios valores, sólo tienes que juntar los números según esta tabla: primero la fila, luego la columna:

```
        FE   FD   FB   F7   EF   DF   BF   7F
    01  CS   A    Q    1    0    P    EN   SP
    02  Z    S    W    2    9    O    L    SS
    04  X    D    E    3    8    I    K    M
    08  C    F    R    4    7    U    J    N
    10  V    G    T    5    6    Y    H    B
```

El orden del array es arriba abajo izquierda derecha disparo salto / arriba abajo izquierda derecha acción, primero para la opción 1 del menú, y luego para la opción 2 (en total, 12 valores), y según `USE_TWO_BUTTONS`. Por ejemplo, para definir "arriba" como "1", deberíamos poner el número `0x01f7` en la primera posición.
