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

static int listDirs(char *thatpath, bool specpath, bool colour, bool showdot,
                    int maxLen) {
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
  int relen = sizeof(char);
  char **words = malloc(relen);
  int count = 0;
  while ((dp = readdir(dirp)) != NULL) {
    char *dirname = dp->d_name;
    if (!startsWithChar(dirname, '.') || showdot == true) {
      relen = relen + strlen(dirname) +
              3; // 3 is so fucking arbitrary, but it works
      words = realloc(words, relen);
      words[count] = malloc(strlen(dirname) + 3);
      words[count] = dirname;
      count++;
    }
  }
  free(dirp);
  free(dp);
  qsort(words, count - 1, sizeof(words), cmp);
  char oldwd[PATH_MAX];
  strcpy(oldwd, wd);
  int currLen = 0;
  for (int i = 0; i < count; i++) {
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
        printf(ANSI_PURPLE);
        printf("%s  ", words[i]);
        printf(ANSI_RESET);
      } else if (isDirectory(wd) == true) {
        printf(ANSI_BLUE);
        printf("%s  ", words[i]);
        printf(ANSI_RESET);
      } else if (isExecutable(wd) == true) {
        printf(ANSI_GREEN);
        printf(ANSI_BOLD);
        printf("%s  ", words[i]);
        printf(ANSI_RESET);
        printf(ANSI_RESET);
      } else {
        printf("%s  ", words[i]);
      }
    }
  }
  free(words);
  printf("\n");
  return 0;
}

// lots o' code ~~stolen~~ borrowed from
// https://pubs.opengroup.org/onlinepubs/9699919799/functions/readdir.html
int ls(int argc, char **argv) {
  // define default options
  bool colour = false;
  bool showdot = false;
  bool specpath = false;
  int maxLen = 180;
  int paths = 0;
  int relen = 0;
  for (int i = 1; i < argc; i++) {
    char *arg = argv[i];
    if (!strcmp(arg, "--help")) {
      char *help =
          "Drake's Epic Coreutils (working title) " DRAKECU_VERSION "\n"
          "ls - print all files and directories in working directory\n"
          "Available arguments:\n"
          "	--help:        show this help message\n"
          "	--version:     show the version of the program\n"
          "	-a, --all:     show all files, including dotfiles\n"
          "	-c, --color:   colour the output depending on whether there is "
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
      int i2, n;
      n = 0;
      for (i2 = 8; (size_t)i2 < strlen(arg); i2++) {
        widthstr[n] = arg[i2];
        n++;
      }
      maxLen = atoi(widthstr);
    } else if (arg[0] == '-') {
      for (int i2 = 1; (size_t)i2 < strlen(arg); i2++) {
        if (arg[i2] == 'c') {
          colour = true;
        } else if (arg[i2] == 'C') {
          maxLen = 0;
        } else if (arg[i2] == 'a') {
          showdot = true;
        }
      }
    } else {
      specpath = true;
      printf("%s:\n", arg);
      listDirs(arg, specpath, colour, showdot, maxLen);
      /*relen = relen + strlen(arg) + 3;
      thatpath = realloc(thatpath, relen + 1);
      thatpath[paths] = malloc(strlen(arg) + 3);
      thatpath[paths] = arg;
      paths++;*/
    }
  }
  if (specpath == false) {
    listDirs(NULL, specpath, colour, showdot, maxLen);
  }
  /*for (int i3 = 0; i3 < paths; i3++) {
    printf("%s:\n", thatpath[i3]);
        listDirs(thatpath[i3], specpath, colour, showdot, maxLen);
  }
  free(thatpath);*/
  return 0;
}
