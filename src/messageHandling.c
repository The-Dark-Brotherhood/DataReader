#include "../inc/dataReader.h"

/*
int addToMasterlist(pid_t newClientPID, MasterList* list)
{
  const int numClients = list->numberOfDCs;

   // Server is full
  if(list->numberOfDCs == MAX_DC_ROLES)
  {
    return -1;
  }

  // Look for existing client
  for(int counter = 0; counter < numClients; counter++)
  {
    if(list->dc[counter].dcProcessID == newClientPID)
    {
      // DEBUG: Reset timer varible
      list->dc[counter].lastTimeHeardFrom = time(NULL);
      return 1;
    }
  }

  // Add to server master list
  list->dc[numClients].dcProcessID = newClientPID;
  list->dc[numClients].lastTimeHeardFrom = time(NULL);
  return 0;
}

// DEBUG: Does it have to be in order (the DCs)
void checkInactivity(MasterList* list)
{
  for(int counter = 0; counter < list->numberOfDCs; counter++)
  {
    // Remove if the last time heard from is bigger or equal to allowed delay
    if((int)difftime(time(NULL), list->dc[counter].lastTimeHeardFrom) >= EXIT_DELAY)
    {
      list->dc[counter] = list->dc[list->numberOfDCs - 1];  // Replace with the last element
      list->numberOfDCs--;                                // Resize array
    }
  }
}

void processMessage(MasterList* list, msgData msg)
{
  list->numberOfDCs++;
  int lastDCindex = list->numberOfDCs - 1;
  list->dc[lastDCindex].dcProcessID = msg.clientId;
  printf("Received Process ID: %d\n", (int)list->dc[lastDCindex].dcProcessID);
}
*/
