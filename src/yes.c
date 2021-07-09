#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

#include "version.h"

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
		do {
			printf("y\n");
		} while (1);
	} else {
		for (int i = 0; i < argc; i++) {
			char* arg = argv[i];
			/*printf(arg);
			printf(" ");*/
			if (!strcmp(arg, "--help")) {
				char* help = 
					"Drake's Epic Coreutils (working title) "
					DRAKECU_VERSION
					"\n"
					"yes - spams 'y'.\n"
					"Available arguments:\n"
					"	--help: show this help message\n"
					"	--version: show the version of the program\n"
					"	--uid: print the users numeric UID, instead of username";
				printf("%s\n", help);
				return 0;
			} else if (!strcmp(arg, "--version")) {
				printf(DRAKECU_VERSION);
				return 0;
			}
		}
	}
}