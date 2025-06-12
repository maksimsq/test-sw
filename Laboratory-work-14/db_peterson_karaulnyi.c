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

// Змінні для алгоритму Петерсона
int flag[2] = {0, 0}; // Позначає бажання потоку увійти в критичну секцію
int turn;             // Черга входу в критичну секцію

// Функція для потоку T1
void* T1(void* arg) {
    // Затримка для імітації паралельної роботи
    usleep(100000);
    
    // Читання значення
    printf("T1: Read year = %d\n", db_printer.year);
    
    // Алгоритм Петерсона для T1 (процес 0)
    flag[0] = 1;
    turn = 1;
    while (flag[1] == 1 && turn == 1) {
        usleep(10000);
    }
    
    // Критична секція: зміна значення
    db_printer.year += 1;
    printf("T1: Updated year = %d\n", db_printer.year);
    
    // Вихід з критичної секції
    flag[0] = 0;
    
    return NULL;
}

// Функція для потоку T2
void* T2(void* arg) {
    // Затримка для імітації паралельної роботи
    usleep(150000);
    
    // Читання значення
    printf("T2: Read year = %d\n", db_printer.year);
    
    // Алгоритм Петерсона для T2 (процес 1)
    flag[1] = 1;
    turn = 0;
    while (flag[0] == 1 && turn == 0) {
        usleep(10000);
    }
    
    // Критична секція: зміна значення
    db_printer.year += 2;
    printf("T2: Updated year = %d\n", db_printer.year);
    
    // Вихід з критичної секції
    flag[1] = 0;
    
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
