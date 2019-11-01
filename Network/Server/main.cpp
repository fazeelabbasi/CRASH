#include "Server.h"
#include <thread>
#include "iostream"
#include <chrono>
#include <vector>
int main()
{
	std::cout << "Yeet" << std::endl;

	Server* s = new Server();
	s->start();
	//std::thread t(&Server::waitForClient, s);
	std::thread t([&]() {
		std::vector<std::thread*> threads;
		while (true) {
			SOCKET sock = s->waitForClient();
			//Client c();
			//std::thread listener(&Server::listenToClient, s, sock);
			std::thread listen([&]() {
				try {
					s->listenToClient(sock);
				}
				catch (std::exception & ex) {
					std::cout << "fuck me, right?" << std::endl;
				}
				/*s->clients.erase(
					std::remove(
						s->clients.begin(),
						s->clients.end(),
						c
					),
					clients.end()
				);*/
			});
			Client c(sock, listen);
			s->clients.push_back(c);
			threads.push_back(&listen);
			listen.detach();
			//c.listener = &listen;
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

