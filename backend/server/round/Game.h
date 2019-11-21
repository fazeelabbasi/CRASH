#ifndef ROUNDLOGIC_H
#define ROUNDLOGIC_H
#include <string>
#include <vector>
#include "Player.h"

using namespace std;

class Game
{
	public:
		vector<Player> players;
		int roundsPlayed;
		string roundStatus;

		Game();
		virtual ~Game();
		void clientLogin(const string& username);

		int getPlayerIndex(std::string username);
		bool playerExists(const string& username);
		Player* getPlayer(std::string username);
};

#endif // ROUNDLOGIC_H
