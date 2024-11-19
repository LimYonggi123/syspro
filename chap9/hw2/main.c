#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_CMD_LEN 1024
#define MAXARG 100

void execute_command(char *cmd) {
    char *args[MAXARG];
    char *token;
    int background = 0;
    int pid;
	int status;
	pid = fork();
   
    if (cmd[strlen(cmd) - 1] == '&') {
        background = 1;
        cmd[strlen(cmd) - 1] = '\0';
    }

    int i = 0;
    token = strtok(cmd, " ");
    while (token != NULL) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;

    if (pid == 0) {
		printf("[%d]Child process start\n", getpid());
		execvp(args[0], args); 
        perror("execvp failed");
        exit(1);
    } else {
		printf("[%d]Parent process start\n", getpid());
        if (!background) {
            wait(NULL);
			if(WIFEXITED(status)&& WEXITSTATUS(status) == 0)
				printf("SUCCESS\n");

            printf("[%d] Child process end\n", getpid());
		}
		 printf("Parent process end\n");
    }
}

void parse_and_execute(char *input) {
    char *cmd = strtok(input, ";");
    while (cmd != NULL) {
   
        char *redirect_out = strstr(cmd, ">");
        char *redirect_in = strstr(cmd, "<");
        
        if (redirect_out) {
            *redirect_out = '\0';
            redirect_out++;
            char *outfile = strtok(redirect_out, " ");
            int fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd == -1) {
                perror("Failed to open output file");
                return;
            }
            if (fork() == 0) {
                dup2(fd, STDOUT_FILENO);
                close(fd);
                execute_command(cmd);
                exit(0);
            } else {
                wait(NULL);
                close(fd);
            }
        } else if (redirect_in) {
            *redirect_in = '\0';
            redirect_in++;
            char *infile = strtok(redirect_in, " ");
            int fd = open(infile, O_RDONLY);
            if (fd == -1) {
                perror("Failed to open input file");
                return;
            }
            if (fork() == 0) {
                dup2(fd, STDIN_FILENO);
                close(fd);
                execute_command(cmd);
                exit(0);
            } else {
                wait(NULL);
                close(fd);
            }
        } else {
            execute_command(cmd);
        }

        cmd = strtok(NULL, ";");
    }
}

int main() {
    char input[MAX_CMD_LEN];

    while (1) {
        printf("pls input cmd : ");
        if (fgets(input, MAX_CMD_LEN, stdin) == NULL) {
            break;
        }

        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "exit") == 0) {
			printf("Exit\n");
            break;
        }

        parse_and_execute(input);
    }

    return 0;
}

