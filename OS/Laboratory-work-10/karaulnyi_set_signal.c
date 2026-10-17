#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main() {
    pid_t pid;

    // Запитуємо у користувача PID процесу, якому потрібно надіслати сигнал
    printf("Введіть PID цільового процесу: ");
    scanf("%d", &pid);

    // Надсилаємо сигнал SIGUSR2 процесу з вказаним PID
    if (kill(pid, SIGUSR2) == 0) {
        printf("SIGUSR2 надіслано процесу %d\n", pid);
    } else {
        perror("Не вдалося надіслати сигнал");
    }

    return 0;
}
