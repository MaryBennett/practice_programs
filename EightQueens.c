#include <stdio.h
#include <string.h>
#include <stdlib.h>

#define QUEENS 8
#define WIDTH 8
#define LENGTH 8
#define SIZE WIDTH * LENGTH

bool board[QUEENS][SIZE];
int position[QUEENS];
int stack = 0;
void InitVar (void);
bool NextAvailable (void);
void PushStack (void);
void PopStack (void);

int
main (const int argc, const char **argv)
{
  InitVar ();

  while (true)
    {
      if (NextAvailable () == false)
	{
	  PopStack ();
	}
      else
	{
	  PushStack ();
	}
    }
}

void
InitVar (void)
{
  stack = 0;
  position[stack] = 0;
  memset (board[stack], true, SIZE);
}

bool
NextAvailable (void)
{
  while (position[stack] < WIDTH)
    {
      if (board[stack][stack * WIDTH + position[stack]] == true)
	{
	  const int startPosn = stack * WIDTH + position[stack];

	  for (int i = 1; i < LENGTH - stack; i++)
	    {
	      board[stack][(stack + i) * WIDTH + position[stack]] = false;
	      if (position[stack] >= i)
		{
		  board[stack][(stack + i) * WIDTH + position[stack] - i] = false;
		}
	      if (position[stack + i] < WIDTH)
		{
		  board[stack][(stack + i) * WIDTH + position[stack] + i] = false;
		}
	    }
	  printf ("Queen #%d at Position #%d\n", stack + 1, position[stack] + 1);

	  return true;
	}

      position[stack]++;
    }
  return false;
  }

void
PushStack (void)
{
  if (++stack == QUEENS)
    {
      fprintf (stderr, "Find the solution\n"); exit (-1);
    }

  memcpy (board[stack], board[stack - 1], SIZE);
  position[stack] = 0;
  printf ("Pushed stack for Row #%d\n", stack);
}

void
PopStack (void)
{
  if (stack == 0)
    {
      fprintf (stderr, "Could not find a solution\n");
      exit (-2);
    }

  stack--;
  position[stack]++;
  printf("Popped stack for Row #%d\n", stack + 1);
}
