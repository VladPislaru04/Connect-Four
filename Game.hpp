#include "Board.hpp"


class Game {

private:
    Board board;
    std::shared_ptr<Player> playerOne;
    std::shared_ptr<Player> playerTwo;
public:
    Game();

    Game(Board const &newBoard, std::shared_ptr<Player> newPlayer1, std::shared_ptr<Player> newPlayer2);

    void gameWin(std::shared_ptr<Player> activePlayer);
    void gameDraw();

    void startGame();
    int restartGame();

    Game& operator=(const Game& other);

    ~Game();
};