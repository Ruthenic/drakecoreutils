#include <fcntl.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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

static int copyFile(const char *src, const char *dst) {
  FILE *sfp, *dfp;
  sfp = fopen(src, "r");
  dfp = fopen(dst, "w");
  if (sfp == NULL) {
    printf("failed to open '%s'. perhaps the path doesn't exist?\n", src);
    exit(1);
  }
  char *contents = NULL;
  char *buf = malloc(2);
  int n = 0;
  while (fgets(buf, 2, sfp) != NULL) {
    fseek(dfp, n, SEEK_SET);
    fwrite(buf, 2, sizeof(buf), dfp);
    n++;
  }
  free(buf);
  fclose(sfp);
  fclose(dfp);
  return 0;
}

int cp(int argc, char **argv) {
  int isDst = 0;
  char *src;
  char *dst;
  if (argc == 1) {
    printf("no arguments supplied.");
    return -1;
  } else {
    for (int i = 1; i < argc; i++) {
      char *arg = argv[i];
      /*printf(arg);
      printf(" ");*/
      if (!strcmp(arg, "--help")) {
        char *help =
            "Drake's Epic Coreutils (working title) " DRAKECU_VERSION "\n"
            "cp - prints the working user's username (unless --uid is "
            "specified)\n"
            "Available arguments:\n"
            "	--help: show this help message\n"
            "	--version: show the version of the program\n"
            "	--uid: print the users numeric UID, instead of username";
        printf("%s\n", help);
        return 0;
      } else if (!strcmp(arg, "--version")) {
        printf("%s\n", DRAKECU_VERSION);
        return 0;
      } else {
        if (isDst == 0 && strcmp(arg, argv[0])) {
          src = arg;
          isDst = 1;
        } else {
          copyFile(src, arg);
        }
      }
    }
  }
}
