#pragma once

#include "RoundStatus.h"
#include "Round.fwd.h"
#include "Player.fwd.h"
#include <vector>

class Round {
public:
    Round(std::vector<Player*> participants);
    Round();
    void addParticipant(Player* user);
    std::vector<Player*> participants;
    int roundNumber;
    RoundStatus status;
    int endTime;

};