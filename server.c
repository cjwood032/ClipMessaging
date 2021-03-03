#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

short socketCreate(void) {
    short hSocket;
    printf("Create the socket");
    hSocket=socket(AF_INET, SOCK_STREAM,0);
    return hSocket;
}
int bindCreatedSocket (int hsocket){
    int iRetval=-1;
    int clientPort = 12345;
    struct sockaddr_in remote = {0};
    remote.sin_family=AF_INET;
    remote.sin_addr.s_addr = htonl(INADDR_ANY);
    remote.sin_port = htons(clientPort);
    iRetval = bind(hsocket,(struct sockaddr *) &remote, sizeof(remote));
    return iRetval;
}
int main(int argc, char *argv[])
{
    int socket_desc=0, sock=0, clientLen=0;
    struct sockaddr_in client;
    char client_message[200]={0};
    char message[100]={0};
    const char *pMessage="HELLO FROM THE SERVER";
    socket_desc = socketCreate();
    if(socket_desc==-1)
    {
        printf("couldn't create socket\n");
        return 1;
    }
    printf("socket created");
    if (bindCreatedSocket(socket_desc)<0)
    {
        perror("bind failed.");
        return 1;
    }
    printf("bind done\n");
    listen(socket_desc,3);
    while(1)
    {
        printf("waiting for incoming connections \n");
        clientLen = sizeof(struct sockaddr_in);
        sock = accept(socket_desc, (struct sockaddr *) &client,(socklen_t*)&clientLen);
        if (sock < 0)
        {
            perror("accept failed");
            return 1;
        }
        printf("Connection accepted\n");
        memset(client_message, '\0', sizeof client_message);
        memset(message, '\0', sizeof message);
        if(recv(sock, client_message, 200,0)<0)
        {
            printf("recv failed");
            break;
        }
        printf("Client reply:%s\n",client_message);
        if(strncmp(pMessage,client_message,5)==0)
        {
            strcpy(message,"Hi there!");
        }
        else
        {
            strcpy(message,"Invalid message.");
        }
        if(send(sock,message,strlen(message),0)<0)
        {
            printf("send failure");
            return 1;
        }
        close(sock);
        sleep(1);
    }
    return 0;
}