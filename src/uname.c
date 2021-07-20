#include <bits/local_lim.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/utsname.h>
#include <unistd.h>

/*
whoami - prints the working user's username (unless --uid is specified)
Available arguments:
        --help: show this help message
        --version: show the version of the program (WIP)
        --uid: print the users numeric UID, instead of username
*/

// https://stackoverflow.com/questions/4770985/how-to-check-if-a-string-starts-with-another-string-in-c/4770992#4770992
bool startsWithChar(const char *pre, const char str) {
  char *e;
  int index;
  e = strchr(pre, str);
  index = (int)(e - pre);
  return index == 0;
}

int main(int argc, char **argv) {
  struct utsname uts;
  uname(&uts);
  if (argc == 1) {
    printf("%s\n", uts.sysname);
  } else {
    for (int i = 1; i < argc; i++) {
      char *arg = argv[i];
      /*printf(arg);
       */
      if (!strcmp(arg, "--help")) {
        char *help =
            "Drake's Epic Coreutils (working title) " DRAKECU_VERSION "\n"
            "uname - prints system information.\n"
            "Available arguments:\n"
            "	--help:         show this help message\n"
            "	--version:      show the version of the program\n"
            "	-a, --all:      print all information (equivalent to -shrvm). "
            "\n"
            "	-s, --sysinfo:  kernel type(?)\n"
            "	-h, --hostname: hostname\n"
            "	-r, --krelease: kernel version\n"
            "	-v, --kversion: verbose kernel build version info\n"
            "	-m, --arch:     cpu architecture\n"
            "Examples:\n"
            "	Command:\n"
            "		uname -srh\n"
            "	Example output (on my system):\n"
            "		Linux 5.12.14_1 ruthenic-void";
        printf("%s\n", help);
        return 0;
      } else if (!strcmp(arg, "--version")) {
        printf("%s\n", DRAKECU_VERSION);
        return 0;
      } else if (!strcmp(arg, "--hostname")) {
        char hostname[HOST_NAME_MAX + 1];
        gethostname(hostname, HOST_NAME_MAX + 1);
        printf("%s ", hostname);
      } else if (!strcmp(arg, "--sysinfo")) {
        printf("%s ", uts.sysname);
      } else if (!strcmp(arg, "--krelease")) {
        printf("%s ", uts.release);
      } else if (!strcmp(arg, "--kversion")) {
        printf("%s ", uts.version);
      } else if (!strcmp(arg, "--arch")) {
        printf("%s ", uts.machine);
      } else if (!strcmp(arg, "--all")) {
        // equivalent to -shrvm
        printf("%s ", uts.sysname);
        char hostname[HOST_NAME_MAX + 1];
        gethostname(hostname, HOST_NAME_MAX + 1);
        printf("%s ", hostname);
        printf("%s ", uts.release);
        printf("%s ", uts.version);
        printf("%s ", uts.machine);
      } else if (startsWithChar(arg, '-')) {
        char info;
        for (unsigned long n = 1; n < strlen(arg); n++) {
          info = arg[n];
          // printf(info);
          // printf("\n");
          if (info == 'h') {
            char hostname[HOST_NAME_MAX + 1];
            gethostname(hostname, HOST_NAME_MAX + 1);
            printf("%s ", hostname);
          }
          if (info == 's') {
            printf("%s ", uts.sysname);
          }
          if (info == 'r') {
            printf("%s ", uts.release);
          }
          if (info == 'v') {
            printf("%s ", uts.version);
          }
          if (info == 'm') {
            printf("%s ", uts.machine);
          }
          if (info == 'a') {
            // equivalent to -shrvm
            printf("%s ", uts.sysname);
            char hostname[HOST_NAME_MAX + 1];
            gethostname(hostname, HOST_NAME_MAX + 1);
            printf("%s ", hostname);
            printf("%s ", uts.release);
            printf("%s ", uts.version);
            printf("%s ", uts.machine);
          }
        }
      }
    }
    printf("\n");
  }
}
