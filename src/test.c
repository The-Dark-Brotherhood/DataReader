#include "../inc/dataReader.h"

// testAddToList
int testAddToList(void);



int main(void)
{
  testAddToList();

  return 0;
}


int testAddToFullList(void)
{
  printf("TEST 1:\n");
  // Insert Data
  MasterList* list = malloc(20 * sizeof(DCInfo));
  list->dc[0].dcProcessID = (pid_t)3;
  list->dc[0].lastTimeHeardFrom = time(NULL);
  list->numberOfDCs = 10;

  pid_t newClient = 10;

  // Run function
  int expected = -1;     // Already exists
  int retCode = addToMasterlist(newClient, list);
  printf("Result from Function:%d\n &--> %d [1(TRUE) & 0(FALSE)]\n", retCode, expected == retCode);

  free(list);
  return 0;
}
