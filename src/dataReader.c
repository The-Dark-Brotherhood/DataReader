#include "../inc/dataReader.h"

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
  if(msgID = msgget(msgKey, 0) == -1)
  {
    msgID = msgget(msgKey, (IPC_CREAT | 660));
    if(msgID == -1)
    {
      printf("ERROR: Unable to create queue\n%s\n", strerror(errno));
      return errno;
    }
  }

  printf("Message: %d\n",msgID );

  // MASTER LIST;
  // Grabs key and check for existing shared memory, creates if necessary
  key_t shmKey = ftok(KEY_PATH, SHM_KEYID);
  int shmID = 0;
  if(shmKey == ID_ERROR)
  {
    printf("ERROR: Unable to generate a key for shared memory\n");
    return ID_ERROR;
  }

  // Grab or Create shared memory
  MasterList* shList = NULL;
  if(shmID = shmget(shmKey, sizeof(MasterList), 0) == -1)
  {
    shmID = shmget(shmKey, sizeof(MasterList), (IPC_CREAT | 0660));
    if(shmID == -1)
    {
      printf("ERROR: Unable to create shared memory\n%s\n", strerror(errno));
      return errno;
    }
  }
  shList = (MasterList *)shmat (shmID, NULL, 0);

  // Sleep for timeout seconds
  printf("Waiting for %d...\n", TIMEOUT);
  sleep(TIMEOUT);

  // Listening loop

  // Clean up and exit
  shmdt(shList);
  shmctl (shmID, IPC_RMID, 0);
  msgctl (msgID, IPC_RMID, (struct msqid_ds*)NULL);

  return 0;
}
