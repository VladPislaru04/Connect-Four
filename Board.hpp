#include <vector>
#include "HumanPlayer.hpp"

class Board {
private:
    int height, length;
    std::vector<std::string> state;
public:
    static const char EMPTY_CELL = '#';
    Board();
    Board(int const new_height, int const new_length);
    friend std::ostream& operator<< (std::ostream& out, Board const &board);
    int checkFour(std::shared_ptr<Player> activePlayer);

    int makeMove(std::shared_ptr<Player> activePlayer);
    void updateBoard(const int choice, std::shared_ptr<Player> activePlayer);
    void reset();
    int isFull();
};