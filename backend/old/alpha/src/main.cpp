//
// Created by User on 2019-10-07.
//

#include "main.h"
//#include "web/server.h"
#include "core/GameHost.h"
#include "core/Player.h"
#include "web/Server.h"
#include "web/Client.h"

int main() {
    GameHost host;
    Player adam = Player("Adam");
    Player doug = Player("Doug");
    Player stan = Player("Stan");
    host.createRound();
    host.round.addParticipant(&adam);
    host.round.addParticipant(&doug);
    host.round.addParticipant(&stan);
    printf("The winner is %s", host.playRound().name.c_str());
//    begin();
    Client c;
    c.fetch();
}
