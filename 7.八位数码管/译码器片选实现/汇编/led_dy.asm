/*;******************************************************************************
; 标题:                  试验数码管上显示数字（译码器位选 共阴极）            *
;																		      *
; *  连接方法：用短路帽将J15和J16连起来
             JP10（P0口）接J2
             P2.2、P2.3、P2.4分别接J6的A、B、C 		 
                                         *
;******************************************************************************
;                        	       										      *
;请学员认真消化本例程，用573锁存器控制和138译码器控制数码管                   *
;******************************************************************************/ 
 
	   C2  DATA   20H
	
	   First DATA 50H   ;第一个数码管（右边开始）
	   Two   DATA 51H	;第二个数码管
	   Three DATA 52H	;第三个数码管
	   Four	 DATA 53H	;第四个数码管
	   Five	 DATA 54H
	   Six	 DATA 55H
	   Seven DATA 56H
	   Eight DATA 57H
	
	
		ORG 0000H
		LJMP INTI	   ;进入初始化子程序
		ORG 030H

;--------------------------------------------------------------
;初始化程序
;-------------------------------------------------------------- 
INTI:	MOV 20H,#00H
	    MOV A,20H
		MOV C2 , #08H
		MOV First , #00H	 ;第一个数码管
		MOV Two ,   #00H
		MOV Three , #00H
		MOV Four ,  #00H	;第四个数码管
;--------------------------------------------------------------
;主程序程序
;-------------------------------------------------------------- 
MAIN:

		CALL Num_Handle	 ;调用子程序 数字的进位处理
	    CALL Display	 ;调用显示 子程序
	    CALL Code138     ;处理译码器 子程序
		MOV C2 , #08H
	 	AJMP MAIN

;--------------------------------------------------------------
;数码管数字显示子程序
;-------------------------------------------------------------- 
Display:	
		MOV A , First
		ANL A,#0FH	    ;屏蔽累加器的高4位
		MOV DPTR,#TAB	;将数据表格的首地址 0100H存入16位的数据地址指针DPTR中
		MOVC A,@A+DPTR	;查表
		MOV 60H,A	    
	
		MOV A , Two
		ANL A,#0FH	    ;屏蔽累加器的高4位
		MOV DPTR,#TAB	;将数据表格的首地址 0100H存入16位的数据地址指针DPTR中
		MOVC A,@A+DPTR	;查表
		MOV 61H,A	    
	
	
		MOV A , Three
		ANL A,#0FH	    ;屏蔽累加器的高4位
		MOV DPTR,#TAB	;将数据表格的首地址 0100H存入16位的数据地址指针DPTR中
		MOVC A,@A+DPTR	;查表
		MOV 62H,A	    
	 
		MOV A , Four
		ANL A,#0FH	    ;屏蔽累加器的高4位
		MOV DPTR,#TAB	;将数据表格的首地址 0100H存入16位的数据地址指针DPTR中
		MOVC A,@A+DPTR	;查表
		MOV 63H,A
		
		MOV 64H,60H	
		MOV 65H,61H	
		MOV 66H,62H	
		MOV 67H,63H	    
	
		RET
;--------------------------------------------------------------
;数字变化子程序
;-------------------------------------------------------------- 
Num_Handle:
	    MOV A , First 
		ADD A , #01H
		MOV First , A
		CJNE A , #0AH , DONE   ;若A等于10 向下执行 否则跳转
		MOV First , #00H
	
		MOV A ,Two
		ADD A , #01H
	    MOV Two , A
		CJNE A , #0AH	, DONE
		MOV Two , #00H
	
		MOV A , Three
		ADD A , #01H
		MOV Three , A
		CJNE A , #0AH , DONE
		MOV Three , #00H
	
		MOV A , Four
		ADD A , #01H
		MOV  Four , A
		CJNE A , #0AH , DONE
		MOV  Four , #00H

DONE:   RET

;--------------------------------------------------------------
;控制译码器子程序
;--------------------------------------------------------------      
Code138:
	   	  CLR A
LAB1:     MOV R5 , A
		  ADD A , #60H 
		  MOV R0 , A
		  MOV P0 , @R0	   ;60H地址开始的数据送到P0口
	  	  MOV A , R5       ;将累加器的数据暂存在R5中  准备移位
		  MOV DPTR ,#TAB1  ;将数据表格的首地址 0120H存入16位的数据地址指针DPTR中
		  MOVC A , @A+DPTR ;查表 (译码器的三个控制脚 P2.3 P2.4 P2.5)
		  MOV P2 , A	   ;将其移位结果送到P2口
		  MOV A , R5	 
		  CALL DEL1mS 	   ;调用延时子程序
		  INC A
		  DJNZ C2 ,LAB1	   ;如果为0 向下执行 否则跳转到 CODE138
		  RET

;--------------------------------------------------------------
;延时子程序
;-------------------------------------------------------------- 
DEL1mS: MOV R6,#02H
DEL1:	MOV R7,#0FFH
    	DJNZ R7,$
	    DJNZ R6,DEL1
    	RET


	 ORG 0100H
TAB: DB 0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x40	;LED字模表
     
	ORG 0120H
TAB1:DB 0xff,0xfb,0xf7,0xf3,0xef,0xeb,0xe7,0xe3       //位码 查表的方法控制译码器
	
	END

	
