#include <math.h>

int IsPrime(int n) {
    if(n < 2) {
        return 0;
    }
    for(int i = 2; i * i <= n; i++) {
        if(n % i == 0) {
            return 0;
        }
    }
    return 1;
}

int PrimeCount(int a, int b) {
    int count = 0;

    for(int i = a; i <= b; i++) {
        if(IsPrime(i) == 1) {
            count++;
        }
    }
    
    return count;
}

float E(int x) {
    return pow((1 + 1. / x), x);
}

