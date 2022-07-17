#include "com.h"

int whatday(int day_of_the_year, int *month, int *day) {
    int month_count = 0;
    const int day_of_month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (day_of_the_year < 1 | day_of_the_year > 365) {
        return WHATDAY_NG;
    }
    while (day_of_the_year - day_of_month[month_count] > 0) {
        day_of_the_year = day_of_the_year - day_of_month[month_count];
        month_count += 1;
    }
    *month = month_count;
    *day = day_of_the_year;
    return WHATDAY_OK;
}

int main() {
    char language[100];

    printf("Language?\n");
    scanf("%s", &language[0]);
    if ((strcmp(language, "Japanese") == 0) | (strcmp(language, "ja") == 0)) {
        whatday_ja();
    } else if (((strcmp(language, "English") == 0) | (strcmp(language, "en") == 0))) {
        whatday_en();
    } else {
        printf("Sorry, we don't support this language now.\n");
    }
    return 0;
}
