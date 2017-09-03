#include <rmv.h>
#include <argp.h>

#define r_doc "-r, recursive     recursively remove files beginning at directory [FILE]"
#define f_doc "-f, force      force removal of files, don't error if file doesn't exist"
#define i_doc "-i, --interactive      prompt before each removal"
#define v_doc "-v, --version        display program version and exit"
#define h_doc "-h, --help         display program help"

const char* version = "rmv v. 0.1";

static struct argp_option options[] = {
    {"recursive", 'r', 0, 0, r_doc},
    {"force", 'f', 0, 0, f_doc},
    {"interactive", 'i', 0, 0, i_doc},
    {"version", 'v', 0, 0, v_doc},
    {"help", 'h', 0, 0, h_doc},
    {0}
};

static char args_doc[] = "[FILES]...";
static char doc[] = "rmv - a program for safely deleting files and storing them in ~/.trash";

bool parse_error_state = false;


void arg_state_add_filename(struct arguments *s, char *filename) {
    s->n_files++;
    if (s->n_files > 10) {
        s->filenames = realloc(s->filenames, sizeof(char*) * s->n_files);
    }
    s->filenames[s->n_files - 1] = filename;
    printf("%d\n", s->n_files);
}

static error_t parse_option(int key, char *arg, struct argp_state *state) {
    struct arguments *args = state->input;

    switch (key) {
        case 'r':
            printf("no_filenames is %d\n", args->n_files);
            if (args->rec) {
                argp_usage(state);
                parse_error_state = true;
            }
            args->rec = true;
            break;
        case 'h':
            if (args->help) {
                argp_usage(state);
                parse_error_state = true;
            }
            args->help = true;
            break;
        case 'v':
            if (args->version) {
                argp_usage(state);
                parse_error_state = true;
            }
            args->version = true;
            break;
        case 'f':
            if (args->force) {
                argp_usage(state);
                parse_error_state = true;
            }
            args->force = true;
            break;
        case ARGP_KEY_ARG:
            printf("found key arg\n");
            //if we've already parsed more than five arguments, or we already have a filename...
            arg_state_add_filename(args, arg); //only non option argument is a filename
            break;
        case ARGP_KEY_END:
            if (state->arg_num < 1) {
                argp_usage(state);
                parse_error_state = true;
            }
            break;
        default:
            return ARGP_ERR_UNKNOWN;
    }
    return 0;
}

static struct argp argp = {options, parse_option, args_doc, doc};

 bool  command_arguments_parse(int argc, char **argv, struct arguments *args) {
    if (argc < 1) {
        return false;
    }

    args->interactive = false;
    args->help = false;
    args->version = false;
    args->rec = false;
    args->force = false;
    args->filenames = malloc(sizeof(char *) * 10);
    args->n_files = 0;
    //10 element array


    argp_parse(&argp, argc, argv, 0, 0, args);
	printf("PARSE ERROR STATE: %d\n", parse_error_state);
    return !parse_error_state;
}

void command_arguments_clean(struct arguments * ptr) {
    free(ptr->filenames);
}
