//
// Created by User on 2019-10-07.
//

#ifndef AVATAR_GAMEHOST_H
#define AVATAR_GAMEHOST_H

#include "Round.h"

class GameHost {
public:
    Round round;
    void init();
    void createRound();
    User& playRound();
};


#endif //AVATAR_GAMEHOST_H
