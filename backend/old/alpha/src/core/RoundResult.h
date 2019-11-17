//
// Created by Michael on 31/10/2019.
//

#ifndef AVATAR_ROUNDRESULT_H
#define AVATAR_ROUNDRESULT_H

class RoundResult {
public:
    RoundResult(Round, Player, ResultType);
    Round round;
    Player player;
    ResultType result;
};

#endif //AVATAR_ROUNDRESULT_H
