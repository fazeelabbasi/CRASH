#pragma once

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

class Client {
	SOCKET ConnectSocket = INVALID_SOCKET;

public:
	void start(PCSTR host);
	void sendInfo();
	void receiveInfo();
	void stop();
};
