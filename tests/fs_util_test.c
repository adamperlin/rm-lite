#include <fsutil.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
const char *test_file_1 = "test_files/file1.txt";
const char *test_file_2 = "test_files/file2.txt";

const char *test_file_3 = "test_files/file3.txt";
const char *test_dir = "test_files/test_dir";
int main() {
	if (!same_filesystem(test_file_1, test_file_2)) {
		fprintf(stderr, "Files should be in same filesystem\n");
			exit(-1);
	}

	int res = file_copy(test_file_3, "copy_file3.txt");
	if (!res) {
		fprintf(stderr, "Copy failed\n");
		exit(-1);
	}

	struct stat st;
	if (stat("copy_file3.txt", &st) < 0) {
		fprintf(stderr, "Copied file doesn't exist\n");
		exit(-1);
	}
	
	if (!is_dir(test_dir)) {
		fprintf(stderr, "Directory not identified\n");
		exit(-1);
	}
	
	printf("Tests passed!\n");
	return 0;
}
