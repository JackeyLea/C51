/********************************************************************************
;*         	        跑马灯实验                                                  *
;																				*
;     延时实现LED流水灯效果   p2口八个灯作跑马灯。采用了寄存器存中间数	        *
;     连接方法： JP11（P2）和J12(LED灯) 用8PIN排线连接起来					    *
;********************************************************************************/

#include "mcs51/8051.h"

void delay(unsigned int i); //声明延时函数
char LED;

main() {
    unsigned char i;

    while (1) {
        LED = 0xfe;

        for (i = 0; i < 8; i++) {
            P2 = LED;
            delay(500);
            LED = LED << 1;   // 左移
            LED = LED | 0x01; // 移位后，后面的位为高电平
            if (LED == 0x7f)
                break; //提前退出 FOR 循环
        }

        for (i = 0; i < 8; i++) {

            P2 = LED;
            delay(500);
            LED = LED >> 1;   // 右移
            LED = LED | 0x80; // 移位后，后面的位为高电平
        }
    }
}

/*******延时函数*************/
void delay(unsigned int i) {
    unsigned char j;
    for (i; i > 0; i--)
        for (j = 255; j > 0; j--)
            ;
}
