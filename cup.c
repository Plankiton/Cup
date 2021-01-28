#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * program_name;

typedef struct {
    void * value;
    int identifier;
} Option;

void usage(void) {
    printf("%s [Options]\n\n" , program_name);
    puts(
"Options"
"\n---------------\n\n"
"-h                 show this message.\n"
"-l <cat>           list the projects on a category\n"
"                              default: all\n"
"-L                 list the categories\n"
"-c <cat>/<proj>    create new project on a category\n"
"                            default cat: proj\n"
"-d <cat>/<proj>    delete new project on a category\n"
"                            default cat: proj\n"
"-s <cat|proj>      show directory of category or project\n\n"
        );
}

char in(char * s, char *ls[], int lsl) {
    for (int i = 0; i < lsl; i++)
        if (!strcmp(s, ls[i]))
            return 1;
    return 0;
}

void parse_command_line(const int c, char *a[]) {
    program_name = a[0];

    for (int i = 0; i < c; i ++) {
        for (int o = 0; o < 5; o ++) {
            if (!strcmp(a[i], "-h")) {
                usage();
                exit(0);
            }

        }
    }

    usage();
    exit(1);
}

int main(int argc, char *argv[]) {
    parse_command_line(argc, argv);

    return 0;
}
