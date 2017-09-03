#include <fsutil.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <unistd.h>
#include <fcntl.h>

#define INITIAL_BUF_SIZ 8192
 

int same_filesystem(const char *path1, const char *path2) {
    struct stat s1, s2;
    if (stat(path1, &s1) < 0) {
        fprintf(stderr, "failed to stat file %s\n", path1);
        return 0;
    }

    uint32_t dev1_id = (uint32_t) s1.st_dev;

    if (stat(path2, &s2) < 0) {
        fprintf(stderr, "failed to stat file %s\n", path2);
        return 0;
    }

    uint32_t dev2_id = (uint32_t) s2.st_dev;
    return dev1_id == dev2_id;
}

int file_copy (const char *i_path, const char *o_path) {
    char buf[INITIAL_BUF_SIZ];

    int in_fd;
    int out_fd;

    struct stat st;
	printf("input path is: %s\n", i_path);
    if (stat(i_path, &st) < 0) {
        return 0;
    }

    in_fd = open(i_path, O_RDWR);
    out_fd = open(o_path, O_RDWR|O_CREAT);

    ssize_t res;

    while ((res = read(in_fd, buf, sizeof(buf)))) {
        write(out_fd, buf, res);
    }
	
	if (chmod(o_path, st.st_mode & 7777) != 0) {
		fprintf(stderr, "chmod failed");
		return 0;
	}
    return 1;
}

// returns 0 if file doesn't exist at all
int is_dir(const char *filepath) {
	struct stat sbuf;
	if (stat(filepath, &sbuf) < 0) {
		fprintf(stderr, "Can't stat directory\n");
		return 0;
	}
	return S_ISDIR(sbuf.st_mode); 
}
