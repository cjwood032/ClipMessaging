#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "secrets.h"
#include "client.h"
#include "CopyClipboard.h"
short clientSocketCreate(void) 
{
    short hSocket;
    printf("Create the socket\n");
    hSocket = socket(AF_INET,SOCK_STREAM,0);
    return hSocket;
}
int clientSocketConnect(int hSocket,int target)
{
    //1 is tower, 2 is mac, 3 is new laptop default to self for testing
    int iRetval=-1;
    int ServerPort = SERVERPORT;
    struct sockaddr_in remote= {0};
    remote.sin_addr.s_addr = inet_addr("127.0.0.1");//an internal default
    if(target==1)
    {
        remote.sin_addr.s_addr = inet_addr(TDSIP);
    }
    else if (target==2)
    {
        remote.sin_addr.s_addr = inet_addr(MACIP);
    }
    else if (target==3)
    {
        remote.sin_addr.s_addr = inet_addr(TLSIP);
    }
    
    remote.sin_family=AF_INET;
    remote.sin_port = htons(ServerPort);
    iRetval = connect(hSocket, (struct sockaddr *)&remote,sizeof(struct sockaddr_in));
    return iRetval;
}
int clientSocketSend(int hSocket, char* Rqst, short lenRqst)
{
    int shortRetval = -1;
    struct timeval tv;
    tv.tv_sec = 20;
    tv.tv_usec =0;
    if(setsockopt(hSocket,SOL_SOCKET,SO_SNDTIMEO, (char *)&tv, sizeof(tv))<0)
    {
        printf("Time out\n");
        return -1;
    }
    shortRetval=send(hSocket, Rqst, lenRqst, 0);
    return shortRetval;
}
/*
int clientSocketReceive(int hSocket, char* Rsp, short RvcSize)
{
    int shortRetval = -1;
    struct timeval tv;
    tv.tv_sec = 10;
    tv.tv_usec=0;
    if (setsockopt(hSocket, SOL_SOCKET, SO_RCVTIMEO, (char*)&tv,sizeof(tv))<0)
    {
        printf("Time Out\n");
        return -1;
    }
    shortRetval = recv(hSocket, Rsp, RvcSize, 0);
    printf("Response %s\n",Rsp);
    return shortRetval;
}
*/
void *sendToClient(int selection)
{
    int hSocket=0, read_size=9;
    struct sockaddr_in server;
    
    char server_reply[200] = {0};
    hSocket = clientSocketCreate();
    if(hSocket ==-1)
    {
        printf("Could not create socket\n");
        return NULL;
    }
    printf("Socket is created\n");
    if(clientSocketConnect(hSocket,selection)<0)
    {
        perror("connect failed.\n");
        return NULL;
    }
    char *sendToServer = copyFromClipboard();
    clientSocketSend(hSocket,sendToServer, strlen(sendToServer));
    //read_size = socketReceive(hSocket, server_reply, 200);
    //printf("Server Response : %s\n", server_reply);
    close(hSocket);
    return NULL;
}