/* Fibonacci Non-Recursive V1.0 */
/* 13 July By Mary */
/* Lists first 12 fibonacci numbers */
#include <stdio.h>

#define MAX_VALUE 12

int main (void)
{
  int answer = 0;
  int i, fn1 = 1, fn2 = 0;

  for (i = 0; i <= MAX_VALUE; i++)
    {
      if (i == 0) answer = 0;
      else if (i == 1) answer = 1;
      else
	{
	  answer = fn1 + fn2;
	  fn2 = fn1;
	  fn1 = answer;
	}
      printf("Answer %i: %i\n",i,answer);
       
    }
}
