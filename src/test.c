#include "../inc/dataReader.h"

// FUNCTION      : ¦fˆÌ0Ù”bHÊXèÉ1Ã$Æ!ãc†IŒ&+2L`ÈxÈÊXÌÉ1‰rLWfIŒFIŒ«(Æ“2–:2Œ`É1ˆÉXèÉ1ŠâdjÆòo
// DESCRIPTION   : Kill the DC process indicated by the index
//
// PARAMETERS    :
//	MasterList* list : Pointer to the shared memory master list
//  int index        : Index of the client in the master list
//
// RETURNS       :
//	Returns 0 if the process was killed, -1 if the client does not exist in the list
//  1 if the process was not killed (already was closed)
int killTheThing(MasterList* list, int index)
{
  int errorCode = -1;
  DCInfo* clientToKill = getElementAt(list, index);
  if(clientToKill == NULL)  // Client does not exists
  {
    return errorCode;
  }

  errorCode = kill(clientToKill->dcProcessID, SIGHUP);
  if(errorCode == 0)
  {
    printf("success\n");
  }
  else
  {
    printf("already closed\n");
  }

  return errorCode;
}

// testAddToList
void testListExistingElement();
void testListNewElementBegin();
void testListNewElementEnd();
void testListNewElementMiddle();
void testAddFullList();
void testListDeleteElement();
void testListDeleteFirstElement();
void testListDeleteLastElement();
void testListInactivityRemoval();
void testListAddingHead();
void testListGetNotExistingElement();
void testListGetElementAtIndex();
void testListEmptyListIndex();
void testKillThing();

int main(void)
{
  /*
  testListNewElementBegin();
  testListNewElementEnd();
  testListNewElementMiddle();
  testListExistingElement();
  testListAddingHead();
  testAddFullList();

  testListDeleteElement();
  testListDeleteFirstElement();
  testListDeleteLastElement();
  testListInactivityRemoval();
  */

  testListGetElementAtIndex();
  testListGetNotExistingElement();
  testListEmptyListIndex();
  testKillThing();

  return 0;
}

void testListNewElementBegin()
{
  // Create list
  printf("======\nTEST : Add a new element at the beginning of the list\n");
  printf("Returns a pointer to the node if it was added or already existed,\n");
  printf("NULL if the server is full\n======\n");

  // Create and insert dummy data
  MasterList* list = malloc(20 * sizeof(DCInfo));
  list->head = NULL;
  for(int i = 2; i <= 5; i++)
  {
    DCInfo* currentNode = createAndSetNode(i);
    insertNodeToList(list, currentNode);
  }

  // Insert new node
  DCInfo* node = createAndSetNode(1);
  DCInfo* returnedNode= insertNodeToList(list, node);
  printLists(list->head);

  printf("==> Expected: NOT NULL -- Result: ");
  if(returnedNode != NULL)
  {
    printf("NOT NULL");
  }
  else
  {
    printf("NULL");
  }
  printf("\n\n");
  free(list);
}

void testListExistingElement()
{
  // Create list
  printf("======\nTEST : Add an element that already exists\n");
  printf("Returns a pointer to the node if it was added or already existed,\n");
  printf("NULL if the server is full\n======\n");

  // Create and insert dummy data
  MasterList* list = malloc(20 * sizeof(DCInfo));
  list->head = NULL;
  for(int i = 1; i <= 5; i++)
  {
    DCInfo* currentNode = createAndSetNode(i);
    insertNodeToList(list, currentNode);
  }

  // Insert new node
  DCInfo* node = createAndSetNode(5);
  DCInfo* returnedNode = insertNodeToList(list, node);
  printLists(list->head);

  printf("==> Expected: EXISTING NOT NULL -- Result: ");
  if(returnedNode != NULL)
  {
    printf("NOT NULL");
  }
  else
  {
    printf("NULL");
  }
  printf("\n\n");
  free(list);
}

void testAddFullList()
{
  // Create list
  printf("======\nTEST : Add an element to a full list\n");
  printf("Returns a pointer to the node if it was added or already existed,\n");
  printf("NULL if the server is full\n======\n");

  // Create and insert dummy data
  MasterList* list = malloc(20 * sizeof(DCInfo));
  list->head = NULL;
  for(int i = 1; i <= MAX_DC_ROLES; i++)
  {
    DCInfo* currentNode = createAndSetNode(i);
    insertNodeToList(list, currentNode);
  }

  // Insert new node
  DCInfo* node = createAndSetNode(20);
  DCInfo* returnedNode = insertNodeToList(list, node);
  printLists(list->head);

  printf("==> Expected: NULL -- Result: ");
  if(returnedNode != NULL)
  {
    printf("NOT NULL");
  }
  else
  {
    printf("NULL");
  }
  printf("\n\n");
  free(list);
}

