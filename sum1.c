/* Sum series up */
/* 14 July By Mary Bennett */

#include <stdio.h>
#include <math.h>

double nTerm (unsigned long long int n);

int main ()
{
  unsigned long long int n = 0;
  double sum = 0.0;
  double prSum = 0.1;

  while (sum != prSum)
    {
      prSum = sum;
      sum += nTerm (n);
      n++;
      if (n % 100000000000 == 0)
	  printf("%.6f\n", sum);
      if (n == 1000000000000)
	{
	  printf("ERROR: too long.\n");
	  return 1;
	}
    }
  printf("Answer for %ld: %.6f\n", i, sum);
  return 0;
}

double nTerm (unsigned long long int n)
{
  double denom = 100 * n + M_PI;

  return 1/denom;
}

//https://git.embecosm.com/engineering-training/graduate-training-program
