#pragma once

#include <string>

typedef void * (*THREADFUNCPTR)(void *);
 
class Network { 
public:
    int sockfd;
    int connectToServer(const char *serverAddr);
    static void sendAsync(int sockfd, std::string sendbuf);
    static void* sendRaw(void *raw);
    char* receiveBlocking(int sockfd);
};

struct sendInfo {
    int sockfd;
    std::string sendbuf;
};