void testListNewElementEnd()
{
  // Create list
  printf("======\nTEST : Add a new element in the end of the list\n");
  printf("Returns a pointer to the node if it was added or already existed,\n");
  printf("NULL if the server is full\n======\n");

  // Create and insert dummy data
  MasterList* list = malloc(20 * sizeof(DCInfo));
  list->head = NULL;
  for(int i = 1; i <= 5; i++)
  {
    DCInfo* currentNode = createAndSetNode(i);
    insertNodeToList(list, currentNode);
  }

  // Insert new node
  DCInfo* node = createAndSetNode(6);
  DCInfo* returnedNode = insertNodeToList(list, node);
  printLists(list->head);

  printf("==> Expected: NOT NULL -- Result: ");
  if(returnedNode != NULL)
  {
    printf("NOT NULL");
  }
  else
  {
    printf("NULL");
  }
  printf("\n\n");
  free(list);
}

void testListNewElementMiddle()
{
  // Create list
  printf("======\nTEST : Add a new element in the middle of the list\n");
  printf("Returns a pointer to the node if it was added or already existed,\n");
  printf("NULL if the server is full\n======\n");

  // Create and insert dummy data
  MasterList* list = malloc(20 * sizeof(DCInfo));
  list->head = NULL;
  for(int i = 1; i <= 5; i++)
  {
    DCInfo* currentNode = createAndSetNode(i);
    insertNodeToList(list, currentNode);
  }

  DCInfo* currentNode = createAndSetNode(7);
  insertNodeToList(list, currentNode);

  // Insert new node
  DCInfo* node = createAndSetNode(6);
  DCInfo* returnedNode = insertNodeToList(list, node);
  printLists(list->head);

  printf("==> Expected: NOT NULL -- Result: ");
  if(returnedNode != NULL)
  {
    printf("NOT NULL");
  }
  else
  {
    printf("NULL");
  }
  printf("\n\n");
  free(list);
}

void testListAddingHead()
{
  // Create list
  printf("======\nTEST : Add the existing head node\n");
  printf("Returns a pointer to the node if it was added or already existed,\n");
  printf("NULL if the server is full\n======\n");

  // Create and insert dummy data
  MasterList* list = malloc(20 * sizeof(DCInfo));
  list->head = NULL;
  for(int i = 1; i <= 5; i++)
  {
    DCInfo* currentNode = createAndSetNode(i);
    insertNodeToList(list, currentNode);
  }

  // Insert new node
  DCInfo* node = createAndSetNode(1);
  DCInfo* returnedNode = insertNodeToList(list, node);
  printLists(list->head);

  printf("==> Expected: EXISTING NOT NULL -- Result: ");
  if(returnedNode != NULL)
  {
    printf("NOT NULL");
  }
  else
  {
    printf("NULL");
  }
  printf("\n\n");
  free(list);
}

//============================== DELETE =======================================//
void testListDeleteElement()
{
  // Create list
  printf("======\nTEST : Remove an element in the middle of the list\n");

  // Create and insert dummy data
  MasterList* list = malloc(20 * sizeof(DCInfo));
  list->head = NULL;
  for(int i = 1; i <= 5; i++)
  {
    DCInfo* currentNode = createAndSetNode(i);
    insertNodeToList(list, currentNode);
  }
  printLists(list->head);
  printf("\n= After");

  // Insert new node
  DCInfo* nodeToDelete = findClient(list->head, 3);
  deleteNode(list, nodeToDelete);

  printLists(list->head);
  printf("Expected: 4 -- Result: %d\n\n", list->numberOfDCs );

  //printf("==> Expected:  -- Result: %d\n\n", retCode);
  free(list);
}

