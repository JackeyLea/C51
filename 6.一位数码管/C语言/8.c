#include <mcs51/8051.h>

main() {
    while (1) {
        // 将字模送到P0口显示
        P0 = 0x80;//显示小数点
    }
}