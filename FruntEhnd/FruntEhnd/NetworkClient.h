#pragma once
#include <winsock2.h>
#include <string>

public ref class NetworkClient {
	SOCKET ConnectSocket = INVALID_SOCKET;

public:
	void start(PCSTR host, PCSTR port);
	void sendInfo(std::string);
	std::string receiveInfo();
	bool isConnected();
	void stop();
};