void testListDeleteFirstElement()
{
  // Create list
  printf("======\nTEST : Remove the first element of the list\n");

  // Create and insert dummy data
  MasterList* list = malloc(20 * sizeof(DCInfo));
  list->head = NULL;
  for(int i = 1; i <= 5; i++)
  {
    DCInfo* currentNode = createAndSetNode(i);
    insertNodeToList(list, currentNode);
  }
  printLists(list->head);
  printf("\n= After");

  // Insert new node
  DCInfo* nodeToDelete = findClient(list->head, 1);
  deleteNode(list, nodeToDelete);

  printLists(list->head);
  printf("Expected: 4 -- Result: %d\n\n", list->numberOfDCs );

  free(list);
}

void testListDeleteLastElement()
{
  // Create list
  printf("======\nTEST : Remove the last element of the list\n");

  // Create and insert dummy data
  MasterList* list = malloc(20 * sizeof(DCInfo));
  list->head = NULL;
  for(int i = 1; i <= 5; i++)
  {
    DCInfo* currentNode = createAndSetNode(i);
    insertNodeToList(list, currentNode);
  }
  printLists(list->head);
  printf("\n= After");

  // Insert new node
  DCInfo* nodeToDelete = findClient(list->head, 5);
  deleteNode(list, nodeToDelete);

  printLists(list->head);
  printf("Expected: 4 -- Result: %d\n\n", list->numberOfDCs );

  free(list);
}

void testListEmptyListIndex()
{
  // Create list
  printf("======\nTEST : Index an element of an empty list\n");

  // Create and insert dummy data
  MasterList* list = malloc(20 * sizeof(DCInfo));
  DCInfo* returnedNode = getElementAt(list, 3);

  printf("==> Expected: NULL -- Result: ");
  if(returnedNode != NULL)
  {
    printf("NOT NULL");
  }
  else
  {
    printf("NULL");
  }
  printf("\n\n");

  free(list);
}

void testListInactivityRemoval()
{
  // Create list
  printf("======\nTEST : Remove inactive client from the list\n");
  printf("Returns the number of clients removed from the list \n");

  // Create and insert dummy data with delay
  MasterList* list = malloc(20 * sizeof(DCInfo));
  list->head = NULL;
  for(int i = 1; i <= 5; i++)
  {
    DCInfo* currentNode = createAndSetNode(i);
    insertNodeToList(list, currentNode);
    sleep(5);
  }

  checkInactivity(list);
  printLists(list->head);
  printf("Change the EXIT_DELAY to observe changes\n");
  free(list);
}

void testListGetElementAtIndex()
{
  // Create list
  printf("======\nTEST : Get existing element at an index\n");
  printf("Returns a pointer to the node if it exists,\n");
  printf("NULL if it does not\n======\n");

  // Create and insert dummy data
  MasterList* list = malloc(20 * sizeof(DCInfo));
  list->head = NULL;
  for(int i = 1; i <= 5; i++)
  {
    DCInfo* currentNode = createAndSetNode(i);
    insertNodeToList(list, currentNode);
  }

  // Get node
  DCInfo* returnedNode = getElementAt(list, 1);

  printf("==> Expected: NOT NULL -- Result: ");
  if(returnedNode != NULL)
  {
    printf("NOT NULL");
  }
  else
  {
    printf("NULL");
  }
  printf("\n\n");
  free(list);
}

void testListGetNotExistingElement()
{
  // Create list
  printf("======\nTEST : Get a non existing element at an index\n");
  printf("Returns a pointer to the node if it exists,\n");
  printf("NULL if it does not\n======\n");

  // Create and insert dummy data
  MasterList* list = malloc(20 * sizeof(DCInfo));
  list->head = NULL;
  for(int i = 1; i <= 5; i++)
  {
    DCInfo* currentNode = createAndSetNode(i);
    insertNodeToList(list, currentNode);
  }

  // Get node
  DCInfo* returnedNode = getElementAt(list, 6);

  printf("==> Expected: NULL -- Result: ");
  if(returnedNode != NULL)
  {
    printf("NOT NULL");
  }
  else
  {
    printf("NULL");
  }
  printf("\n\n");
  free(list);
}

void testKillThing()
{
  // Create list
  printf("======\nTEST :Can the thing kill");
  printf("\n======\n");

  // Create and insert dummy data
  MasterList* list = malloc(20 * sizeof(DCInfo));
  list->head = NULL;
  for(int i = 1; i <= 5; i++)
  {
    DCInfo* currentNode = createAndSetNode(i);
    insertNodeToList(list, currentNode);
  }

  killTheThing(list, 0);

  free(list);
}
