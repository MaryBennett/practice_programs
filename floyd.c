/* Floyd-Warshall Algroithm */
/* 21 July */

#include <stdio.h>

/* define v & dist */
#define VERTEX 4
#define INFINITE 1027 // Max value
signed int DIST[VERTEX][VERTEX];


/* The meaty loop */
void loopDist (void);

/* Print dist */
void printDist (void);

int main ()
{
  /* Initialise to -1? */
  for (int m = 0; m < VERTEX; m++)
    for (int n = 0; n < VERTEX; n++)
      DIST[n][m] = INFINITE;
  
  /* Set the 0s */
  for (int i = 0; i < VERTEX; i++)
    DIST[i][i] = 0;

  /* Fill the easy squares (To be replaced) */
  DIST[1][0] = 4;
  DIST[0][2] = -2;
  DIST[1][2] = 3;
  DIST[2][3] = 2;
  DIST[3][1] = -1;
  printf("Current table:\n*/");
  printDist();

  loopDist();
  printf("\n\nNew table:\n");
  printDist();
}

/* The meaty loop */
void loopDist (void)
{
  /*for k from 1 to V
  for i from 1 to V
    for j from 1 to V
      if dist[i][j] > dist[i][k] + dist[k][j]
      dist[i][j] <- dist[i][k] + dist[k][j]*/
  for (int k = 0; k < VERTEX; k++)
    for (int j = 0; j < VERTEX; j++)
      for (int i = 0; i < VERTEX; i++)
	{
	  if (DIST[i][j] > DIST[i][k] + DIST[k][j])
	    DIST[i][j] = DIST[i][k] + DIST[k][j];
	}
}

/* Print dist */
void printDist (void)
{
  printf("|---------------|\n|");
  for (int i = 0; i < VERTEX; i++)
    {
      for (int j = 0; j < VERTEX; j++)
	{
	  printf(" %i |", DIST[i][j]);
	}
      printf("\n|---------------|\n|");
    }
}
