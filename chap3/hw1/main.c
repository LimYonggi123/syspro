#include <stdio.h>
#include <string.h>
#include "copy.h"

char line[MAXLINE];
char longest[5][MAXLINE];
char temp[MAXLINE];

int main() {
	int len;
	int max;
	int i = 0;
	int l[5];
	int count = 0;
	max = 0;

	while(i < 5 && gets(line) != NULL) {
	len = strlen(line);
	l[i] = len;
	copy(line, longest[i]);
		if(len > max) {
			max = len;
		}
		i++;
		count++;
	} 
	for(int j = 0; j < count - 1; j++){
		for(int k = j + 1; k < count; k++) {
			if(l[j] < l[k]){
		 		int Len = l[j];
				l[j] = l[k];
				l[k] = Len;

				copy(longest[j], temp);
				copy(longest[k], longest[j]);
				copy(temp, longest[k]);
				}
		}
	}


	if(max > 0){
		for(int j= 0; j < count; j++){
		printf("%s \n", longest[j]);
		}
	}
	return 0;
}
