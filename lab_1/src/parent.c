#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main() {
    char filename[100];
    printf("Введите имя файла для чтения: ");
    fgets(filename, sizeof(filename), stdin);

    
    int len = strlen(filename);
    if (filename[len - 1] == '\n') {
        filename[len - 1] = '\0';
    } 

    int fd[2];
    if (pipe(fd) == -1) {
        perror("Ошибка при создании pipe");
        exit(-1);
    }

    pid_t child_id = fork();

    if (child_id == -1) {
        perror("Ошибка при создании дочернего процесса");
        exit(-1);
    }

    if (child_id == 0) {
        close(fd[0]);
        if(dup2(fd[1], STDOUT_FILENO) == -1) {
            perror("Ошибка в dup2");
            exit(-1);
        }
        close(fd[1]);

        if(execlp("./child", "./child", filename, NULL) == -1) {
            perror("Ошибка при запуске дочернего процесса");
            exit(-1);
        };
    } 
    
    else {
        close(fd[1]);
        char buffer[100];
        ssize_t read_bytes;

        while ((read_bytes = read(fd[0], buffer, sizeof(buffer))) > 0) {
            write(STDOUT_FILENO, buffer, read_bytes);
            //if(read_bytes != sizeof())
        }

        close(fd[0]);
        wait(NULL);    
    }

    return 0;
}
