#include "Server.h"
#include <thread>
#include "iostream"
#include <chrono>
#include <vector>
#include <algorithm>
int main()
{
	std::cout << "Yeet" << std::endl;

	Server* s = new Server();
	s->start();
	std::thread t([&]() {
		int count = 0;
		while (true) {
			SOCKET sock = s->waitForClient();
			Client* c;
			std::thread listen([&]() {
				s->listenToClient(sock, count++);
				s->clients.erase(
					std::remove(
						s->clients.begin(),
						s->clients.end(),
						c
					),
					s->clients.end()
				);
				delete c;
			});
			c = new Client(sock, listen);
			s->clients.push_back(c);
			listen.detach();
		}
	});
	for (int i=0;;i++) {
		std::this_thread::sleep_for(std::chrono::seconds(1));
		std::cout << "Beep!\t" << i << "\t" << s->clients.size() << std::endl;
		if (i % 2 == 0 && s->clients.size() > 0) {
			printf("Sending to client A\n");
			s->sendToClient(s->clients.at(0)->socket, "fuck you");
		} else if (s->clients.size() > 1) {
			printf("Sending to client B\n");
			s->sendToClient(s->clients.at(1)->socket, "suh dude");
		}
	}

	s->stop();
	return 0;
}

