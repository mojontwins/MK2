
/*
 *      Sprite Pack V2.0
 *
 *      Spectrum and Timex Computers Game Engine
 *      Visit http://justme895.tripod.com/main.htm
 *
 *      Alvin Albrecht 01.2003
 */

#define _SPLIB
#include "spritepack.h"

void *sp_PixelDown(void *scrnaddr)
{
#asm
   LIB SPPixelDown

   ld hl,2
   add hl,sp
   ld a,(hl)
   inc hl
   ld h,(hl)
   ld l,a
   or a
   call SPPixelDown
   ccf
#endasm
}

/*
  enter: HL = valid screen address
  exit : No Carry = moved off screen 
         HL = moves one pixel down 
*/
