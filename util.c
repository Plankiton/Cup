#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include "util.h"


char strin(const char * s, const char *list[], const int lenght) {
    if (lenght < 0) {
        for (int i = 0; list[i] != NULL; i++) {
            if (!list[i]) continue;
            if (!strcmp(s, list[i]))
                return 1;
        }
    }
    for (int i = 0; i < lenght; i++) {
        if (!list[i]) continue;
        if (!strcmp(s, list[i]))
            return 1;
    }
    return 0;
}

char in(const int v, const int* list, const int lenght) {
    if (lenght < 0) {
        for (int i = 0; list[i] >= 0; i++) {
            if (!list[i]) continue;
            if (v == list[i])
                return 1;
        }
    }

    for (int i = 0; i < lenght; i++) {
        if (!list[i]) continue;
        if (v == list[i])
            return 1;
    }
    return 0;
}

char * to_lower(const char * s) {
    char * d = (char *)malloc(strlen(s));
    memset(d, 0, strlen(s));
    int i = 0;
    for (; s[i]!='\0'; i++) {
        d[i] = s[i];
        if(s[i] >= 'A' && s[i] <= 'Z') {
            d[i] = s[i] + 32;
        }
    }
    d[i] = 0;

    return d;
}

void die(const char * format, ...) {
    va_list l;
    va_start(l, format); {

        char error [] = "ERROR: ";
        char * error_format = strcat(error, format);
        vfprintf(stderr, error_format, l);

    } va_end(l);

    exit(1);
}
