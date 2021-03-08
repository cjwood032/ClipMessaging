#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "CopyClipboard.h"
//#include <pthread.h>
#include "server.h"
#include "secrets.h"
pthread_mutex_t lock;
short socketCreate(void) {
    short hSocket;
    hSocket=socket(AF_INET, SOCK_STREAM,0);
    return hSocket;
}
int bindCreatedSocket (int hsocket){
    int iRetval=-1;
    int clientPort = SERVERPORT;
    struct sockaddr_in remote = {0};
    remote.sin_family=AF_INET;
    remote.sin_addr.s_addr = htonl(INADDR_ANY);
    remote.sin_port = htons(clientPort);
    iRetval = bind(hsocket,(struct sockaddr *) &remote, sizeof(remote));
    return iRetval;
}

void * serverReceive()
{
     _Bool received = 0;
    int socket_desc=0, sock=0, clientLen=0;
    struct sockaddr_in client;
    char client_message[200]={0};
    char message[100]={0};
    //const char *pMessage="HELLO FROM THE SERVER";
    socket_desc = socketCreate();
    if(socket_desc==-1)
    {
        printf("couldn't create socket\n");
        return NULL;
    }
    if (bindCreatedSocket(socket_desc)<0)
    {
        perror("bind failed.\n");
        return NULL;
    }
    listen(socket_desc,3);
    while(!received)
    {
        printf("waiting for incoming connections \n");
        clientLen = sizeof(struct sockaddr_in);
        sock = accept(socket_desc, (struct sockaddr *) &client,(socklen_t*)&clientLen);
        if (sock < 0)
        {
            perror("accept failed");
            return NULL;
        }
        printf("Connection accepted\n");
        memset(client_message, '\0', sizeof client_message);
        memset(message, '\0', sizeof message);
        if(recv(sock, client_message, 200,0)<0)
        {
            printf("recv failed");
            break;
        }
        else
        {
            printf("Copying...\n");
            copyToClipboard(client_message);
            received=1;
        }
        close(sock);
        sleep(1*WINMULTIPLIER);
        /*
        if(pthread_mutex_trylock(&lock)==0)
        {
            received=1;
        }
        */

    }
    return NULL;
}
/*
void* monitorServer()
{
    char exit[10];
    pthread_mutex_lock(&lock);
    puts("Hit enter to exit server.");
    fgets(exit,10,stdin);
    pthread_mutex_unlock(&lock);
    return NULL;
}
void* receiveProgramme()
{
    pthread_t threadServer, threadMonitor;
    
    if (pthread_mutex_init(&lock,NULL)!=0) //dynamic mutex init
    {
        printf("Mutex init failure.\n");
        return NULL;
    }
    pthread_create(&threadServer, NULL, serverReceive, NULL);
    pthread_create(&threadMonitor, NULL, monitorServer, NULL);
    //pthread_join(threadMonitor, NULL);
    //pthread_join(threadServer,NULL);
    pthread_exit(NULL);
    return NULL;
}
*/