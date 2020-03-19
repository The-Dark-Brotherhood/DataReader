#include "../inc/dataReader.h"

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

int main(void)
{
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
