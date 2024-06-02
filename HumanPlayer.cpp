#include "HumanPlayer.hpp"


HumanPlayer::HumanPlayer(std::string const& name, char const ID) : Player(name, ID) {}


int HumanPlayer::chooseMove (int length) {
    int choice = 0, steps = 0;
    std::cout << Player::playerName << "'s Turn ";
    std::cout << "Please enter a number between 1 and " << length << ": ";
    std::cin >> choice;
    if (choice <= 0) {
        std::cout << "Wrong format!\n";
        return -1;
    }
    return choice;
}

std::shared_ptr<Player> HumanPlayer::clone() const {
    return std::make_shared<HumanPlayer>(*this);
}