#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <ctype.h>

#define READ 0
#define WRITE 1

int main(int argc, char *argv[]) {
    int pipe1[2], pipe2[2];
    char str[1024];
    char *command1, *command2;

    if (argc == 1) {
        printf("[shell] ");
        fgets(str, sizeof(str), stdin);
        str[strlen(str) - 1] = '\0';

        if (strchr(str, '|') != NULL) {
            command1 = strtok(str, "|");
            command2 = strtok(NULL, "|");

            while (*command1 == ' ') command1++;
            while (*command2 == ' ') command2++;

            pipe(pipe1);

            if (fork() == 0) {
                close(pipe1[READ]);
                dup2(pipe1[WRITE], STDOUT_FILENO);
                close(pipe1[WRITE]);
                execlp(command1, command1, NULL);
                exit(EXIT_FAILURE);
            }

            if (fork() == 0) {
                close(pipe1[WRITE]);
                dup2(pipe1[READ], STDIN_FILENO);
                close(pipe1[READ]);
                execlp(command2, command2, NULL);
                exit(EXIT_FAILURE);
            }

            close(pipe1[READ]);
            close(pipe1[WRITE]);
            wait(NULL);
            wait(NULL);
        } else {
            pipe(pipe1);
            pipe(pipe2);

            if (fork() == 0) {
                close(pipe1[READ]);
                char input[100];
                printf("input string: ");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = '\0';
                write(pipe1[WRITE], input, strlen(input) + 1);
                close(pipe1[WRITE]);
                exit(0);
            }

            if (fork() == 0) {
                close(pipe1[WRITE]);
                close(pipe2[READ]);
                char buffer[100];
                read(pipe1[READ], buffer, sizeof(buffer));
                for (int i = 0; buffer[i]; i++) {
                    buffer[i] = toupper(buffer[i]);
                }
                write(pipe2[WRITE], buffer, strlen(buffer) + 1);
                close(pipe1[READ]);
                close(pipe2[WRITE]);
                exit(0);
            }

            close(pipe1[READ]);
            close(pipe1[WRITE]);
            close(pipe2[WRITE]);

            char result[100];
            read(pipe2[READ], result, sizeof(result));
            printf("%s\n", result);
            close(pipe2[READ]);

            wait(NULL);
            wait(NULL);
        }
    } else if (argc == 4 && strcmp(argv[2], "|") == 0) {
        command1 = argv[1];
        command2 = argv[3];

        pipe(pipe1);

        if (fork() == 0) {
            close(pipe1[READ]);
            dup2(pipe1[WRITE], STDOUT_FILENO);
            close(pipe1[WRITE]);
            execlp(command1, command1, NULL);
            exit(EXIT_FAILURE);
        }

        if (fork() == 0) {
            close(pipe1[WRITE]);
            dup2(pipe1[READ], STDIN_FILENO);
            close(pipe1[READ]);
            execlp(command2, command2, NULL);
            exit(EXIT_FAILURE);
        }

        close(pipe1[READ]);
        close(pipe1[WRITE]);
        wait(NULL);
        wait(NULL);
    }

    return 0;
}

