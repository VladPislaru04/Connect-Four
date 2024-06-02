#include <iostream>
#include <vector>
#include "Game.hpp"


int main()
{
    std::string namePlayerOne, namePlayerTwo;
	std::cout << "Let's Play Connect 4" << "\n\n";
	std::cout << "Player One please enter your name: ";
	std::cin >> namePlayerOne;
	std::cout << "Player Two please enter your name: ";
	std::cin >> namePlayerTwo;

	Board board;
	HumanPlayer playerOne(namePlayerOne, Player::ID1);
	SmartAIPlayer playerTwo(namePlayerTwo, Player::ID2);
	Game game(board, playerOne.clone(), playerTwo.clone());

	game.startGame();
    return 0;
}
