#include "Player.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

Player::Player()
{
    name = "";
    moneyAmount = 0;
    netWorth = 0;
    status = "OUT";
    index = -1;
}

Player::Player(const string& username)
{
    name = username;
    moneyAmount = 100;
    netWorth = 100;
    status = "IN";
    index = -1;
}

Player::Player(const Player& copy)
{
    name = copy.name;
    moneyAmount = copy.moneyAmount;
    netWorth = copy.netWorth;
    status = copy.status;
    index = copy.index;
}

Player::~Player()
{
    //dtor
}

void Player::updateMoney(const double& money)
{
    moneyAmount += money;
    netWorth += money;
    if (moneyAmount < 1) {
        status = "OUT";
        cout << "Bankrupt" << endl;
    }
}

double Player::getMoney()
{
    return moneyAmount;
}

void Player::updateIndex(const int& in)
{
    index = in;
}

int Player::getIndex()
{
    return index;
}

string Player::getStatus()
{
    return status;
}

string Player::getName()
{
    return name;
}

void Player::setStatus(const string& stat)
{
    status = stat;
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
