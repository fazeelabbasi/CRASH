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
        double getNetWorth();
        void setNetWorth(const double& assets);
        void updateIndex(const int& in);
        int getIndex();
        string getName();
        string getStatus();
        void setStatus(const string& stat);
    protected:

    private:
        string name;
        double moneyAmount, netWorth;
        string status;
        int index;
};

#endif // PLAYER_H