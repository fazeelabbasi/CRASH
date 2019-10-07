//
// Created by User on 2019-10-07.
//

#ifndef AVATAR_ROUND_H
#define AVATAR_ROUND_H

#include "User.h"
#include <vector>

class Round {
public:
    Round(std::vector<User> participants);
    Round();
    void addParticipant(User &user);

public:
    std::vector<User> participants;
};


#endif //AVATAR_ROUND_H
