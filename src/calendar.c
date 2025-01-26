#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <iso646.h>
#include <assert.h>

#include "headers/calendar.h"

const int __MONTH_LENS[] = {-1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const char* __TABLE_HEADERS[] = {"MO TU WE TH FR SA SU",    // ru
                                 "SU MO TU WE TH FR SA"};   // en

bool leap_year
(int year)
{
    assert(1900 <= year and year <= 9999);

    if (year % 400 == 0)
        return true;
    if (year % 100 == 0)
        return false;
    if (year % 4 == 0)
        return true;
    return false;
}

enum __DAYS zeller
(int day, int month, int year)
{
    assert(1900 <= year and year <= 9999);
    assert(1 <= month and month <= 12);
    assert(1 <= day and day <= __MONTH_LENS[month] + (month == 2 and leap_year(year) ? 1 : 0));

    bool jan_or_feb = month < 3;
    int q = day,
        m = jan_or_feb ? month + 12 : month,
        K = jan_or_feb ? (year - 1) % 100 : year % 100,
        J = jan_or_feb ? (year - 1) / 100 : year / 100;
    int result = (q + 13 * (m + 1) / 5 + K + K / 4 + J / 4 + 5 * J) % 7;
    return (enum __DAYS)result;
}

struct calendar_t* build_calendar
(int month, int year)
{
    struct calendar_t* cal = (struct calendar_t*)malloc(sizeof(struct calendar_t));
    if (cal == NULL) {
        puts("Error 3: unable to allocate memory for (calendar_t).");
        puts("Please, contact the author with this problem.");
        exit(3);
    }

    cal->month_len = __MONTH_LENS[month];
    if (month == 2 and leap_year(year))
        ++cal->month_len;
    
    cal->month = (enum __DAYS*)calloc(cal->month_len + 1, sizeof(enum __DAYS));
    cal->month[0] = NONE;
    cal->month[1] = zeller(1, month, year);
    for (int day = 2; day <= cal->month_len; ++day)
        cal->month[day] = (cal->month[day - 1] + 1) % 7;
    
    cal->was_built = true;
    return cal;
}

void destroy_calendar
(struct calendar_t* cal)
{
    free(cal->month);
    free(cal);
    return;
}

void print_calendar
(struct calendar_t* cal, const char* lang)
{
    assert(cal);
    assert(cal->was_built);

    int header_ind;
    int shift;
    enum __DAYS week_end;
    if (strcmp(lang, "ru") == 0) {
        header_ind = 0;
        shift = 5;
        week_end = SUNDAY;
    } else { // strcmp(lang, "en") == 0
        header_ind = 1;
        shift = 6;
        week_end = SATURDAY;
    }

    puts(__TABLE_HEADERS[header_ind]);

    int empty_cells = (cal->month[1] + shift) % 7; // number of empty cells in the beginning of table.
    while (empty_cells--)
        printf_s("   "); // 3 spaces

    for (int day = 1; day <= cal->month_len; ++day) {
        printf_s("%2d ", day);
        if (cal->month[day] == week_end)
            printf_s("\n");
    }
    if (cal->month[cal->month_len] != week_end)
        printf_s("\n");

    return;
}
