//
// Created by User on 2019-10-07.
//

#ifndef AVATAR_PLAYER_H
#define AVATAR_PLAYER_H

#include <string>
#include "Round.h"

class Player {
public:
    Player(const std::string &name);

    std::string name;
    float money;
    Round roundsPlayed[];
    PlayerStatus status;
    float netWorth;

};


#endif //AVATAR_PLAYER_H
