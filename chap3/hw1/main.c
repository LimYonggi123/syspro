#include <stdio.h>
#include <string.h>
#include "copy.h"

char line[MAXLINE];
char longest[MAXLINE];

int main() {
	int len;
	int max;
	int i;
	max = 0;
	i = 0;

	while(gets(line) != NULL && i <= 4) {
	len = strlen(line);

		if(len > max) {
			max = len;
			copy(line, longest);
		}
		i++;
	}
    
	if(max > 0){
		while(i <= 0){
		printf("%s \n", longest);
		i--;
		}
	}
	return 0;
}
