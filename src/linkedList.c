/*
*  FILE          : linkedList.cpp
*  PROJECT       : Assignment #3
*  PROGRAMMER    : Gabriel Gurgel
*  FIRST VERSION : 2019-06-10
*  DESCRIPTION   : Modified version of the Data Structures Assignment #1 linked list code...cool, right?
*                  This file contains the definitions for the functionsto linked list implementations
*/
#include "../inc/dataReader.h"
bool ascendingComp(DCInfo* tracker, DCInfo* node);      // Sorting parameter

// FUNCTION      : createAndSetNode
// DESCRIPTION   : Creates a node in the heap and stores client info in the created node
//
// PARAMETERS
//   int clientId  : Process Id of the client who wants to connect to the server
//
// RETURNS
//	 DCInfo* : Returns the location of the created node, IF there is an error, returns NULL
DCInfo* createAndSetNode(int clientId)
{
	int errorCode = 0;

	// Create node in the Heap
	DCInfo* node = (DCInfo*)malloc(sizeof(DCInfo));
	if (node == NULL)
	{
		printf("-- ERROR: Cannot allocate memory for client list\n");
		errorCode = -1;
	}
	else
	{
		// Set node variables
		node->dcProcessID = clientId;
    node->lastTimeHeardFrom = time(NULL);
	  node->prev = node->next = NULL;
	}

	return node;
}

// FUNCTION      : insertNodeToList
// DESCRIPTION   : Insert a node in a ascending client ID order
//
// PARAMETERS    :
//	MasterList* list : List containing information about all server clients
//  DCInfo*  node   : Pointer to the node that is being inserted
//
// RETURNS       :
//	Returns -1 if the server list is full, 1 if the element already exists and its time
//  was updated, 0 if the element was added to the list
int insertNodeToList(MasterList* list, DCInfo* node)
{
  // Memory location of the beginning and end of the list
  DCInfo** head = &(list->head);
  DCInfo** tail = &(list->tail);

	// First element case --> Server is empty
	if (*head == NULL)
	{
		*head = *tail = node;
    list->numberOfDCs++;
	}
	// New node that goes in the beginning of the list --> Replace head node
	else if (node->dcProcessID < (*head)->dcProcessID)
	{
		node->next = *head;
		node->prev = (*head)->prev;
		(*head)->prev = node;
		*head = node;
    list->numberOfDCs++;
	}
  // Add node to the list in ascending client ID order
	else
	{
		// Tracker pointers
		DCInfo* preNode  =  *head;
		DCInfo* postNode = (*head)->next;

    // Transverse through the list
		while (postNode != NULL && postNode->dcProcessID < node->dcProcessID)
		{
			preNode  = postNode;
			postNode = preNode->next;
		}

		// If node is on the list --> Refresh time
		if(preNode->dcProcessID == node->dcProcessID)
		{
			postNode->lastTimeHeardFrom = time(NULL);
			return 1;
		}

    // Check if the server is full
   if(list->numberOfDCs == MAX_DC_ROLES)
   {
     return -1;
   }

    // Link to the list
		node->next = postNode;
		node->prev = preNode;
		preNode->next = node;
		if (postNode == NULL)
		{
			*tail = node;            // CASE: Last Node
		}
		else
		{
			postNode->prev = node;   // CASE: Middle Node
		}
    list->numberOfDCs++;       // Update number of clients
	}
  return 0;
}

// FUNCTION      : printLists
// DESCRIPTION   : Prints all the nodes from both lists
//
// PARAMETERS    :
//	songInfo* rateHead    : First node from the Rate-Sorted list
//  songInfo* artistHead  : First node from the Artist-Sorted list
//
// RETURNS       :
//	NOTHING
void printLists(DCInfo* head)
{
	DCInfo* tracker = head;

	printf("\n--Sorted List--\n ");
	while (tracker != NULL)
	{
		printf("|%2d|->", tracker->dcProcessID);
		tracker = tracker->next;
	}
  printf("\n");
}

// FUNCTION      : findClient
// DESCRIPTION   : Search for a client node in a list based on the info passed
//
// PARAMETERS    :
//	songInfo* head : Pointer to the list where to search the client
//
// RETURNS       :
//	songInfo* : Returns pointer to the node IF there is a match, returns NULL otherwise
DCInfo* findClient(DCInfo* head, int clientId)
{
	DCInfo* tracker = head;

	while (tracker != NULL)
	{
		if (tracker->dcProcessID == clientId)
		{
			break;
		}
		tracker = tracker->next;
	}

	return tracker;
}

// FUNCTION      : deleteNode
// DESCRIPTION   : Deletes a particular node from a list
//
// PARAMETERS    :
//	songInfo* node  : Pointer to the node that is going to be deleted
//	songInfo** head : Pointer to the memory location of beginning of the linked list
//  songInfo** tail : Pointer to the memory location of the end of the linked list
//
// RETURNS       :
//	NOTHING
void deleteNode(DCInfo* node, DCInfo** head, DCInfo** tail)
{
	if (node == *head)
	{
		*head = node->next;
		if (*head == NULL)
		{
			*head = *tail = NULL;
		}
		else
		{
			(*head)->prev = NULL;
		}
	}
	else
	{
		DCInfo* postNode = node->next;
		DCInfo* preNode = node->prev;

		preNode->next = postNode;
		if (postNode == NULL)
		{
			*tail = preNode;
		}
		else
		{
			postNode->prev = preNode;
		}
	}

	free(node);
}

// FUNCTION      : freeLinkedList
// DESCRIPTION   : Free the linked list from the heap
//
// PARAMETERS    :
//	songInfo* head : Pointer to the first element of the list
//
// RETURNS       :
//	NOTHING
void freeLinkedList(DCInfo* head)
{
	DCInfo* deletePtr = NULL;
	DCInfo* trackerPtr = head;

	while (trackerPtr != NULL)
	{
		deletePtr = trackerPtr;
		trackerPtr = trackerPtr->next;
		free(deletePtr);
	}
}
