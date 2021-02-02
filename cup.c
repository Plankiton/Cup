#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "util.h"
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
        if (f)
            cat = f;

        char * root_path = getenv("HOME");
        if (root_path[strlen(root_path)-1] != '/')
            root_path = strcat(root_path, "/");
        root_path = strcat(root_path, "Create/");

        const int types [] = {4, -1};
        int count = count_items(root_path, types);
        char ** cat_list = ls(root_path, count, types);
        if (cat) {
            char * category = NULL;
            if (count > 0) {
                for (int i = 0; i < count; i ++) {
                    char * l_cat = to_lower(cat);
                    char * cat_name = to_lower(cat_list[i]);

                    if (strstr(cat_name, l_cat)) {
                        category = cat_list[i];
                        break;
                    }
                }

            }

            if (category) {
                char * cat_path = root_path;
                cat_path = strcat(cat_path, category);
                if (cat_path[strlen(cat_path)-1] != '/')
                    cat_path = strcat(cat_path, "/");

                int count = count_items(cat_path, types);
                char ** proj_list = ls(cat_path, count, types);
                for (int i = 0; i < count; i ++) {
                    if (strcmp(proj_list[i], ".")&&strcmp(proj_list[i], ".."))
                        puts(proj_list[i]);
                }

                free_list(proj_list, count);
            } else {
                fprintf(stderr, "ERROR: Category not found!");
            }

        } else {
        }
        free_list(cat_list, count);
    }

    return 0;
}
