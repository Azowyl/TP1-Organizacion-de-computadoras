#include <mips/regdef.h>

	.text
	.globl mcd
	.ent mcd
mcd:
	subu	$sp,$sp,32	# Saved Register Area
	sw 	$ra,28($sp)
	sw 	$fp,24($sp)
	sw 	$gp,20($sp)
	move $fp,$sp

	sw 	$4,0($fp)		# Argument Auilding Area	
	sw 	$5,4($fp)		
	lw	$2,0($fp)
	lw	$3,4($fp)
	
	beq	$3,0,fin		# Si a1 es cero termino
	
	move $4,$3		# seteo de argumentos para la llamada recursiva
	rem 	$5,$2,$3
	jal 	mcd

fin:		
	lw 	$ra,28($sp)
	lw 	$fp,24($sp)
	addu $sp,$sp,32
	j 	$ra
	.end mcd
	