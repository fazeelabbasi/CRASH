//
// Created by User on 2019-10-07.
//

#ifndef AVATAR_GAMEHOST_H
#define AVATAR_GAMEHOST_H

#include "Round.h"
#include <string>
#include <vector>

class GameHost {
public:
    Round round;
    void init();
    void createRound();
    Player& playRound();
private:
    std::vector<std::string> hashedPasswords;
};


#endif //AVATAR_GAMEHOST_H
