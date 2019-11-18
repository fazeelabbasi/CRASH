#ifndef ROUNDLOGIC_H
#define ROUNDLOGIC_H
#include <string>
#include <vector>
#include "Player.h"

using namespace std;

class RoundLogic
{
    public:
        RoundLogic();
        virtual ~RoundLogic();
        void clientLogin(const string& username);
        void clientUpdate(const Player& user);
        int getRoundsPlayed();
        void playRound();
        Player getPlayer(const int& index);
        string getStatus();
    protected:

    private:
        vector<Player> loggedInUsers;
        int roundsPlayed;
        string roundStatus;
        int validClients;
        int clientsFinished;
        int roundTimer;
};

#endif // ROUNDLOGIC_H
