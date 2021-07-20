#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
yes - spams a message (by default `y`) to stdout.
Available arguments:
        --help: show this help message.
        --version: show version of the program.
Usage:
        yes [--help] [--version] [message]
*/

int main(int argc, char **argv) {
  char *spammy = malloc(sizeof(char) * 16);
  if (argc == 1) {
    spammy = "y";
  } else {
    for (int i = 1; i < argc; i++) {
      char *arg = argv[i];
      /*printf(arg);
      printf(" ");*/
      if (!strcmp(arg, "--help")) {
        char *help =
            "Drake's Epic Coreutils (working title) " DRAKECU_VERSION "\n"
            "yes - spams a message (by default `y`) to stdout.\n"
            "Available arguments:\n"
            "	--help: show this help message.\n"
            "	--version: show version of the program.\n"
            "Usage:\n"
            "	yes [--help] [--version] [message]";
        printf("%s\n", help);
        return 0;
      } else if (!strcmp(arg, "--version")) {
        printf(DRAKECU_VERSION);
        return 0;
      } else {
        spammy = realloc(spammy, strlen(arg) + strlen(spammy) + 1);
        strcat(spammy, arg);
        strcat(spammy, " ");
      }
    }
  }
  do {
    printf("%s\n", spammy);
  } while (1);
}
