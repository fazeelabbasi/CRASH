// Server.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>
#include <vector>

class Server {
	WSADATA wsaData;
	SOCKET ListenSocket = INVALID_SOCKET;
	std::vector<SOCKET> clients;
public:
	void start();
	void waitForClient();
	void stop();
};

// TODO: Reference additional headers your program requires here.
