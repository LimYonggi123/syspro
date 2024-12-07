#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

int main() {
    int pipe1[2], pipe2[2];

    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

	printf("parent process start\n");

    pid_t pid1 = fork();
    if (pid1 < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
     
    if (pid1 == 0) {
        close(pipe1[0]);
        char input[100];
        printf("input string: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';
        write(pipe1[1], input, strlen(input) + 1);
        close(pipe1[1]);
        exit(0);
    }

    pid_t pid2 = fork();
    if (pid2 < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }


    if (pid2 == 0) {
        close(pipe1[1]);
        close(pipe2[0]);
        char buffer[100];
        read(pipe1[0], buffer, sizeof(buffer));
        for (int i = 0; buffer[i]; i++) {
            buffer[i] = toupper(buffer[i]);
        }
        write(pipe2[1], buffer, strlen(buffer) + 1);
        close(pipe1[0]);
        close(pipe2[1]);
        exit(0);
    }

    close(pipe1[0]);
    close(pipe1[1]);
    close(pipe2[1]);

    char result[100];
    read(pipe2[0], result, sizeof(result));
    printf("%s\n", result);
    close(pipe2[0]);

    wait(NULL);
    wait(NULL);

    return 0;
}

