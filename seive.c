/* Sieve of E V1.0 */
/* 13 July By Mary */
/* Finds prime numbers */

#include <stdio.h>

#define MAX_VALUE 10000
#define PRIME 0
#define COMPOSITE 1

int main ()
{
  int noList [MAX_VALUE];  /* Table of numbers */
  int i;

  /* Initialize */
  for (i = 0; i < MAX_VALUE ; i++)
    {
      noList[i] = PRIME;
    }

  /* Find primes */
  for (i = 2; i < MAX_VALUE ; i++)
    {
      if (noList[i] == PRIME) /* skip if known not prime*/
	{
	  int j;
	  
	  for (j = i + 1; j < MAX_VALUE ; j++)
	    {
	      if (j % i == 0) /* If there is a remainder, not prime */
		{
		  noList[j] = COMPOSITE;
		}
	    }
	}
      else
	noList[i] = COMPOSITE;
    }

  /* Print primes */
  for (i = 0; i < MAX_VALUE ; i++)
    {
      if (noList[i] == PRIME)
	printf("Answer: %i\n", i);
    }
}
