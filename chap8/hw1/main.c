#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{

	char **ptr;
	extern char **environ;

     if(argc == 2 && strcmp(argv[1], "-e") == 0) {
	for(ptr = environ; *ptr != NULL; ptr++)
		printf("%s \n", *ptr);

	exit(0);

	 }
	 if(argc == 3 && strcmp(argv[1], "-e") == 0){
		 char *a = getenv(argv[2]);
		 if(a) {
				 printf("%s = %s\n", argv[2], a);
			 }
		 exit(0);
	 }


			 

    if(strcmp(argv[1], "-u") == 0) {
	printf("My Realistic User ID: %d(%s)\n", getuid(), getpwuid(getuid())->pw_name);
    printf("My Valid User ID : %d(%s)\n", geteuid(), getpwuid(geteuid())->pw_name);
	}

	else if(strcmp(argv[1], "-g") == 0) {
	printf("My Realistic Group ID : %d(%s)\n", getgid(), getgrgid(getgid())->gr_name);
	printf("My Valid Group ID : %d(%s)\n", getegid(), getgrgid(getegid())->gr_name);
	}



    if(strcmp(argv[1], "-i") == 0) {
		printf("my process number : [%d]\n", getpid());
	}
	if(strcmp(argv[1], "-p") == 0) {
		printf("parent's process number : [%d]\n", getppid());
	}

}

