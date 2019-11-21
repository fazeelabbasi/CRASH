#include <iostream>
#include <pthread.h>
#include <stdlib.h>
#include <thread>
#include <chrono>
#include <string>
#include <sstream>

#include "Server.h"
#include "round/Game.h"
#include "round/Player.h"
#include "round/StockGenerator.h"

Server server(2878);
Game game;
std::vector<int> clients;
int seed = 4;
std::string winnerName;
/*
====================================================
====	Network Send Protocols
====================================================
*/
void notifyAll(void *(f)(void *)) {
	for (auto df : clients) {
		pthread_t t;
		struct Server::Connector *args = (Server::Connector *) malloc(sizeof(struct Server::Connector));
		args->source_fd=df;
		if (pthread_create(&t, NULL, f, (void *) args) != 0) {
			std::cout << "FAIL NOTIFYING PLAYER!" << std::endl;
			return;
		}
	}
}

void * sendPlayerList(void *raw) {
	struct Server::Connector *args = (struct Server::Connector *) raw;

	// send the balance for each user
	std::ostringstream ss;
	for (auto p : game.players) {
		ss << "USER " << p.name << " " << p.balance << std::endl;
	}
	server.sendMessage(*args, ss.str().c_str());
	free(raw); 
}

void * sendRoundInfo(void *raw) {
	struct Server::Connector *args = (struct Server::Connector *) raw;
	std::ostringstream ss;
	ss << "SEED " << seed << std::endl;
	server.sendMessage(*args, ss.str().c_str());
	free(raw); 
}

void * sendWinnerInfo(void *raw) {
	struct Server::Connector *args = (struct Server::Connector *) raw;
	std::ostringstream ss;
	ss << "WIN " << winnerName << std::endl;
	server.sendMessage(*args, ss.str().c_str());
	free(raw); 
}

void notifyWinner() {
	notifyAll(sendWinnerInfo);
}

void notifyPlayerList() {
	notifyAll(sendPlayerList);
}

void notifyRoundBegin() {
	seed++;
	notifyAll(sendRoundInfo);
}
/*
====================================================
====	Periodic Updating
====================================================
*/

void * asyncSend(void *raw) {
	struct Server::Connector *args = (struct Server::Connector *) raw;
	for(;;) {
		usleep(5000000);
		// std::cout << "sending woohoo" << std::endl;
		// server.sendMessage(*args, "woohoo");
		void *x = malloc(sizeof(struct Server::Connector));
		memcpy(x,raw,sizeof(struct Server::Connector));
		sendPlayerList(x);
	}
	free(args);
}

/*
====================================================
====	socket Join/Leave Handling
====================================================
*/

void onDisconnect(uint16_t df) {
	std::cout << df << " disconnected." << std::endl;
	for (int i=0; i<clients.size(); i++) {
		if (clients[i] == df) {
			clients.erase(clients.begin()+i);
			return;
		}
	}
}

void onConnect(uint16_t df) {
	std::cout << df << " connected." << std::endl;
	clients.push_back(df);
	
	pthread_t t;
	struct Server::Connector *args = (Server::Connector *) malloc(sizeof(struct Server::Connector));
	args->source_fd=df;
	if (pthread_create(&t, NULL, asyncSend, (void * ) args) != 0){
		printf("shit's fucked yo\n");
	}
}

