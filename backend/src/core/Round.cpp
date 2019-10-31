//
// Created by User on 2019-10-07.
//

#include "Round.h"
#include "Player.h"
#include <utility>

Round::Round(std::vector<Player*> participants) : participants(std::move(participants)) {}
Round::Round() : participants() {}

void Round::addParticipant(Player* user) {
    participants.push_back(user);
}
