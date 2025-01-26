#define __CALPAGE__VERSION__ "1.1"
#define __CALPAGE__AUTHOR__ "Danila \"akshin_\" Axyonov"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <iso646.h>

#include "headers/calendar.h"

const char* get_lang
()
{
    const char* file_name = "lang.txt";
    FILE* lang_file = fopen(file_name, "r");
    if (lang_file == NULL) {
        printf_s("Error 2: unable to read from %s.\n", file_name);
        puts("Please, contact the author with this problem.");
        exit(2);
    }
    
    char buf[3];
    fgets(buf, 3, lang_file);
    fclose(lang_file);
    
    if (strcmp(buf, "ru") == 0)
        return "ru";
    if (strcmp(buf, "en") == 0)
        return "en";

    printf_s("Error 2: %s file was damaged.\n", file_name);
    puts("Please, change the style of calendar page by hand or contact the author with this problem.");
    exit(2);
}

void set_lang
(const char* lang)
{
    const char* file_name = "lang.txt";
    FILE* lang_file = fopen(file_name, "w");
    if (lang_file == NULL) {
        printf_s("Error 2: unable to write to %s.\n", file_name);
        puts("Please, contact the author with this problem.");
        exit(2);
    }
    fputs(lang, lang_file);
    fclose(lang_file);
    return;
}

bool all_digits
(const char* S)
{
    for (; *S; ++S)
        if (*S < '0' or '9' < *S)
            return false;
    return true;
}

void calendar_processing
(int month, int year, const char* lang)
{
    struct calendar_t* cal = build_calendar(month, year);
    print_calendar(cal, lang);
    destroy_calendar(cal);
    return;
}

int main
(int argc, const char* argv[])
{   
    // Unacceptable number of arguments
    if (argc == 1
     or argc  > 3)
    {
        const char* error_msg = (argc == 1 ? "no arguments were entered" : "too many arguments");
        printf_s("Error 52: %s.\n", error_msg);
        puts("Please, see the documentation for help.");
        return 52;
    }

    if (argc == 2)
    {   
        if (strcmp(argv[1], "-v")        == 0
         or strcmp(argv[1], "--version") == 0)
        {
            puts("CALPAGE");
            printf_s("Current program's version: %s\n", __CALPAGE__VERSION__);
            printf_s("Project's author: %s\n", __CALPAGE__AUTHOR__);
        }
        else if (strcmp(argv[1], "-h")     == 0
              or strcmp(argv[1], "--help") == 0)
        {
            const char* file_name = "help.txt";
            FILE* help_file = fopen("help.txt", "r");
            if (help_file == NULL) {
                printf_s("Error 1: unable to read from %s.\n", file_name);
                puts("Please, contact the author with this problem.");
                return 1;
            }
            for (char c = getc(help_file); c != EOF; c = getc(help_file))
                putchar(c);
            fclose(help_file);
        }
        else if (strcmp(argv[1], "ru") == 0
              or strcmp(argv[1], "en") == 0)
        {
            set_lang(argv[1]);
            printf_s("Style of calendar page was successfully set to '%s'.\n", argv[1]);
        }
        else if (strcmp(argv[1], "today") == 0)
        {
            time_t t = time(NULL);
            struct tm* cur_date = localtime(&t);
            calendar_processing(cur_date->tm_mon + 1, 1900 + cur_date->tm_year, get_lang());
        } else {
            puts("Error 52: unacceptable input format.");
            puts("Please, see the documentation for help.");
            return 52;
        }
    }
    else // argc == 3
    {
        if (strlen(argv[1]) > 4
         or strlen(argv[2]) > 4
         or not all_digits(argv[1])
         or not all_digits(argv[2]))
        {
            puts("Error 52: unacceptable input format.");
            puts("Please, see the documentation for help.");
            return 52;
        }

        int month = atoi(argv[1]),
            year  = atoi(argv[2]);
        if (month > year) {
            int tmp = month;
            month = year;
            year = tmp;
        }

        if (not (1 <= month and month <= 12 and 1900 <= year and year <= 9999)) {
            puts("Error 52: unacceptable date.");
            puts("Please, see the documentation for help.");
            return 52;
        }

        calendar_processing(month, year, get_lang());
    }

    return 0;
}
