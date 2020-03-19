#include "../inc/dataReader.h"


int main(int argc, char const *argv[])
{
  // MESSAGE QUEUE;
  // Generate key
  key_t msgKey = ftok(KEY_PATH, 'G');
  int msgID = 0;

  if(msgKey == ID_ERROR)
  {
    printf("ERROR: Unable to generate a key for message queue\n");
    return ID_ERROR;
  }

  // Creates or Grab message queue
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
  // Generattes key
  key_t shmKey = ftok(KEY_PATH, SHM_KEYID);
  int shmID = 0;
  if(shmKey == ID_ERROR)
  {
    printf("ERROR: Unable to gsenerate a key for shared memory\n");
    return ID_ERROR;
  }

  // Creates or Grabs shared memory
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

  /*
  //DEBUG: Clean up
  msgctl (msgID, IPC_RMID, (struct msqid_ds*)NULL);
  shmdt(shList);
  shmctl (shmID, IPC_RMID, 0);
  */

  //--> Listening loop
  shList = (MasterList*)shmat (shmID, NULL, 0);       // Grabs the shared memory and
  shList->msgQueueID = msgID;                         // Assign the message queue ID

  printf("Waiting for %d seconds\n", TIMEOUT);        // Wait for clients to start
  sleep(TIMEOUT);

  msgData msg;
  int msgSize = sizeof(msgData) - sizeof(long);

  time_t startTime = time(NULL);                      // Listen for messages loop
  while((int)difftime(time(NULL), startTime) < 20)    // DEBUG: Change to timeout
  {
    // Process messages if received and it is able to add to the master list
    if(msgrcv(msgID, &msg, msgSize, 10, IPC_NOWAIT) != -1 &&
       insertNodeToList(shList, createAndSetNode(msg.clientId)))    // DEBUG: Change message type (10)
    {
      //printLists(shList->head);
      checkInactivity(shList);
      printf("==> Wait for %.2f sec\n", MSG_DELAY);
      sleep(MSG_DELAY);
      startTime = time(NULL);
    }
  }

  // Clean up and exit
  // DEBUG: Clean up the shared memory heap allocation
  msgctl (msgID, IPC_RMID, (struct msqid_ds*)NULL);
  shmdt(shList);
  shmctl (shmID, IPC_RMID, 0);

  return 0;
}
