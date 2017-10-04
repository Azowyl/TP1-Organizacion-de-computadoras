#include <mips/regdef.h>

#define fp $30
#define gp $28

	.text
	.globl mcd
	.ent mcd
mcd:
	subu	sp,sp,32	# Saved Register Area
	sw		ra,24(sp)
	sw 		fp,20(sp)	
	sw 		gp,16(sp)	
	move 	fp,sp

	sw 		a0,32(sp)		# Argument Building Area	
	sw		a1,36(sp)
	sw		a2,40(sp)
	sw		a3,44(sp)

	lw		v0,32(sp)
	lw		v1,36(sp)

	beq		v1,0,fin		# Si a1 es cero termino
	
	move 	a0,v1		# seteo de argumentos para la llamada recursiva
	rem 	a1,v0,v1
	jal 	mcd

fin:
	lw 		ra,24(sp)
	lw 		fp,20(sp)
	addu 	sp,sp,32
	j 		ra
	.end mcd
	