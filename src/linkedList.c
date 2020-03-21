/*
*  FILE          : linkedList.cpp
*  PROJECT       : Assignment #3
*  PROGRAMMER    : Gabriel Gurgel
*  FIRST VERSION : 2019-06-10
*  DESCRIPTION   : Modified version of the Data Structures Assignment #1 linked list code...cool, right?
*                  This file contains the definitions for the functionsto linked list implementations
*/
#include "../inc/dataReader.h"
#include "../inc/logger.h"

void createLogMessage(DCInfo* node, int logType, int index, int msgStatus)
{
  char logMessage[255] = "";

  switch (logType)
  {
		case NEW_CLIENT:
			sprintf("DC-YY [XXX] added to the master list – NEW DC – Status 0 (Everything is OKAY)");
			break;
    case MESSAGE:
      sprintf(logMessage, "DC-%02d [%d] updated in the master list – MSG RECEIVED – Status %d (AAAAA)\n", index, node->dcProcessID, msgStatus);
      break;
    case NON_RESPONSIVE:
      sprintf(logMessage, "DC-%02d [%d] removed from master list – NON-RESPONSIVE\n", index, node->dcProcessID);
      break;
    case GO_OFFLINE:
      sprintf(logMessage, "DC-%02d [%d] has gone OFFLINE – removing from master-list\n", index, node->dcProcessID);
      break;
    case ALL_OFF:
      sprintf(logMessage, "All DCs have gone offline or terminated – DR TERMINATING\n");
      break;
  }
  writeToLog(logMessage, DR_LOG_PATH);
}

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
// DESCRIPTION   : Insert a node in a ascending client ID order or Updates there
//								 existing client timer
//
// PARAMETERS    :
//	MasterList* list : List containing information about all server clients
//  DCInfo*  node   : Pointer to the node that is being inserted
//
// RETURNS       :
//	Returns a pointer to the node if it was added or already existed,
//  NULL if the server is full
DCInfo* insertNodeToList(MasterList* list, DCInfo* node, int* ptrIndex)
{
  // Memory location of the beginning and end of the list
  DCInfo** head = &(list->head);
  DCInfo** tail = &(list->tail);
	*ptrIndex = 0;

	// First element case --> Server is empty
	if (*head == NULL)
	{
		*head = *tail = node;
    list->numberOfDCs++;
	}
	// Element being added is the first element
	else if((*head)->dcProcessID == node->dcProcessID)
	{
		(*head)->lastTimeHeardFrom = time(NULL);
		return (*head);
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
		(*ptrIndex)++;

    // Transverse through the list
		while (postNode != NULL && postNode->dcProcessID <= node->dcProcessID)
		{
			if(postNode->dcProcessID == node->dcProcessID)	// Reset timer if client already exists
			{
				postNode->lastTimeHeardFrom = time(NULL);
				return postNode;
			}
			preNode  = postNode;
			postNode = preNode->next;
			(*ptrIndex)++;
		}

    // Check if the server is full
   if(list->numberOfDCs == MAX_DC_ROLES)
   {
     return NULL;
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
	createLogMessage(node, NEW_CLIENT, *ptrIndex, 0);
  return node;
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

// FUNCTION      : checkInactivity
// DESCRIPTION   : Deletes an innactivity client from the server list
//
// PARAMETERS    :
//	MasterList* list : Pointer to the shared memory master list
//
// RETURNS       :
//	void
void checkInactivity(MasterList* list)
{
	DCInfo* tracker = list->head;
	int index = 0;

	while (tracker != NULL)
	{
		if((int)difftime(time(NULL), tracker->lastTimeHeardFrom) >= EXIT_DELAY)		//DEBUG: Change delay
		{
			deleteNode(list, tracker);
			createLogMessage(tracker, NON_RESPONSIVE, index, 0);
		}
		tracker = tracker->next;
		index++;
	}
}

// FUNCTION      : getElementAt
// DESCRIPTION   : Gets the element at index
//
// PARAMETERS    :
//	MasterList* list : Pointer to the shared memory master list
//	int index : index of the element we are getting
//
// RETURNS       :
//	Pointer to client node
DCInfo* getElementAt(MasterList* list, int index)
{
	if(list->numberOfDCs == 0)
	{
		return NULL;
	}

	DCInfo* tracker = list->head;
	for(int counter = 0; counter < index && tracker != NULL; counter++)
	{
		tracker = tracker->next;
	}
	return tracker;
}

// FUNCTION      : deleteNode
// DESCRIPTION   : Deletes a particular node from a list
//
// PARAMETERS    :
//	DCInfo* node     : Pointer to the node that is going to be deleted
//	MasterList* list : Pointer to the shared memory master list
//
// RETURNS       :
//	NOTHING
void deleteNode(MasterList* list, DCInfo* node)
{
	DCInfo** head = &(list->head);
	DCInfo** tail = &(list->tail);

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
	list->numberOfDCs--;
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
