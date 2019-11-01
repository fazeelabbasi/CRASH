#include "Server.h"
#include <thread>
#include "iostream"
#include <chrono>
int main()
{
	std::cout << "Yeet" << std::endl;

	Server* s = new Server();
	s->start();
	//std::thread t(&Server::waitForClient, s);
	std::thread t([&]() {
		while (true) {
			s->waitForClient();
		}
	});
	//t.detach();
	for (int i=0;;i++) {
		std::this_thread::sleep_for(std::chrono::seconds(1));
		std::cout << "Beep!\t" << i << std::endl;
		/*if (i % 2 == 0 && s->clients.size() > 0) {
			s->sendToClient(s->clients.at(0), "fuck you");
		} else if (s->clients.size() > 1) {
			s->sendToClient(s->clients.at(1), "suh dude");
		}*/
	}

	s->stop();
	return 0;
}

