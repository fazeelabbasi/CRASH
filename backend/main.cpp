//
// Created by User on 2019-10-07.
//

#include "main.h"
//#include "web/server.h"
#include "core/GameHost.h"
#include "core/User.h"
int main() {
    GameHost host;
    User adam = User("Adam");
    User doug = User("Doug");
    User stan = User("Stan");
    host.createRound();
    host.round.addParticipant(adam);
    host.round.addParticipant(doug);
    host.round.addParticipant(stan);
    printf("The winner is %s", host.playRound().name.c_str());
}
