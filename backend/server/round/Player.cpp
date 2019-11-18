#include "Player.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

Player::Player()
{
    name = "";
    moneyAmount = 0;
    assets = 0;
    status = false;
    index = -1;
}

Player::Player(const string& username)
{
    name = username;
    moneyAmount = 100;
    assets = 0;
    status = true;
    index = -1;
}

Player::Player(const Player& copy)
{
    name = copy.name;
    moneyAmount = copy.moneyAmount;
    assets = copy.assets;
    status = copy.status;
    index = copy.index;
}

Player::~Player()
{
    //dtor
}

void Player::updateMoney(const double& money)
{
    // Now just updates the money to the new value instead of taking the change
    moneyAmount = money;
    if (moneyAmount < 1) {
        status = false;
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

bool Player::getStatus()
{
    return status;
}

string Player::getName()
{
    return name;
}

void Player::setStatus(const bool& stat)
{
    status = stat;
}

double Player::getAssets() {
    return assets;
}

void Player::setAssets(const double& new_assets) {
    assets = new_assets;
}

/*int main() {
    Player test("testName");
    test.updateIndex(2);
    cout << test.getIndex() << endl;
    cout << test.getMoney() << endl;
    test.updateMoney(123);
    cout << test.getMoney() << endl;
    Player test2(test);
    cout << test2.getIndex() << endl;
    cout << test2.getMoney() << endl;
}*/
