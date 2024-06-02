#include "HumanPlayer.hpp"

class SmartAIPlayer : public Player {
public:
	explicit SmartAIPlayer(std::string const& name, char const ID);
	int chooseMove(int length, std::vector<std::string> const& state) override;
	std::shared_ptr<Player> clone() const override;
private:
    int minMax(std::vector<std::string>& state, int depth, bool isMaximizing);
    int evaluateBoard(const std::vector<std::string>& state);
    bool isWinningMove(const std::vector<std::string>& state, char playerID);
    std::vector<int> generateMoves(const std::vector<std::string>& state);
    void makeMove(std::vector<std::string>& state, int col, char playerID);
    void undoMove(std::vector<std::string>& state, int col);
    bool isFull(const std::vector<std::string>& state);
    int scorePosition(int countPlayer, int countEmpty, int countOpponent);
    static const int MAX_DEPTH = 20; // Adjust this for difficulty
};

