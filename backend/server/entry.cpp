#include <iostream>
#include <pthread.h>
#include <stdlib.h>
#include <thread>
#include <chrono>
#include <string>

#include "Server.h"
#include "round/RoundLogic.h"
#include "round/Player.h"
#include "round/StockGenerator.h"

Server server(2878);
RoundLogic game;

/*
====================================================
====	Network Communication
====================================================
*/
void * asyncSend(void *raw) {
	struct Server::Connector *args = (struct Server::Connector *) raw;
	for(;;) {
		usleep(5000000);
		std::cout << "sending woohoo" << std::endl;
		server.sendMessage(*args, "woohoo");
	}
	free(args);
}

void * listenBlocking(void *raw) {
	for(;;)
		server.loop();
}
void onInput(uint16_t df, char *buffer) {
	std::cout << "[" << df << "]\t<" << buffer << ">" << std::endl; 
	// Connector c = 
	server.sendMessage((struct Server::Connector){.source_fd=df}, "yeet");
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


/*
====================================================
====	Game Logic
====================================================
*/
void addPlayer(std::string username) {
	game.clientLogin(username);
}



void roundLoop() {
	game.validClients = 0;
	for (;;) {
		game.roundsPlayed++;
		game.roundTimer = 0;
		game.roundStatus = "warmup";
		game.clientsFinished = 0;

		// Player asdfC = test.loggedInUsers[0];
		// Player qwertyC = test.loggedInUsers[1];
		// this_thread::sleep_for(chrono::seconds(2));
		// for (int i = 0; i < test.loggedInUsers.size(); i++) {
		// 	cout << "status: " << test.loggedInUsers[i].getStatus() << endl;
		// 	if(test.loggedInUsers[i].getStatus() == "IN") {
		// 		cout << "Valid client" << endl;
		// 		test.validClients++;
		// 		test.loggedInUsers[i].setStatus("OUT");
		// 	}
		// }
		// test.roundStatus = "begin";
		// asdfC.updateMoney((double)-10000);
		// qwertyC.updateMoney((double)150);
		// test.clientUpdate(qwertyC);
		// test.clientUpdate(asdfC);
		// while(test.clientsFinished < test.validClients && test.roundTimer < 2) {
		// 	this_thread::sleep_for(chrono::seconds(1));
		// 	test.roundTimer++;
		// }

		// for(int i = 0; i < test.loggedInUsers.size(); i++){
		// 	if(test.loggedInUsers[i].getStatus() == "OUT"){
		// 		test.loggedInUsers.erase(test.loggedInUsers.begin() + i);
		// 	}
		// }

		// for(int i = 0; i < test.loggedInUsers.size(); i++){
		// 	test.loggedInUsers[i].updateIndex(i);
		// }

		// cout << test.loggedInUsers[0].getMoney() << endl;
		// cout << test.loggedInUsers[0].getName() << endl;
		// cout << test.loggedInUsers[0].getIndex() << endl;
	}
}


/*
====================================================
====	Entrypoint
====================================================
*/
int main() {
	std::cout << "Launching server" << std::endl;
	std::cout << "Binding socket events...";
	{
		server.onConnect(&onConnect);
		server.onDisconnect(&onDisconnect);
		server.onInput(&onInput);
	}
	std::cout << "\t\tOK!" << std::endl;
	std::cout << "Binding socket to port...";
	{
		server.init();
	}
	std::cout << "\t\tOK!" << std::endl;
	std::cout << "Creating socket background thread...";
	{
		pthread_t t;
		if (pthread_create(&t, NULL, listenBlocking, NULL) != 0) {
			std::cout << "FAIL!" << std::endl;
			return 1;
		}	
	}
	std::cout << "\tOK!" << std::endl;
	std::cout << "Server launched successfully!" << std::endl;

	roundLoop();

	return 0;
}