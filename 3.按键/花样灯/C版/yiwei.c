/*******************************************************************************
*           按键控制程序      								                   *
*  连接方法：JP10（P2） 与 J12 （LED灯）连接，   							   *
*            JP11（P0） 与 JP5（按键接口）连接                                 *
             用led读出按键的状态

本节主要注意：switch 语句的用法   函数的调用
                                                                               *
*******************************************************************************/
#include <mcs51/8051.h>

unsigned int key;
void         delay(unsigned ms);
void         scan_key();
void         led1();
void         led2();
void         led3();
void         led4();
void         led5();
void         led6();
void         led7();
void         led8();

main() {
    while (1) {
        scan_key(); //检测按键

        switch (key) //读出对应值
        {
            case 1:
                led1();
                key = 0;
                break;
            case 2:
                led2();
                key = 0;
                break;
            case 3:
                led3();
                key = 0;
                break;
            case 4:
                led4();
                key = 0;
                break;
            case 5:
                led5();
                key = 0;
                break;
            case 6:
                led6();
                key = 0;
                break;
            case 7:
                led7();
                key = 0;
                break;
            case 8:
                led8();
                key = 0;
                break;
            default:;
        }
    }
}

void led1() // led 左移
{
    unsigned char i;
    P2 = 0x01;
    for (i = 8; i > 0; i--) {
        P2 <<= 1;
        delay(100);
    }
}

void led2() // led右移
{
    unsigned char i;
    P2 = 0x80;
    for (i = 8; i > 0; i--) {
        P2 >>= 1;
        delay(100);
    }
}

void led3() // led 交替闪1
{
    P2 = 0xaa;
    delay(100);
    P2 = 0x55;
    delay(100);
    P2 = 0xaa;
    delay(100);
    P2 = 0x55;
    delay(100);
}

void led4() ////led 交替闪2
{
    P2 = 0x55;
    delay(100);
    P2 = 0xaa;
    delay(100);
    P2 = 0x55;
    delay(100);
    P2 = 0xaa;
    delay(100);
}

void led5() ////led 交替闪3
{
    P2 = 0xcc;
    delay(100);
    P2 = 0x33;
    delay(100);
    P2 = 0xcc;
    delay(100);
    P2 = 0x33;
    delay(100);
}

void led6() ////led 交替闪4
{
    P2 = 0x33;
    delay(100);
    P2 = ~P2; //取反
    delay(100);
    P2 = ~P2;
    delay(100);
    P2 = ~P2;
    delay(100);
}

void led7() {
    led1();
    led2();
    led3();
    led4();
    led5();
    led6(); //全来一遍
}

void led8() {
    P2 = 0XFF; //全亮
}

void scan_key() //按键检测函数
{
    if (P0 == 0xfe)
        key = 1;
    if (P0 == 0xfd)
        key = 2;
    if (P0 == 0xfb)
        key = 3;
    if (P0 == 0xf7)
        key = 4;
    if (P0 == 0xef)
        key = 5;
    if (P0 == 0xdf)
        key = 6;
    if (P0 == 0xbf)
        key = 7;
    if (P0 == 0x7f)
        key = 8;
}

void delay(unsigned ms) {
    unsigned i, j;
    for (i = ms; i > 0; i--)
        for (j = 110; j > 0; j--)
            ;
}
