#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handle_signal(int signum) {
    printf("Process of Karaulnyi got signal SIGUSR2\n");
}

int main() {
    signal(SIGUSR2, handle_signal); // Призначення обробника сигналу

    printf("Waiting for SIGUSR2... (PID: %d)\n", getpid());

    while (1) {
        pause(); // Очікування сигналу
    }

    return 0;
}
