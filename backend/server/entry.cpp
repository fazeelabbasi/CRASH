#include <iostream>
#include <pthread.h>
#include <stdlib.h>
#include <thread>
#include <chrono>

#include "Server.h"
#include "round/RoundLogic.h"
#include "round/Player.h"
#include "round/StockGenerator.h"

Server s(2878);



void * asyncSend(void *raw) {
	struct Server::Connector *args = (struct Server::Connector *) raw;
	for(;;) {
		usleep(5000000);
		std::cout << "sending woohoo" << std::endl;
		s.sendMessage(*args, "woohoo");
	}
	free(args);
}

void onInput(uint16_t df, char *buffer) {
	std::cout << "[" << df << "]\t<" << buffer << ">" << std::endl; 
	// Connector c = 
	s.sendMessage((struct Server::Connector){.source_fd=df}, "yeet");
}

void onDisconnect(uint16_t df) {
	std::cout << df << " disconnected." << std::endl;
}

void onConnect(uint16_t df) {
	std::cout << df << " connected." << std::endl;
	pthread_t t;
	struct Server::Connector *args = (Server::Connector *) malloc(sizeof(struct Server::Connector));
	args->source_fd=df;
	if (pthread_create(&t, NULL, asyncSend, (void * ) args) != 0){
		printf("shit's fucked yo\n");
	}
}

int main() {
	std::cout << "Launching server" << std::endl;
	s.onConnect(&onConnect);
	s.onDisconnect(&onDisconnect);
	s.onInput(&onInput);

	s.init();
	for(;;) s.loop();
	std::cout << "we done now " << std::endl;
	return 0;
}


int roundTest()
{
	RoundLogic test;
	test.roundsPlayed++;
	test.roundTimer = 0;
	test.roundStatus = "warmup";
	test.clientsFinished = 0;
	test.validClients = 0;
	test.clientLogin("asdf");
	test.clientLogin("qwerty");
	Player asdfC = test.loggedInUsers[0];
	Player qwertyC = test.loggedInUsers[1];
	this_thread::sleep_for(chrono::seconds(2));
	for (int i = 0; i < test.loggedInUsers.size(); i++) {
		cout << "status: " << test.loggedInUsers[i].getStatus() << endl;
		if(test.loggedInUsers[i].getStatus() == "IN") {
			cout << "Valid client" << endl;
			test.validClients++;
			test.loggedInUsers[i].setStatus("OUT");
		}
	}
	test.roundStatus = "begin";
	asdfC.updateMoney((double)-10000);
	qwertyC.updateMoney((double)150);
	test.clientUpdate(qwertyC);
	test.clientUpdate(asdfC);
	while(test.clientsFinished < test.validClients && test.roundTimer < 2) {
		this_thread::sleep_for(chrono::seconds(1));
		test.roundTimer++;
	}

	for(int i = 0; i < test.loggedInUsers.size(); i++){
		if(test.loggedInUsers[i].getStatus() == "OUT"){
			test.loggedInUsers.erase(test.loggedInUsers.begin() + i);
		}
	}

	for(int i = 0; i < test.loggedInUsers.size(); i++){
		test.loggedInUsers[i].updateIndex(i);
	}

	cout << test.loggedInUsers[0].getMoney() << endl;
	cout << test.loggedInUsers[0].getName() << endl;
	cout << test.loggedInUsers[0].getIndex() << endl;
}