/*
====================================================
====	Message Event Handling
====================================================
*/
void handleMessage(uint16_t df, const char *buffer) {
	std::cout << "[" << df << "]\t<" << buffer << ">" << std::endl; 
	std::string msg(buffer);
	if (msg.size() >= 6 && msg.substr(0,6) == "LOGIN ") {
		msg.erase(0,6);
		std::istringstream ss(msg);
		std::string username;
		ss >> username;
		game.clientLogin(username);
		std::cout << "<" << username << "> has joined the game!" << std::endl;
	} else if (msg.size() >= 7 && msg.substr(0,7) == "FINISH ") {
		msg.erase(0,7);
		std::istringstream ss(msg);
		std::string username;
		ss >> username;
		Player* p = game.getPlayer(username);
		if (p) {
			p->status = "FINISHED";
			std::cout << "Set <" << p->name << "> status to FINISHED" << std::endl;
		} else {
			std::cout << "Failed to update status for <" << username << ">" << std::endl;
		}
	} else if (msg.size() >= 8 && msg.substr(0,8) == "BALANCE ") {
		msg.erase(0,7);
		std::istringstream ss(msg);
		std::string username;
		ss >> username;
		double balance;
		ss >> balance;
		Player* p = game.getPlayer(username);
		if (p) {
			p->balance = balance;
			std::cout << "Updated <" << p->name << "> balance to $" << p->balance << std::endl;
		} else {
			std::cout << "Failed updating balance for <" << username << ">" << std::endl;
		}
	} else if (msg.size() >= 5 && msg.substr(0,5) == "DONE ") {
		msg.erase(0,5);
		std::istringstream ss(msg);
		std::string username;
		ss >> username;
		double balance;
		ss >> balance;
		Player* p = game.getPlayer(username);
		if (p) {
			p->balance = balance;
		} else {
			std::cout << "Failed to find player [" << username << "]" << std::endl;
		}
	} else {
		std::cout << "No action taken." << std::endl;
	}
	// server.sendMessage((struct Server::Connector){.source_fd=df}, "yeet");	
}

void onMessage(uint16_t df, char *buffer) {
	std::string msg(buffer);
	int pos;
	while (pos = msg.find("\n")) {
		std::string chunk = msg.substr(0, pos);
		handleMessage(df, chunk.c_str());
		if (pos == msg.size()-1)
			return;
		msg = msg.substr(pos+1);
	}
	handleMessage(df, msg.c_str());
}

void * listenBlocking(void *raw) {
	for(;;)
		server.loop();
}

void * setupServer(void* raw) {
	std::cout << "Launching server" << std::endl;
	std::cout << "Binding socket events...";
	{
		server.onConnect(&onConnect);
		server.onDisconnect(&onDisconnect);
		server.onInput(&onMessage);
	}
	std::cout << "\t\tOK!" << std::endl;
	std::cout << "Binding socket to port...";
	{
		server.init();
	}
	std::cout << "\t\tOK!" << std::endl;
	// std::cout << "Creating socket background thread...";
	{
		// pthread_t t;
		// if (pthread_create(&t, NULL, listenBlocking, NULL) != 0) {
		// 	std::cout << "FAIL!" << std::endl;
		// 	return 1;
		// }	
		std::cout << "Server launched successfully!" << std::endl;
		listenBlocking(nullptr);
	}
	// std::cout << "\tOK!" << std::endl;
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
	for (i=0;i<10;i++) {
		// WARMUP
		{
			std::cout << "Warmup started" << std::endl;
			game.roundsPlayed++;
			game.roundStatus = "warmup";
		}

		// BEGIN
		{
			for(;game.players.size()==0;) {
				std::cout << "No players in the game! Waiting for more..." << std::endl;
				this_thread::sleep_for(chrono::seconds(5));
			}
			std::cout << "Beginning round" << std::endl;
			// this_thread::sleep_for(chrono::seconds(2));
			game.roundStatus = "begin";
			for (auto& player : game.players)
				player.status = "WAITING";
			notifyRoundBegin();
		}

		// WAIT (BLOCKING) 
		{
			bool done = false;
			const int timeout = 999;
			for (int roundTimer = 0; !done && roundTimer < timeout; roundTimer++) {
				std::cout << "Waiting for all players to respond, " << (timeout - roundTimer) << "s remaining." << std::endl;
				this_thread::sleep_for(chrono::seconds(1));
				done=true;
				for (auto& player : game.players)
					if (player.status != "FINISHED")
						done=false;
			}
		}

		// END ROUND
		{
			std::cout << "Round over!" << std::endl;
			for (auto& player : game.players) {
				std::cout << "<" << player.name << "> $" << player.balance << std::endl;
				player.status = "READY";
			}
		}
	}
	if (game.players.size() == 0)
		return;
	Player& winner = game.players[0];
	for (Player& p : game.players) {
		if (p.balance > winner.balance) {
			winner=p;
		}
	}
	winnerName = winner.name;
	notifyWinner(winner.name);
}

/*
====================================================
====	Entrypoint
====================================================
*/
int main() {
	pthread_t t;
	if (pthread_create(&t, NULL, setupServer, NULL) != 0) {
		std::cout << "FAIL!" << std::endl;
		return 1;
	}
	//setupServer();

	roundLoop();

	return 0;
}