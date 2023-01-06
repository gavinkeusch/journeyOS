#include "str.h"

void strcpy(char* dest, char* src)
{
    int i = 0;

    while (*src != '\0') {
        dest[i] = *src;

        src++;
        i++;
    }
}

int strcmp(char* str1, char* str2)
{
    while (*str1 != '\0') {
        if (*str1 != *str2)
            return 0;

        str1++;
        str2++;
    }

    if (*str2 != '\0')
        return 0;

    return 1;
}