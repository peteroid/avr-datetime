# avr-datetime
A lightweight DateTime library specializing for AVR development as well as C.

## Getting started
```c
#include "datetime.h"
```

## Example
```c
#include <stdio.h>
#include <unistd.h>
#include "datetime.h"

int main() {
  DateTime d;
  setDateTime(&d, 2016, 1, 1, 0, 0, 0);
  while(1) {
    printf("%d/%d/%d\n%d:%d:%d\n",
    d.year, d.month, d.day, d.hour, d.minute, d.second);
    sleep(1);
    tickSecond(&d);
  }

  return 0;
}
```

## API
- `DateTime d;`: declare a new DateTime variable
- `unsigned int d.year`: get the year
- `unsigned int d.month`: get the month
- `unsigned int d.day`: get the day
- `unsigned int d.hour`: get the hour
- `unsigned int d.minute`: get the minute
- `unsigned int d.day`: get the day
- `void setDateTime(DateTime* d, int year, int month, int day, int hour, int minute, int second)`: set the time to the desired parameters
- `void tickSecond(DateTime* d)`: tick 1 second and updat the variable
