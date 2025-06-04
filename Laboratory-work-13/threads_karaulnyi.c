#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

// Функція f1
void* f1(void* arg) {
    int n = *(int*)arg;
    for (int i = 1; i <= n; i++) {
        printf("f1: Hello from Karaulnyi - function 1 (%d)\n", i);
        sleep(1);
    }
    pthread_exit(0);
}

// Функція f2
void* f2(void* arg) {
    int n = *(int*)arg;
    for (int i = 1; i <= n; i++) {
        printf("f2: Hello from Karaulnyi - function 2 (%d)\n", i);
        sleep(1);
    }
    pthread_exit(0);
}

int main(void) {
    pthread_t f1_thread, f2_thread;

    int iterations = 17; // 12 (варіант) + 5

    // Створення потоків
    pthread_create(&f1_thread, NULL, f1, &iterations);
    pthread_create(&f2_thread, NULL, f2, &iterations);

    // Очікування завершення потоків
    pthread_join(f1_thread, NULL);
    pthread_join(f2_thread, NULL);

    printf("Main thread: Both threads finished.\n");

    return 0;
}
