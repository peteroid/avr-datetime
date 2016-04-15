#ifndef DATETIME_H
#define DATETIME_H

#define DATETIME_MAX_MONTH 12
#define DATETIME_MIN_MONTH 1
#define DATETIME_MIN_DAY 1
#define DATETIME_MAX_HOUR 23
#define DATETIME_MIN_HOUR 0
#define DATETIME_MAX_MINUTE 59
#define DATETIME_MIN_MINUTE 0
#define DATETIME_MAX_SECOND 59
#define DATETIME_MIN_SECOND 0

typedef struct {
  unsigned int second, minute, hour, day, month, year;
} DateTime;

void initDateTime(DateTime* dateTime);
void addDate(DateTime* dateTime, int year, int month, int day);
void addTime(DateTime* dateTime, int hour, int minute, int second);
void setDateTime(DateTime* dateTime, int year, int month, int day, int hour, int minute, int second);
void rollDateTime(DateTime* dateTime);
void forceRollDateTime(DateTime* dateTime);
unsigned char roll(unsigned int *from, unsigned int *to, int rollLimit, int rollReset);
unsigned char rollDays(unsigned int *day, unsigned int *month, unsigned int *year);
void tickSecond(DateTime* dateTime);

#endif