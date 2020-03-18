#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>

// Constants
#define KEY_PATH     "/home/gabsantana/Downloads"
#define ID_ERROR      -1

#define SHM_KEYID     16535

// in seconds // DEBUG: Change values to reflect requirements
#define TIMEOUT       5
#define EXIT_DELAY    15      // Check if this is right for closing the server
#define MSG_DELAY     1.5

// Structures
//--> Message QUEUE
#define MSG_LEN 121
typedef struct
{
  long msgType;
  pid_t clientId;
  char msgContent[MSG_LEN];
} msgData;

//--> Shared Memory
#define MAX_DC_ROLES  10
typedef struct DCInfo
{
  pid_t dcProcessID;
  time_t lastTimeHeardFrom;   // TODO: Not sure if this the best data type for that

  struct DCInfo* next;
  struct DCInfo* prev;
} DCInfo;

typedef struct
{
  int msgQueueID;
  int numberOfDCs;
  DCInfo* head;
  DCInfo* tail;
} MasterList;

// Function Prototypes
/*
void processMessage(MasterList* list, msgData msg);
int addToMasterlist(pid_t newClientPID, MasterList* list);
void checkInactivity(MasterList* list);
*/

// Linked List
DCInfo* createAndSetNode(int clientId);
void printLists(DCInfo* head);
DCInfo* findClient(DCInfo* head, int clientId);
int insertNodeToList(MasterList* list, DCInfo* node);
void deleteNode(DCInfo* node, DCInfo** head, DCInfo** tail);
void freeLinkedList(DCInfo* head);
