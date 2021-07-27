#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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

static int concatFileToStdoutWithOptions(char *file, bool showLineEnds) {
  FILE *fp;
  fp = fopen(file, "r");
  if (fp == NULL) {
    printf("failed to open '%s'. perhaps the path doesn't exist?\n", file);
    exit(1);
  }
  char *contents = malloc(2);
  while (fgets(contents, 2, fp) != NULL) {
    if (showLineEnds == true && contents[0] == '\n') {
      printf("$");
    }
    printf("%s", contents);
  }
  free(contents);
  fclose(fp);
  return 0;
}

int main(int argc, char **argv) {
  if (argc == 1) {
    char ch;
    while (read(STDIN_FILENO, &ch, 1) > 0) {
      printf("%c", ch);
    }
    return 0;
  } else {
    bool showLineEnds = false;
    for (int i = 1; i < argc; i++) {
      char *arg = argv[i];
      if (!strcmp(arg, "--help")) {
        char *help =
            "Drake's Epic Coreutils (working title) " DRAKECU_VERSION "\n"
            "cat - concatenate file to stdout.\n"
            "Usage:\n"
            "	cat [options] [FILE]\n"
            "Available arguments:\n"
            "	--help:                            show this help message\n"
            "	--version:                         show the version of the "
            "program\n"
            "	--show-ends, --show-line-ends, -E: print '$' at the end of "
            "lines.\n"
            "Notes:\n"
            "	If no file is specified, FILE will be stdin.";
        printf("%s\n", help);
        return 0;
      } else if (!strcmp(arg, "--version")) {
        printf("%s\n", DRAKECU_VERSION);
        return 0;
      } else if (!strcmp(arg, "--show-ends") ||
                 !strcmp(arg, "--show-line-ends") || !strcmp(arg, "-E")) {
        showLineEnds = true;
      } else {
        concatFileToStdoutWithOptions(arg, showLineEnds);
      }
    }
    return 0;
  }
}
