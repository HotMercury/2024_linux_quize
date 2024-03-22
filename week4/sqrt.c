#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <strings.h>

typedef int (*func_t)(int);
int i_sqrt1(int n);
int i_sqrt2(int n);
int i_sqrt3(int n);
int i_sqrt4(int n);
int i_sqrt5(int n);

func_t f = i_sqrt5;
int n = 0;
static inline unsigned long __ffs(int word);
int main(int argc, char *argv[]){
    if(argc == 1){
        printf("Usage: %s <number>\n", argv[0]);
        return 1;
    }else{
        n = atoi(argv[1]);
        if(n < 0){
            printf("The number must be positive\n");
            return 1;
        }
    }
    printf("The square root of %d is %d\n", n, f(n));
    return 0;
}
int i_sqrt1(int n){
    int msb = (int)log2(n);
    printf("The most significant bit is %d\n", msb);
    int a = 1 << msb;
    int result = 0;
    while(a != 0){
        if((result + a) * (result + a) <= n)
            result += a;
        a >>= 1; 
    }
    return result;
}

int i_sqrt2(int N)
{
    int msb = 0;
    int n = N;
    while (n > 1) {
        n >>= 1;
        msb++;
    }
    int a = 1 << msb;
    int result = 0;
    while (a != 0) {
        if ((result + a) * (result + a) <= N)
            result += a;
        a >>= 1;
    }
    return result;
} 

int i_sqrt3(int n)
{
    if (n <= 1) /* Assume n is always positive */
        return n;

    int c = 0;
    for (int d = 1UL << ((31 - __builtin_clz(n)) & ~1UL); d; d >>= 2) {
        int y = c + d;
        c >>= 1;
        if (n >= y)
            n -= y, c += d;               
    }
    return c;
}

int i_sqrt4(int n)
{
    if (n <= 1) /* Assume n is always positive */
        return n;

    int c = 0;
    for (int d = 1UL << ((31 - ffs(n)) & ~1UL); d; d >>= 2) {
        int y = c + d;
        c >>= 1;
        if (n >= y)
            n -= y, c += d;               
    }
    return c;
}

// replace ffs with __ffs
int i_sqrt5(int n)
{
    if (n <= 1) /* Assume n is always positive */
        return n;

    int c = 0;
    for (int d = 1UL << ((31 - __ffs(n)) & ~1UL); d; d >>= 2) {
        int y = c + d;
        c >>= 1;
        if (n >= y)
            n -= y, c += d;               
    }
    return c;
}
static inline unsigned long __ffs(int word)
{
    int num = 0;

#if BITS_PER_LONG == 64
    if ((word & 0xffffffff) == 0) {
        num += 32;
        word >>= 32;
    }
#endif
    if ((word & 0xffff) == 0) {
        num += 16;
        word >>= 16;
    }
    if ((word & 0xff) == 0) {
        num += 8;
        word >>= 8;
    }
    if ((word & 0xf) == 0) {
        num += 4;
        word >>= 4;
    }
    if ((word & 0x3) == 0) {
        num += 2;
        word >>= 2;
    }
    if ((word & 0x1) == 0)
        num += 1;
    return num;
}