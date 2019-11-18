#pragma once

#include <string>
#include "net.h"

class Game {
public:
    std::string username;
    Network net;
    float money;
    void login();
    int joinServer();
    void mainLoop();
    void listenServer();
};