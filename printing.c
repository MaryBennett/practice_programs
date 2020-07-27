#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LINE_LEN 60

/* Work out how many collumns
   Return collumn length (FAIL: 0) */
unsigned int readFile (char fname[256]);

int main(int argc, char const *argv[])
{
  if (argc != 2)
  {
    printf("Please specify the CSV file as an input.\n");
    return -1;
  }
  char fname[256];
  strcpy(fname, argv[1]);

  int collumn = readFile(fname);
  if (collumn < 1)
    printf("ERROR: Wrong number of collumns.\n");
  printf("collumn: %i\n", collumn);

  return 0;
}

/* Work out how many collumns
   Return collumn length (FAIL: 0) */
unsigned int readFile (char fname[256])
{
  FILE *file;
  file = fopen(fname, "r");
  if (file == NULL)
    {
      printf("ERROR: File not opening.\n");
      return -1;
    }

  int i = 0;

  char line[LINE_LEN];
  const char DELIM[3] = " ,";
  
  while (fgets (line, LINE_LEN, file) != NULL)
    {
      if (i != 0)
	{	  
	  puts(line);
	  
	  // strtok (line, DELIM);
	  // strtok (NULL, DELIM);
	}

      i++; //Gives amount of collumns
    }
  
  fclose(file);
  return i;
}
