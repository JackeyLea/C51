	ORG	0000H			;伪指令，指定程序从8000H开始存放
	AJMP	MAIN		;跳转指令，程序跳转到MAIN处

	ORG	0100H			;伪指令，指定以下程序从8100H开始存放
MAIN:
	MOV	SP,#60			;给堆栈指针赋初值
LOOP:		ACALL	MUSIC
	AJMP	LOOP

;***********************
;蜂鸣器输出声响子程序
;**********************
MUSIC:
	MOV	R5,#60H			;控制音长
MIC:
	CPL	P1.5
	ACALL	DELAY5MS		;控制音调
	DJNZ	R5,MIC
	RET


;***************
;延时子程序
;***************
DELAY5MS:
	MOV	R7,#3H
DELAY0:		MOV	R6,#40H
DELAY1:		DJNZ	R6,DELAY1
	DJNZ	R7,DELAY0
	RET
	;

END