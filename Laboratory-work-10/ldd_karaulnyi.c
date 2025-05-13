#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Помилка створення процесу");
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("The child of Karaulnyi executes: ldd\n");
        sleep(1); // затримка перед execv

        char *args[] = {"/usr/bin/ldd", "-d", "/bin/bash", NULL};
        execv("/usr/bin/ldd", args);

        // Якщо execv не спрацює:
        perror("execv failed");
        return 1;
    } else {
        // Parent process
        wait(NULL); // чекаємо завершення дочірнього процесу
    }

    return 0;
}
