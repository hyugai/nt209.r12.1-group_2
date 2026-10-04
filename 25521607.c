#include <stdio.h>

int divpw2(int x, int n) {
    int tmp = ~n + 1;   // tmp = -n (dương)
    return x << tmp;    // x * 2^(-n) = x / 2^n
}

int divpw2s(int x, int n) {
    int mask = x >> 31;               // 0x00000000 nếu x >= 0, 0xFFFFFFFF nếu x < 0
    int bias = mask & ((1 << n) - 1); // bias = 2^n - 1 nếu x âm, 0 nếu x dương
    return (x + bias) >> n;
}	

int isOpposite(int x, int y) {
    return !(x ^ (~y + 1)) & !!(x ^ y);
}

int is16x(int x) {
    return !(x & 15);
}

unsigned float_twice(unsigned uf) {
    unsigned sign = uf & 0x80000000;
    unsigned exp  = (uf >> 23) & 0xFF;
    unsigned frac = uf & 0x007FFFFF;
 
    if (exp == 0xFF) return uf;                // NaN hoặc ±∞
    if (exp == 0)                               // số không chuẩn hóa
        return sign | ((uf & 0x7FFFFFFF) << 1);
    exp = exp + 1;                              // nhân 2 = tăng exp
    if (exp == 0xFF) return sign | 0x7F800000;  // tràn → ±∞
    return sign | (exp << 23) | frac;
}

int main()
{
    printf("%d\n",divpw2(10,-1));
    printf("%d\n",divpw2(15,-2));
    printf("%d\n",divpw2(2,-4));
    printf("%d\n",divpw2(1,-30));
    
    printf("%d\n",divpw2s(15,1));
    printf("%d\n",divpw2s(-15,1));
    printf("%d\n",divpw2s(-33,4));
    printf("%d\n",divpw2s(-8,2));
    printf("%d\n",divpw2s(-1,1));
    printf("%d\n",divpw2s(0,0));

    printf("%d\n",isOpposite(-2,2));
    printf("%d\n",isOpposite(4,4));
    printf("%d\n",isOpposite(0,0));
    printf("%d\n",isOpposite(0x80000000, 0x80000000));
    printf("%d\n",isOpposite(5,-5));

    printf("%d\n", is16x(16));
    printf("%d\n", is16x(48));
    printf("%d\n", is16x(3));
    printf("%d\n", is16x(0));
    printf("%d\n", is16x(-32));

    printf("0x%08X\n", float_twice(0x3F800000));
    printf("0x%08X\n", float_twice(0x00000001));
    printf("0x%08X\n", float_twice(0x007FFFFF));
    printf("0x%08X\n", float_twice(0x7F7FFFFF));
    printf("0x%08X\n", float_twice(0xFF7FFFFF));
    printf("0x%08X\n", float_twice(0x7F800000));
    printf("0x%08X\n", float_twice(0x7FC00000));
    printf("0x%08X\n", float_twice(0x80000000));
    return 0;
}