#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "util.h"
#include "cli.h"

void usage(const char * program_name) {
    printf("%s [Options]\n\n" , program_name);
    puts(
"Options\n"
"    default: -s\n"
"---------------\n\n"
"-h                          show this message.\n"
"-l <cat> <proj>/<subdir>    list the projects on a category\n"
"                               default cat: all, proj: none, subdir: none\n"
"-L                          list the categories\n"
"-c <cat> <proj>/<subdir>    create new project on a category\n"
"                               default cat: proj, subdir: none\n"
"-d <cat> <proj>/<subdir>    delete new project on a category\n"
"                               default cat: proj, subdir: none\n"
"-s <cat|proj>/<subdir>      show directory of category or project\n\n"
"                               default cat: proj, subdir: none\n"
        );
}

void get_arg_value(char **first, char **second, char ** a, int c, int i, char ** arglist) {
    i++;
    if (i >= c)
        return;

    if (!strin(a[i], (const char **)arglist, 6)) {
        if (i >= c)
            return;

        if (a[i] && first)
            *first = a[i];
        i++;
        if (i >= c)
            return;

        if (!strin(a[i], (const char **)arglist, 6)) {
            if (a[i] && second)
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
    char *al2[3];{int ch = 0;
        al2[ch++] = (char *)"-d";
        al2[ch++] = (char *)"-c";
        al2[ch++] = (char *)"-s";
    }
    char *al1[4];{int ch = 0;
        al1[ch++] = (char *)"-l";
        al1[ch++] = (char *)"-s";
        al1[ch++] = (char *)"-d";
        al1[ch++] = (char *)"-c";
    }
    char *al[2] = {"-L", "-l"};

    for (int i = 1; i < c; i ++) {
        if (!strcmp(a[i], "-h")) {
            usage(program_name);
            exit(0);
        }

        if (strin(a[i], (const char **)al2, 3)) {

            *cmd = a[i];
            get_arg_value(f, s, a, c, i, arglist);

            if (*f) {
                if (*s) {
                    return;
                }
            }
        } else if (!strin(a[i], (const char **)arglist, 6)) {
            *cmd = "-s";
            *f = a[i];
            *s = a[i+1];

            if (*f)
                if (*s)
                    return;
        }
        if (strin(a[i], (const char **)al1, 4)) {
            *cmd = a[i];
            get_arg_value(f, s, a, c, i, arglist);

            if (*f) {
                return;
            }
        } else if (!strin(a[i], (const char **)arglist, 6)) {
            *cmd = "-s";
            *f = a[i];
            if (*f)
                return;
        }
        if (strin(a[i], (const char **)al, 2)) {
            *cmd = a[i];
            return;
        }
    }

    usage(program_name);
    die("Have a missing argument!");
}

