#include <stdlib.h>
#include <math.h>

int PrimeCount(int a, int b) {
    int *primes = (int* )malloc((b + 1) * sizeof(int));
    int count = 0;
    
    for(int i = 0; i <= b; i++) {
        primes[i] = 1;
    }

    primes[0] = primes[1] = 0;

    for(int p = 2; p * p <= b; p++) {
        if(primes[p] == 1) {
            for(int i = p * p; i <= b; i += p) {
                primes[i] = 0;
            }
        }
    }

    for(int i = a; i <= b; i++) {
        if(primes[i] == 1) {
            count++;
        }
    }
    free(primes);
    return count;
}

float E(int x) {
    double ans = 0, s = 1;
    for(int i = 0; i <= x; i++) {
        if(i != 0) {
            s *= i;
        }
        ans += 1. / s;
    }
    return ans;
}
