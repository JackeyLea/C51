	org	0000h
	ajmp	main
	org	0030h
main:

	MOV	R2,#08H
DLV1:	MOV	R3,#0FAH
DLV2:	CPL	P1.5
	LCALL	DELAY1		;延时
	DJNZ	R3,DLV2
	DJNZ	R2,DLV1
	MOV	R2,#10H		;改变循环初值

DLV3:	MOV	R3,#0FAH
DLV4:	CPL	P1.5
	LCALL	DELAY2
	DJNZ	R3,DLV4
	DJNZ	R2,DLV3
	ajmp	main
delay1:
	mov	r7,#00h

LLA:	DJNZ	R7,LLA
	ret

delay2:
	mov	r7,#128

LLB:	DJNZ	R7,LLB
	ret
		
	end
