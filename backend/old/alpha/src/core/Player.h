//
// Created by User on 2019-10-07.
//

#pragma once

#include "Player.fwd.h"
#include <string>
#include "Round.fwd.h"
#include "PlayerStatus.h"
#include <vector>
class Player {
public:
    Player(const std::string &name);

    std::string name;
    float money;
    std::vector<Round*> roundsPlayed;
    PlayerStatus status;
    float netWorth;

};
