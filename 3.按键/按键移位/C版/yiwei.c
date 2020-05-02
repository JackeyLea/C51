/*******************************************************************************
 *           按键控制程序      								                   *
 *  连接方法：JP10（P2） 与 J12 （LED灯）连接，   							   *
 *            JP11（P0） 与 JP5（按键接口）连接                                 *
 *         开始点亮P1LED                                  		               *
 *         按P01 LED向右移一位                                                  *
 *         按P00 LED向左移一位                                         	       *
 *	 连续按动按钮LED会不停的左移或右移										   *
 *******************************************************************************/
#include <mcs51/8051.h>

unsigned char scan_key();
void          proc_key(unsigned char key_v);
void          delayms(unsigned char ms);
#define       K1 P0_0 //对应按钮K1
#define       K2 P0_1 //对应按钮K2

main() {
    unsigned char key_s, key_v;
    key_v = 0x03;
    P2    = 0xfe;
    while (1) {
        key_s = scan_key();
        if (key_s != key_v) {
            delayms(10);
            key_s = scan_key();
            if (key_s != key_v) {
                key_v = key_s;
                proc_key(key_v);
            }
        }
    }
}

unsigned char scan_key() {
    unsigned char key_s;
    key_s = 0x00;
    key_s |= K2;
    key_s <<= 1;
    key_s |= K1;
    return key_s;
}

void proc_key(unsigned char key_v) {
    if ((key_v & 0x01) == 0) {
        P2 = (P2<<(8-1))|(P2>>1);
    } else if ((key_v & 0x02) == 0) {
        P2 = (P2<<(8-1))|(P2>>1);
    }
}

void delayms(unsigned char ms) // 延时子程序
{
    unsigned char i;
    while (ms--) {
        for (i = 0; i < 120; i++)
            ;
    }
}
