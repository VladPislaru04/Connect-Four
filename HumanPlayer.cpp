#include "HumanPlayer.hpp"


HumanPlayer::HumanPlayer(std::string const& name, char const ID) : Player(name, ID) {}


int HumanPlayer::chooseMove (int length, std::vector<std::string> state) {
    int choice = 0;
    std::cout << Player::playerName << "'s Turn ";
    std::cout << "Please enter a number between 1 and " << length << ": ";
    std::cin >> choice;
    int steps = 0;
    while (!checkMove(length, choice, state)) {
        steps++;
        if (steps > 100) {
            return -1;
        }
        std::cout << "Please enter a number between 1 and " << length << ": ";
        std::cin >> choice;
    }
    return choice;
}

std::shared_ptr<Player> HumanPlayer::clone() const {
    return std::make_shared<HumanPlayer>(*this);
}