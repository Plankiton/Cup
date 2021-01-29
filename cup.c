#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * program_name;
char *cmd, *cat, *proj, *subdir;
char * al [4], * al2 [2], * arglist [6];

void usage(void) {
    printf("%s [Options]\n\n" , program_name);
    puts(
"Options"
"\n---------------\n\n"
"-h                          show this message.\n"
"-l <cat>                    list the projects on a category\n"
"                               default: all\n"
"-L                          list the categories\n"
"-c <cat> <proj>/<subdir>    create new project on a category\n"
"                               default cat: proj, subdir: .\n"
"-d <cat> <proj>/<subdir>    delete new project on a category\n"
"                               default cat: proj, subdir: .\n"
"-s <cat|proj>/<subdir>      show directory of category or project\n\n"
        );
}

char in(char * s, char *ls[], int lsl) {
    for (int i = 0; i < lsl; i++) {
        if (!ls[i]) continue;
        if (!strcmp(s, ls[i])) {
            return 1;
        }
    }
    return 0;
}

void get_arg_value(char **first, char **second, char ** a, int c, int i) {
    i++;
    if (i >= c)
        return;

    if (!in(a[i], arglist, 6)) {
        if (i >= c)
            return;

        *first = a[i++];
        if (i >= c)
            return;

        if (!in(a[i], arglist, 6)) {
            *second = a[i];
        }

    }
}

char *f = NULL, *s = NULL;
void parse_command_line(const int c, char *a[]) {
    program_name = a[0];

    for (int i = 0; i < c; i ++) {
        if (!strcmp(a[i], "-h")) {
            usage();
            exit(0);
        }

        if (in(a[i], al2, 2)) {

            cmd = a[i];
            get_arg_value(&f, &s, a, c, i);

            if (f) {
                if (s) {
                    return;
                }
            }
        }
        if (in(a[i], al, 4)) {
            cmd = a[i];
            get_arg_value(&f, &s, a, c, i);

            if (f) {
                return;
            }
        }
    }

    usage();
    fputs("ERROR: Have a missing argument!", stderr);
}

int main(int argc, char *argv[]) {
    {int ch = 0;
        arglist[ch++] = (char *)"-l";
        arglist[ch++] = (char *)"-L";
        arglist[ch++] = (char *)"-h";
        arglist[ch++] = (char *)"-s";
        arglist[ch++] = (char *)"-d";
        arglist[ch++] = (char *)"-c";
    }
    {int ch = 0;
        al2[ch++] = (char *)"-d";
        al2[ch++] = (char *)"-c";
    }
    {int ch = 0;
        al[ch++] = (char *)"-l";
        al[ch++] = (char *)"-s";
        al[ch++] = (char *)"-d";
        al[ch++] = (char *)"-c";
    }

    parse_command_line(argc, argv);
    printf("%s %s %s %s\n", program_name, cmd, f, s);
    return 0;
}
