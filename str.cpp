#include <stdio.h>
#include <cstring>
#include <stdlib.h>
#include <cmath>
#include <ctype.h>
#include <string> 
#include <cassert>

#include "str.h"

int main()
{
    const char *a = "18 5qwerty";
    char b1[CONSTANT] = "uiop";
    char b2[CONSTANT] = "uiop";
    char string1[CONSTANT] = {0};
    char string2[CONSTANT] = {0};
    char string3[CONSTANT] = {0};
    char string4[CONSTANT] = {0};
    char string5[CONSTANT] = {0};

    MyOwnPuts(a);
    putchar('\n');

    //printf("%d\n", strchr(a, 'y') - a);
    printf("MyOwnStrchr   %d\n", MyOwnStrchr(a, 'y') - a);

    //printf("%d\n", strlen(a));
    printf("MyOwnStrlen   %d\n", MyOwnStrlen(a));

    //printf("%s\n", strcpy(string3, a));
    printf("MyOwnStrcpy   %s\n", MyOwnStrcpy(string4, a));

    //printf("%s\n", strncpy(string3, a, 5));
    printf("MyOwnStrncpy  %s\n", MyOwnStrncpy(string5, a, 5));

    //printf("%s\n", strcat(b, a));
    printf("MyOwnStrcat   %s\n", MyOwnStrcat(b1, a));

    //printf("%s\n", strncat(b, a, 2));
    printf("MyOwnStrncat  %s\n", MyOwnStrncat(b2, a, 2));

    printf("%d\n", atoi(a));
    printf("MyOwnAtoi     %d\n", MyOwnAtoi(a));

    FILE *filee = fopen("ggg.txt", "r");
    fgets(string1, sizeof(string1), filee);
    fclose(filee);
    filee = fopen("ggg.txt", "r");
    MyOwnFgets(string2, sizeof(string2), filee);
    fclose(filee);
    printf(",%s,\n", string1);
    printf("MyOwnFgets    ,%s,\n", string2);

    //printf("%s\n", strdup(a));
    printf("MyOwnStrdup   %s\n", MyOwnStrdup(a));

    size_t buff_size = 1;
    char *lineptr = (char *)calloc(buff_size, sizeof(char));
    //printf("/%s/\n", lineptr);
    filee = fopen("ggg.txt", "r");
    printf("MyOwnGetline  %d\n", MyOwnGetline(&lineptr, &buff_size, filee));
    printf("%s\n", lineptr);
    free(lineptr);
    fclose(filee);
    printf("%d\n", buff_size);
    /*char *lineptr = (char *)calloc(buff_size, sizeof(char));
    filee = fopen("ggg.txt", "r");
    printf("%d\n", getline(&lineptr, &buff_size, filee));//все норм
    free(lineptr);
    fclose(filee);*/

    return 0;
}

int MyOwnPuts(const char *input_str)
{
    if (input_str == nullptr)
        return EOF;
    for (int i = 0; i < strlen(input_str); i++)
    {
        int check_output = putc(input_str[i], stdout);
        if (check_output == EOF)
            return EOF;
    }
    putc('\n', stdout);
    return 0;
}

char* MyOwnStrchr(const char *input_str, int symbol)
{
    while (*(input_str))
    {
        if ((int)*(input_str) == symbol)
            return (char*)input_str;
        input_str++;
    }
    return nullptr;
}

size_t MyOwnStrlen(const char *input_str)
{
    int i = 0;

    while (input_str[i])
        i++;

    return i;
}

char* MyOwnStrcpy(char *copy_of_str, const char *str)
{
    assert(str != nullptr);
    int len = strlen(str);
    for (int i = 0; i < len; i++)
        copy_of_str[i] = str[i];
    copy_of_str[len] = '\0';
    return copy_of_str;
}

char* MyOwnStrncpy(char *copy_of_str, const char *str, size_t amount)
{
    for (int i = 0; i < amount; i++)
        copy_of_str[i] = str[i];
    return copy_of_str;
}

char* MyOwnStrcat(char *first_str, const char *second_str)
{
    int counter1 = 0, counter2 = 0;

    while (first_str[counter1])
        counter1++;

    while (second_str[counter2])
    {
        first_str[counter1] = second_str[counter2];
        counter1++;
        counter2++;
    }
    first_str[counter1] = '\0';
    return first_str;
}

char* MyOwnStrncat(char *first_str, const char *second_str, size_t num)
{
    int counter1 = 0, counter2 = 0;

    while (first_str[counter1])
        counter1++;

    while (second_str[counter2] && counter2 < num)
    {
        first_str[counter1] = second_str[counter2];
        counter1++;
        counter2++;
    }
    first_str[counter1] = '\0';
    return first_str;
}

int MyOwnAtoi(const char *str)
{
    int i = 0, j = 0;
    int numm = 0;
    char mass[CONSTANT] = {0};
    while (isspace(str[i]) || isdigit(str[i]))
    {
        if (isdigit(str[i]))
        {
            mass[j] = str[i];
            j++;
        }
        if (j > 0 && isspace(str[i]))
            break;
        i++;
    }
    for (int k = 0; k < j; k++)
    {
        numm = numm * 10 + (int)mass[k] - (int)'0';
    }
    return numm;
}

char* MyOwnFgets(char *string, int amount, FILE *filestr)
{
    char ch = 0;
    int i = 0;
    while ((ch = getc(filestr)) != EOF && amount-- > 0)
    {
        if (ch == '\n')
        {
            string[i] = '\n';
            break;
        }
        string[i++] = ch;
    }
    string[i + 1] = '\0';
    return string;
}

char* MyOwnStrdup(const char* str)
{
    char *copystr = 0;
    int len = strlen(str);
    copystr = (char *)calloc(len + 1, sizeof(char));
    if (copystr == nullptr)
        return nullptr;
    for (int i = 0; i < len; i++)
    {
        copystr[i] = str[i];
    }
    copystr[len] = '\0';// pullrequest github
    return copystr;
}

ssize_t MyOwnGetline(char **lineptr, size_t *buff_size, FILE *filestr)
{
    char ch = 0, i = 0;
    char *buff = *lineptr;
    if (filestr == nullptr)
        return -1;
    while ((ch = getc(filestr)) != '\n')
    {
        if ((int)*buff_size < i + 1)
        {
            char *new_buff = (char*) realloc(buff, sizeof(char));
            if (new_buff = nullptr)
            {
                //free(buff);
                return i;
            }
        }
        *(buff + i) = ch;
        i++;
    }
    *buff_size = strlen(buff);
    char *new_new_buff = (char*)realloc(buff, sizeof(char));
    *(buff + i) = '\n';
    *(buff + i + 1) = '\0';
    *lineptr = buff;
    //free(buff);
    if (i == 0)
        return -1;
    else
        return i;
}