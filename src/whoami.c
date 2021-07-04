#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

/*
whoami - prints the working user's username (unless --uid is specified)
Available arguments:
	--help: show this help message
	--version: show the version of the program (WIP)
	--uid: print the users numeric UID, instead of username
*/

int main(int argc, char** argv) {
	uid_t userid = geteuid();
	char * username = getpwuid(userid)->pw_name;
	if (argc == 1) {
		printf(username);
		return 0;
	} else {
		for (int i = 0; i < argc; i++) {
			char* arg = argv[i];
			/*printf(arg);
			printf(" ");*/
			if (!strcmp(arg, "--help")) {
				char* help = 
					"Drake's Epic Coreutils (working title)\n"
					"whoami - prints the working user's username (unless --uid is specified)\n"
					"Available arguments:\n"
					"	--help: show this help message\n"
					"	--version: show the version of the program (WIP)\n"
					"	--uid: print the users numeric UID, instead of username";
				printf("%s\n", help);
				return 0;
			} else if (!strcmp(arg, "--version")) {
				printf("6.9.69\n");
				return 0;
			} else if (!strcmp(arg, "--uid")) {
				printf("%lu\n", (unsigned long int)userid);
				return 0;
			}
		}
	}
}
