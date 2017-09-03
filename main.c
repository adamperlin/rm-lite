#include <rmv.h>
#include <join.h>
#include <string.h>
#include <fsutil.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>

int main(int argc, char **argv) {
    struct arguments args;
    if (!command_arguments_parse(argc, argv, &args)) {
    	return 1; 
    } 

	exec_remove(&args);
	command_arguments_clean(&args);
	return 0; 
}
