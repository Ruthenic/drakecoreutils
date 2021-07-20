#include <sys/stat.h>

static _Bool isRegularFile(const char *path) {
  struct stat path_stat;
  lstat(path, &path_stat);
  return S_ISREG(path_stat.st_mode);
}

static _Bool isDirectory(const char *path) {
  struct stat path_stat;
  lstat(path, &path_stat);
  return S_ISDIR(path_stat.st_mode);
}

static _Bool isSymlink(const char *path) {
  struct stat path_stat;
  lstat(path, &path_stat);
  return S_ISLNK(path_stat.st_mode);
}
