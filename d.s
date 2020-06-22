	.file	"d.c"
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__SREG__ = 0x3f
__tmp_reg__ = 0
__zero_reg__ = 1
	.text
	.section	.text.startup,"ax",@progbits
.global	main
	.type	main, @function
main:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	in r24,0xa
	ori r24,lo8(31)
	out 0xa,r24
	ldi r24,0
	ldi r19,lo8(57)
	ldi r18,lo8(18)
.L2:
	ldi r30,lo8(499)
	ldi r31,hi8(499)
1:	sbiw r30,1
	brne 1b
	rjmp .
	nop
	ldi r25,lo8(1)
	add r25,r24
	mul r25,r19
	mov r24,r1
	clr __zero_reg__
	lsr r24
	lsr r24
	mul r24,r18
	sub r25,r0
	clr __zero_reg__
	mov r24,r25
	mov r30,r25
	ldi r31,0
	subi r30,lo8(-(wave))
	sbci r31,hi8(-(wave))
	ld r25,Z
	out 0xb,r25
	rjmp .L2
	.size	main, .-main
	.section	.rodata
	.type	wave, @object
	.size	wave, 18
wave:
	.string	"\025\031\035\037\037\035\032\025\020\013\006\002"
	.string	""
	.ascii	"\002\005\t\017"
	.ident	"GCC: (GNU) 10.1.0"
.global __do_copy_data
