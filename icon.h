#include <dirent.h>

typedef struct {
    const char * key;
    const char * icon;
} Icon;

typedef enum {
    Directory = 4
} FileType;
const Icon get_icon(struct dirent *file);
const Icon get_icon_by_name(char * name);
