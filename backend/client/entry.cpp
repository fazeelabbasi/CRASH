#include <iostream>
#include <string>
#include <stdlib.h>
#include "entry.h"


void Game::login() {
    std::cout << "Enter your username: ";
    std::cin >> this->username;
}

int Game::joinServer() {
    char* serverAddr;
    std::cout << "Enter the server address: ";
    std::cin >> serverAddr;
    return this->net.connectToServer(serverAddr);
}

void Game::listenServer() {
    for (;;) {
        char* recvBuff = this->net.receiveBlocking(this->net.sockfd);
    }
}

void Game::mainLoop() {
    while (true) {
        std::cout << "Actions:" << std::endl;
        std::cout << "1.\tSend message" << std::endl;
        std::cout << "2.\tExit" << std::endl;
        std::cout << std::endl;
        std::cout << "Action: ";
        int action;
        std::cin >> action;
        std::cin.clear();
        switch(action) {
            case 1: {
                char* msg = (char*) malloc(sizeof(char) * 1024);
                std::cout << "Enter a message: ";
                std::cin >> msg;
                std::cout << "You entered <" << msg << ">" << std::endl;
                this->net.sendAsync(this->net.sockfd, msg);
                std::cin.clear();
                free(msg);
                break;
            }
            case 2: {
                return;
            }
            default: {
                std::cout << "Unknown option chosen." << std::endl;
                break;
            }
        }
    }
}



int main() {
    Game *g = new Game();
    
    g->login();
    while (g->joinServer()!=0){};

    pthread_t t;
    if (pthread_create(&t, NULL, (THREADFUNCPTR) &Game::listenServer, g)!=0) {
        printf("Failed to create listener thread!");
    }

    g->mainLoop();
    return 0;
}