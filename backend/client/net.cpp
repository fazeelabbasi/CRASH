#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 
#include <pthread.h>
#include <iostream>
#include "net.h"

void* Network::sendRaw(void *raw) {
    int iResult;
    struct sendInfo *info = (struct sendInfo*) raw;
    std::cout << "Sending raw message on [" << info->sockfd << "] <" << info->sendbuf << ">" << std::endl;
    iResult = send(info->sockfd, info->sendbuf.c_str(), info->sendbuf.size(), 0);
    printf("[%d]\tBytes Sent: %d\n",info->sockfd, iResult);
    // return iResult;
    // free(info->sendbuf);
    free(raw);
}

void Network::sendAsync(int sockfd, std::string sendbuf) {
    std::cout << "Sending async message raw [" << sockfd << "] <" << sendbuf << ">" << std::endl;

    pthread_t t;
    struct sendInfo *info = (struct sendInfo*) malloc(sizeof(struct sendInfo));
    info->sockfd = sockfd;
    info->sendbuf = sendbuf;
    // memcpy(info->sendbuf,sendbuf,sizeof(sendbuf) * sizeof(char));

    std::cout << "Sending async message struct [" << info->sockfd << "] <" << info->sendbuf << ">" << std::endl;
    if (pthread_create(&t, NULL, Network::sendRaw, (void *) info) != 0) {
        printf("Failed to send message\n");
    }
}


int Network::connectToServer(const char* serverAddr) {
    int sockfd = 0;
    struct sockaddr_in serv_addr; 

    // if(argc != 2)
    // {
    //     printf("\n Usage: %s <ip of server> \n",argv[0]);
    //     return 1;
    // } 

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    } 

    memset(&serv_addr, '0', sizeof(serv_addr)); 

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(2878); 

    if(inet_pton(AF_INET, serverAddr, &serv_addr.sin_addr)<=0)
    {
        printf("\n inet_pton error occured\n");
        return 1;
    } 

    if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
       printf("\n Error : Connect Failed \n");
       return 1;
    } 
    
    this->sockfd = sockfd;
    return 0;
}

char* Network::receiveBlocking(int sockfd) {
    // char recvBuff[1024];
    char* recvBuff = (char *) malloc(sizeof(char)*1024);
    int n=0;
    memset(recvBuff, '0',sizeof(recvBuff));

    n = read(sockfd, recvBuff, sizeof(recvBuff)-1);
    recvBuff[n] = 0;
    printf("Received <%s>\n", recvBuff);

    if(n < 0) {
        printf("\n Read error \n");
    } 
    return recvBuff;
}