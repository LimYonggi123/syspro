#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define MAX_LINES 10
#define MAX_LEN 100

int main(int argc, char *argv[]) {
	int fd, total_lines = 0;
	char saveText[MAX_LINES][MAX_LEN], buffer[MAX_LEN];
	ssize_t text_read;

      if((fd = open(argv[1], O_RDONLY)) == -1) {
		  exit(1);
	  }

	  while((text_read = read(fd, buffer, MAX_LEN -1)) > 0){
		  buffer[text_read] = '\0';
		  char *line = strtok(buffer, "\n");
		  while(line != NULL) {
			   strncpy(saveText[total_lines], line, MAX_LEN -1);
			   total_lines++;
			   if(total_lines >= MAX_LINES) break;

			   line = strtok(NULL, "\n");
		  }
		  if(total_lines >= MAX_LINES) break;
	  }

	  close(fd);

	  printf("File read success\n");
	  printf("Total Line : %d\n", total_lines);
	  printf("Yon can choose 1 ~ %d Line\n", total_lines);
	  printf("Plz 'Enter' the line to select : ");


	  char input[MAX_LEN];
	  fgets(input, sizeof(input), stdin);
	  input[strcspn(input, "\n")] = 0;

	  if(strcmp(input, "*") == 0) {
		  for(int i = 0; i < total_lines; i++){
			  printf("%s\n", saveText[i]);
		  }
	  }
	  else if(strchr(input, '-') != NULL) {
		  int start, end;
		  sscanf(input,"%d-%d", &start, &end);
		  for(int i = start - 1; i <= end - 1; i++){
			  if(i>=0 && i < total_lines) {
				  printf("%s\n", saveText[i]);
			  }
		  }
	  }
	  else if(strchr(input, ',') != NULL) {
		  char *token = strtok(input, ",");
		  while(token != NULL) {
			  int line_num = atoi(token) - 1;
			  if(line_num >= 0 && line_num < total_lines) {
				  printf("%s\n", saveText[line_num]);
			  }
			  token = strtok(NULL, ",");
		  }
	  } else {
		  int line_num = atoi(input) - 1;
		  if(line_num >= 0 && line_num < total_lines) {
			  printf("%s\n", saveText[line_num]);
		  }
	  }

	  return 0;
}
