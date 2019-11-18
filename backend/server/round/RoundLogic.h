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
        void clientUpdate(const double& money, const string& username);
        int getRoundsPlayed();
        void playRound();
        Player getPlayer(const int& index);
        string getStatus();
        bool playerExists(const string& username);

        vector<Player> loggedInUsers;
        int roundsPlayed;
        string roundStatus;
        int validClients;
        int clientsFinished;
        int roundTimer;
    protected:

    private:


};

#endif // ROUNDLOGIC_H
