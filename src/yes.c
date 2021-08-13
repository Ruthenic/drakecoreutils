#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
yes - spams a message (by default `y`) to stdout.
Available arguments:
        --help: show this help message.
        --version: show version of the program.
Usage:
        yes [--help] [--version] [message]
*/

int main(int argc, char **argv) {
  char *spammy = malloc((sizeof(char) * 16) * 2);
  int len = 2048; // max length of buffer
  char buf[len];
  FILE *stdoutFP = stdout;
  if (argc == 1) {
    spammy = "y\n";
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
        printf("%s\n", DRAKECU_VERSION);
        return 0;
      } else {
        spammy = realloc(spammy, strlen(arg) + 1);
        sprintf(spammy, "%s\n", arg);
      }
    }
  }
  int n = 0;
  int splen = strlen(spammy);
  do {
    sprintf(buf, "%s%s", buf, spammy);
    n++;
  } while (n < len);
  do {
    fwrite(buf, sizeof(char), len, stdoutFP);
  } while (1);
}
