#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define MESSAGE_LENGTH  100
#define MACHINE_ON      1
#define EVERYTHING_OKAY 0
#define KEY             1337
#define LOG_FOLDER_PATH "/tmp/"
#define DR_LOG_PATH     "/tmp/dataReader.log"
#define FALSE           0
#define TRUE            1
#define KEY_PATH        "/tmp/"
#define TYPES           10
#define LOG_LEN         256


#define NEW_CLIENT        0
#define NON_RESPONSIVE    1
#define GO_OFFLINE        2
#define ALL_OFF           3



// Function Prototypes
void getTime(char* output);
void createFilePathIfNotExists();
void writeToLog(char* logMessage, char* path);
