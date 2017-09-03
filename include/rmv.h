/* Function prototypes here: */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


struct arguments {
    bool interactive;
    bool help;
    bool rec;
    bool version;
    bool force;
    char **filenames;
    int n_files;
};


//const char *doc = "DOC...";

void command_arguments_register();
//bool command_arguments_parse();/* Function prototypes here: */
bool command_arguments_parse(int, char**, struct arguments *);

void command_arguments_clean(struct arguments *);

char *create_trash_dir();

void exec_remove(struct arguments *args);

int single_remove_file(const char *, const char *);

int recursive_remove_file(char *dir, const char *);
