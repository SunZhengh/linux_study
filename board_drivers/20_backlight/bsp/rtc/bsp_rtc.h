#ifndef __BSP_RTC_H
#define __BSP_RTC_H

#include "imx6ul.h"

#define SECONDS_OF_DAY      (86400)
#define SECONDS_OF_HOUR     (3600)
#define SECONDS_OF_MIN      (60)
#define DAYS_OF_YEAR        (365)
#define YEAR_RANGE_START    (1970)
#define YEAR_RANGE_END      (2099)

typedef struct {
    unsigned short year;
    unsigned char month;
    unsigned char day;
    unsigned char hour;
    unsigned char minute;
    unsigned char second;
}RTC_TIME_TYPE;

extern RTC_TIME_TYPE rtcDate;

void rtc_init(void);
void rtc_getdatetime(RTC_TIME_TYPE *datetime);
void rtc_setdatetime(RTC_TIME_TYPE *datetime);

#endif // !__BSP_RTC_H