#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <vector>

using namespace std;

class Player
{
    public:
        Player();
        Player(const string& username);
        Player(const Player& copy);
        virtual ~Player();
        void updateMoney(const double& money);
        double getMoney();
        void updateIndex(const int& in);
        int getIndex();
        string getName();
        bool getStatus();
        void setStatus(const bool& stat);
    protected:

    private:
        string name;
        double moneyAmount, netWorth;
        bool status;
        int index;
};

#endif // PLAYER_H
