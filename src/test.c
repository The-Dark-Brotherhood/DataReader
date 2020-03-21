#include "../inc/dataReader.h"
#include "../inc/logger.h"


// testAddToList
//void testListExistingElement();
//void testListNewElementBegin();
//void testListNewElementEnd();
//void testListNewElementMiddle();
//void testAddFullList();
//void testListDeleteElement();
//void testListDeleteFirstElement();
//void testListDeleteLastElement();
void testListInactivityRemoval();
//void testListAddingHead();
//void testListGetNotExistingElement();
//void testListGetElementAtIndex();
//void testListEmptyListIndex();
//void testLog();

int main(void)
{
  /*
  testListNewElementBegin();
  testListNewElementEnd();
  testListNewElementMiddle();
  testListExistingElement();
  testListAddingHead();
  testAddFullList();

  testListGetElementAtIndex();
  testListGetNotExistingElement();
  testListEmptyListIndex();

  testListDeleteElement();
  testListDeleteFirstElement();
  testListDeleteLastElement();
  testListInactivityRemoval();
  */

  testListInactivityRemoval();
  return 0;
}

void testListInactivityRemoval()
{
  int number = 0;
  // Create list
  printf("======\nTEST : Remove inactive client from the list\n");
  printf("Returns the number of clients removed from the list \n");

  // Create and insert dummy data with delay
  MasterList* list = malloc(20 * sizeof(DCInfo));

  for(int i = 0; i < 5; i++)
  {
    DCInfo client = { .dcProcessID = i, .lastTimeHeardFrom = time(NULL)};
    list->dc[list->numberOfDCs] = client;
    list->numberOfDCs++;
  }

  list->dc[0].lastTimeHeardFrom = 40;
  list->dc[1].lastTimeHeardFrom = 40;
  list->dc[2].lastTimeHeardFrom = 40;
  list->dc[3].lastTimeHeardFrom = 40;
  list->dc[4].lastTimeHeardFrom = 40;

  checkInactivity(list);
  for(int i = 0; i < list->numberOfDCs; i++)
  {
    printf("|%d|->", list->dc[i].dcProcessID);
  }
  printf("\n");
  printf("Change the EXIT_DELAY to observe changes\n");
  free(list);
}
