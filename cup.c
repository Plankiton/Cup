#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "cup.h"

char show_cat = 0;
char * root_path;
char * program_name;
char *f = NULL, *s = NULL;
char *cmd, *cat, *proj, *subdir;
char * al [4], * al2 [2], * arglist [6];

int main(int argc, char *argv[]) {
    program_name = argv[0];

    parse_command_line(argc, argv, &f, &s, &cmd);

    root_path = getenv("HOME");
    if (root_path[strlen(root_path)-1] != '/')
        root_path = strcat(root_path, "/");
    root_path = strcat(root_path, "Create/");

    const int types [] = {4, -1};
    int count = count_items(root_path, types);
    if (count < 0)
        die("\"%s\" %s", root_path, "not exists, create it first");
    char ** cat_list = ls(root_path, count, types);

    if (!strcmp(cmd, "-L")) {
        if (count > 0) {
            for (int i = 0; i < count; i ++) {
                if (strcmp(cat_list[i], ".")&&strcmp(cat_list[i], ".."))
                    puts(cat_list[i]);
            }
        }
    } else if (!strcmp(cmd, "-l")) {
        if (f)
            cat = f;
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

            if (category)
                list_proj(category);
            else
                die("Category not found!");

        } else {
            int lenght = 0;
            for (int i = 0; i < count; i ++) {
                int cat_len = strlen(cat_list[i]);
                if (lenght < cat_len)
                    lenght = cat_len;
            }

            show_cat = 1;
            putchar('\n');
            for (int i = 0; i < count; i ++) {
                if (strcmp(cat_list[i], ".")&&strcmp(cat_list[i], ".."))
                {
                    cat = cat_list[i];
                    if (!has_proj(cat))
                        continue;
                    printf("%s: \n",
                            cat);
                    list_proj(cat);

                    putchar('\n');
                    if (i < count - 2)
                        putchar('\n');
                }
            }
        }

    }

    free_list(cat_list, count);
    return 0;
}

int has_proj(char * category) {
    const int types [] = {4, -1};
    char cat_path [strlen(root_path)+strlen(category)];
    strcpy(cat_path, root_path);

    strcat(cat_path, category);
    if (cat_path[strlen(cat_path)-1] != '/')
        strcat(cat_path, "/");

    int count = count_items(cat_path, types);
    return count>2 ? count : 0;
}

void list_proj(char * category) {
    const int types [] = {4, -1};
    char cat_path [strlen(root_path)+strlen(category)];
    strcpy(cat_path, root_path);

    strcat(cat_path, category);
    if (cat_path[strlen(cat_path)-1] != '/')
        strcat(cat_path, "/");

    int count = count_items(cat_path, types);
    char ** proj_list = ls(cat_path, count, types);
    for (int i = 0; i < count; i ++) {
        if (strcmp(proj_list[i], ".")&&strcmp(proj_list[i], "..")){
            if (show_cat)
                putchar('\t');
            puts(proj_list[i]);
        }
    }

    free_list(proj_list, count);
}
