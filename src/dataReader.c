#include "../inc/dataReader.h"

int main(int argc, char const *argv[])
{
  // Grab key for identifying the message queue
  key_t key = ftok(KEY_PATH, 'G');
  int msgID = 0;

  if(key == MSG_ID_ERROR)
  {
    printf("ERROR: Unable to generate a key for message queue\n");
    return MSG_ID_ERROR;
  }

  // Grab or Create message key
  if(msgID = msgget(key, 0) == -1)
  {
    msgID = msgget(key, (IPC_CREAT | 660));
    if(msgID == -1)
    {
      printf("ERROR: Unable to create queue\n%s\n", strerror(errno));
    }
  }

  // Create master list (shared memory)

  // Wait 15 seconds 

  return 0;
}
