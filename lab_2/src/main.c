#include <stdio.h>
#include <stdlib.h> // для работы с памятью
#include <string.h>
#include <errno.h> 
#include <pthread.h>
#include <stdint.h>

#define MAX_THREADS 1000
#define MAX_STRING_LENGTH 1000

char main_string[MAX_STRING_LENGTH];
char substring[MAX_STRING_LENGTH];
int size, number_threads;
int len_substring, len_string;
int *result;
//int result_size = 0;


void *search_substring(void *arg) {
    long thread_id = (long)arg;
    int start = thread_id * (len_string / number_threads);
    int end = (thread_id + 1) * (len_string / number_threads);

    for(int i = start; i < end; i++) {
        int j;
        for(j = 0; j < len_substring; j++) {
            if(main_string[i + j] != substring[j]) {
                break;
            }
        }
        if (j == len_substring) {
            result[i] = 1;
        }
    }
    pthread_exit(NULL);
}


int main(int argc, char *argv[]) {
    
    if(argc != 2) {
        perror("Неверное число параметров");
        exit(-1);
    }
    number_threads = atoi(argv[1]);
    if (number_threads <= 0 || number_threads > MAX_THREADS) {
        perror("Недопустимое число потоков");
        exit(-1);
    }
    
    printf("Введите строку: ");
    fgets(main_string, MAX_STRING_LENGTH, stdin);
    len_string = strlen(main_string);
    if(main_string[len_string - 1] == '\n') {
        main_string[len_string - 1] = '\0';
        len_string--;
     }

    printf("Введите подстроку для поиска: ");
    fgets(substring, MAX_STRING_LENGTH, stdin);
    len_substring = strlen(substring);
    if(substring[len_substring - 1] == '\n') {
        substring[len_substring - 1] = '\0';
        len_substring--;
    }

    result = (int *)malloc(number_threads * sizeof(int));
    pthread_t threads[number_threads];
    int new_thread;

    for(int t = 0; t < number_threads; t++) {
        new_thread = pthread_create(&threads[t], NULL, search_substring, (void *)(intptr_t)t);

        if(new_thread) {
            perror("Ошибка при создании потока");
            exit(-1);
        }
    }

    for(int t = 0; t < number_threads; t++) {
        pthread_join(threads[t], NULL);
    }

    int ans = 0;
    for(int i = 0; i < number_threads; i++) {
        if(result[i] == 1) {
            ans = 1;
            break;
        }
    }

    if(ans) {
        printf("Подстрока найдена\n");
    }
    else {
        printf("Подстрока не найдена\n");
    }

    free(result);
    return 0;
}
