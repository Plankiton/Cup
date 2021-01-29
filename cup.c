#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "cup.h"

char * program_name;
char *f = NULL, *s = NULL;
char *cmd, *cat, *proj, *subdir;
char * al [4], * al2 [2], * arglist [6];

int main(int argc, char *argv[]) {
    program_name = argv[0];

    parse_command_line(argc, argv, &f, &s, &cmd);
    printf("%s %s %s %s\n", program_name, cmd, f, s);
    return 0;
}
