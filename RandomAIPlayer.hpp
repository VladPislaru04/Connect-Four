#include "Player.hpp"

class RandomAIPlayer : public Player {
public:
	explicit RandomAIPlayer(std::string const& name, char const ID);
	int chooseMove(int length, std::vector<std::string> const& state) override;
	std::shared_ptr<Player> clone() const override;
};

