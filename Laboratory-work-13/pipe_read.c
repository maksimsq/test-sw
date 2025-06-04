#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pipe_fd>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int pipe_fd = atoi(argv[1]);
    char buffer[256];

    ssize_t bytesRead = read(pipe_fd, buffer, sizeof(buffer) - 1);
    if (bytesRead == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }

    buffer[bytesRead] = '\0'; // null-terminate string
    printf("I`m child process of Karaulnyi with pid=%d\n", getpid());
    printf("Message received: %s\n", buffer);
    printf("Size of message received: %zd bytes\n", bytesRead);

    close(pipe_fd);
    return 0;
}
