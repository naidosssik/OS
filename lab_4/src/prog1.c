#include <stdio.h>

int PrimeCount(int a,int b);
float E(int x);

int main() {
    int key;
    while(scanf("%d", &key) > 0) {
        if(key == 1) {
            int a, b;
            scanf("%d%d", &a, &b);
            printf("Prime count on segment from %d to %d : %d\n", a, b, PrimeCount(a, b));
        }
        else if(key == 2) {
            int x;
            scanf("%d", &x);
            printf("E(%d) = %f\n", x, E(x));
        }
        else {
            printf("Error\n");
        }
    }

    return 0;
}