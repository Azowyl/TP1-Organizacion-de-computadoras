#include <mips/regdef.h>

	.text
	.globl mcm
	.extern mcd
	.ent mcm
mcm:
	.frame	$fp,32,ra
	subu	sp,sp,32	# Saved Register Area
	.cprestore 0
	sw		ra,24(sp)
	sw 		$fp,20(sp)	# el regsitro 30 es fp
	sw 		gp,16(sp)	# el registro 28 es gp
	move 	$fp,sp

	sw 		a0,32(sp)	# Argument Building Area	
	sw		a1,36(sp)
	sw		a2,40(sp)
	sw		a3,44(sp)

	jal 	mcd

	lw		a0,32(sp)
	lw		a1,36(sp)
	mul		a0,a0,a1
	divu	v0,a0,v0			

	lw 		ra,24(sp)	# fin
	lw 		$fp,20(sp)
	addu 	sp,sp,32
	j 		ra
	.end mcm
	
