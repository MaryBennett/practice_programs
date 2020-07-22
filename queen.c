/* 8 Queens */
/* 13 July By Mary Bennett */
/* 8 by 8 board, queens cant touch */

#include <stdio.h>

#define POSSIBLE 0
#define BLOCKED 1

/* Functions for Stack */
/* Push */
/* Pop */

/* Flips board */
/* Return: PASS FAIL */
void flipBoard (int *brd[64], int queens);

/* Finds next possible space */
/* Return: PASS FAIL */
int findNext (int brd[64], int *qunPos);

/* Print Queens */
void printQueens (int queens[8]);

/* Print board */
void printBoard (int board[64]);

int main()
{
  int board[8][64];  // board[queens placed][position]
  int queens[8];     // position of queens

  /* Initalise arrays */
  /* Set first queen to position 0 */
  int i;
  for (i = 0; i < 8; i++)
    queens[i] = 0;
  for (i = 0; i < 64; i++)
    board[0][i] = POSSIBLE;

  /* Block unusable squares */
  flipBoard(&board[0], queens[0]);
  
  // Save move?

  /* Find next queen */
  int *store;
  if (findNext(board[0], store) == 1)
    {
      printf("Error: Failed to find next position.\n");
      return 1;
    }
  else
    queens[1] = *store;
  
  /* Print answer */
  printQueens (queens);
  printBoard(board[0]);
}

/* Flips board */
void flipBoard (int *brd[64], int queen)
{
  int x_pos = queen / 8;
  int y_pos = queen % 8;
  int i;

  brd[queen] = BLOCKED;

  for (i = 0; i < 64; i++)
    {
      if (i / 8 == x_pos)      // Horizontal
	{
	  brd[i] = BLOCKED;
	  printf("\tBlock x for %i\n", i);
	}
      //else if (i % 8 == y_pos) // Vertical
      //{
      //  brd[i] = BLOCKED;
      //  printf("\tBlock y\n");
      //}
    }
}

/* Finds next possible space */
/* Return: PASS FAIL */
int findNext (int brd[64], int *qunPos)
{
  int i;

  for (i = 0; i < 64; i++)
    {
      if (brd[i] == POSSIBLE)
	{
	  *qunPos = i;
	  return 0;
	}
    }
  return 1;  // No more possible spaces
}

/* Print Queens */
void printQueens (int queens[8])
{
  int i;

  printf("Queen locations: ");
  
  for (i = 0; i < 8; i++)
    printf(" %i", queens[i]);
  printf("\n");
}


/* Print board */
void printBoard (int board[64])
{
  int i;
  
  for (i = 0; i < 64; i++)
    {
      if (i % 8 == 0)
	printf("\n---------------------------------\n| %i |", board[i]);
      else
        printf(" %i |", board[i]);
    }
  
  printf("\n---------------------------------\n\n");
}
