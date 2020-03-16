#pragma once
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>

// Constants
#define KEY_PATH     "/home/gabsantana/Downloads"
#define ID_ERROR      -1

#define SHM_KEYID     16535

// in seconds
#define TIMEOUT       5       
#define EXIT_DELAY    35       // Check if this is right for closing the server
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
typedef struct
{
  pid_t dcProcessID;
  long lastTimeHeardFrom;   // TODO: Not sure if this the best data type for that
} DCInfo;

typedef struct
{
  int msgQueueID;
  int numberOfDCs;
  DCInfo dc[MAX_DC_ROLES];
} MasterList;
