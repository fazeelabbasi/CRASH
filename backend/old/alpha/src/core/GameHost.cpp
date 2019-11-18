#include "GameHost.h"
#include <random>
#include <sstream>

void GameHost::createRound() {
    round = Round();
}

Player& GameHost::playRound() {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<> roll(0, round.participants.size()-1);
    int index = roll(rng);
    Player& winner = *round.participants.at(index);
    return winner;
}
