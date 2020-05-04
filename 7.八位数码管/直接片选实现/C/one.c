/*
* 显示8个数码管中的最右侧等一个
*/

#include "mcs51/8051.h"

int main(){
    while(1){
        P0=0x3f;//数值
        P1=0x7f;//位置
    }
}