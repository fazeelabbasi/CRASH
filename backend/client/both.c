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

struct sendArgs {
    int sockfd;
};

void * mySend(void *raw) {
    struct sendArgs *args = (struct sendArgs *) raw;
    for (int i=0;;i++) {
        usleep(1000000);
        int iResult;
        const char *sendbuf = "benis";
        
        // Send an initial buffer
        iResult = send(args -> sockfd, sendbuf, (int)strlen(sendbuf), 0);

        printf("[%d]\tBytes Sent: %d\n",i, iResult);

    }
}

void * receive() {

}

int main(int argc, char *argv[])
{
    int sockfd = 0, n = 0;
    char recvBuff[1024];
    struct sockaddr_in serv_addr; 

    if(argc != 2)
    {
        printf("\n Usage: %s <ip of server> \n",argv[0]);
        return 1;
    } 

    memset(recvBuff, '0',sizeof(recvBuff));
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    } 

    memset(&serv_addr, '0', sizeof(serv_addr)); 

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(2878); 

    if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr)<=0)
    {
        printf("\n inet_pton error occured\n");
        return 1;
    } 

    if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
       printf("\n Error : Connect Failed \n");
       return 1;
    } 

    pthread_t t;
    struct sendArgs args;
    args.sockfd=sockfd;
    if (pthread_create(&t, NULL, mySend, (void *)&args) != 0){
        printf("shit's fuckyed yo\n");
    }

    
    while ( (n = read(sockfd, recvBuff, sizeof(recvBuff)-1)) > 0)
    {
        recvBuff[n] = 0;
        // if(fputs(recvBuff, stdout) == EOF)
        // {
        //     printf("\n Error : Fputs error\n");
        // }
        // printf("n=%d\n", n);
        // fwrite(recvBuff, n, 1, stdout);
        printf("Received <%s>\n", recvBuff);
        // fflush(stdout);
    } 

    if(n < 0)
    {
        printf("\n Read error \n");
    } 

    return 0;
}