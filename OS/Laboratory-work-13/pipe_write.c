#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/wait.h>


int main() {
    int fd[2];
    if (pipe(fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child process
        close(fd[1]); // Close write end

        // Convert read descriptor to string for exec
        char fd_str[10];
        snprintf(fd_str, sizeof(fd_str), "%d", fd[0]);

        execl("./pipe_read", "pipe_read", fd_str, NULL);
        perror("execl");
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        close(fd[0]); // Close read end

        const char *message = "The Laboratory Work of Karaulnyi";
        ssize_t bytesWritten = write(fd[1], message, strlen(message));

        printf("I`m parent process of Karaulnyi with pid=%d\n", getpid());
        printf("Size of message sent: %zd bytes\n", bytesWritten);

        close(fd[1]);
        wait(NULL); // Wait for child process
    }

    return 0;
}
