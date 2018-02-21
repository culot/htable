#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "htable.h"

#define HSIZE	10000

struct pbook_s {
  char *name;
  char *phone;
  HTABLE_ENTRY (pbook_s);
};

void
extract_key (struct pbook_s *data, char **key, int *len)
{
  *key = data->name;
  *len = strlen (data->name);
}

int
compare (struct pbook_s *data1, struct pbook_s *data2)
{
  const int KEYLEN = strlen (data1->name);
  
  if (strlen (data2->name) == KEYLEN
      && !memcmp (data1->name, data2->name, KEYLEN))
    return 0;
  else
    return 1;
}

int
main (int argc, char **argv)
{
  HTABLE_HEAD (pbook, HSIZE, pbook_s) *my_book;

  printf ("*************************************\n");
  printf ("* Hash table dynamic initialization *\n");
  printf ("*************************************\n");

  HTABLE_GENERATE (pbook, pbook_s, extract_key, compare);

  my_book = malloc (sizeof (struct pbook));
  HTABLE_INIT (my_book);
  
  printf ("Hash Table init done:\n");
  printf ("         size : %d (awaited: %d)\n", (int)HTABLE_SIZE (my_book),
          HSIZE);
  printf ("        items : %u (should be 0)\n", HTABLE_COUNT (my_book));
  printf ("   collisions : %3.1f %% (should be 0.0 %%)\n",
          HTABLE_COLLS (my_book));
  printf ("         load : %3.1f %% (should be 0.0 %%)\n",
          HTABLE_LOAD (my_book));

  free (my_book);
  
  return EXIT_SUCCESS;
}
