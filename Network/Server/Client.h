#pragma once
#include <WinSock2.h>
#include <thread>
class Client {
public:
	Client(SOCKET* socket, std::thread* listener);
	SOCKET* socket;
	std::thread* listener;
};