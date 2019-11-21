#pragma once
#include <winsock2.h>
#include <string>

public delegate void Del(System::String^ msg);

interface struct MessageEventSource {
public:
	event Del ^ onMessage;
	void fire(System::String^ msg);
};

public ref class NetworkClient: public MessageEventSource {
public:
	virtual event Del^ onMessage;
	virtual void fire(System::String^ msg) {
		onMessage(msg);
	};

	void start(PCSTR host, PCSTR port);
	void sendInfo(std::string msg);
	void sendInfo(System::String^ msg);
	std::string receiveInfo();
	bool isConnected();
	void stop();
private:
	SOCKET ConnectSocket = INVALID_SOCKET;
};
