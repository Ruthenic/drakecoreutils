#include <stdio.h>
#include <string.h>
#include <sys/utsname.h>

/*
arch - prints the current machine's architecture
Available arguments:
        --help: show this help message
        --version: show the version of the program (WIP)
*/

int main(int argc, char **argv) {
  if (argc == 1) {
    struct utsname e;
    uname(&e);
    printf("%s\n", e.machine);
    return 0;
  } else {
    for (int i = 0; i < argc; i++) {
      char *arg = argv[i];
      /*printf(arg);
      printf(" ");*/
      if (!strcmp(arg, "--help")) {
        char *help =
            "Drake's Epic Coreutils (working title) " DRAKECU_VERSION "\n"
            "arch - prints the current machine's architecture\n"
            "Available arguments:\n"
            "	--help: show this help message\n"
            "	--version: show the version of the program";
        printf("%s\n", help);
        return 0;
      } else if (!strcmp(arg, "--version")) {
        printf("%s\n", DRAKECU_VERSION);
        return 0;
      }
    }
  }
}
