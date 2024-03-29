
; Tabla de instrumentos
TABLA_PAUTAS: DW PAUTA_0,PAUTA_1,0,0,0,0,PAUTA_6,PAUTA_7,PAUTA_8,0,PAUTA_10,PAUTA_11

; Tabla de efectos
TABLA_SONIDOS: DW SONIDO0,SONIDO1,SONIDO2,SONIDO3

;Pautas (instrumentos)
;Instrumento 'Piano'
PAUTA_0:	DB	12,0,11,0,10,0,9,0,129
;Instrumento 'Techno -vol'
PAUTA_8:	DB	72,0,7,0,6,0,6,0,7,0,7,0,6,0,6,0,129
;Instrumento 'Trompeta'
PAUTA_7:	DB	10,0,11,0,11,0,12,0,12,0,11,0,10,0,8,0,7,0,7,0,7,0,129
;Instrumento 'Techno +1'
PAUTA_6:	DB	74,0,9,0,8,0,8,0,9,0,9,0,8,0,8,0,129
;Instrumento 'piano vol-'
PAUTA_10:	DB	10,0,9,0,8,0,7,0,129
;Instrumento 'piano--'
PAUTA_11:	DB	7,0,6,0,5,0,5,0,129
;Instrumento 'blip'
PAUTA_1:	DB	11,0,8,0,9,0,7,0,5,0,0,129

;Efectos
;Efecto 'bass drum'
SONIDO0:	DB	184,109,0,140,104,0,0,6,0,202,32,0,69,64,0,255
;Efecto 'drum'
SONIDO1:	DB	209,60,20,13,41,11,13,38,9,255
;Efecto 'ggdrum'
SONIDO2:	DB	209,60,20,13,41,11,13,38,9,255
;Efecto 'castlev'
SONIDO3:	DB	24,105,8,0,6,9,255

;Frecuencias para las notas
DATOS_NOTAS: DW 0,0
DW 1711,1614,1524,1438,1358,1281,1210,1142,1078,1017
DW 960,906,855,807,762,719,679,641,605,571
DW 539,509,480,453,428,404,381,360,339,320
DW 302,285,269,254,240,227,214,202,190,180
DW 170,160,151,143,135,127,120,113,107,101
DW 95,90,85,80,76,71,67,64,60,57
