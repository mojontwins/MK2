// MT Engine MK2 v0.90b
// Copyleft 2016 the Mojon Twins

// levelnames.h
// Completely custom. But easily customizable. Just read.

#define LEVELNAMES_SIZE 10
#define LEVELNAMES_X 11
#define LEVELNAMES_Y 23
#define LEVELNAMES_C 79

unsigned char *levelnames = "          LA CAMOLLA          HOMBRO IZQEL PECHITOHOMBRO DERBRAZO IZQ.LA BARRIGABRAZO DER.UNA CADERA LA PISHA UNA CADERALA RODILLA          LA RODILLA PIE IZQ.            PIE DER. ";

xxxxxxxxxxxxxxxxxxxxxxxxXXXXXX
   EL FINAL DE LOS DOMINIOS   
    EL ARMARIO DE MACARIO     
 CRIPTA DEL SIRVIENTE VICENTE 
        ]VAYA SOLARIUM!       
   CRIPTA DEL ENANO MARRANO   
   TERRENO BALDIO CON POMIO   
  TERRENO BALDADO CON PESCADO 
     CRIPTA, DULCE CRIPTA     
 CHALECICO DE LA BRUJA MARUJA 
     LA TORRE DEL ESPANTO     
    EL OLEODUCTO DEL ERUCTO   
CRIPTA DE JUANILLO EL COLMILLO
  LA CAPILLA DE LA CHINCHILLA 
  CRIPTA DEL GIGANTE ELEGANTE 
    ]LA CAMARA DEL TESORO!    
    EL BICHARRACO BERRACO     
    EL CUARTO DE INVITADOS    
  SALA DE LECTURAS A OSCURAS  
    VESTIBULO CON PATIBULO    
      MOJONES CALIENTES       
       CACOTA HIRVIENDO       
      MIERDA BURBUJEANTE      
    EL ESPANTO DE LEPANTO     
   LA ABOMINACION EN ACCION   
   MISTERIOSA ARQUITECTURA    
     ]SE ME CAE LA LAVA!      
   MI CUEVA ESTA COMO NUEVA   
   EL FANTASMA QUE TE PASMA   
        MENUDO DESORDEN       
   EL CONDENADO ENCABRONADO   

void print_level_name (void) {
	gen_pt = levelnames + n_pant * LEVELNAMES_SIZE;
	gpit = LEVELNAMES_X; gpjt = LEVELNAMES_SIZE;
	while (gpjt --) {
		// sp_PrintAtInv (LEVELNAMES_Y, gpit ++, LEVELNAMES_C, (*gen_pt ++) - 32);
		#asm
				; enter:  A = row position (0..23)
				;         C = col position (0..31/63)
				;         D = pallette #
				;         E = graphic #

				ld  hl, (_gen_pt)
				ld  a, (hl)
				sub 32
				ld  e, a
				inc hl
        ld  (_gen_pt), hl

				ld  a, (_gpit)
				ld  c, a
				inc a
				ld  (_gpit), a

				ld  a, LEVELNAMES_Y

				ld  d, LEVELNAMES_C

				call SPPrintAtInv
		#endasm
	}
}
