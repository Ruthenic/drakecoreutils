#include <dirent.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "ansi-colour.h"
#include "checks.h"
#include "file.h"

/*
BSD 3-Clause License

Copyright (c) 2021, Ruthenic
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/*
ls - print all files and directories in working directory
Available arguments:
        --help: show this help message
        --version: show the version of the program (WIP)
*/

/*static int printBool(bool cond) {
        printf("%s\n", cond ? "true" : "false");
        return 0;
}*/

static int cmp(const void *a, const void *b) {
  return strcmp(*(char **)a, *(char **)b);
}

// lots o' code ~~stolen~~ borrowed from
// https://pubs.opengroup.org/onlinepubs/9699919799/functions/readdir.html
int main(int argc, char **argv) {
  // define default options
  bool colour = false;
  bool showdot = false;
  bool specpath = false;
  int maxLen = 180;
  char *thatpath;
  for (int i = 1; i < argc; i++) {
    char *arg = argv[i];
    /*printf(arg);
    printf(" ");*/
    if (!strcmp(arg, "--help")) {
      char *help =
          "Drake's Epic Coreutils (working title) " DRAKECU_VERSION "\n"
          "ls - print all files and directories in working directory\n"
          "Available arguments:\n"
          "	--help:        show this help message\n"
          "	--version:     show the version of the program\n"
          "	--color:       colour the output depending on whether there is "
          "a file or folder\n"
          "	--colour:      same as --color, but for our Bri'ish folks\n"
          "	-C, --columns: print every entry on a seperate line\n"
          "	--width=LEN:   limit maximum line length to LEN\n"
          "Usage:\n"
          "	ls [options] DIRECTORY\n"
          "Notes:\n"
          "	If DIRECTORY is not specified, then the CWD is used.";
      printf("%s\n", help);
      return 0;
    } else if (!strcmp(arg, "--version")) {
      printf("%s\n", DRAKECU_VERSION);
      return 0;
    } else if (!strcmp(arg, "--color") || !strcmp(arg, "--colour")) {
      colour = true;
    } else if (!strcmp(arg, "--all")) {
      showdot = true;
    } else if (!strcmp(arg, "--columns")) {
      maxLen = 0;
    } else if (startsWithStr("--width", arg)) {
      char widthstr[100]; // if someone has a longer width than this, then owo
      int i, n;
      n = 0;
      for (i = 8; (size_t)i < strlen(arg); i++) {
        widthstr[n] = arg[i];
        n++;
      }
      maxLen = atoi(widthstr);
    } else if (arg[0] == '-') {
      for (int i = 1; (size_t)i < strlen(arg); i++) {
        if (arg[i] == 'c') {
          colour = true;
        } else if (arg[i] == 'C') {
          maxLen = 0;
        } else if (arg[i] == 'a') {
          showdot = true;
        }
      }
    } else {
      // TODO: interpret absolute *and* relative paths. can't be that hard,
      // right?
      specpath = true;
      thatpath = arg;
    }
  }
  char wd[PATH_MAX];
  if (specpath == false) {
    getcwd(wd, sizeof(wd));
  } else if (specpath == true) {
    char *e = realpath(thatpath, NULL);
    if (e == NULL) {
      printf("couldn't open '%s'. perhaps the path doesn't exist?\n", thatpath);
      return 1;
    }
    strcpy(wd, e);
    free(e);
  }
  // printf(wd);
  DIR *dirp;
  struct dirent *dp;
  dirp = opendir(wd);
  if (dirp == NULL) {
    printf("couldn't open '%s'. perhaps the path doesn't exist?\n", wd);
    return 1;
  }
  int len = sizeof(char);
  char *out = malloc(len);
  out = NULL;
  dp = readdir(dirp);
  do {
    char *dirname = dp->d_name;
    if (!startsWithChar(dirname, '.') || showdot == true) {
      len += 1 + strlen(dirname) + strlen("§");
      out = realloc(out, len);
      strcat(out, dirname);
      strcat(out, "§");
    }
  } while ((dp = readdir(dirp)) != NULL);
  if (out == NULL) {
    // printf(" \n");
    // imo this shouldn't be commented out for consistency with the rest of the
    // program, but gnu does it so so do we (english:tm:)
    return 0;
  }
  free(dirp);
  char *word, *words[strlen(out) / 2 + 1];
  int i, n;
  i = 0;
  word = strtok(out, "§");
  while (word != NULL) {
    words[i++] = word;
    word = strtok(NULL, "§");
  }
  n = i;
  qsort(words, n, sizeof(*words), cmp);
  char oldwd[PATH_MAX];
  strcpy(oldwd, wd);
  int currLen = 0;
  for (i = 0; i < n; i++) {
    currLen += strlen(words[i]);
    if (currLen >= maxLen) {
      printf("\n");
      currLen = 0;
    }
    if (colour == false) {
      printf("%s  ", words[i]);
    } else {
      strcpy(wd, oldwd);
      strcat(wd, "/");
      strcat(wd, words[i]);
      // printf(wd);
      if (isSymlink(wd) == true) {
        printf(ANSI_GREEN);
        printf("%s  ", words[i]);
        printf(ANSI_RESET);
      } else if (isDirectory(wd) == true) {
        printf(ANSI_BLUE);
        printf("%s  ", words[i]);
        printf(ANSI_RESET);
      } else {
        printf("%s  ", words[i]);
      }
    }
  }
  free(out);
  printf("\n");
  return 0;
}
