// Server.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>
#include <vector>
#include <thread>
#include "Client.h"

class Server {
	WSADATA wsaData;
	SOCKET ListenSocket = INVALID_SOCKET;
public:
	std::vector<Client*> clients;
public:
	void start();
	void waitForClient();
	void closeClient(Client* c);
	void sendToClient(Client* c, std::string);
	void stop();
};

// TODO: Reference additional headers your program requires here.
