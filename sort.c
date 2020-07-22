/* Sort V1.0 */
/* 15 July By Mary */
/* Create a structure with two fields. Sort that structure twice, initially on the first field, then take that output and sort on the second field. Compare the results with Bubble sort and Shell’s sort.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 40
#define FNAME 0
#define SNAME 1

/* Linked list related functions */
int insertRecord (char surname [MAX_LEN], char firstName [MAX_LEN]);
void delList (void);
void displayList (void);

typedef struct names
{
  struct names *next;

  char surname [MAX_LEN];
  char firstName [MAX_LEN];
} NAMES;

NAMES *head = NULL;
NAMES *tail = NULL;

static char *nameList [3][19] =
  { { "Jeremy", "Bennett" },
    { "Simon", "Cook" },
    { "Andrew", "Burgess" },
    { "Ed", "Jones" },
    { "Judith", "Bennett" },
    { "Evelyn", "Ng" },
    { "Mary", "Bennett" },
    { "Ian", "Loveless" },
    { "Paolo", "Savini" },
    { "Sarah", "Cook" },
    { "Lewis", "Revill" },
    { "Pietra", "Ferreira" },
    { "Craig", "Blackmore" },
    { "Maxim", "Blinov" },
    { "Jenny", "Storta" },
    { "Will", "Jones" },
    { "Jessica", "Mills" },
    { "", "" }};

int main ()
{
  int i = 0;
  
  while ((strcmp (nameList[i][FNAME], "") != 0) && (strcmp (nameList[i][SNAME], "") != 0))
    {
      printf("LOOP\n");
      if (insertRecord (nameList[i][SNAME], nameList[i][FNAME]) != 0)
	{
	  printf("ERROR: Failed to added.\n");
	  return 1;
	}
      i++;
    }
  
  displayList ();
  delList ();
  
  return 0;
}

/* Displays the list */
void displayList (void)
{
  NAMES *record = head;
  while (record != NULL)
    {
      printf("NAME: %s %s\n", record->firstName, record->surname);
      record = record->next;
    }
}

/* Takes ptr to last in list */
/* Returns pass/fail */
int insertRecord (char surname [MAX_LEN], char firstName [MAX_LEN])
{
  NAMES *record = (NAMES *) malloc (sizeof (NAMES));
  record->next = NULL;
  strcpy (surname, record->surname);
  strcpy (firstName, record->firstName);
  
  /* If list is blank */
  if (head == NULL)
    {
      head = record;
    }
  else
    {
      tail->next = record;
    }

  tail = record;

  return 0;
}

/* Only the head remains */
void delList (void)
{
  if (head == NULL)
    return;
  
  NAMES *record = head;
  
  while (record->next != tail)
    {
      record->next;
    }
  free (tail);
  tail = record;

  delList();
}
