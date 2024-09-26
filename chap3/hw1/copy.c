#include <stdio.h>

void copy(char form[], char to[]){
	int i;
	i = 0;
	while((to[i] = form[i]) != '\0')
		++i;
}
