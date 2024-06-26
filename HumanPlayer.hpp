
#include "RandomAIPlayer.hpp"

class HumanPlayer : public Player {
public:
	int chooseMove (int length, std::vector<std::string> const& state) override;

	explicit HumanPlayer(std::string const& name, char const ID);

	std::shared_ptr<Player> clone() const override;
};

