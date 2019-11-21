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
    if(playerExists(username)) {
        cout << "Player already exists!" << endl;
    } else {
        Player login(username);
        int newIndex = loggedInUsers.size();
        login.updateIndex(newIndex);
        loggedInUsers.push_back(login);
    }
}

void RoundLogic::clientUpdate(const Player& user)
{
    // Need to implement a check here that a user with that name exists in the vector
    Player update(user);
    if(playerExists(update.getName())) {
        for (int i = 0; i < loggedInUsers.size(); i++) {
            if (loggedInUsers[i].getName() == update.getName()) {
                loggedInUsers[i] = update;
            }
        }
    }
}

string RoundLogic::getStatus()
{
    return roundStatus;
}

int RoundLogic::getRoundsPlayed()
{
    return roundsPlayed;
}

bool RoundLogic::playerExists(const string& username)
{
    for (int i = 0; i < loggedInUsers.size(); i++) {
        if (loggedInUsers[i].getName() == username) {
            return true;
        }
    }
    return false;
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

        StockGenerator roundInfo(0.002, 0.01);

        // tellClientsRoundInfo(roundInfo);

        // untested
        for(int i = 0; i < loggedInUsers.size(); i++) {
            cout << loggedInUsers[i].getStatus() << endl;
            if (loggedInUsers[i].getStatus() == "IN" ) {
                validClients++;
                /* Increments the valid client tracker and sets the status to OUT
                 * The status should be set back to "IN" in the clientUpdate method
                 * All clients that are still "OUT" (have not been updated) are removed
                 */
                loggedInUsers[i].setStatus("OUT");
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
        for(int i = 0; i < loggedInUsers.size(); i++) {
            if(loggedInUsers[i].getStatus() == "OUT") {
                // UNTESTED
                loggedInUsers.erase(loggedInUsers.begin() + i);
            }
        }

        // After removing all the clients, iterate over the entire array to update their index values accordingly
        for (int i = 0; i < loggedInUsers.size(); i++) {
            loggedInUsers[i].updateIndex(i);
        }

    }
}

Player RoundLogic::getPlayer(const int& index)
{
    Player ret(loggedInUsers[index]);
    return ret;
}

Player RoundLogic::buyout(const Player& user, const Player& victim){
	Player buy(user);
	Player sell(victim);
	
	buy.setNetWorth() = sell.getNewWorth() - sell.getMoney() - (0.25 * sell.getNetWorth());
	sell.setNetWorth(0);
	sell.updateMoney(-(sell.getMoney()));
	sell.setStatus("OUT");
	
}

int main()
{
    RoundLogic test;
    test.roundsPlayed++;
    test.roundTimer = 0;
    test.roundStatus = "warmup";
    test.clientsFinished = 0;
    test.validClients = 0;
    test.clientLogin("asdf");
    test.clientLogin("qwerty");
    Player asdfC = test.loggedInUsers[0];
    Player qwertyC = test.loggedInUsers[1];
    this_thread::sleep_for(chrono::seconds(2));
    for (int i = 0; i < test.loggedInUsers.size(); i++) {
        cout << "status: " << test.loggedInUsers[i].getStatus() << endl;
        if(test.loggedInUsers[i].getStatus() == "IN") {
            cout << "Valid client" << endl;
            test.validClients++;
            test.loggedInUsers[i].setStatus("OUT");
        }
    }
    test.roundStatus = "begin";
    asdfC.updateMoney((double)-10000);
    qwertyC.updateMoney((double)150);
    test.clientUpdate(qwertyC);
    test.clientUpdate(asdfC);
    while(test.clientsFinished < test.validClients && test.roundTimer < 2) {
        this_thread::sleep_for(chrono::seconds(1));
        test.roundTimer++;
    }

    for(int i = 0; i < test.loggedInUsers.size(); i++){
        if(test.loggedInUsers[i].getStatus() == "OUT"){
            test.loggedInUsers.erase(test.loggedInUsers.begin() + i);
        }
    }

    for(int i = 0; i < test.loggedInUsers.size(); i++){
        test.loggedInUsers[i].updateIndex(i);
    }

    cout << test.loggedInUsers[0].getMoney() << endl;
    cout << test.loggedInUsers[0].getName() << endl;
    cout << test.loggedInUsers[0].getIndex() << endl;
}
