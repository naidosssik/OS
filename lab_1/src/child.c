#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Использование: %s <имя файла>\n", argv[0]);
        exit(-1);
    }

    char *filename = argv[1];
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        perror("Ошибка при открытии файла");
        exit(-1);
    }

    float sum = 0;
    float number;

    while (fscanf(file, "%f", &number) != EOF) {
        sum += number;
    }

    printf("Сумма чисел из файла %s: %f\n", filename, sum);
    fclose(file);
    
    return 0;
}
