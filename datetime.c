#include "datetime.h"

// start with december
int DATETIME_MAX_DAY[] = {
  31, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30
};

void initDateTime(DateTime* dateTime) {
  dateTime->year = 0;
  dateTime->month = 0;
  dateTime->day = 0;
  dateTime->hour = 0;
  dateTime->minute = 0;
  dateTime->second = 0;
}

void addDate(DateTime* dateTime, int year, int month, int day) {
  dateTime->year += year;
  dateTime->month += month;
  dateTime->day += day;
  forceRollDateTime(dateTime);
}

void addTime(DateTime* dateTime, int hour, int minute, int second) {
  dateTime->hour += hour;
  dateTime->minute += minute;
  dateTime->second += second;
  forceRollDateTime(dateTime);
}

void setDateTime(DateTime* dateTime, int year, int month, int day, int hour, int minute, int second) {
  initDateTime(dateTime);
  addTime(dateTime, hour, minute, second);
  addDate(dateTime, year, month, day);
}

void rollDateTime(DateTime* dateTime) {
  if (roll(&(dateTime->second), &(dateTime->minute), DATETIME_MAX_SECOND, DATETIME_MIN_SECOND)) {
    if (roll(&(dateTime->minute), &(dateTime->hour), DATETIME_MAX_MINUTE, DATETIME_MIN_MINUTE)) {
      if (roll(&(dateTime->hour), &(dateTime->day), DATETIME_MAX_HOUR, DATETIME_MIN_HOUR)) {
        if (rollDays(&(dateTime->day), &(dateTime->month), &(dateTime->year))) {
          roll(&(dateTime->month), &(dateTime->year), DATETIME_MAX_MONTH, DATETIME_MIN_MONTH);
        }
      }
    }
  }
}

void forceRollDateTime(DateTime* dateTime) {
  roll(&(dateTime->second), &(dateTime->minute), DATETIME_MAX_SECOND, DATETIME_MIN_SECOND);
  roll(&(dateTime->minute), &(dateTime->hour), DATETIME_MAX_MINUTE, DATETIME_MIN_MINUTE);
  roll(&(dateTime->hour), &(dateTime->day), DATETIME_MAX_HOUR, DATETIME_MIN_HOUR);
  roll(&(dateTime->month), &(dateTime->year), DATETIME_MAX_MONTH, DATETIME_MIN_MONTH);
  rollDays(&(dateTime->day), &(dateTime->month), &(dateTime->year));
  roll(&(dateTime->month), &(dateTime->year), DATETIME_MAX_MONTH, DATETIME_MIN_MONTH);
}

unsigned char roll(unsigned int *from, unsigned int *to, int rollLimit, int rollReset) {
  if ((*from) > rollLimit) {
    (*to) += (*from) / (rollLimit + 1);
    (*from) = (*from) % (rollLimit + 1) + rollReset;
    return 1;
  }
  return 0;
}

unsigned char rollDays(unsigned int *day, unsigned int *month, unsigned int *year) {
  unsigned char returnBool = 0;
  char leapYearFix = ((*month == 2) && (*year % 4 == 0))? 1 : 0;
  while((*day) > (DATETIME_MAX_DAY[*month % 12] + leapYearFix)) {
    returnBool = 1;
    (*day) -= (DATETIME_MAX_DAY[*month % 12] + leapYearFix);
    (*month)++;
  }
  return returnBool;
}

void tickSecond(DateTime* dateTime) {
  addTime(dateTime, 0, 0, 1);
  rollDateTime(dateTime);
}