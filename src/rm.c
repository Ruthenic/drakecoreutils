#include <dirent.h>
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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

int removeFileOrDirectory(char *path, bool recursive, bool force) {
  if (isDirectory(path)) {
    if (recursive == true) {
      DIR *dirp;
      struct dirent *dp;
      char *fullname;
      dirp = opendir(path);
      do {
        if ((dp = readdir(dirp)) != NULL) {
          if (strcmp(dp->d_name, ".") && strcmp(dp->d_name, "..")) {
            fullname = malloc(strlen(dp->d_name) + strlen(path) + 2);
            sprintf(fullname, "%s/%s", path, dp->d_name);
            // printf("%s\n", dp->d_name);
            if (!isDirectory(fullname)) {
              unlink(fullname);
            } else {
              removeFileOrDirectory(fullname, recursive, force);
            }
            free(fullname);
            if (errno != 0) {
              if (errno == EACCES || errno == EPERM) {
                printf("unable to access '%s'. you probably need higher "
                       "permissions.\n",
                       path);
              } else {
                printf("unknown error occured when trying to remove '%s'.\n",
                       path);
              }
              return errno;
            }
          }
        }
      } while (dp != NULL);
      rmdir(path);
    } else {
      rmdir(path);
      if (errno == 0) {
        return 0;
      } else if (errno == ENOTEMPTY) {
        printf("'%s' not empty. try recursive deletion instead.\n", path);
      } else if (errno == EACCES) {
        printf("unable to access '%s'. you probably need higher permissions.\n",
               path);
      } else {
        printf("unknown error occured when trying to remove '%s'.\n", path);
      }
      return errno;
    }
  } else {
    unlink(path);
    if (errno == 0) {
      return 0;
    } else if (errno == EACCES || errno == EPERM) {
      printf("unable to access '%s'. you probably need higher permissions.\n",
             path);
    } else {
      printf("unknown error occured when trying to remove '%s'.\n", path);
    }
    return errno;
  }
}

int main(int argc, char **argv) {
  bool recursive = false;
  bool force = false;
  char *path;
  for (int i = 1; i < argc; i++) {
    char *arg = argv[i];
    /*printf(arg);
    printf(" ");*/
    if (!strcmp(arg, "--help")) {
      char *help =
          "Drake's Epic Coreutils (working title) " DRAKECU_VERSION "\n"
          "rm - removes files and directories.\n"
          "available arguments:\n"
          "	--help:          show this help message\n"
          "	--version:       show the version of the program\n"
          "	--recursive, -r: recursively delete files inside directories.\n"
          "usage:\n"
          "	rm -{r} [long options] [file/directory]";
      printf("%s\n", help);
      return 0;
    } else if (!strcmp(arg, "--version")) {
      printf("%s\n", DRAKECU_VERSION);
      return 0;
    } else if (!strcmp(arg, "--recursive")) {
      recursive = true;
    } else if (!strcmp(arg, "--force")) {
      // what does --force/-f *actually* mean? yea, we all use it... but like
      // why not use `rm -r`
      // this might just be a placebo/compatibility thing atm, lol
      force = true;
    } else if (startsWithChar(arg, '-')) {
      for (int i = 1; i < (int)strlen(arg); i++) {
        if (arg[i] == 'r') {
          recursive = true;
        } else if (arg[i] == 'f') {
          force = true;
        }
      }
    } else {
      removeFileOrDirectory(arg, recursive, force);
    }
  }
}
