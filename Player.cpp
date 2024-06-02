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


bool Player::checkMove(int length, int choice, std::vector<std::string> state) {
    if (choice < 1 || choice > length || state[0][choice - 1] == Player::ID1 || state[0][choice - 1] == Player::ID2) {
        if (choice < 1 || choice > length) {
            std::cout << "The column inserted is not correct!\n";
        }
        else if (state[0][choice - 1] == Player::ID1 || state[0][choice - 1] == Player::ID2) {
            std::cout << "That column is full\n";
        }
        return false;
    }        
    return true;
}
