/* Sum down */
/* 14 July By Mary */

#include <stdio.h>
#include <math.h>

double nTerm (unsigned long long int n)

int main ()
{
  double maxAns = 0.553835;
  unsigned long long int n = 0;

  while (maxAns != 0.0)
    {
      maxAns -= nTerm (n);
      n++;
      if (n == 100000000000)
	break;
    }
  printf ("maxAns at %ld: %.5f", n, maxAns);
}

double nTerm (unsigned long long int n)
{
  double denom = 100 * n + M_PI;

  return 1/denom;
}
