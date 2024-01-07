#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

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

    float sum = 0, number;

    int fd = shm_open("/my_shared_memory", O_RDWR, S_IRWXU);
    float *shared_data = (float* )mmap(NULL, sizeof(float), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    close(fd);

    while (fscanf(file, "%f", &number) != EOF) {
        sum += number;
    }

    fclose(file);

    *shared_data = sum;
    munmap(shared_data, sizeof(float));
    
    return 0;
}
