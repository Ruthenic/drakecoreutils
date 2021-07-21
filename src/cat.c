#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv) {
  if (argc == 1) {
    char ch;
    while (read(STDIN_FILENO, &ch, 1) > 0) {
      printf("%c", ch);
    }
    return 0;
  } else {
    char *file = NULL;
    for (int i = 1; i < argc; i++) {
      char *arg = argv[i];
      if (!strcmp(arg, "--help")) {
        char *help =
            "Drake's Epic Coreutils (working title) " DRAKECU_VERSION "\n"
            "cat - concatenate file to stdout.\n"
            "Usage:\n"
            "	cat [options] [FILE]\n"
            "Available arguments:\n"
            "	--help: show this help message\n"
            "	--version: show the version of the program\n"
            "Notes:\n"
            "	If no file is specified, FILE will be stdin.";
        printf("%s\n", help);
        return 0;
      } else if (!strcmp(arg, "--version")) {
        printf("%s\n", DRAKECU_VERSION);
        return 0;
      } else {
        file = arg;
        break;
      }
    }
    if (file == NULL) {
      printf(
          "somehow, you got past the argv check without a file. congrats?\n");
      return 1;
    }
    FILE *fp;
    fp = fopen(file, "r");
    if (fp == NULL) {
      printf("failed to open '%s'. perhaps the path doesn't exist?\n", file);
      return 1;
    }
    char *contents = malloc(LINE_MAX + 1);
    while (fgets(contents, LINE_MAX + 1, fp) != NULL) {
      printf("%s", contents);
    }
    free(contents);
  }
}