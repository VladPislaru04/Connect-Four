#include <iostream>
#include "Player.hpp"

Player::Player() : playerName(""), playerID(ID1), isActive(false) {}

Player::Player(std::string const &name, char const ID) : playerName(name), playerID(ID) {
    isActive = ID == ID1 ? true : false;
}

Player::Player(char const ID) : playerName("Player"), playerID(ID) {
    if (ID == ID1)
        playerName += "1";
    else playerName += "2";
    isActive = ID == ID1 ? true : false;
}

std::string Player::getPlayerName() {
    return playerName;
}

char Player::getPlayerID () {
    return playerID;
}

std::ostream& operator<< (std::ostream& out, Player const &player)
{
    out << "Player name: " << player.playerName << "\n";
    out << "Is Active: ";
    (player.isActive) ? out << "YES\n" : out << "NO\n";
    out << "Player's ID: " << player.playerID;
    return out;
}

int  Player::chooseMove(int length) {
    return 1;
}
