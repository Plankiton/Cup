char ** ls(const char *path, int count, const int * types);
int count_items(const char *path, const int * types);
void free_list(char **list, int lenght);

void just_ls(const char *path, const char * format, const int * types);
