#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "htable.h"

#define HSIZE	10

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
  int i;
  struct pbook_s my_book[] = {
    {"friend1", "555-1111"},
    {"friend2", "555-2222"},
    {"person3", "555-3333"},
    {"person4", "555-4444"},    
    {"police", "113"},
    {"unknown", "555-0000"}
  };
  const int NOENTRIES = sizeof (my_book) / sizeof (struct pbook_s);
  HTABLE_HEAD (pbook, HSIZE, pbook_s) my_table = HTABLE_INITIALIZER (&my_table);

  printf ("**************************\n");
  printf ("* Hash Table insert test *\n");
  printf ("**************************\n");

  HTABLE_GENERATE (pbook, pbook_s, extract_key, compare);

  for (i = 0; i < NOENTRIES; i++)
    HTABLE_INSERT (pbook, &my_table, &my_book[i]);

  printf ("Size of resulting hash table (should be %d): %d\n",
          HSIZE, (int)HTABLE_SIZE (&my_table));
  printf ("Number of entries in the hash table (should be %d): %d\n",
          NOENTRIES, HTABLE_COUNT (&my_table));

  return EXIT_SUCCESS;
}
