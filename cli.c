#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "cli.h"

void usage(const char * program_name) {
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

void get_arg_value(char **first, char **second, char ** a, int c, int i, char ** arglist) {
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

void parse_command_line(const int c, char *a[], char ** f, char ** s, char ** cmd) {
    char * program_name = a[0];
    char *arglist[6];{int ch = 0;
        arglist[ch++] = (char *)"-l";
        arglist[ch++] = (char *)"-L";
        arglist[ch++] = (char *)"-h";
        arglist[ch++] = (char *)"-s";
        arglist[ch++] = (char *)"-d";
        arglist[ch++] = (char *)"-c";
    }
    char *al2[2];{int ch = 0;
        al2[ch++] = (char *)"-d";
        al2[ch++] = (char *)"-c";
    }
    char *al[4];{int ch = 0;
        al[ch++] = (char *)"-l";
        al[ch++] = (char *)"-s";
        al[ch++] = (char *)"-d";
        al[ch++] = (char *)"-c";
    }

    for (int i = 0; i < c; i ++) {
        if (!strcmp(a[i], "-h")) {
            usage(program_name);
            exit(0);
        }

        if (in(a[i], al2, 2)) {

            *cmd = a[i];
            get_arg_value(f, s, a, c, i, arglist);

            if (f) {
                if (s) {
                    return;
                }
            }
        }
        if (in(a[i], al, 4)) {
            *cmd = a[i];
            get_arg_value(f, s, a, c, i, arglist);

            if (f) {
                return;
            }
        }
    }

    usage(program_name);
    fputs("ERROR: Have a missing argument!", stderr);
}

