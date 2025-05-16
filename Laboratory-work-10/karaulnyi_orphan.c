#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork(); // Створення child-процесу
    int n = 12; // Номер варіанту

    if (pid == -1) {
        perror("Помилка створення процесу");
        return 1;
    } else if (pid == 0) { // Код child-процесу
        for (int i = 0; i < (2 * n + 1); i++) {
            sleep(1);
            printf("Parent of Karaulnyi (PPID: %d)\n", getppid());
        }
    } else { // Код parent-процесу
        sleep(n + 1); // Очікування перед завершенням
        printf("Parent process of Karaulnyi is terminating...\n");
        return 0; // Завершення parent-процесу
    }

    return 0;
}
