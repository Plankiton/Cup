#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "list.h"
#include "cup.h"

char * program_name;
char *f = NULL, *s = NULL;
char *cmd, *cat, *proj, *subdir;
char * al [4], * al2 [2], * arglist [6];

int main(int argc, char *argv[]) {
    program_name = argv[0];

    parse_command_line(argc, argv, &f, &s, &cmd);

    if (!strcmp(cmd, "-l")) {
        int count = count_items("/home/plankiton/Create/");
        if (count > 0) {
            char ** list = ls("/home/plankiton/Create/", 7);

            int i = 0;

            printf("\n\n%p:\n", list);
            while (i < count){
                printf("  %p %s\n", list[i], list[i]);
                free(list[i++]);
            }
            free(list);
        }
    }

    return 0;
}
