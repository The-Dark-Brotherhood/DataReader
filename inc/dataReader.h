#pragma once
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>

#define KEY_PATH     "/home/gabsantana/Downloads"
#define ID_ERROR      -1

#define SHM_KEYID     16535

#define TIMEOUT       15

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
