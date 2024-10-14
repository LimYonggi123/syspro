#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define MAX_LINES 100
#define MAX_LEN 100

int main(int argc, char *argv[]) {
	char lines[MAX_LINES][MAX_LEN];
	int total_lines = 0;
	int fd;
	char buffer;
	int line;

	fd = open(argv[1], O_RDONLY);

	while(read(fd, &buffer, 1) > 0) {
		if(buffer == '\n') {
			lines[total_lines][line] = '\0';
			total_lines++;
			line = 0;
		}
		else {
			lines[total_lines][line++] = buffer;
		}
	}

	close(fd);


	for(int i = total_lines - 1; i >= 0; i--) {
		printf("%s\n", lines[i]);
	}

	return 0;
}
