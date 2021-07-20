#include <libgen.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/*
whoami - prints the working user's username (unless --uid is specified)
Available arguments:
        --help: show this help message
        --version: show the version of the program (WIP)
        --uid: print the users numeric UID, instead of username
*/

int main(int argc, char **argv) {
  char *wd;
  char *upname = NULL;
  if (argc == 1) {
    char tmp[PATH_MAX];
    getcwd(tmp, sizeof(tmp));
    upname = tmp;
  } else {
    for (int i = 1; i < argc; i++) {
      char *arg = argv[i];
      /*printf(arg);
      printf(" ");*/
      if (!strcmp(arg, "--help")) {
        char *help =
            "Drake's Epic Coreutils (working title) " DRAKECU_VERSION "\n"
            "basename - prints the last component of the path\n"
            "Available arguments:\n"
            "	--help: show this help message\n"
            "	--version: show the version of the program";
        printf("%s\n", help);
        return 0;
      } else if (!strcmp(arg, "--version")) {
        printf(DRAKECU_VERSION);
        return 0;
      } else {
        upname = arg;
        break;
      }
    }
  }
  wd = basename(upname);
  printf("%s\n", wd);
}
