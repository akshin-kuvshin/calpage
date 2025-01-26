#ifndef __CALPAGE__CALENDAR__
#define __CALPAGE__CALENDAR__

#include <stdbool.h>

enum __DAYS
{
    MONDAY = 2,
    TUESDAY = 3,
    WEDNESDAY = 4,
    THURSDAY = 5,
    FRIDAY = 6,
    SATURDAY = 0,
    SUNDAY = 1,
    NONE = -1
};

struct calendar_t
{
    enum __DAYS* month; // size = month_len + 1; month[0] always equals NONE, month[1..month_len] - main data.
    int month_len;
    bool was_built;
};

// Returns (true), if (year) is a leap year, and (false) otherwise.
bool leap_year(int year);

// Returns day of week of given date (day, month, year).
// https://en.wikipedia.org/wiki/Zeller%27s_congruence
enum __DAYS zeller(int day, int month, int year);

// Allocates memory for (calendar_t) structure and builds it, basing on (month) and (year).
// ! Requires (destroy_calendar) function call after to avoid memory leak !
struct calendar_t* build_calendar(int month, int year);

// Free all memory, allocated in (build_calendar) function.
void destroy_calendar(struct calendar_t* cal);

// Prints calendar page (cal) as a table in (lang)-style. 
void print_calendar(struct calendar_t* cal, const char* lang);

#endif
