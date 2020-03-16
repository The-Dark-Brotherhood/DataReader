#include "../inc/dataReader.h"
void processMessage(MasterList* list, msgData msg);   //DEBUG:


int main(int argc, char const *argv[])
{
  // MESSAGE QUEUE;
  // Grabs key and check for existing queue, creates if necessary
  key_t msgKey = ftok(KEY_PATH, 'G');
  int msgID = 0;

  if(msgKey == ID_ERROR)
  {
    printf("ERROR: Unable to generate a key for message queue\n");
    return ID_ERROR;
  }

  // Grab or Create message key
  msgID = msgget(msgKey, 0);
  if(msgID == -1)
  {
    msgID = msgget(msgKey, (IPC_CREAT | 0660));
    if(msgID == -1)
    {
      printf("ERROR: Unable to create queue\n%s\n", strerror(errno));
      return errno;
    }
  }

  printf("DEBUG MESSAGE ID: %d\n", msgID );

  // MASTER LIST;
  // Grabs key and check for existing shared memory, creates if necessary
  key_t shmKey = ftok(KEY_PATH, SHM_KEYID);
  int shmID = 0;
  if(shmKey == ID_ERROR)
  {
    printf("ERROR: Unable to gsenerate a key for shared memory\n");
    return ID_ERROR;
  }

  // Grab or Create shared memory
  MasterList* shList = NULL;
  shmID = shmget(shmKey, sizeof(MasterList), 0);
  printf("DEBUG SHM ID: %d\n", shmID);
  if(shmID == -1)
  {
    shmID = shmget(shmKey, sizeof(MasterList), (IPC_CREAT | 0660));
    if(shmID == -1)
    {
      printf("ERROR: Unable to create shared memory\n%s\n", strerror(errno));
      return errno;
    }
  }
  //--> Create master list: keeps tracks of the clients connect to the queue
  shList = (MasterList*)shmat (shmID, NULL, 0);
  shList->msgQueueID = msgID;

  // Sleep for timeout seconds
  printf("Waiting for %d...\n", TIMEOUT);
  sleep(TIMEOUT - 10);
  printf("NOW\n" );

  // Listening loop
  msgData msg;
  int msgSize = sizeof(msgData) - sizeof(long);

  time_t start_t = time(NULL);
  while((int)difftime(time(NULL), start_t) < 10)
  {
  //  if(msgrcv(msgID, &msg, msgSize, 10, IPC_NOWAIT) == -1)
    {
      printf("How\n" );
      //processMessage(shList, msg);
      sleep(1);   // DEBUG: Change to 1.5 segundos
    }
  }

  // Clean up and exit
  // DEBUG: Add the shared memory here later
  msgctl (msgID, IPC_RMID, (struct msqid_ds*)NULL);
  shmdt(shList);
  shmctl (shmID, IPC_RMID, 0);

  return 0;
}


void processMessage(MasterList* list, msgData msg)
{
  list->numberOfDCs++;
  int lastDCindex = list->numberOfDCs - 1;
  list->dc[lastDCindex].dcProcessID = msg.clientId;
  printf("Received Process ID: %d\n", (int)list->dc[lastDCindex].dcProcessID);
}
