files: main1 main2

main1: libd2.so prog1.c
    gcc prog1.c -L. -ld2 -o main1 -Wl,-rpath -Wl,.

main2: libd1.so libd2.so prog2.c
    gcc prog2.c -L. -ld1 -ld2 -o main2 -Wl,-rpath -Wl,.

libd1.so: d1.o
    gcc -shared d1.o -o libd1.so

libd2.so: d2.o
    gcc -shared d2.o -o libd2.so

d1.o: first.c
    gcc -fPIC -c first.c -o d1.o

d2.o: second.c
    gcc -fPIC -c second.c -o d2.o

clean:
    rm -f *.so *.o main1 main2
