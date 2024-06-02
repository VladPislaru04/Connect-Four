#include "RandomAIPlayer.hpp"


RandomAIPlayer::RandomAIPlayer(std::string const& name, char const ID) : Player(name, ID) {}

int RandomAIPlayer::chooseMove(int length, std::vector<std::string> const& state) {
	srand(time(0));
    int choice = 1 + (rand() % length);
    int steps = 0;
    while (!checkMove(length, choice, state)) {
        steps++;
        if (steps > 100) {
            return -1;
        }
        choice = 1 + (rand() % length);
    }
    return choice;
}

std::shared_ptr<Player> RandomAIPlayer::clone() const {
	return std::make_shared<RandomAIPlayer>(*this);
}