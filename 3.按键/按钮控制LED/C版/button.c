/*******************************************************************************
*           按键控制程序                                                         *
*  连接方法：JP10（P2） 与 J12 （LED灯）连接，                               *
*            JP11（P0） 与 JP5（按键接口）连接                                 *
            用led读出按键的状态
*******************************************************************************/
#include <mcs51/8051.h>

unsigned int key;
void         scan_key();

main() {
    while (1) {
        scan_key(); //检测按键

        switch (key) //读出对应值
        {
            case 1:
                P2 = 0x01;
                break;
            case 2:
                P2 = 0x02;
                break;
            case 3:
                P2 = 0x04;
                break;
            case 4:
                P2 = 0x08;
                break;
            case 5:
                P2 = 0x10;
                break;
            case 6:
                P2 = 0x20;
                break;
            case 7:
                P2 = 0x40;
                break;
            case 8:
                P2 = 0x80;
                break;
            default:;
        }
    }
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