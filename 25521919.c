#include <stdio.h>
#include <stdlib.h>
//BT2.3
int isPositive(int x)
{
    int y = x>>31;
    int isZero = !x;
    return  !(y|isZero) ;
}
//BT2.4
int isGE2(int x,int n)
{
    int y = 1 << n;
    int z = ~y + 1;
    int u = (x+z)>>31;
    return !u;
}
//BT2.5
int subOK(int x, int y)
{
  int  kq = x + (~y + 1);

  int  sx = (x >> 31) ;
  int sy = (y >> 31) ;
  int  skq = (kq >> 31) ;

    return !((sx ^ sy) & (skq ^ sx));
}
//BT2.6
int bitParity(int x)
{
    x = x^(x>>16);
    x = x^(x>>8);
    x = x^(x>>4);
    x = x^(x>>2);
    x = x^(x>>1);
    return x&1;

}
//BT3.4
int float_f2i(unsigned uf)
{
    unsigned sign = uf >> 31;
    unsigned frac = uf & 0x7FFFFF;
    int exp = (uf >> 23) & 0xFF;
    int E;

    if (exp == 0xFF)
        return 0x80000000;

    E = exp - 127;

    if (E < 0)
        return 0;
    if (E >= 31)
        return 0x80000000;

    frac = frac | 0x800000;

    if (E > 23)
        frac = frac << (E - 23);
    else
        frac = frac >> (23 - E);

    if (sign)
        return -(int)frac;

    return (int)frac;
}
int main()
{

    return 0;
}
