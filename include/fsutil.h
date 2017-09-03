#ifndef FSUTIL_H
#define FSUTIL_H


#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int same_filesystem(const char *p1, const char *p2);

int file_copy(const char *i_path, const char *o_path);

int is_dir(const char *file_path);

#endif
