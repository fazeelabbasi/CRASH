#include "round/Game.h"
#include <string>
#include <vector>
#include "Player.h"
#include "StockGenerator.h"
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

Game::Game()
{
	players;
	roundTimer = 0;
	roundsPlayed = 0;
	roundStatus = "none";
}

Game::~Game()
{
	//dtor
}

void Game::clientLogin(const string& username)
{
	if(playerExists(username)) {
		cout << "Player already exists!" << endl;
	} else {
		Player login(username);
		int newIndex = players.size();
		login.index = newIndex;
		players.push_back(login);
	}
}

void Game::clientUpdate(const Player& user)
{
	// Need to implement a check here that a user with that name exists in the vector
	Player update(user);
	if(playerExists(update.name)) {
		for (int i = 0; i < players.size(); i++) {
			if (players[i].name == update.name) {
				players[i] = update;
			}
		}
	}
}

void Game::playRound()
{
	while(true) {
		// implement for loop for updating indices, and something else to get rid of inactive clients
		roundsPlayed++;
		roundTimer = 0;
		roundStatus = "warmup";
		clientsFinished = 0;
		validClients = 0;
		this_thread::sleep_for(chrono::seconds(25));

		// ledgerUpdate(loggedInUsers);

		StockGenerator roundInfo(0.002, 0.01);

		// tellClientsRoundInfo(roundInfo);

		// untested
		for(int i = 0; i < players.size(); i++) {
			cout << players[i].status << endl;
			if (players[i].status == "IN" ) {
				validClients++;
				/* Increments the valid client tracker and sets the status to OUT
				 * The status should be set back to "IN" in the clientUpdate method
				 * All clients that are still "OUT" (have not been updated) are removed
				 */
				players[i].status = "OUT";
			}
		}
		roundStatus = "begin";
		// scrapped the sleep(25) because the round times are variable
		while(clientsFinished < validClients && roundTimer < 30) {
			this_thread::sleep_for(chrono::seconds(1));
			roundTimer++;
		}
		/* The purpose of the next bit of code is to flush out all the clients
		 * who have not responded within the 30 second time limit. It is assumed
		 * that clients who are past this time are gone. There is currently nothing
		 * to handle the case where a client sends its data at 31+ seconds. When receiving
		 * requests, need to check that a client with that username exists in the vector first
		 * This could be handled in the updateClient method.
		 */
		// Remove all users with an "OUT" status
		for(int i = 0; i < players.size(); i++) {
			if(players[i].status == "OUT") {
				// UNTESTED
				players.erase(players.begin() + i);
			}
		}

		// After removing all the clients, iterate over the entire array to update their index values accordingly
		for (int i = 0; i < players.size(); i++) {
			players[i].index = i;
		}

	}
}



Player Game::getPlayer(const int& index)
{
	Player ret(players[index]);
	return ret;
}

bool Game::playerExists(const string& username) {
	return getPlayerIndex(username) != -1;
}

Player* Game::getPlayer(std::string username) {
	int i = getPlayerIndex(username);
	if (i==-1)
		return nullptr;
	return &players[i];
}

int Game::getPlayerIndex(std::string username) {
	for (int i = 0; i < players.size(); i++)
		if (players[i].name == username)
			return i;
	return -1;
}

void Game::setBalance(Player* p, double balance) {
	p->balance = balance;
	// moneyAmount += money;
	// netWorth += money;
	// if (moneyAmount < 1) {
	// 	status = "OUT";
	// 	cout << "Bankrupt" << endl;
	// }
}