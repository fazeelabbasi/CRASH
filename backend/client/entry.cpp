#include <sstream>
#include <iostream>
#include <string>
#include <stdlib.h>
#include "entry.h"


void Game::login() {
	// std::cout << "Enter your username: ";
	// std::cin >> this->username;
}

int Game::joinServer() {
	std::string input;
	std::cout << "Enter the server address [0.0.0.0]: ";
	getline(std::cin, input);
	if (input.empty()) {
		input = "0.0.0.0";
	}
	return this->net.connectToServer(input.c_str());
}

void Game::listenServer() {
	for (;;) {
		char* recvBuff = this->net.receiveBlocking(this->net.sockfd);
	}
}

void Game::mainLoop() {
	while (true) {
		std::cout << "Actions:" << std::endl;
		std::cout << "1.\tSend message" << std::endl;
		std::cout << "2.\tExit" << std::endl;
		std::cout << std::endl;
		std::cout << "Action: ";
		int action;
		std::string input;
		getline(std::cin, input);
		if (input.empty()) {
			std::cout << "No input given." << std::endl;
			continue;
		} else {
			std::istringstream ss(input);
			ss >> action;
		}
		switch(action) {
			case 1: {
				std::string msg;
				std::cout << "Enter a message: ";
				getline(std::cin, msg);
				// std::cin.ignore();
				std::cout << "You entered <" << msg << ">" << std::endl;
				this->net.sendAsync(this->net.sockfd, msg);
				break;
			}
			case 2: {
				return;
			}
			default: {
				std::cout << "Unknown option chosen." << std::endl;
				break;
			}
		}
	}
}



int main() {
	Game *g = new Game();
	
	g->login();
	while (g->joinServer()!=0){};

	pthread_t t;
	if (pthread_create(&t, NULL, (THREADFUNCPTR) &Game::listenServer, g)!=0) {
		printf("Failed to create listener thread!");
	}

	g->mainLoop();
	return 0;
}