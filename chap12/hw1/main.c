#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    int a[2];
    if (pipe(a) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid > 0) {
        close(a[0]);
        char msg[50];
        sprintf(msg, "Hello from PID %d\n", getpid());
        printf("Send: [%d] %s", getpid(), msg);
        write(a[1], msg, strlen(msg) + 1);
        close(a[1]);
        wait(NULL);
    } else {
        close(a[1]);
        char buffer[50];
        read(a[0], buffer, sizeof(buffer));
        printf("Recv: [%d] %s", getpid(), buffer);
        close(a[0]);
    }

    return 0;
}

