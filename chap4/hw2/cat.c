#include <stdio.h>

int main(int argc, char *argv[])
{
	char c;
	FILE  *fp1, *fp2;
	if(argc < 2) {
		fprintf(stderr, "How to use:%s File1 File2\n", argv[0]);
		return 1;
	}
	for(int i = 1; i <argc; i++) { 
   fp1 = fopen(argv[i], "r");
   if(fp1 == NULL) {
	   fprintf(stderr, "File %s Open Error\n", argv[i]);
	   return 2;
   }

   while((c = fgetc(fp1)) != EOF)
	   putchar(c);
    
   fclose(fp1);
	}

   return 0;
}

