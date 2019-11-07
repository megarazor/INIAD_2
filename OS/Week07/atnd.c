#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

/**
 * Sets i-th (0 <= 0 < 32) bit of data stored at address to 1.
 * addressに格納されているdataのi bit目に1をセットする
 */
void setbit(uint32_t *address, int i) {
    uint32_t bit= 1;
    bit= bit << i;
    *address= *address | bit;
}

/**
 * Gets i-th (0 <= 0 < 32) bit of data stored at address.
 * addressに格納されているdataのi bit目を返す
 */
unsigned getbit(uint32_t *address, int i) {
    uint32_t bit= 1;
    bit= bit << i;
    bit= bit & *address;
    bit= bit >> i;
    return bit;
}

void printbit(unsigned n) {
    printf("0b");
    for (int i = sizeof(unsigned) * 8 - 1; i >= 0; i--) {
        printf("%d", (n & (1 << i)) != 0);
    }
    printf("\n");
    printf("%x\n", n);
}

int __test_num = 0;

#define test(desc, _c) do { \
    printf("%d - %s: %s\n", ++__test_num, desc, (_c) ? "PASSED" : "FAILED"); \
} while (0)

int main(int argc, char const* argv[])
{
    unsigned data = 0x0a0a0a0a;
    printbit(data);
    setbit(&data, 0);
    test("setbit 0", data == 0x0a0a0a0b /*== 0b00001010000010100000101000001011*/);
    setbit(&data, 0);
    test("do nothing if already set bit",
         data == 0x0a0a0a0b /*== 0b00001010000010100000101000001011*/);
    test("getbit 0",
         getbit(&data, 0) == 1 /*== 0b00000000000000000000000000000001*/);
    return 0;
}