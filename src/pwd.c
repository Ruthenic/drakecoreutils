#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <pwd.h>


/*
whoami - prints the working user's username (unless --uid is specified)
Available arguments:
	--help: show this help message
	--version: show the version of the program (WIP)
	--uid: print the users numeric UID, instead of username
*/

int main(int argc, char** argv) {
	char wd[PATH_MAX];
	getcwd(wd, sizeof(wd));
	if (argc == 1) {
		printf("%s\n", wd);
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
					"pwd - prints the current working directory\n"
					"Available arguments:\n"
					"	--help: show this help message\n"
					"	--version: show the version of the program";
				printf("%s\n", help);
				return 0;
			} else if (!strcmp(arg, "--version")) {
				printf(DRAKECU_VERSION);
				return 0;
			}
		}
	}
}
