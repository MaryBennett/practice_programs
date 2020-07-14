/* Fibonacci Recursive V1.0 */
/* 13 July By Mary */
/* Lists first 12 fibonacci numbers */
#include <stdio.h>

#define MAX_VALUE 12

int fib (int i);

int main (void)
{
  printf("%i\n", fib(MAX_VALUE));
}

int fib (int i)
{
  if (i == 0)
    {
      return 0;
    }
  /* Base: if i = 1 */
  /* return 1 */
  else if (i == 1)
    return 1;
  else
    {
      /* Add fib (i-1) and fib (i-2)*/
      return (fib (i - 1) + fib (i - 2));
    }
}
