#include "Player.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

Player::Player()
{
	name = "";
	balance = 0;
	netWorth = 0;
	status = "OUT";
	index = -1;
}

Player::Player(const string& username)
{
	name = username;
	balance = 100;
	netWorth = 100;
	status = "IN";
	index = -1;
}

Player::Player(const Player& copy)
{
	name = copy.name;
	balance = copy.balance;
	netWorth = copy.netWorth;
	status = copy.status;
	index = copy.index;
}

Player::~Player()
{
	//dtor
}



/*int main() {
	Player test("testName");
	test.updateIndex(2);
	cout << test.getIndex() << endl;
	test.updateMoney(2.3);
	cout << test.getMoney() << endl;
	Player test2(test);
	cout << test2.getIndex() << endl;
	cout << test2.getMoney() << endl;
}*/