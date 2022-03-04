;
; void ListConcat(LIST *list1, LIST *list2)
; Alvin Albrecht 02.2003
;

XLIB SPListConcat
XREF _u_free

; enter: hl = list2, de = list1
; exit : list1 = list1 concat list2, list2 is deleted
; uses : af, bc, de, hl

.SPListConcat
   push hl               ; save list2
   ld a,(hl)
   inc hl
   or (hl)
   jp z, list2nonempty

   ; list2 is empty, do nothing

   pop de
   push de
   ld hl,(_u_free)
   call JPHL             ; free(list2)
   pop de
   ret

.list2nonempty
   ex de,hl              ; de = list2.count+1, hl = list1
   ld a,(hl)
   inc hl
   or (hl)
   jp nz, list1nonempty

   ; list1 empty, copy list2

   dec de
   dec hl
   ex de,hl              ; hl = list2, de = list1
   ld bc,9
   ldir                  ; copy list2 into list1
   dec de
   dec de
   dec de
   ex de,hl              ; hl = list1.head+1
   ld e,(hl)
   dec hl
   ld d,(hl)             ; de = list1 head
   dec hl
   ld (hl),e
   dec hl
   ld (hl),d             ; list1.current = list1 head
   dec hl
   ld (hl),1             ; INLIST
   pop de
   push de
   ld hl,(_u_free)
   call JPHL             ; free(list2)
   pop de
   ret

   ; both lists nonempty

.list1nonempty           ; de = list2.count+1, hl = list1.count+1
   dec de
   dec hl
   ld a,(de)
   add a,(hl)
   ld (hl),a
   inc de
   inc hl
   ld a,(de)
   adc a,(hl)
   ld (hl),a             ; ** list1 count += list2 count
   inc hl                ; hl = list1.state
   inc de
   inc de
   inc de
   inc de                ; de = list2.head
   ld a,(hl)
   cp 2                  ; ** state = AFTER?
   jp nz, list1notafter

   ld (hl),1             ; ** list1.state = INLIST
   inc hl
   ld a,(de)
   ld (hl),a
   inc de                ; de = list2.head+1
   inc hl                ; hl = list1.current+1
   ld a,(de)
   ld (hl),a             ; ** list1 current = list2 head
   dec de                ; de = list2.head
   inc hl
   inc hl
   inc hl                ; hl = list1.tail
   jp rejoin1

.list1notafter           ; de = list2.head, hl = list1.state
   ld bc,5
   add hl,de             ; hl = list1.tail
.rejoin1
   ld b,(hl)
   inc hl                ; hl = list1.tail+1
   ld c,(hl)             ; bc = list1 tail NODE
   inc bc
   inc bc                ; bc = list1 tail NODE.next
   ld a,(de)
   ld (bc),a
   inc de                ; de = list2.head+1
   inc bc
   ld a,(de)
   ld (bc),a             ; ** list1 tail NODE.next = list2 head NODE

   ex de,hl              ; hl = list2.head+1, de = list1.tail+1
   ld c,(hl)
   dec hl                ; hl = list2.head
   ld b,(hl)             ; bc = list2 head NODE
   inc bc
   inc bc
   inc bc
   inc bc
   inc bc                ; bc = list2 head NODE.prev+1
   ld a,(de)
   ld (bc),a
   dec bc
   dec de                ; de = list1.tail
   ld a,(de)
   ld (bc),a             ; ** list2 head NODE.prev = list1 tail NODE

   inc hl
   inc hl                ; hl = list2.tail
   ldi
   ldi                   ; ** list1 tail = list2 tail

   pop de
   push de
   ld hl,(_u_free)
   call JPHL             ; free(list2)
   pop de
   ret

.JPHL
   jp (hl)
