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
