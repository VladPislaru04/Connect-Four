#include "Board.hpp"

    Board::Board() {
        height = 6;
        length = 7;
        state.resize(height + 1);
        for (int i = 0; i < height; i++)
            for (int j = 0; j < length; j++)
                state[i] += Board::EMPTY_CELL;
    }
    Board::Board(int const new_height, int const new_length) {
        height = new_height;
        length = new_length;
        state.resize(height);
        for (int i = 0; i < height; i++)
            for (int j = 0; j < length; j++)
                state[i] += Board::EMPTY_CELL;
    }
    std::ostream& operator<< (std::ostream& out, Board const &board)
    {
       for (int i = 0; i < board.height; i++) {
            out << "|";
            for (int j = 0; j < board.length; j++)
                out << board.state[i][j];
            out << "|";
            out << "\n";
        }
        return out;
    }
    int Board::checkFour(std::shared_ptr<Player> activePlayer) {
        char activePlayerID = activePlayer -> getPlayerID();
        int win = 0;
        for(int i = height - 1; i >= 0; i--)
        {
            for(int j = length - 1; j >= 0; j-- )
            {

                /// check horizontal
                if(j >= 3 && state[i][j] == activePlayerID && state[i][j-1] == activePlayerID &&
                    state[i][j-2] == activePlayerID && state[i][j-3] == activePlayerID) {

                    win = 1;
                }

                /// check vertical
                if(i >= 3 && state[i][j] == activePlayerID && state[i-1][j] == activePlayerID &&
                    state[i-2][j] == activePlayerID && state[i-3][j] == activePlayerID) {

                    win = 1;
                }

                /// check diagonal going bottom left to top right
                if(i >= 3 && j >= 3 && state[i][j] == activePlayerID && state[i-1][j-1] == activePlayerID &&
                    state[i-2][j-2] == activePlayerID && state[i-3][j-3] == activePlayerID) {

                    win = 1;
                }

                /// check diagonal going bottom right to top left
                if(i >= 3 && j + 3 < length && state[i][j] == activePlayerID && state[i-1][j+1] == activePlayerID &&
                    state[i-2][j+2] == activePlayerID && state[i-3][j+3] == activePlayerID) {

                    win = 1;
                }

            }
        }

        return win;
    }

    int Board::makeMove(std::shared_ptr<Player> activePlayer) {

        int choice = activePlayer -> chooseMove(length);
        int steps = 0;
        while(choice < 1 || choice > length || state[0][choice - 1] == Player::ID1 || state[0][choice - 1] == Player::ID2) {

            steps++;
            if (steps > 100) {
                std::cout << "Too many wrong tries!\n";
                return -1;
            }

            if (choice < 1 || choice > length) {
                std::cout << "The column inserted is not correct!\n";
            }
            else if (state[0][choice - 1] == Player::ID1 || state[0][choice - 1] == Player::ID2) {
                std::cout << "That column is full\n";
            }
            choice = activePlayer -> chooseMove(length);
        }
        return choice;
    }
    void Board::updateBoard(const int choice, std::shared_ptr<Player> activePlayer) {
        for (int i = height - 1; i >= 0; i--)
            if (state[i][choice] != Player::ID1 && state[i][choice] != Player::ID2) {
                state[i][choice] = activePlayer -> getPlayerID();
                break;
            }
    }
    void Board::reset() {
        for (int i = 0; i < height; i++)
            for (int j = 0; j < length; j++)
                state[i][j] = Board::EMPTY_CELL;
    }
    int Board::isFull() {
        for (int j = 0; j < length; j++)
            if (state[0][j] == Board::EMPTY_CELL)
                return 0;
        return 1;
    }