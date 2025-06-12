#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

// Структура, що відповідає реляційній таблиці printer
typedef struct {
    int pr_id;
    char model[20];
    int year;
} Printer;

// Глобальна змінна для даних
Printer db_printer = {1, "HP LaserJet", 2020};

// Змінні блокування
int lock1 = 0, lock2 = 0;

// Функція для потоку T1
void* T1(void* arg) {
    // Затримка для імітації паралельної роботи
    usleep(100000);
    
    // Читання значення
    printf("T1: Read year = %d\n", db_printer.year);
    
    // Алгоритм змінних блокування
    lock1 = 1;
    while (lock2 == 1) {
        lock1 = 0;
        usleep(10000);
        lock1 = 1;
    }
    
    // Зміна значення
    db_printer.year += 1;
    printf("T1: Updated year = %d\n", db_printer.year);
    
    // Зняття блокування
    lock1 = 0;
    
    return NULL;
}

// Функція для потоку T2
void* T2(void* arg) {
    // Затримка для імітації паралельної роботи
    usleep(150000);
    
    // Читання значення
    printf("T2: Read year = %d\n", db_printer.year);
    
    // Алгоритм змінних блокування
    lock2 = 1;
    while (lock1 == 1) {
        lock2 = 0;
        usleep(10000);
        lock2 = 1;
    }
    
    // Зміна значення
    db_printer.year += 2;
    printf("T2: Updated year = %d\n", db_printer.year);
    
    // Зняття блокування
    lock2 = 0;
    
    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    
    // Створення потоків
    pthread_create(&thread1, NULL, T1, NULL);
    pthread_create(&thread2, NULL, T2, NULL);
    
    // Очікування завершення потоків
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    
    printf("Final year = %d\n", db_printer.year);
    
    return 0;
}
