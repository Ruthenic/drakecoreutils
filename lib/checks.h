#include <stdbool.h>
#include <string.h>

static bool startsWithChar(const char *pre, const char str) {
  char *e;
  int index;
  e = strchr(pre, str);
  index = (int)(e - pre);
  return index == 0;
}

static bool startsWithStr(char *prefix, char *string) {
  if (strlen(prefix) > strlen(string)) {
    return false;
  }
  int max = strlen(prefix);
  int i = 0;
  do {
    if (prefix[i] == string[i]) {
      i++;
    } else {
      return false;
    }
  } while (i < max);
  return true;
}
