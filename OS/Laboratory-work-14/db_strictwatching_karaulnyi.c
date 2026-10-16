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

// Змінна для алгоритму "Строге чергування"
int turn = 1; // 1 - черга T1, 2 - черга T2

// Функція для потоку T1
void* T1(void* arg) {
    // Затримка для імітації паралельної роботи
    usleep(100000);
    
    // Очікування своєї черги
    while (turn != 1) {
        usleep(10000);
    }
    
    // Читання значення
    printf("T1: Read year = %d\n", db_printer.year);
    
    // Зміна значення
    db_printer.year += 1;
    printf("T1: Updated year = %d\n", db_printer.year);
    
    // Передача черги T2
    turn = 2;
    
    return NULL;
}

// Функція для потоку T2
void* T2(void* arg) {
    // Затримка для імітації паралельної роботи
    usleep(150000);
    
    // Очікування своєї черги
    while (turn != 2) {
        usleep(10000);
    }
    
    // Читання значення
    printf("T2: Read year = %d\n", db_printer.year);
    
    // Зміна значення
    db_printer.year += 2;
    printf("T2: Updated year = %d\n", db_printer.year);
    
    // Передача черги T1
    turn = 1;
    
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
