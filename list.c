#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "list.h"

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
int ls(const char *path, char ** list, int count) {
    DIR *d;
    struct dirent *file;

    d = opendir(path);
    if (!d)
        return 0;

    int i = 0; {
        while ((file = readdir(d)) != NULL && i < count-1)
        {
            puts("JOAO");
            strcpy(list[i], file->d_name);
            i ++;
        }
        closedir(d);
    }

    return 1;
}
int count_items(const char *path) {
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
#endif
