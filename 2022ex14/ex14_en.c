#include "com.h"

static char month_name[12][20] = {"January", "February", "March", "April", "May", "June", "July", "August", "September",
                                  "October", "November", "December"};

void whatday_en() {
    int day_of_year, month, day;
    printf("Please entry the day of the year.\n");
    scanf("%d", &day_of_year);
    if (whatday(day_of_year, &month, &day) == WHATDAY_OK) {
        printf("The %dth day of a year is %s %dth.\n", day_of_year, month_name[month], day);
    } else {
        printf("Day is not in the range of a year.\n");
    }
}