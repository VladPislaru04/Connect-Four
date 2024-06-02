#include "RandomAIPlayer.hpp"


RandomAIPlayer::RandomAIPlayer(std::string const& name, char const ID) : Player(name, ID) {}

int RandomAIPlayer::chooseMove(int length) {
	srand(time(0));
	return 1 + (rand() % length);
}

std::shared_ptr<Player> RandomAIPlayer::clone() const {
	return std::make_shared<RandomAIPlayer>(*this);
}