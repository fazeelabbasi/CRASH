#ifndef ROUNDLOGIC_H
#define ROUNDLOGIC_H
#include <string>
#include <vector>
#include "Player.h"

using namespace std;

class Game
{
	public:
		vector<Player> loggedInUsers;
		int roundsPlayed;
		string roundStatus;
		int validClients;
		int clientsFinished;
		int roundTimer;

		Game();
		virtual ~Game();
		void clientLogin(const string& username);
		void clientUpdate(const Player& user); //fix this stuff
		void playRound();

		int getPlayerIndex(std::string username);
		bool playerExists(const string& username);
		Player getPlayer(const int& index);
		Player* getPlayer(std::string username);
		void setBalance(Player* p, double balance);
};

#endif // ROUNDLOGIC_H
