#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <vector>

using namespace std;

class Player
{
	public:
		string name;
		double balance, netWorth;
		string status;
		int index;

		Player();
		Player(const string& username);
		Player(const Player& copy);
		virtual ~Player();
};

#endif // PLAYER_H
