#include <stdio.h>
#include <stdlib.h>
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
        printf("Child of Karaulnyi is finished (PID: %d)\n", getpid());
        exit(0); // Завершення child-процесу
    } else { // Код parent-процесу
        sleep(3 * n); // Очікування (36 секунд)
        waitpid(pid, NULL, 0); // Очікування завершення child-процесу (запобігання zombie)
        printf("Parent process finished\n");
    }

    return 0;
}
