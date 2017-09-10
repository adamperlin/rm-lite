#include <rmv.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <join.h>
#include <string.h>
#include <fsutil.h>
#include <dirent.h>

#define TRASH_DIR_PERM 0700
int is_special_dir(char *dir);

const char *trash_dir_root = ".trash";

void exec_remove(struct arguments *args) {
	if (args == NULL) return;
	//printf("creating trash dir\n");
	char *trash_dir_root = create_trash_dir();

    for (int i = 0; i < args->n_files; i++) {
        if (is_dir(args->filenames[i])) {
            if (!args->rec) {
                fprintf(stderr, "Error: must use '-r' Option with directories");
                exit(-1);
            }
            recursive_remove_file(args->filenames[i], trash_dir_root);
        } else {
            single_remove_file(args->filenames[i], trash_dir_root);
        }
    }
	free(trash_dir_root);
}

int single_remove_file(const char *pname, const char *trash_dir_root) {
    int s_len = strlen(pname) + strlen(trash_dir_root) + 2;
    char new_path[s_len];
    new_path[s_len - 1] = '\0';
    path_join(new_path, trash_dir_root, pname);

    if (!same_filesystem(pname, (const char*) new_path)) {
        return file_copy(pname, (const char *) new_path);
    }

//    printf("renaming file");
    int errno;
    if ((errno = rename(pname, (const char *) new_path)) < 0) {
        fprintf(stderr, "syscall rename return errno %d\n", errno);
        return 0;
    }

 //   printf("Returning 1!"); 
    return 1;
}


char *create_trash_dir() {
	const char *trash_dir_root = ".trash";
    char *homedir = getenv("HOME");
    if ((homedir = getenv("HOME")) == NULL) {
        homedir = getpwuid(getuid())->pw_dir;
    }

    int len = strlen(homedir) + strlen(trash_dir_root) + 2;
    char joined[len];
    joined[len - 1] = '\0';
    path_join(joined, (const char *) homedir, trash_dir_root);

    struct stat st;
    if (stat(joined, &st) == -1) {
        mkdir(joined, TRASH_DIR_PERM);
    }
	
	char *dir = malloc(sizeof(char) * len);
	dir[len - 1] = '\0';
	strncpy(dir, joined, len);
	return dir; 
}

int recursive_remove_file(char *dir, const char *trash_dir_root) {
	DIR *dirp = opendir(dir);
	struct dirent *dp;

	int dirname_len = strlen(dir);
	int full_new_path_len = dirname_len + strlen(trash_dir_root) + 2;
	char full_new_path[full_new_path_len];
	full_new_path[full_new_path_len - 1] = '\0';
	path_join(full_new_path, trash_dir_root, dir);
	
	struct stat st; 
	if (stat(dir, &st) < 0) {
		return 0;
	} 

//	printf("Creating new directory\n");
	mkdir(full_new_path, st.st_mode & 0700);

	while((dp = readdir(dirp))) {
//		printf("in loop");
		char *fname = dp->d_name;
//		if (fname != NULL) printf("current file: %s\n", fname);
		if (fname != NULL && !is_special_dir(fname)) {
			int len = dirname_len + strlen(fname) + 2; 
			char temp_name[len];
			temp_name[len - 1] = '\0';
			path_join(temp_name, dir, fname);
			
//			printf("File to remove path is: %s\n", temp_name); 
			if (is_dir(temp_name)) {
				recursive_remove_file(temp_name, trash_dir_root);
			} else {
				single_remove_file(temp_name, trash_dir_root);
			}
		}
	}
	rmdir(dir);
	return 1;
}

int is_special_dir(char *fname) {
	return strcmp(fname, ".") == 0 || strcmp(fname, "..") == 0; 
}
