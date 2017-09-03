#include <rmv.h>
#include <stdio.h> 
#include <sys/stat.h>

#define FAIL(a) fprintf(stderr, "TEST FAILED WITH MESSAGE %s\n", (a)); \
	exit(-1);

#define TEST_PASS() printf("TESTS PASSED!\n");

void test_remove_single_file();
void test_remove_multiple_files();
void test_remove_directory();
void test_missing_args();

void (*tests[])() = {
	test_remove_single_file,
	test_remove_multiple_files,
	test_remove_directory
};

const int TESTS = 3;

int main() {
	for (int i = 0; i < TESTS; i++) {
		tests[i](); 
	}
}

void test_remove_single_file() {
	char *argv[] = {"rmv", "file.txt"};
	int argc = 2; 
	
	struct arguments args;

	int err = command_arguments_parse(argc, argv, &args);
	if (!err) {
		FAIL("Command line parsing failed\n");
	}
	FILE *fp = fopen("file.txt", "ab+");
	fprintf(fp, "Test file\n");
	fclose(fp);

	exec_remove(&args);

	struct stat st; 
	
	if (stat("file.txt", &st) >= 0) {
		FAIL("File not removed correctly\n");
	}

	TEST_PASS(); 
}

void test_remove_multiple_files() {
	char *files[] = {"file.txt", "file1.txt", "file2.txt"};
	char *argv[] = {"rmv", "file.txt", "file1.txt", "file2.txt"};
	int argc = 4; 
	
	struct arguments args;

	int err = command_arguments_parse(argc, argv, &args);
	if (!err) {
		FAIL("Command line parsing failed\n");
	}
	for (int i = 0; i < 3; i++) {
		FILE *fp = fopen(files[i], "ab+");
		fprintf(fp, "Test file\n");
		fclose(fp);
	}


	exec_remove(&args);
	
	struct stat st;	
	for (int i = 0; i < 3; i++) { 
		if (stat(files[i], &st) >= 0) {
			FAIL("File not removed correctly\n");
		}
	}
	TEST_PASS(); 
}

void test_remove_directory() {
	char *dirs[] = {"test_dir", "test_dir/dir1", "test_dir/dir1/dir2"};
	for (int i = 0; i < 3; i++) {
		mkdir(dirs[i], 0700);
	}

	char *files[] = { "test_dir/file2.txt",  "test_dir/dir1/file3.txt", "test_dir/dir1/dir2/file3.txt"};
	for (int i = 0; i < 3; i++) {
		FILE *fp = fopen(files[i], "ab+");
		fprintf(fp, "Test file\n");
		fclose(fp);
	}
	
	struct arguments args;
	char *argv[] = {"rmv", "-r", "test_dir"};
	int argc = 3;

	if (!command_arguments_parse(argc, argv, &args)) {
		FAIL("Command arguments not parsed correctly\n");
	}

	TEST_PASS(); 
}

void test_missing_args() {

}


