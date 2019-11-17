#include "Server.h"
#include <iostream>
#include <pthread.h>
#include <stdlib.h>

Server s(2878);



void * asyncSend(void *raw) {
    struct Server::Connector *args = (struct Server::Connector *) raw;
    for(;;) {
        usleep(5000000);
        std::cout << "sending woohoo" << std::endl;
        s.sendMessage(*args, "woohoo");
    }
    free(args);
}

void onInput(uint16_t df, char *buffer) {
    std::cout << "[" << df << "]\t<" << buffer << ">" << std::endl; 
    // Connector c = 
    s.sendMessage((struct Server::Connector){.source_fd=df}, "yeet");
}

void onConnect(uint16_t df) {
    std::cout << df << " connected." << std::endl;
    pthread_t t;
    struct Server::Connector *args = (Server::Connector *) malloc(sizeof(struct Server::Connector));
    args->source_fd=df;
    if (pthread_create(&t, NULL, asyncSend, (void * ) args) != 0){
        printf("shit's fucked yo\n");
    }
}

int main() {
    std::cout << "howdy" << std::endl;
    s.onConnect(&onConnect);
    // MyHandler mh;
    s.onInput(&onInput);
    s.onDisconnect([](uint16_t df) {
        std::cout << df << " disconnected." << std::endl;
    });
    s.init();
    for(;;) s.loop();
    std::cout << "we done now " << std::endl;
    return 0;
}