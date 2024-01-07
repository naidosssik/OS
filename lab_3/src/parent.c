#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <string.h>
#include <fcntl.h>


#define MAX_SIZE 100000

int main() {
    char filename[MAX_SIZE];
    printf("Введите имя файла для чтения: ");
    fgets(filename, sizeof(filename), stdin);

    
    int len = strlen(filename);
    if (filename[len - 1] == '\n') {
        filename[len - 1] = '\0';
    } 

    int fd = shm_open("/my_shared_memory", O_CREAT | O_RDWR | S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("Ошибка при создании shared memory");
        exit(EXIT_FAILURE);
    }

    if(ftruncate(fd, sizeof(float)) == -1) {
        perror("Ошибка");
        exit(EXIT_FAILURE);
    }

    float *shared_data = (float* )mmap(NULL, sizeof(float), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
        

    pid_t child_id = fork();

    if (child_id == -1) {
        perror("Ошибка при создании дочернего процесса");
        exit(-1);
    }
    
    if (child_id == 0) { //child
        close(fd);
        exit(EXIT_SUCCESS);


        if(execlp("./child", "./child", filename, NULL) == -1) {
            perror("Ошибка при запуске дочернего процесса");
            exit(-1);
        };
    } 
    
    else {
        
        FILE *file = fopen(filename, "r");
        if (file == NULL) {
            perror("Ошибка открытия файла");
            exit(-1);
        }

        float number;
        while(fscanf(file, "%f", &number) != EOF) {
            *shared_data += number;
        }

        fclose(file);
        wait(NULL);

        printf("Сумма чисел из файла %s: %f\n", filename, *shared_data);

        munmap(shared_data, sizeof(float));
        shm_unlink("/my_shared_memory");
    }

    return 0;
}
