#include "util.h"
#include "list.h"
#include "cli.h"
char ** get_list_proj(char * category);
int get_list_proj_count(char * category);

void list_proj(char * category);
int has_proj(char * category);

char * get_from_patt(char * patt, char **list, int count);
char * get_cat_path(char * category);
char * get_proj_path(char * category, char * project);
