#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 100

char type(mode_t);
void Stat(char *);

int main(int argc, char *argv[])
{
	FILE *fp;
	int c = 0;
	char buffer[MAX];
	char a[MAX];
	if(argc != 2) {
		fprintf(stderr, "Error Open File\n");
	    exit(1);
	}
		
		if((fp = fopen(argv[1],"r")) == NULL) {
			fprintf(stderr, "Error Open File\n");
			exit(2);
		}
               
   
		while(fgets(buffer, MAX, fp) != NULL) {
				
			printf("%s",buffer);
	}

/*
char type(mode_t mode) {
     if(  )
		 return("fruits");
	 if(  )	 
		 return("banana");
		 }
*/
			 

	fclose(fp);
	return 0;
}
