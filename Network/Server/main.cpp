#include "Server.h"
#include <thread>
#include "iostream"
#include <chrono>
int main()
{
	std::cout << "Yeet";

	Server* s = new Server();
	s->start();
	//std::thread t(&Server::waitForClient, s);
	std::thread t([&]() {
		while (true) {
			s->waitForClient();
		}
	});
	for (;;) {
		std::this_thread::sleep_for(std::chrono::seconds(1));
		std::cout << "Beep!" << std::endl;
	}
	s->stop();
	return 0;
}

