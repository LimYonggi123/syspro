#include <stdio.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>

int main() {

	printf("my Realistic User ID: %d(%s)\n", getuid(), getpwuid(getuid())->pw_name);
	printf("my Valid User ID: %d(%s)\n", geteuid(), getpwuid(geteuid())->pw_name);
	printf("my Realistic Group ID : %d(%s)\n", getgid(), getgrgid(getgid())->gr_name);
	printf("my Valid Group ID: %d(%s)\n", getegid(), getgrgid(getegid())->gr_name);
}

