#include <stdio.h>
#include <stdlib.h>
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

    // Отримання ідентифікатора черги
    msgid = msgget(MSG_KEY, 0666);
    if (msgid == -1) {
        perror("msgget failed");
        exit(1);
    }

    // Отримання повідомлення
    if (msgrcv(msgid, &message, sizeof(message.msg_text), 1, 0) == -1) {
        perror("msgrcv failed");
        exit(1);
    }

    printf("Message received: %s\n", message.msg_text);

    // Видалення черги
    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}
