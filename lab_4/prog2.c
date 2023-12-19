#include <stdio.h>
#include <dlfcn.h>

int main(int argc, char* argv[]) {

    void *ext_library = NULL;
    int (*PrimeCount)(int a, int b);
    float (*E)(int x);

    int key, start_library;
    printf("Choose start library: 1 or 2: ");
    scanf("%d\n", &start_library);
    if(start_library == 1) {
        ext_library = dlopen("/Users/n/Projects/OS/lab_4/libd1.so", RTLD_LAZY);

    }
    else if(start_library == 2) {
        ext_library = dlopen("/Users/n/Projects/OS/lab_4/libd2.so", RTLD_LAZY);
    }
    else {
        printf("Don't write right key\n");
    }

    if(!ext_library) {
        fprintf(stderr, "dlopen() error %s\n", (char* )dlerror);
        return 1;
    }

    PrimeCount = dlsym(ext_library, "PrimeCount");
    E = dlsym(ext_library, "E");
    while (scanf("%d",&key) > 0) {
        if(key == 1) {
            int a, b;
            scanf("%d%d", &a, &b);
            printf("%s(%d, %d) = %d\n","PrimeCount", a, b, (*PrimeCount)(a, b));
        } 
        else if(key == 2) {
            int x;
            scanf("%d", &x);
            printf("%s(%d) = %f\n","E",x,(*E)(x));
        } 
        else if(key == 0) {
            dlclose(ext_library);
            if(start_library == 1) {
                ext_library = dlopen("./libd2.so", RTLD_LAZY);
                start_library = 2;
            } 
            else if(start_library == 2) {
                ext_library = dlopen("./libd1.so", RTLD_LAZY);
                start_library = 1;
            }
            if(!ext_library) {
                fprintf(stderr,"dlopen() error: %s\n", (char* )dlerror());
                return 1;
            }
            PrimeCount = dlsym(ext_library,"PrimeCount");
            E = dlsym(ext_library, "E");
        }
    }

    dlclose(ext_library);
}
