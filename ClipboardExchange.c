#include "client.h"
#include "server.h"
#include "CopyClipboard.h"
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
void* sendProgramme();
void* sendAndReceiveProgramme();
int main()
{
    char option[5];
    puts("Would you like to do:\n   1. Only send\n   2. Only receive\n   3. Both\n   0. exit");
    fgets(option, 5, stdin);
    switch (atoi(option))
    {
    case 1:
        sendProgramme();
        break;
    case 2:
        serverReceive();
        //receiveProgramme();
        break;
    case 3:
        sendAndReceiveProgramme();
        break;
    default:
        return 0;
        break;
    }
    return 0;
}
void* sendProgramme()
{
    char option[5];
    do
    {   //1 is tower, 2 is mac, 3 is new laptop
        puts("Choose a device to send to (make sure the content is in the clipboard)\n   1. TheDarkSide\n   2. MacBook\n   3. TheLightSide\n   4. TheLinuxSide\n   0. Exit");
        fgets(option, 5, stdin);
        if(atoi(option))
        {
            sendToClient(atoi(option));
        }
        else
        {
            break;
        }
    }
    while (atoi(option));
    
}
void*  sendAndReceiveProgramme()
{
    //Set up 2 threads one for send and one for receive. 
    pthread_t threadServer, threadClient;
    pthread_create(&threadServer, NULL, receiveProgramme, NULL);
    pthread_create(&threadClient, NULL, sendProgramme, NULL);
    pthread_join(threadClient, NULL);
    pthread_join(threadServer,NULL);
    pthread_exit(NULL);
}