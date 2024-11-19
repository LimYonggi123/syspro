#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_CMD_LEN 1024
#define MAXARG 100

void execute_command(char *input) {
    char *args[MAXARG];
    pid_t pid;
    int status;
    int is_ls = 0;
    int background = 0;

    if (input[strlen(input) - 1] == '&') {
        background = 1;
        input[strlen(input) - 1] = '\0';
        while (strlen(input) > 0 && input[strlen(input) - 1] == ' ') {
            input[strlen(input) - 1] = '\0';
        }
    }

    char *token = strtok(input, " ");
    int i = 0;
    while (token != NULL) {
        args[i++] = token;
        if (strcmp(token, "ls") == 0) {
            is_ls = 1;
        }
        token = strtok(NULL, " ");
    }
    args[i] = NULL;

    pid = fork();

    if (pid == -1) {
        perror("Fork failed");
        return;
    }

    if (pid == 0) {
        if (!is_ls) {
            printf("[%d] child process start\n", getpid());
        }
        execvp(args[0], args);
        exit(1);
    } else {
        printf("[%d] Parent process start\n", getpid());
        waitpid(pid, &status, 0);
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
            if (!is_ls) {
                printf("[%d] child process end %d\n", pid, pid);
            }
            printf("SUCCESS\n");
        } else {
            if (!is_ls) {
                printf("Parent process end\n");
            }
        }
    }
}

int main() {
    char input[MAX_CMD_LEN];

    while (1) {
        printf("Pls input cmd : ");
        if (fgets(input, MAX_CMD_LEN, stdin) == NULL) {
            break;
        }

        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "exit") == 0) {
            printf("Exit\n");
            break;
        }

        execute_command(input);
    }

    return 0;
}

