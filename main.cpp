#include <bits/stdc++.h>
using namespace std;

class Player{
private:
	string playerName;
	char playerID;
	bool isActive;
public:
    Player() {
        playerName = "";
        isActive = false;
    }

    Player(char ID) {
        playerName = "Player" + ID;
        playerID = ID;
    }

    void setPlayerName(const string name) {
        playerName = name;
    }

    string getPlayerName() {
        return playerName;
    }

    void setPlayerID(const char ID) {
        playerID = ID;
    }

    char getPlayerID () {
        return playerID;
    }
    friend std::ostream& operator<< (std::ostream& out, const Player& player)
    {
        out << player.playerName;
        return out;
    }
};


class Board {
private:
    int height, length;
    vector<string> state;
public:
    Board() {
        height = 6;
        length = 7;
        state.resize(height + 1);
        for (int i = 0; i < height; i++)
            for (int j = 0; j < length; j++)
                state[i] += '#';
    }
    Board(int new_height, int new_length) {
        height = new_height;
        length = new_length;
        state.resize(height);
        for (int i = 0; i < height; i++)
            for (int j = 0; j < length; j++)
                state[i] += '#';
    }
    void displayBoard() {
        for (int i = 0; i < height; i++) {
            cout << "|";
            for (int j = 0; j < length; j++)
                cout << state[i][j];
            cout << "|";
            cout << "\n";
        }
        cout << "\n";
    }
    friend std::ostream& operator<< (std::ostream& out, const Board& board)
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
            for(int j = length; j >= 0; --j )
            {
                if(i >= 3 && j >= 3 && state[i][j] == activePlayerID && state[i-1][j-1] == activePlayerID &&
                    state[i-2][j-2] == activePlayerID && state[i-3][j-3] == activePlayerID) {

                    win = 1;
                }

                if(j >= 3 && state[i][j] == activePlayerID && state[i][j-1] == activePlayerID &&
                    state[i][j-2] == activePlayerID && state[i][j-3] == activePlayerID) {

                    win = 1;
                }

                if(i >= 3 && state[i][j] == activePlayerID && state[i-1][j] == activePlayerID &&
                    state[i-2][j] == activePlayerID && state[i-3][j] == activePlayerID) {

                    win = 1;
                }

                if(i >= 3 && j + 3 < length && state[i][j] == activePlayerID && state[i-1][j+1] == activePlayerID &&
                    state[i-2][j+2] == activePlayerID && state[i-3][j+3] == activePlayerID) {

                    win = 1;
                }

                if (j + 3 < length && state[i][j] == activePlayerID && state[i][j+1] == activePlayerID &&
                     state[i][j+2] == activePlayerID && state[i][j+3] == activePlayerID) {
                    win = 1;
                }
            }
        }

        return win;
    }

    int makeMove(Player activePlayer) {

        int choice, steps = 0;
        cout << activePlayer.getPlayerName()<< "'s Turn ";
        cout << "Please enter a number between 1 and " << length << ": ";
        cin  >> choice;
        if (choice == 0) {
            cout << "Wrong format!\n";
            return -1;
        }
        while(choice < 1 || choice > length || state[0][choice - 1] == 'X' || state[0][choice - 1] == 'O') {

            steps++;
            if (steps > 100) {
                cout << "Too many wrong tries!\n";
                return -1;
            }

            if (choice < 1 || choice > length) {
                cout << "The column inserted is not correct!\n";
            }
            else if (state[0][choice - 1] == 'X' || state[0][choice - 1] == 'O') {
                cout << "That column is full\n";
            }
            cout << "Please enter a number between 1 and " << length << ": ";
            cin  >> choice;
        }
        return choice;
    }
    void updateBoard(int choice, Player activePlayer) {
        for (int i = height - 1; i >= 0; i--)
            if (state[i][choice] != 'X' && state[i][choice] != 'O') {
                state[i][choice] = activePlayer.getPlayerID();
                break;
            }
    }
    void reset() {
        for (int i = 0; i < height; i++)
            for (int j = 0; j < length; j++)
                state[i][j] = '#';
    }
    int isFull() {
        for (int j = 0; j < length; j++)
            if (state[0][j] == '#')
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
    Game() {
        board = Board();
        playerOne = Player('X');
        playerTwo = Player('O');
    }
    Game(Board newBoard, Player newPlayer1, Player newPlayer2) {
        board = newBoard;
        playerOne = newPlayer1;
        playerTwo = newPlayer2;
    }
    void gameWin(Player activePlayer){
        cout << "\n" << activePlayer.getPlayerName() << " Connected Four, You Win!" << "\n";
    }
    void gameDraw() {
        cout << "\nThe board is full, it's a draw!" << "\n";
    }

    void startGame() {
        cout << board << "\n";
        int again = 0;
        while (again != 2) {
            int choice = board.makeMove(playerOne);
            if (choice != -1) {
                board.updateBoard(choice - 1, playerOne);
                cout << board << "\n";
            }
            else {
                cout << "Too many wrong tries!\n";
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

            cout << board << "\n";
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
        cout << "Would you like to play again? Yes(1) No(2): ";
        cin  >> restart;
        if (restart == 1){
            board.reset();
            return restart;
        }
        else cout << "Thanks for playing!" << "\n";
        return 2;
    }
    ~Game() {
        cout << "Game over!\n";
    }
};


int main()
{
	Player playerOne, playerTwo;
	Board board;
    string namePlayerOne, namePlayerTwo;
	cout << "Let's Play Connect 4" << "\n\n";
	cout << "Player One please enter your name: ";
	cin  >> namePlayerOne;
	playerOne.setPlayerName(namePlayerOne);
	playerOne.setPlayerID('X');
	cout << "Player Two please enter your name: ";
	cin  >> namePlayerTwo;
	playerTwo.setPlayerName(namePlayerTwo);
	playerTwo.setPlayerID('O');
	Game game(board, playerOne, playerTwo);
	cout << board << "\n";
	game.startGame();
    return 0;
}
