#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>

// Constants
#define KEY_PATH     "/tmp/"
#define ID_ERROR      -1
#define SHM_KEYID     16535
#define EXIT_CODE     6

#define NEW_CLIENT        0
#define NON_RESPONSIVE    1
#define MESSAGE           2
#define GO_OFFLINE        3

// in seconds
#define TIMEOUT       5       // DEBUG: CHANGE LATER
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
  int lastTimeHeardFrom;
} DCInfo;

typedef struct
{
  int msgQueueID;
  int numberOfDCs;
  DCInfo dc[MAX_DC_ROLES];
} MasterList;


// Function Prototypes
void checkInactivity(MasterList* list);
void deleteNode(MasterList* list, int index);
int insertNodeToList(MasterList* list, DCInfo client);
int findClient(MasterList* list, pid_t id);

void createLogMessage(DCInfo node, int logType, int index, int msgStatus);
void debugLog(const char* logMessage);
