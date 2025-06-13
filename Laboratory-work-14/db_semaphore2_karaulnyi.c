#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>
#include <fcntl.h> // Додано для O_CREAT

// Структура, що відповідає реляційній таблиці printer
typedef struct {
    int pr_id;
    char model[20];
    int year;
} Printer;

// Глобальна змінна для даних
Printer db_printer = {1, "HP LaserJet", 2020};

// Двійковий семафор
sem_t *semaphore;

// Функція для потоку T1
void* T1(void* arg) {
    // Затримка для імітації паралельної роботи
    usleep(100000);
    
    // Читання значення
    printf("T1: Read year = %d\n", db_printer.year);
    
    // Захоплення семафору
    sem_wait(semaphore);
    
    // Критична секція: зміна значення
    db_printer.year += 1;
    printf("T1: Updated year = %d\n", db_printer.year);
    
    // Звільнення семафору
    sem_post(semaphore);
    
    return NULL;
}

// Функція для потоку T2
void* T2(void* arg) {
    // Затримка для імітації паралельної роботи
    usleep(150000);
    
    // Читання значення
    printf("T2: Read year = %d\n", db_printer.year);
    
    // Захоплення семафору
    sem_wait(semaphore);
    
    // Критична секція: зміна значення
    db_printer.year += 2;
    printf("T2: Updated year = %d\n", db_printer.year);
    
    // Звільнення семафору
    sem_post(semaphore);
    
    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    
    // Ініціалізація семафору з назвою "karaulnyi" та правами 0660
    semaphore = sem_open("/karaulnyi", O_CREAT, 0660, 1);
    if (semaphore == SEM_FAILED) {
        perror("sem_open failed");
        return 1;
    }
    
    // Створення потоків
    pthread_create(&thread1, NULL, T1, NULL);
    pthread_create(&thread2, NULL, T2, NULL);
    
    // Очікування завершення потоків
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    
    // Виведення кінцевого значення
    printf("Final year = %d\n", db_printer.year);
    
    // Закриття та видалення семафору
    sem_close(semaphore);
    sem_unlink("/karaulnyi");
    
    return 0;
}
