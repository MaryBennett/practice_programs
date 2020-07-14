/* 8 Queens */
/* 13 July By Mary Bennett */
/* 8 by 8 board, queens cant touch */

#include <stdio.h>

#define POSSIBLE 0
#define BLOCKED 1

/* Functions for Stack */
/* Push */
/* Pop */

/* Initialise */
void initBoard (int *board[64], int *queens[8]);

/* Print Queens */
void printQueens (int queens[8]);

int main()
{
  int board[64];
  int queens[8];

  initBoard (&board, &queens);

  /* Set first queen to position 0 */
  queens[0] = 0;
  board[0] = BLOCKED;

  /* Print answer */
  printQueens (queens);
}

/* Initialise board */
void initBoard (int *board[64], int *queens[8])
{
  int i;
  for (i = 0; i < 8; i++)
    queens[i] = 0;
  for (i = 0; i < 64; i++)
    board[i] = POSSIBLE;
}

/* Print Queens */
void printQueens (int queens[8])
{
  int i;
  for (i = 0; i < 8; i++)
    printf(" %i", queens[i]);
  printf("\n");
}
