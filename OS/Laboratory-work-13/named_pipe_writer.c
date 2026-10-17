#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>


int main() {
    const char *fifo_path = "karaulnyi";

    // 2.4.1 Створення іменованого каналу з правами 0660
    if (mkfifo(fifo_path, 0660) == -1) {
        perror("mkfifo");
        // Якщо fifo вже існує, не переривати програму
    } else {
        printf("FIFO '%s' created successfully.\n", fifo_path);
    }

    // 2.3.2 Запис команди pstree -p -a у канал
    FILE *fp = popen("pstree -p -a", "r");
    if (!fp) {
        perror("popen");
        return 1;
    }

    int fifo_fd = open(fifo_path, O_WRONLY); // блокуватиметься, поки не буде читача
    if (fifo_fd == -1) {
        perror("open fifo for writing");
        return 1;
    }

    char buffer[256];
    ssize_t bytes;
    while (fgets(buffer, sizeof(buffer), fp)) {
        write(fifo_fd, buffer, strlen(buffer));
    }

    close(fifo_fd);
    pclose(fp);

    // 2.4.1 Видалення FIFO
    if (remove(fifo_path) == 0) {
        printf("FIFO '%s' removed successfully.\n", fifo_path);
    } else {
        perror("remove");
    }

    return 0;
}
