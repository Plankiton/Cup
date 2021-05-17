#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <regex.h>
#include "icon.h"
#include "cup.h"

char * root_path;
char * program_name;
char *f = NULL, *s = NULL;
char *cmd, *cat, *proj, *subdir;
char * al [4], * al2 [2], * arglist [6];

const int types [] = {4, -1};
int main(int argc, char *argv[]) {
    program_name = argv[0];

    parse_command_line(argc, argv, &f, &s, &cmd);

    root_path = getenv("HOME");
    if (root_path[strlen(root_path)-1] != '/')
        root_path = strcat(root_path, "/");
    root_path = strcat(root_path, "Create/");

    const int types [] = {4, -1};
    int cat_count = count_items(root_path, types);
    if (cat_count < 0)
        die("\"%s\" %s", root_path, "not exists, create it first");
    else if (cat_count == 0)
        die("not exist categories, create it first");
    char ** cat_list = ls(root_path, cat_count, types);

    if (!strcmp(cmd, "-L")) {
        just_ls(root_path, "%s  %s\n", NULL);
    } else if (!strcmp(cmd, "-l")) {
        if (f)
            cat = f;
        if (s)
            proj = s;
        else proj = f;

        if (cat) {
            char * category = get_from_patt(cat, cat_list, cat_count);
            char ** proj_list = NULL;
            int count = 0;
            subdir = strchr(proj, '/');
            if (subdir)
                *subdir++ = 0;

            if (category) {
                proj_list = get_list_proj(category);
                count = get_list_proj_count(category);
                if (cat == proj)
                    proj = NULL;
            } else {
                cat = NULL;
                for (int c = 0; c < cat_count; c++) {
                    cat = cat_list[c];

                    if (!strcmp("..", cat)||!strcmp(".", cat))
                        continue;

                    category = get_from_patt(cat, cat_list, cat_count);
                    proj_list = get_list_proj(category);
                    count = get_list_proj_count(category);

                    char * project = get_from_patt(proj, proj_list, count);
                    if (project) {

                        char proj_path[] = "";
                        strcat(proj_path, get_cat_path(category));
                        strcat(proj_path, project);
                        if (proj_path[strlen(proj_path)-1] != '/')
                            strcat(proj_path, "/");

                        if (subdir)
                            strcat(proj_path, subdir);

                        just_ls(proj_path, "%s  %s\n", NULL);

                        free_list(cat_list, cat_count);
                        free_list(proj_list, count);
                        exit(0);
                    }
                }
            }

            if (proj) {
                char * project = get_from_patt(proj, proj_list, count);
                if (project) {

                    char proj_path[] = "";
                    strcat(proj_path, get_cat_path(category));
                    strcat(proj_path, project);
                    if (proj_path[strlen(proj_path)-1] != '/')
                        strcat(proj_path, "/");

                    if (subdir)
                        strcat(proj_path, subdir);

                    just_ls(proj_path, "%s  %s\n", NULL);

                } else die("Project not found!");
                free_list(cat_list, cat_count);
                free_list(proj_list, count);
                exit(0);

            } else if (category)
                just_ls(get_cat_path(category), "%s  %s\n", types);

        } else if (!cat && !proj) {
            putchar('\n');
            for (int i = 0; i < cat_count; i ++) {
                if (strcmp(cat_list[i], ".")&&strcmp(cat_list[i], ".."))
                {
                    cat = cat_list[i];
                    if (!has_proj(cat))
                        continue;
                    const char * icon = get_icon_by_name("dir").icon;

                    printf("%s  %s \n",
                            icon, cat);
                    just_ls(get_cat_path(cat), "  %s  %s\n", types);

                    putchar('\n');
                    if (i < cat_count - 2)
                        putchar('\n');
                }
            }
        } else if (cat) {
            char * category = get_from_patt(cat, cat_list, cat_count);
            just_ls(get_cat_path(category), "%s  %s\n", types);
        }

    } else if (!strcmp(cmd, "-s")) {
        if (f)
            cat = f;
        if (s)
            proj = s;
        else proj = f;

        if (cat) {
            char * category = get_from_patt(cat, cat_list, cat_count);
            char ** proj_list = NULL;
            int count = 0;
            subdir = strchr(proj, '/');
            if (subdir)
                *subdir++ = 0;

            if (category) {
                proj_list = get_list_proj(category);
                count = get_list_proj_count(category);
                if (cat == proj)
                    proj = NULL;
            } else {
                cat = NULL;
                for (int c = 0; c < cat_count; c++) {
                    cat = cat_list[c];

                    if (!strcmp("..", cat)||!strcmp(".", cat))
                        continue;

                    category = get_from_patt(cat, cat_list, cat_count);
                    proj_list = get_list_proj(category);
                    count = get_list_proj_count(category);

                    char * project = get_from_patt(proj, proj_list, count);
                    if (project) {

                        char proj_path[] = "";
                        strcat(proj_path, get_cat_path(category));
                        strcat(proj_path, project);
                        if (proj_path[strlen(proj_path)-1] != '/')
                            strcat(proj_path, "/");

                        if (subdir)
                            strcat(proj_path, subdir);

                        puts(proj_path);

                        free_list(cat_list, cat_count);
                        free_list(proj_list, count);
                        exit(0);
                    }
                }
            }

            if (proj) {
                char * project = get_from_patt(proj, proj_list, count);
                if (project) {

                    char proj_path[] = "";
                    strcat(proj_path, get_cat_path(category));
                    strcat(proj_path, project);
                    if (proj_path[strlen(proj_path)-1] != '/')
                        strcat(proj_path, "/");

                    if (subdir)
                        strcat(proj_path, subdir);

                    puts(proj_path);

                } else die("Project not found!");
                free_list(cat_list, cat_count);
                free_list(proj_list, count);
                exit(0);

            } else if (category)
                puts(get_cat_path(category));

        } else if (!cat && !proj) {
            putchar('\n');
            for (int i = 0; i < cat_count; i ++) {
                if (strcmp(cat_list[i], ".")&&strcmp(cat_list[i], ".."))
                {
                    cat = cat_list[i];
                    puts(get_cat_path(cat));
                }
            }
        } else if (cat) {
            char * category = get_from_patt(cat, cat_list, cat_count);
            just_ls(get_cat_path(category), "%s  %s\n", types);
        }
    }


    free_list(cat_list, cat_count);
    return 0;
}

