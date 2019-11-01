#include "Client.h"
#include <stdio.h>
#include <thread>
#include <chrono>

int main(int argc, char** argv) {
	if (argc != 2) {
		printf("usage: %s server-name\n", argv[0]);
		return 1;
	}

	Client* c = new Client();
	c->start(argv[1]);
	c->sendInfo();
	std::thread t([&]() {
		c->receiveInfo();
	});
	std::this_thread::sleep_for(std::chrono::seconds(5));
	c->stop();

	return 0;
}