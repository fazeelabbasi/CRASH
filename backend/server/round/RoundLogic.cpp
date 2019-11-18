#include "RoundLogic.h"
#include <string>
#include <vector>
#include "Player.h"
#include "StockGenerator.h"
#include <iostream>
#include <thread>
#include <random>
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

void RoundLogic::clientUpdate(const double& money, const string& username)
{
    // Now accepts a username and money, directly sets the money in the array
    if(playerExists(username)) {
        for (int i = 0; i < loggedInUsers.size(); i++) {
            if (loggedInUsers[i].getName() == username) {
                loggedInUsers[i].updateMoney(money);
                if (money < 1) {
                    loggedInUsers[i].setStatus(false);
                    cout << "Set to false due to bankruptcy: " << loggedInUsers[i].getName() << endl;
                } else {
                    loggedInUsers[i].setStatus(true);
                }
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

        // Change avg return and volatility values here
        StockGenerator roundInfo(0.002, 0.01);

        // tellClientsRoundInfo(roundInfo);

        // untested
        for(int i = 0; i < loggedInUsers.size(); i++) {
            cout << loggedInUsers[i].getStatus() << endl;
            if (loggedInUsers[i].getStatus()) {
                validClients++;
                /* Increments the valid client tracker and sets the status to OUT
                 * The status should be set back to "IN" in the clientUpdate method
                 * All clients that are still "OUT" (have not been updated) are removed
                 */
                loggedInUsers[i].setStatus(false);
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
            if(loggedInUsers[i].getStatus() == false) {
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

/*int main() {
    srand(1);
    RoundLogic t;
    for(int round = 1; round < 5; round++) {
        cout << "Current round: " << round << endl;
        t.clientsFinished = 0;
        t.validClients = 0;
        this_thread::sleep_for(chrono::seconds(1));
        if(round == 1) {
            t.clientLogin("player1");
            t.clientLogin("player2");
            t.clientLogin("player3");
            t.clientLogin("player4");
            t.clientLogin("player5");
            cout << "Logged in players 1 to 5 on round " << round << endl;
        }
        for(int i = 0; i < t.loggedInUsers.size(); i++) {
            cout << "Status of player " << i;
            cout << ": " << t.loggedInUsers[i].getStatus() << endl;
            if (t.loggedInUsers[i].getStatus()) {
                t.validClients++;
                t.loggedInUsers[i].setStatus(false);
            }
        }
        t.clientUpdate((double)((rand() % 100) - 30), "player1");
        t.clientUpdate((double)((rand() % 100) - 10), "player2");
        t.clientUpdate((double)((rand() % 100) - 10), "player3");
        t.clientUpdate((double)((rand() % 100) - 80), "player4");
        if (round < 2) {
            t.clientUpdate((double)(rand() % 100), "player5");
        }
        cout << "Waiting for requests..." << endl;
        while(t.clientsFinished < t.validClients && t.roundTimer < 5) {
            this_thread::sleep_for(chrono::seconds(1));
            t.roundTimer++;
        }
        for(int i = 0; i < t.loggedInUsers.size(); i++) {
            cout << "Post-update status of Player " << t.loggedInUsers[i].getName();
            cout << ": " << t.loggedInUsers[i].getStatus() << endl;
        }
        for(int i = 0; i < t.loggedInUsers.size(); i++) {
            cout << "Post-update money of Player " << t.loggedInUsers[i].getName();
            cout << ": " << t.loggedInUsers[i].getMoney() << endl;
        }
        for(int i = 0; i < t.loggedInUsers.size(); i++) {
            if(t.loggedInUsers[i].getMoney() < 1 || t.loggedInUsers[i].getStatus() == false) {
                cout << "Pending deletion: " << t.loggedInUsers[i].getName() << endl;
            }
        }
        for(int i = 0; i < t.loggedInUsers.size(); i++) {
            if(t.loggedInUsers[i].getStatus() == false) {
                // UNTESTED
                cout << "Deleted player: " << t.loggedInUsers[i].getName() << endl;
                t.loggedInUsers.erase(t.loggedInUsers.begin() + i);

            }
        }
    }
}*/
