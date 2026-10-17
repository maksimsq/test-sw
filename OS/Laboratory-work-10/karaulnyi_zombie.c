#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork(); // Створення child-процесу

    if (pid == -1) {
        perror("Помилка створення процесу");
        return 1;
    } else if (pid == 0) { // Код child-процесу
        printf("I am Zombie-process of Karaulnyi (PID: %d)\n", getpid());
        exit(0); // Завершення child-процесу, перетворення на zombie
    } else { // Код parent-процесу
        sleep(30); // Затримка, щоб child став zombie
        printf("Parent process still running...\n");
        
        // Завершити zombie, виконавши wait()
        wait(NULL);
    }

    return 0;
}

