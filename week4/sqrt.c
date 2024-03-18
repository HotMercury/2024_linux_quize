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

func_t f = i_sqrt4;
int n = 0;
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

int i_sqrt5(int n)
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