#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

// Одна сигнальна змінна для блокування
int turn = 0;

// Структура, що відповідає реляційній таблиці printer
typedef struct {
    int pr_id;
    char model[20];
    int year;
} Printer;

// Глобальна змінна для даних
Printer db_printer = {1, "HP LaserJet", 2020};

// Функція для потоку T1
void* T1(void* arg) {
    for (int i = 0; i < 3; i++) {
        // Очікування своєї черги
        while (turn != 0) {
            usleep(100000);
        }
        
        // Вхід у критичну секцію
        printf("T1: Critical Region\n");
        printf("T1: Read year = %d\n", db_printer.year);
        
        // Зміна значення
        db_printer.year += 1;
        printf("T1: Write year = %d\n", db_printer.year);
        
        // Передача черги T2
        turn = 1;
        
        // Некритична секція
        printf("T1: Non-Critical Region\n");
        usleep(100000);
    }
    
    return NULL;
}

// Функція для потоку T2
void* T2(void* arg) {
    // Початкова затримка для імітації паралельної роботи
    usleep(100000);
    
    for (int i = 0; i < 3; i++) {
        // Очікування своєї черги
        while (turn != 1) {
            usleep(100000);
        }
        
        // Вхід у критичну секцію
        printf("T2: Critical Region\n");
        printf("T2: Read year = %d\n", db_printer.year);
        
        // Зміна значення
        db_printer.year += 2;
        printf("T2: Write year = %d\n", db_printer.year);
        
        // Передача черги T1
        turn = 0;
        
        // Некритична секція
        printf("T2: Non-Critical Region\n");
        usleep(100000);
    }
    
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
    
    // Виведення кінцевого значення
    printf("Final year = %d\n", db_printer.year);
    
    return 0;
}