char * get_from_patt(char * patt, char **list, int count) {
    regex_t pattern;
    for (int i = 0; i < count; i ++) {
        if (list[i] == NULL) continue;
        char * l_patt = to_lower(patt);
        char * name = to_lower(list[i]);

        if (!regcomp(&pattern, l_patt, 0)) {
            if (!regexec(&pattern, name, 0, NULL, 0)) {
                return list[i];
            }
        }
    }

    return NULL;
}

char * get_cat_path(char * category) {
    char * cat_path = malloc(strlen(root_path)+strlen(category));
    strcpy(cat_path, root_path);

    strcat(cat_path, category);
    if (cat_path[strlen(cat_path)-1] != '/')
        strcat(cat_path, "/");

    return cat_path;
}


char * get_proj_path(char * cat, char * proj) {
    char * cat_path = get_cat_path(cat);

    if (proj) {
        subdir = strchr(proj, '/');
        if (subdir)
            *subdir++ = 0;
        char ** proj_list = get_list_proj(cat);
        int count = get_list_proj_count(cat);

        char * project = get_from_patt(proj, proj_list, count);

        if (project) {

            char * proj_path = cat_path;
            strcat(proj_path, project);
            if (proj_path[strlen(proj_path)-1] != '/')
                strcat(proj_path, "/");

            if (subdir)
                strcat(proj_path, subdir);

            return proj_path;
        }
        free_list(proj_list, count);
    }

    return NULL;
}


int has_proj(char * category) {
    char * cat_path = get_cat_path(category);

    int count = count_items(cat_path, types);
    return count>2 ? count : 0;
}

int get_list_proj_count(char * category) {
    const int types [] = {4, -1};
    char cat_path [strlen(root_path)+strlen(category)];
    strcpy(cat_path, root_path);

    strcat(cat_path, category);
    if (cat_path[strlen(cat_path)-1] != '/')
        strcat(cat_path, "/");

    return count_items(cat_path, types);
}

char ** get_list_proj(char * category) {
    const int types [] = {4, -1};
    char cat_path [strlen(root_path)+strlen(category)];
    strcpy(cat_path, root_path);

    strcat(cat_path, category);
    if (cat_path[strlen(cat_path)-1] != '/')
        strcat(cat_path, "/");

    int count = count_items(cat_path, types);
    return ls(cat_path, count, types);
}

