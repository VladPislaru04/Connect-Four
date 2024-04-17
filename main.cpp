#include <iostream>
#include <vector>

class Player {
private:
	std::string playerName;
	char playerID;
	bool isActive;
public:
    static const char ID1 = 'X';
    static const char ID2 = 'O';
    Player() : playerName(""), playerID(ID1), isActive(false) {}

    Player(std::string const &name, char const ID) : playerName(name), playerID(ID) {
        isActive = ID == ID1 ? true : false;
    }

    explicit Player(char const ID) : playerName("Player"), playerID(ID) {
        if (ID == ID1)
            playerName += "1";
        else playerName += "2";
        isActive = ID == ID1 ? true : false;
    }

    std::string getPlayerName() {
        return playerName;
    }

    char getPlayerID () {
        return playerID;
    }

    friend std::ostream& operator<< (std::ostream& out, Player const &player)
    {
        out << "Player name: " << player.playerName << "\n";
        out << "Is Active: ";
        (player.isActive) ? out << "YES\n" : out << "NO\n";
        out << "Player's ID: " << player.playerID;
        return out;
    }
};


class Board {
private:
    int height, length;
    std::vector<std::string> state;
public:
    static const char EMPTY_CELL = '#';
    Board() {
        height = 6;
        length = 7;
        state.resize(height + 1);
        for (int i = 0; i < height; i++)
            for (int j = 0; j < length; j++)
                state[i] += Board::EMPTY_CELL;
    }
    Board(int const new_height, int const new_length) {
        height = new_height;
        length = new_length;
        state.resize(height);
        for (int i = 0; i < height; i++)
            for (int j = 0; j < length; j++)
                state[i] += Board::EMPTY_CELL;
    }
    friend std::ostream& operator<< (std::ostream& out, Board const &board)
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
    int checkFour(Player activePlayer) {
        char activePlayerID = activePlayer.getPlayerID();
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

    int makeMove(Player activePlayer) {

        int choice = 0, steps = 0;
        std::cout << activePlayer.getPlayerName()<< "'s Turn ";
        std::cout << "Please enter a number between 1 and " << length << ": ";
        std::cin  >> choice;
        if (choice == 0) {
            std::cout << "Wrong format!\n";
            return -1;
        }
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
            std::cout << "Please enter a number between 1 and " << length << ": ";
            std::cin  >> choice;
        }
        return choice;
    }
    void updateBoard(const int choice, Player activePlayer) {
        for (int i = height - 1; i >= 0; i--)
            if (state[i][choice] != Player::ID1 && state[i][choice] != Player::ID2) {
                state[i][choice] = activePlayer.getPlayerID();
                break;
            }
    }
    void reset() {
        for (int i = 0; i < height; i++)
            for (int j = 0; j < length; j++)
                state[i][j] = Board::EMPTY_CELL;
    }
    int isFull() {
        for (int j = 0; j < length; j++)
            if (state[0][j] == Board::EMPTY_CELL)
                return 0;
        return 1;
    }
};

class Game {

private:
    Board board;
    Player playerOne;
    Player playerTwo;
public:
    Game() : board(Board()), playerOne(Player(Player(Player::ID1))), playerTwo(Player(Player::ID2)) {}

    Game(Board const &newBoard, Player const &newPlayer1, Player const &newPlayer2)
    : board(newBoard), playerOne(newPlayer1), playerTwo(newPlayer2) {}

    void gameWin(Player activePlayer){
        std::cout << "\n" << activePlayer.getPlayerName() << " Connected Four, You Win!" << "\n";
    }
    void gameDraw() {
        std::cout << "\nThe board is full, it's a draw!" << "\n";
    }

    void startGame() {
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
    int restartGame() {
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
    ~Game() {
        std::cout << "Game over!\n";
    }
};


int main()
{
    std::string namePlayerOne, namePlayerTwo;
	std::cout << "Let's Play Connect 4" << "\n\n";
	std::cout << "Player One please enter your name: ";
	std::cin >> namePlayerOne;
	std::cout << "Player Two please enter your name: ";
	std::cin >> namePlayerTwo;

	Board board;
	Player playerOne(namePlayerOne, Player::ID1), playerTwo(namePlayerTwo, Player::ID2);
	Game game(board, playerOne, playerTwo);

	game.startGame();
    return 0;
}
