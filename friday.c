/* Friday 13 vs non friday days */
/* 14 July By Mary */

#include <stdio.h>

int main ()
{
  int day = 0;
  int monthDays [12] = {31,29,31,30,31,30,31,30,31,30,31,30};

  while (day <= 365)
    {
      day += 7; // Every Friday
    }
}
