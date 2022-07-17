#include "com.h"

static char month_name[12][10] = {"睦月", "如月", "弥生", "卯月", "皐月", "水無月", "文月", "葉月", "長月",
                                  "神無月", "霜月", "師走"};

void whatday_ja() {
    int day_of_year, month, day;
    printf("年頭から何日目ですか？\n");
    scanf("%d", &day_of_year);
    if (whatday(day_of_year, &month, &day) == WHATDAY_OK) {
        printf("年頭から%d日目は%s%d日です。\n", day_of_year, month_name[month], day);
    } else {
        printf("与えられた日数が正しい範囲にありません。\n");
    }
}