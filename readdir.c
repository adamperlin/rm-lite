#include <stdio.h>
#include <pwd.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

int main() {
	DIR *d = opendir("include");
	if (!d) {
		fprintf(stderr, "Failed to read directory\n");
		exit(-1);
	}
	
	printf("DONE\n");

	struct dirent *dp = NULL;
	
	while(dp = readdir(d)) {
		if (dp->d_name != NULL && strcmp(dp->d_name, "..") != 0 && strcmp(dp->d_name, ".") != 0) {
			printf("%s\n", dp->d_name);
		}
	}
}


