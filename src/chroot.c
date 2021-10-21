#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
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

/*
chroot - changes root directory for a specified process
available arguments:
    --help - prints this help message
    --version - prints version information
    -c <executable> - runs the specified executable in the new root directory
instead of the default

usage:
    chroot [OPTIONS] [DIRECTORY]
*/
int runChroot(char *executable, char *directory) {
  if (chdir(directory) == -1) {
    perror("chdir");
    return 1;
  } else if (chroot(".") == -1) {
    perror("chroot");
    return 1;
  } else if (execvp(executable, NULL) == -1) {
    perror("execvp");
    return 1;
  }
  return 0;
}

int chr(int argc, char *argv[]) {
  int i;
  char *executable = "/bin/sh";
  char *directory = argv[argc - 1];
  for (i = 1; i < argc; i++) {
    if (strcmp(argv[i], "--help") == 0) {
      printf("chroot - changes root directory for a specified process\n");
      printf("available arguments:\n");
      printf("    --help - prints this help message\n");
      printf("    --version - prints version information\n");
      printf("    -c <executable> - runs the specified executable in the new "
             "root directory instead of '/bin/sh'\n");
      printf("instead of the default\n");
      printf("usage:\n");
      printf("    chroot [OPTIONS] [DIRECTORY]\n");
      return 0;
    } else if (strcmp(argv[i], "--version") == 0) {
      printf("%s\n", DRAKECU_VERSION);
      return 0;
    } else if (strcmp(argv[i], "-c") == 0) {
      if (i + 1 < argc) {
        executable = argv[++i];
      } else {
        printf("chroot: option requires an argument -- '-c'\n");
        return 1;
      }
    }
  }
  return runChroot(executable, directory);
}
