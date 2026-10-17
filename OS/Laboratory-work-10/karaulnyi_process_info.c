#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    printf("Ідентифікатор групи процесів: %d\n", getpgrp());
    printf("Ідентифікатор процесу: %d\n", getpid());
    printf("Ідентифікатор parent-процесу: %d\n", getppid());
    printf("Ідентифікатор користувача процесу: %d\n", getuid());
    printf("Ідентифікатор групи користувача процесу: %d\n", getgid());
    
    return 0;
}
