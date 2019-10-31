//
// Created by User on 2019-10-07.
//

#ifndef AVATAR_ROUND_H
#define AVATAR_ROUND_H
#include "RoundStatus.h"
#include "Player.h"
#include <vector>

class Round {
public:
    Round(std::vector<User> participants);
    Round();
    void addParticipant(User &user);
    std::vector<User> participants;
    int roundNumber;
    RoundStatus status;
    int endTime;

};


#endif //AVATAR_ROUND_H
