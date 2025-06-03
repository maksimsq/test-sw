#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MSG_KEY 1112 // msg_key = 1000 + 100 * m + n = 1000 + 100 * 1 + 12 = 1112
#define MSG_SIZE 100

struct msg_buffer {
    long msg_type;
    char msg_text[MSG_SIZE];
};

int main() {
    struct msg_buffer message;
    int msgid;

    // Створення черги
    msgid = msgget(MSG_KEY, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget failed");
        exit(1);
    }

    // Підготовка повідомлення
    message.msg_type = 1;
    strcpy(message.msg_text, "Message from Karaulnyi");

    // Надсилання
    if (msgsnd(msgid, &message, sizeof(message.msg_text), 0) == -1) {
        perror("msgsnd failed");
        exit(1);
    }

    printf("Message sent: %s\n", message.msg_text);
    return 0;
}

