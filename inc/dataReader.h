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
#define KEY_PATH     "/tmp/"
#define ID_ERROR      -1

#define SHM_KEYID     16535

// in seconds
#define TIMEOUT       15
#define EXIT_DELAY    35      // DEBUG: Check if this is right for closing the server
#define MSG_DELAY     1.5

// Structures
//--> Message QUEUE
typedef struct
{
  long msgType;
  pid_t clientId;
  int msgStatus;
} msgData;

//--> Shared Memory
#define MAX_DC_ROLES  10
typedef struct DCInfo
{
  pid_t dcProcessID;
  time_t lastTimeHeardFrom;

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
DCInfo* createAndSetNode(int clientId);
void printLists(DCInfo* head);
DCInfo* findClient(DCInfo* head, int clientId);
DCInfo* insertNodeToList(MasterList* list, DCInfo* node);
void deleteNode(MasterList* list, DCInfo* node);
void freeLinkedList(DCInfo* head);
void checkInactivity(MasterList* list);
