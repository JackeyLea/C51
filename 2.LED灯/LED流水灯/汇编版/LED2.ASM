/**************************************************************************************
*		              LED闪烁的简单试验												  *
*                延时实现p2口LED流水灯效果  			                              *
*	连接方法： JP11（P2）和J12(LED灯) 用8PIN排线连接起来							  *
*																					  *
***************************************************************************************/

	ORG 0000H	 ;程序从000H地址开始运行
	AJMP MAIN	 ;跳转到 MAIN程序

	ORG 030H	  ;MAIN程序从030H开始运行
MAIN:	
    MOV P2,#0FEH
	ACALL DEL	   ;调用延时子程序
	MOV P2,#0FCH
	ACALL DEL	   ;调用延时子程序
	MOV P2,#0F8H
	ACALL DEL
	MOV P2,#0F0H
	ACALL DEL
	MOV P2,#0E0H
	ACALL DEL
	MOV P2,#0C0H
	ACALL DEL
	MOV P2,#080H
	ACALL DEL
	MOV P2,#000H
	ACALL DEL
	MOV P2,#0FFH
	AJMP MAIN	   ;跳转到MAIN程序

; 延时子程序
DEL:	MOV R5,#02H
DEL1:	MOV R6,#0F0H
DEL2:	MOV R7,#0F0H
DEL3:	DJNZ R7, DEL3
	DJNZ R6, DEL2
	DJNZ R5, DEL1
	RET
	END
