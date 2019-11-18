#include "RoundLogic.h"
#include <string>
#include <vector>
#include "Player.h"
#include "StockGenerator.h"
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

RoundLogic::RoundLogic()
{
    loggedInUsers;
    roundTimer = 0;
    roundsPlayed = 0;
    roundStatus = "none";
}

RoundLogic::~RoundLogic()
{
    //dtor
}

void RoundLogic::clientLogin(const string& username)
{
    Player login(username);
    int newIndex = loggedInUsers.size();
    login.updateIndex(newIndex);
    loggedInUsers.push_back(login);
}

void RoundLogic::clientUpdate(const Player& user)
{
    Player update(user);
    int updateIndex = update.getIndex();
    loggedInUsers[updateIndex] = update;
}

string RoundLogic::getStatus()
{
    return roundStatus;
}

int RoundLogic::getRoundsPlayed()
{
    return roundsPlayed;
}

void RoundLogic::playRound()
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

        // Generate stock here as roundInfo
        StockGenerator roundInfo(0.002, 0.01);

        // tellClientsRoundInfo(roundInfo);
        // untested
        for(int i = 0; i < loggedInUsers.size(); i++) {
            cout << loggedInUsers[i].getStatus() << endl;
            if (loggedInUsers[i].getStatus() == "IN" ) {
                validClients++;
            }
        }
        roundStatus = "begin";
        // scrapped the sleep(25) because the round times are variable
        while(clientsFinished < validClients && roundTimer < 30) {
            this_thread::sleep_for(chrono::seconds(1));
            roundTimer++;
        }

    }
}

Player RoundLogic::getPlayer(const int& index)
{
    Player ret(loggedInUsers[index]);
    return ret;
}

/*int main()
{
    RoundLogic test;
    test.clientLogin("asdf");
    test.clientLogin("qwerty");
    Player testplayer = test.getPlayer(1);
    cout << testplayer.getName() << endl;
    testplayer.updateMoney(12345);
    test.clientUpdate(testplayer);
    Player test2 = test.getPlayer(1);
    cout << test2.getMoney() << endl;
}*/
