#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>

// Question: Modify message_receiver.c to receive specific messages.
// Explanation: We use a message queue and process messages in the desired order.

struct msg_buffer {
    long msg_type;
    char msg_text[100];
} message;

int main() {
    key_t key;
    int msgid;

    // Generate a unique key and create message queue
    key = ftok("progfile", 65);
    msgid = msgget(key, 0666 | IPC_CREAT);

    // Receive FAITH
    msgrcv(msgid, &message, sizeof(message), 1, 0);
    printf("Data Received: %s\n", message.msg_text);

    // Destroy the message queue
    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}
