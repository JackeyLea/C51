;********************************************************************************
;               键盘控制的花样彩灯。											*
;  连接方法：JP10（P2） 与 J12 （LED灯）连接，   							    *
;            JP11（P0） 与 JP5（按键接口）连接        						    *
;																				*
;按p24,p27,p26,p27,p2口8个灯分别作 移动右移动，停止 右移 左移*				    *
;																				*
;********************************************************************************
;亮灯控制程序;
;************;

	ORG     0000H
	LJMP    START
	org	0030h
;************;
;  主 程 序  ;
;************;
START:
	MOV P3,       #0FFH
      	JNB       P0.7,FUN0	;   检测按键
      	JNB       P0.4,FUN1
      	JNB       P0.5,FUN2
      	JNB       P0.6,FUN3   	;关闭按纽
      	AJMP	  START
FUN0:	LCALL      DL10MS       ;消岸抖动
     	JB         P0.7,START
WAITL0:	JNB        P0.7,WAITL0  ;等待键释放
FUN01:	LCALL      FUN00
	AJMP	   START
FUN1:	LCALL      DL10MS       ;消岸抖动
	JB         P0.4,START
WAITL1:	JNB        P3.3,WAITL1  ;等待键释放
FUN10:	LCALL      FUN11
	AJMP	   START
FUN2:	LCALL      DL10MS       ;消岸抖动
     	JB         P0.5,START
WAITL2:	JNB        P0.5,WAITL2  ;等待键释放
FUN20:	LCALL      FUN22
	AJMP	   START

FUN3:	LCALL      DL10MS       ;消岸抖动
     	JB         P0.6,START
WAITL3:	JNB        P0.6,WAITL3  ;等待键释放
     	MOV        P2,#0FFH     ;关显示
     	LJMP       START

FUN00:	MOV        A,#0FEH	;左移子程序
FUN000:	MOV        P2,A
      	LCALL      DL05S
      	JNB        ACC.7,OUT	;检测是否结束
      	RL         A
      	AJMP       FUN000
OUT:  	RET

FUN11:	MOV        A,#07FH	;右移子程序
FUN111:	MOV        P2,A
      	LCALL      DL05S
      	JNB        ACC.0,OUT	;检测是否结束
      	RR         A
      	AJMP       FUN111

FUN22:MOV         A,#0AAH	;间隔显示子程序
      MOV         P2,A
      LCALL       DL30S
      CPL         A
      MOV         P2,A
      LCALL       DL30S
      RET

;************;
;  延时程序  ;
;************;
DL512:MOV       R2,#0FFH	;延时500US
LOOP1: DJNZ     R2,LOOP1
       RET

DL10MS:MOV      R3,#14H		;延时10MS
LOOP2: LCALL    DL512
       DJNZ     R3,LOOP2
       RET

DL05S:MOV       R4,#0AH		;延时100MS
LOOP3: LCALL    DL10MS
       DJNZ     R4,LOOP3
       RET

DL30S:MOV       R5,#03H		;延时300MS.
LOOP4:LCALL     DL05S
      DJNZ      R5,LOOP4
      RET     

end
