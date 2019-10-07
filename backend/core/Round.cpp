//
// Created by User on 2019-10-07.
//

#include "Round.h"

#include <utility>

Round::Round(std::vector<User> participants) : participants(std::move(participants)) {}
Round::Round() : participants() {}

void Round::addParticipant(User& user) {
    participants.push_back(user);
}
