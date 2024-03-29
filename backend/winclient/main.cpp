#include "Client.h"
#include <stdio.h>
#include <thread>
#include <chrono>
#include <string>

int main(int argc, char** argv) {
	printf("Launching client...\n");
	Client* c = new Client();
	c->start("127.0.0.1");
	// c->start(argv[1]);
	if (!c->isConnected())
		return 1;


	std::thread send([&]() {
		for (;;) {
			c->sendInfo();
			std::this_thread::sleep_for(std::chrono::seconds(3));
		}
	});

	std::thread t([&]() {
		c->receiveInfo();
	});


	std::this_thread::sleep_for(std::chrono::seconds(15000));
	c->stop();
	t.join();
	
	return 0;
}

/*
Todo List:
- Make Client::start accept an IP and a PORT
- Make QT start connection

- Make Client::sendInfo accept a string message

- Make client check message payload for commands
- Make server send clients the player money info
- Make server send clients the graph points
*/