/* Inkblot Algroithm V0.1

   Copyright (C) 2020 Embecosm Limited <www.embecosm.com>
   Contributor: Mary Bennett <mary.bennett@embecosm.com>
   SPDX-License-Identifier: GPL-3.0-or-later */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 6000    /* Maximum number of digits (=>max answer = MAX_LEN+MAX_LEN) */

/* Usage info */
void usage (void);

/* Initialise answer */
void intiAns (void);

/* Calculates each answer and offset */
/* Returns PASS/ FAIL */
int calcAns (char *str1, char *str2);

/* Print answer */
void printAns (int len);

int stack = 0;
int answer [MAX_LEN + MAX_LEN];

int main(int argc, char const *argv[])
{
 /* Load in stings of numbers */
  if (argc == 1)
    {
      usage();
      return 0;
    }
  else if (argc != 3)
    {
      printf ("Please specify two numbers.\n");
      return -1;
    }

  char *firstStr = strdup (argv[1]);
  if (firstStr == NULL)
  {
    fprintf (stderr, "ERROR: firstStr is NULL");
    return -1;
  }

  char *secStr = strdup (argv[2]);
  if (secStr == NULL)
  {
    fprintf(stderr, "ERROR: secStr is NULL");
    return -1;
  }

  intiAns ();

  if (calcAns (firstStr, secStr) != 0)
    return -1;

  free (firstStr);
  free (secStr);

  return 0;
}

/* Usage info */
void usage (void)
{
  printf("Usage:\n");
  printf("Inkblot Algortim Version 0.1\n\n");
  printf("Copyright (C) 2020 Embecosm Limited <www.embecosm.com>\n");
  printf("Contributor: Mary Bennett <mary.bennett@embecosm.com>\n");
  printf("SPDX-License-Identifier: GPL-3.0-or-later\n\n");
  return;
}

/* Initialise answer */
void intiAns (void)
{
  for (int i = 0; i < (MAX_LEN + MAX_LEN) ; i++)
    answer [i] = 0;
}

/* Calculates each answer and offset */
/* Returns PASS/ FAIL */
int calcAns (char *str1, char *str2)
{
  int i, j;
  int len1 = strlen(str1);
  int len2 = strlen(str2);

  for (i = 0; i < len1; i++)  //= len1 - 1; i >= 0; i--)
    for (j = 0; j < len2; j++) //= len2 - 1; j >= 0; j--)
    {
      /* Check if digit */
      if ((!isdigit(str1 [i])) && (!isdigit(str2 [j])))
      {
        fprintf(stderr, "ERORR: strings have non-digits\n");
        return -1;
      }
      int firInt = str1 [i] - '0';
      int secInt = str2 [j] - '0';
      int ans = firInt * secInt;
      int offset = ((len1 - 1) - i) * len2 + j;

      answer [offset] += ans % 10;  /* Units */
      if (answer [offset] > 9)
      {
        answer [offset + 1] += answer [offset] / 10;
        answer [offset]      = answer [offset] % 10;
      }

      answer [offset + 1] += ans / 10;  /* Carry */

      if (answer [offset + 1] > 9)
      {
        answer [offset + 2] += answer [offset + 1] / 10;
        answer [offset + 1]  = answer [offset + 1] % 10;
      }
    }

  printAns(len1 + len2);

  return 0;
}

/* Print answer */
void printAns (int len)
{
  printf("The answer is:\t");
  for (int i = len - 1; i >= 0; i--)
    printf ("%d", answer [i]);
  printf("\n(12186984)\n");
}
