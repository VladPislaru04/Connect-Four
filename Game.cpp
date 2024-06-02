#include "Game.hpp"



///Game::Game() : board(Board()), playerOne{ Player(Player::ID1) }, Player(Player::ID2).clone() {}

Game::Game(Board const &newBoard, std::shared_ptr<Player> newPlayer1, std::shared_ptr<Player> newPlayer2) : board(newBoard), 
                                                                                           playerOne(std::move(newPlayer1)),
                                                                                           playerTwo(std::move(newPlayer2)) {}

void Game::gameWin(std::shared_ptr<Player> activePlayer){
    std::cout << "\n" << activePlayer -> getPlayerName() << " Connected Four, You Win!" << "\n";
}
void Game::gameDraw() {
    std::cout << "\nThe board is full, it's a draw!" << "\n";
}

void Game::startGame() {
    std::cout << board << "\n";
    int again = 0;
    while (again != 2) {
        int choice = board.makeMove(playerOne);
        if (choice != -1) {
            board.updateBoard(choice - 1, playerOne);
            std::cout << board << "\n";
        }
        else {
            std::cout << "Too many wrong tries!\n";
            break;
        }

        if (board.checkFour(playerOne))
        {
            gameWin(playerOne);
            again = restartGame();
            if (again == 2)
            {
                break;
            }
        }

        choice = board.makeMove(playerTwo);
        board.updateBoard(choice - 1, playerTwo);

        std::cout << board << "\n";
        if (board.checkFour(playerTwo))
        {
            gameWin(playerTwo);
            again = restartGame();
            if (again == 2)
            {
                break;
            }
        }
        if (board.isFull())
        {
            gameDraw();
            again = restartGame();
        }
    }
}
int Game::restartGame() {
    int restart;
    std::cout << "Would you like to play again? Yes(1) No(2): ";
    std::cin  >> restart;
    if (restart == 1){
        board.reset();
        return restart;
    }
    else {
        std::cout << "Thanks for playing!" << "\n";
    }
    return 2;
}
Game::~Game() {
    std::cout << "Game over!\n";
}
