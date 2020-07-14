/* Ackermanns function V1.0 */
/* 13 July By Mary */

#include <stdio.h>

#define MAX_M 3
#define MAX_N 3 

int answer (int m, int n);

int main ()
{
  printf("Answer: %i\n", answer(MAX_M, MAX_N));
}


int answer (int m, int n)
{
  int result;
  printf("A(%i, %i) = ", m, n);
  /* Base cases */
  if (m == 0)
    result = n + 1;
  else if (n == 0)
    result = answer(m - 1, 1);
  else
    result = answer(m - 1, answer(m, n - 1) );
  printf("%i\n", result);

  return result;
}
