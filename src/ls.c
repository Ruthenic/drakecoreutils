#include <stdio.h>
#include <stdbool.h> 
#include <unistd.h>
#include <dirent.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "ansi-colour.h"
#include "version.h"

/*
ls - print all files and directories in working directory
Available arguments:
	--help: show this help message
	--version: show the version of the program (WIP)
*/
//https://stackoverflow.com/questions/4770985/how-to-check-if-a-string-starts-with-another-string-in-c/4770992#4770992
bool startsWithChar(const char *pre, const char str) {
	char *e;
	int index;
	e = strchr(pre, str);
	index = (int)(e - pre);
	return index == 0;
}

int cmp(const void *a, const void *b){
    return strcmp(*(const char **)a, *(const char **)b);
}

//https://stackoverflow.com/a/4553076
bool isRegularFile(const char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}

int printBool(bool cond) {
	printf("%s\n", cond ? "true" : "false");
	return 0;
}

//lots o' code ~~stolen~~ borrowed from https://pubs.opengroup.org/onlinepubs/9699919799/functions/readdir.html
int main(int argc, char** argv) {
	//define default options
	bool colour   = false;
	bool showdot  = false;
	bool specpath = false;
	bool columns  = false;
	char *thatpath;
	for (int i = 1; i < argc; i++) {
		char* arg = argv[i];
		/*printf(arg);
		printf(" ");*/
		if (!strcmp(arg, "--help")) {
			char* help = 
				"Drake's Epic Coreutils (working title) "
				DRAKECU_VERSION
				"\n"
				"ls - print all files and directories in working directory\n"
				"Available arguments:\n"
				"	--help:        show this help message\n"
				"	--version:     show the version of the program\n"
				"	--color:       colour the output depending on whether there is a file or folder\n"
				"	--colour:      same as --color, but for our Bri'ish folks\n"
				"	-C, --columns: print every entry on a seperate line";
			printf("%s\n", help);
			return 0;
		} else if (!strcmp(arg, "--version")) {
			printf(DRAKECU_VERSION);
			return 0;
		} else if (!strcmp(arg, "--color") || !strcmp(arg, "--colour")) {
			colour  = true;
		} else if (!strcmp(arg, "-a") || !strcmp(arg, "--all")) {
			showdot = true;
		} else if (!strcmp(arg, "-C") || !strcmp(arg, "--columns")) {
			columns = true;
		} else {
			//TODO: interpret absolute *and* relative paths. can't be that hard, right?
			specpath = true;
			thatpath = arg;
		}
	}
	char wd[PATH_MAX];
	if (specpath == false) {
		getcwd(wd, sizeof(wd));
	} else if (specpath == true) {
		char *e = realpath(thatpath, NULL);
		strcpy(wd, e);
		free(e);
	}
	//printf(wd);
	DIR* dirp;
	struct dirent *dp;
	dirp = opendir(wd);
	if (dirp == NULL) {
		printf("couldn't open '%s'\n", wd);
		return 1;
	}
	int len = sizeof(char);
	char *out = malloc(len);
	out = NULL;
	dp = readdir(dirp);
	do {
		char* dirname = dp->d_name;
		if (!startsWithChar(dirname, '.') || showdot == true) {
			len += 1 + strlen(dirname) + strlen("§");
			out = realloc(out, len);
			strcat(out, dirname);
			strcat(out, "§");
		}
	} while ((dp = readdir(dirp)) != NULL);
	free(dirp);
	char *word, *words[strlen(out)/2+1];
	int i,n;
	i=0;
	word = strtok(out, "§");
	while (word != NULL) {
		words[i++] = word;
		word = strtok(NULL, "§");
	}
	n = i;
	qsort(words, n, sizeof(*words), cmp);
	char oldwd[PATH_MAX];
	strcpy(oldwd, wd);
	int maxLen = 0;
	if (columns == false) {
		maxLen = 180;
	}
	int currLen = 0;
	for (i = 0; i < n; i++) {
		if (colour == false) {
			printf("%s\n", words[i]);
		} else {
			strcpy(wd, oldwd);
			strcat(wd, "/");
			strcat(wd, words[i]);
			//printf(wd);
			if (isRegularFile(wd) == false) {
				printf(ANSI_BLUE);
				printf("%s\n", words[i]);
				printf(ANSI_RESET);
			} else {
				printf("%s\n", words[i]);
			}
		}
		printf(" ");
		currLen += strlen(words[i]);
		if (currLen >= maxLen) {
			printf("\n");
			currLen = 0;
		}
	}
	free(out);
	return 0;
}
