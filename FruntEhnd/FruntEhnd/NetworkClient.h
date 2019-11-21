#pragma once
#include <winsock2.h>

public ref class NetworkClient {
	SOCKET ConnectSocket = INVALID_SOCKET;

public:
	void start(PCSTR host, PCSTR port);
	void sendInfo();
	void receiveInfo();
	bool isConnected();
	void stop();
};
