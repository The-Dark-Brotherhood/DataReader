#include "../inc/dataReader.h"

/*
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
