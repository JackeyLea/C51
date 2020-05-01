#include "/usr/share/sdcc/include/mcs51/8051.h"

#define Beep P1_5

void delay(unsigned int i);
void main() {
    Beep = 1;
    delay(5);
    Beep = 0;
    delay(5);
}

void delay(unsigned int i) {
    char j;
    for (i; i > 0; i--)
        for (j = 200; j > 0; j--)
            ;
}
