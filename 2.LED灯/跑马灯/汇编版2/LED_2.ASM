;********************************************************************************
;                       跑马灯试验	       										*
;																				*
;       开机8个灯循环点亮。                                                     *
;       硬件连接：p2口8路指示灯，												*
;       连接方法： JP11（P2）和J12(LED灯) 用8PIN排线连接起来 					*
;********************************************************************************

	ORG 0000H	  ;程序0000起始地址
	AJMP MAIN	  ;跳转到MAIN

	ORG 030H      ;MAIN 程序起始地址
MAIN:	MOV P2,#0FEH
	ACALL DEL	    ;调用子程序
	MOV P2,#0FDH	;将立即数传给P2
	ACALL DEL
	MOV P2,#0FBH
	ACALL DEL
	MOV P2,#0F7H
	ACALL DEL
	MOV P2,#0EFH
	ACALL DEL
	MOV P2,#0DFH
	ACALL DEL
	MOV P2,#0BFH
	ACALL DEL
	MOV P2,#07FH
	ACALL DEL
	MOV P2,#0FFH
	AJMP MAIN 

;延时子程序
DEL:	MOV R5,#04H
DEL1:	MOV R6,#0FFH
DEL2:	MOV R7,#0FFH
DEL3:	DJNZ R7, DEL3
	DJNZ R6, DEL2
	DJNZ R5, DEL1
	RET
	END
