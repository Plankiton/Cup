#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "list.h"
#include "icon.h"
#include "util.h"

#ifdef _WIN32
/*
void ls(const char *dir, const Types *types, char ***listdir)
{
    WIN32_FIND_DATA file;
    HANDLE finder = NULL;

    char path[2048];

    //Specify a file mask. *.* = We want everything!

    if((finder = FindFirstFile(path, &file)) == INVALID_HANDLE_VALUE)
    {
        listdir = NULL;
        return;
    }

    listdir = (char ***)malloc(sizeof (file.cFileName));
    do
    {
        //Find first file will always return "."
        //    and ".." as the first two directories.
        if(!strcmp(file.cFileName, ".")
                && !strcmp(file.cFileName, ".."))
        {
            //Build up our file path using the passed in
            //  [dir] and the file/foldername we just found:
            sprintf(path, "%s\\%s", dir, file.cFileName);

            //Is the entity a File or Folder?
            if(file.dwFileAttributes &FILE_ATTRIBUTE_DIRECTORY)
            {
                printf("Directory: %s\n", path);
                ListDirectoryContents(path); //Recursion, I love it!
            }
            else{
                printf("File: %s\n", path);
            }
        }
    }
    while(FindNextFile(finder, &file)); //Find the next file.

    FindClose(finder); //Always, Always, clean things up!

    return true;
}
*/
#else
#include <dirent.h>
#include <inttypes.h>
char ** ls(const char *path, int count, const int * types) {
    DIR *d;
    struct dirent *file;

    d = opendir(path);
    if (!d)
        return 0;

    char ** list = (char**)malloc(count*256);
    int i = 0; {
        while ((file = readdir(d)) != NULL && i <= count)
        {
            if (!types || in(
                    file->d_type,
                    (int *)types,
                    -1
                )) {
                list[i] = malloc(sizeof file->d_name);
                strcpy(list[i], file->d_name);
                /*
                printf("  %p %s <- %s %i %s\n",
                        list[i], list[i], file->d_name, file->d_type,
                        in(file->d_type, types, -1)?"DIR":"FILE");
                        */
                i ++;
            }
        }
        closedir(d);
    }

    return list;
}
int count_items(const char *path, const int * types) {
    DIR *d;
    struct dirent *file;

    d = opendir(path);
    if (!d)
        return -1;

    int i = 0; {
        while ((file = readdir(d)) != NULL)
        {
            i ++;
        }
        closedir(d);
    }

    return i;
}

void just_ls(const char *path, const char * format, const int * types) {
    DIR *d;
    struct dirent *file;

    d = opendir(path);
    if (!d)
        return;

    while ((file = readdir(d)) != NULL)
    {
        if (!strcmp(file->d_name,".")||
                !strcmp(file->d_name,".."))
            continue;
        if (!types || in(
                    file->d_type,
                    (int *)types,
                    -1
                    )) {

            const char * icon = get_icon(file).icon;

            printf(format, icon, file->d_name);
        }
    }
    closedir(d);
}


void free_list(char **list, int lenght) {
    int i = 0;
    while (i < lenght){
        free(list[i++]);
    }
    free(list);
}
#endif
