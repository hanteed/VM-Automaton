/*
 ▄ .▄ ▄▄▄·  ▐ ▄ ▄▄▄▄▄▄▄▄ .
██▪▐█▐█ ▀█ •█▌▐█•██  ▀▄.▀·
██▀▐█▄█▀▀█ ▐█▐▐▌ ▐█.▪▐▀▀▪▄
██▌▐▀▐█ ▪▐▌██▐█▌ ▐█▌·▐█▄▄▌
▀▀▀ · ▀  ▀ ▀▀ █▪ ▀▀▀  ▀▀▀ 
2023.
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "../include.h"

bool DEBUG=false;

int my_strlen(const char *str)
{
    int i = 0;
    while (*str++) i++;
    return (i);
}

char * my_strcpy(char * dest, const char * src)
{
    char * tmp;
    tmp = dest;
    while(*src != '\0')
    {
        *dest=*src;
        dest++;
        src++;
    }
    *dest = '\0';
    if(DEBUG)
    {
        printf("Copy String : %s\n",tmp);
    }
    return tmp;
}


char * my_mstrcpy(char * dest, const char * src)
{
    char * tmp;
    tmp = dest;
    while(*src != '\0')
    {
        *dest=*src;
        dest++;
        src++;
    }
    *dest = '\0';
    printf("Copy String : %s\n",tmp);
    return tmp;
}


char * my_mstrncpy(const char * src, int count)
{
    char * tmp;
    char * dest = malloc(my_strlen(src) * sizeof(char));
    tmp = dest;
    int c = 0;
    while(c < count)
    {
        src++;
        c++;
    }
    while(*src != '\0')
    {
        *dest=*src;
        dest++;
        src++;
    }
    *dest = '\0';
    printf("Copy String : %s\n",tmp);
    return tmp;
}


char * my_strcat(const char * a, const char * b)
{
    char * tmp;
    char * dest = malloc(my_strlen(a) * sizeof(char));
    tmp = dest;
    while(*a != '\0')
    {
        *dest=*a;
        dest++;
        a++;
    }
    while(*b != '\0')
    {
        *dest=*b;
        dest++;
        b++;
    }
    *dest = '\0';
    return tmp;
}

int my_strcmp(const char * str1, const char * str2)
{
    while(*str1 != '\0' && *str2 != '\0')
    {
        if(*str1 != *str2)
        {
            return *str1 - *str2;
        }
        str1++;
        str2++;
    }
    return 0;
}
