/**********************************************************************************
*  标题:               74HC573输出使能试验(单片机直接实现位选 共阴极)             *
*																			      *
                                                  *
*  连接方法：JP10(P0)与J12 用8PIN排线连接	 J16与JP11(P2) 用排线连接
              J21的短路帽挂左边（P1.0）					  *
***********************************************************************************
*  目的：熟悉74HC573的LE输出使能控制                       	       				  *
*  请学员认真消化本例程，用573锁存器控制和单片机脚直接位选控制(非译码器控制)数码管*
***********************************************************************************/

#include "mcs51/8051.h"

void delay(unsigned int i); //函数声名
#define LE P1_0           //定义输出使能控制脚在P1.0上

char DelayCNT; //定义变量

//此表为 LED 的字模, 共阴数码管 0-9  -
unsigned char code Disp_Tab[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d,
                                 0x7d, 0x07, 0x7f, 0x6f, 0x40}; //段码控制

//此表为8个数码管位选控制, 共阴数码管 1-8个  -
unsigned char code dispbit[ 8 ] = {0xfe, 0xfd, 0xfb, 0xf7,
                                   0xef, 0xdF, 0xbF, 0x7F}; //位选控制   查表的方法控制

/************主函数**********************/
main() {
    unsigned int i, LedNumVal = 1; //变量定义
    unsigned int LedOut[ 10 ];     //变量定义

    DelayCNT = 0;

    while (1) {
        if (++DelayCNT >= 20) //控制数字变化速度
        {
            DelayCNT = 0; // 20个扫描周期清零一次
            ++LedNumVal;  //每隔20个扫描周期加一次
        }

        LedOut[ 0 ] = Disp_Tab[ LedNumVal % 10000 / 1000 ];
        LedOut[ 1 ] = Disp_Tab[ LedNumVal % 1000 / 100 ] | 0x80;
        LedOut[ 2 ] = Disp_Tab[ LedNumVal % 100 / 10 ];
        LedOut[ 3 ] = Disp_Tab[ LedNumVal % 10 ];

        LedOut[ 4 ] = Disp_Tab[ LedNumVal % 10000 / 1000 ];      //千位
        LedOut[ 5 ] = Disp_Tab[ LedNumVal % 1000 / 100 ] | 0x80; //百位带小数点
        LedOut[ 6 ] = Disp_Tab[ LedNumVal % 100 / 10 ];          //十位
        LedOut[ 7 ] = Disp_Tab[ LedNumVal % 10 ];                //个位

        for (i = 0; i < 9; i++) {
            LE = 0; //输出使能，锁存器不输出数据
            P0 = LedOut[ i ];
            LE = 1;            //输出使能，锁存器将8位数据一口吐出
            P2 = dispbit[ i ]; //使用查表法进行位选

            delay(150); //扫描间隔时间	  太长会数码管会有闪烁感
        }
        LE = 0; //锁存器不输出数据
    }
}

/**************************************************************************
 *
 *                      延时处理
 *
 ****************************************************************************/
void delay(unsigned int i) {
    char j;
    for (i; i > 0; i--)
        for (j = 200; j > 0; j--)
            ;
}
