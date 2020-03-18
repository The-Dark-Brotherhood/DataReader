#include "../inc/dataReader.h"

// testAddToList
void testAddToList();



int main(void)
{
  //testAddToList();
  testAddToList();
  return 0;
}

void testAddToList()
{
  // Create list
  printf("TEST 1:\nReturns -1 if the server list is full, 1 if the element already exists and its time was updated,\n 0 if the element was added to the list\n");
  MasterList* list = malloc(20 * sizeof(DCInfo));

  // Create and insert dummy data
  list->head = NULL;
  for(int i = 1; i <= 5; i++)
  {
    DCInfo* currentNode = createAndSetNode(i);
    insertNodeToList(list, currentNode);
  }
  // Insert new node
  DCInfo* node = createAndSetNode(1);
  int retCode = insertNodeToList(list, node);

  printLists(list->head);
  printf("==> Result: %d\n", retCode);

  free(list);
}


/*
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

int testCheckForInactivity(void)
{
  printf("TEST 2:\n");

  // Insert Data
  MasterList* list = malloc(20 * sizeof(DCInfo));
  list->dc[0].dcProcessID = (pid_t)10;
  list->dc[0].lastTimeHeardFrom = time(NULL);
  list->dc[1].dcProcessID = (pid_t)11;
  list->dc[1].lastTimeHeardFrom = time(NULL);
  list->dc[2].dcProcessID = (pid_t)12;
  list->dc[2].lastTimeHeardFrom = time(NULL);
  list->numberOfDCs = 3;
  int counter = 0;
  // Print every element in the shared list
  while(counter < 3)
  {
    for(int i = 0; i < list->numberOfDCs; i++)
    {
      printf("== Element #%d\n", list->dc[i].dcProcessID);
      printf("   Last time heard from: %d\n",(int)difftime(time(NULL), list->dc[i].lastTimeHeardFrom));
    }
    sleep(5);
    checkInactivity(list);
    counter++;
  }

  printf("\nResult: %d\n", list->dc[0].dcProcessID );
  printf("\nResult: %d\n", list->dc[1].dcProcessID );
  printf("\nResult: %d\n", list->dc[2].dcProcessID );

  // Cleanup
  free(list);
  return 0;
}
*/
