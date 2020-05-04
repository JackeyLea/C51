#include "mcs51/8051.h"

void delay(unsigned int i); //函数声名

//此表为 LED 的字模, 共阴数码管 0-9  -
unsigned char Disp_Tab[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d,
                            0x7d, 0x07, 0x7f, 0x6f, 0x40}; //段码控制

//此表为8个数码管位选控制, 共阴数码管 1-8个  -
unsigned char dispbit[ 8 ] = {0xfe, 0xfd, 0xfb, 0xf7,
                              0xef, 0xdF, 0xbF, 0x7F}; //位选控制   查表的方法控制

int main(){
    unsigned int i,LedNumVal=1;
    int count=0;
    while(1){
        if(count>=200){
            count=0;
            LedNumVal++;
        }
        for(i=0;i<9;i++){
            if(i==0){
                P0=Disp_Tab[LedNumVal%8];
                P1=0x7f;
            }
            if(i==2){
                P0=Disp_Tab[LedNumVal%8];
                P1=0xdf;
            }
            delay(1);//扫描间隔时间 太长会数码管会有闪烁感
            count++;
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
