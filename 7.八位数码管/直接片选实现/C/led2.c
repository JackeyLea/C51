/**********************************************************************************
*  标题:                  试验数码管上显示数字( 单片机直接实现位选 共阴极)        *
*																			      *
*  连接方法：JP15和JP16短路帽断开 JP8（P1）与J16 用排线连接
                                     JP10（P0）与J12相连 						  *
***********************************************************************************
*                         	       										          *
* 请学员认真消化本例程，用573锁存器控制和单片机脚直接位选控制(非译码器控制)数码管 *
***********************************************************************************/

#include "mcs51/8051.h"

void delay(unsigned int i); //函数声名
char DelayCNT;              //定义变量

//此表为 LED 的字模, 共阴数码管 0-9  -
unsigned char Disp_Tab[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d,
                            0x7d, 0x07, 0x7f, 0x6f, 0x40}; //段码控制

//此表为8个数码管位选控制, 共阴数码管 1-8个  -
unsigned char dispbit[ 8 ] = {0xfe, 0xfd, 0xfb, 0xf7,
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
            P0 = LedOut[ i ];
            P1 = dispbit[ i ]; //使用查表法进行位选

            /*	  switch(i)			   //使用switch 语句控制位选
                     {
                        case 0:P1 = 0x7F;  break;
                        case 1:P1 = 0xbF;  break;
                        case 2:P1 = 0xdF;  break;
                        case 3:P1 = 0xeF;  break;
                        case 4:P1 = 0xf7;  break;
                        case 5:P1 = 0xfb;  break;
                        case 6:P1 = 0xfd;  break;
                        case 7:P1 = 0xfe;  break;

                     }	   */

            delay(150); //扫描间隔时间	  太长会数码管会有闪烁感
        }
    }
}

/*******************延时函数**********************************************/
void delay(unsigned int i) {
    char j;
    for (i; i > 0; i--)
        for (j = 200; j > 0; j--)
            ;
}
