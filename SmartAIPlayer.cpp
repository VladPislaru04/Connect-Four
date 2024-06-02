#include "SmartAIPlayer.hpp"
#include <limits>


SmartAIPlayer::SmartAIPlayer(std::string const& name, char const ID) : Player(name, ID) {}

int SmartAIPlayer::chooseMove(int length, std::vector<std::string>const& state) {

    std::vector<std::string> aux_state = state;
    int bestMove = -1;
    int bestValue = std::numeric_limits<int>::min();
    
    for (int col : generateMoves(state)) {
        if (col > length)
            continue;
        makeMove(aux_state, col, playerID);
        int moveValue = minMax(aux_state, SmartAIPlayer::MAX_DEPTH, false);
        undoMove(aux_state, col);

        if (moveValue > bestValue) {
            bestMove = col;
            bestValue = moveValue;
        }
    }
    return bestMove + 1;
}

int SmartAIPlayer::minMax(std::vector<std::string>&state, int depth, bool isMaximizing) {
    if (depth == 0 || isWinningMove(state, playerID) || isWinningMove(state, playerID == 'X' ? 'O' : 'X')) {
        return evaluateBoard(state);
    }

    if (isMaximizing) {
        int maxEval = std::numeric_limits<int>::min();
        for (int col : generateMoves(state)) {
            makeMove(state, col, playerID);
            int eval = minMax(state, depth - 1, false);
            undoMove(state, col);
            maxEval = std::max(maxEval, eval);
        }
        return maxEval;
    }
    else {
        int minEval = std::numeric_limits<int>::max();
        for (int col : generateMoves(state)) {
            makeMove(state, col, playerID == 'X' ? 'O' : 'X');
            int eval = minMax(state, depth - 1, true);
            undoMove(state, col);
            minEval = std::min(minEval, eval);
        }
        return minEval;
    }
}

std::vector<int> SmartAIPlayer::generateMoves(const std::vector<std::string>& state) {
    std::vector<int> validMoves;
    for (int col = 0; col < (int) state[0].size(); ++col) {
        if (state[0][col] != 'X' && state[0][col] != 'O') {
            validMoves.push_back(col);
        }
    }
    return validMoves;
}

void SmartAIPlayer::makeMove(std::vector<std::string>& state, int col, char activePlayerID) {
    
    for (int row = 0; row < (int) (state.size() - 1); ++row) {
        if (state[row][col] != 'X' && state[row][col] != 'O') {
            state[row][col] = activePlayerID;
            break;
        }
    }
}

void SmartAIPlayer::undoMove(std::vector<std::string>& state, int col) {
    for (int row = (int) (state.size() - 2); row >= 0; --row) {
        if (state[row][col] == 'X' || state[row][col] == 'O') {
            state[row][col] = ' ';
            break;
        }
    }
}


bool SmartAIPlayer::isWinningMove(const std::vector<std::string>& state, char activePlayerID) {
    int rows = (int) (state.size() - 1);
    int cols = (int) (state[0].size());
   
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col + 3 < cols; ++col) {
            
            if (state[row][col] == activePlayerID && state[row][col + 1] == activePlayerID &&
                state[row][col + 2] == activePlayerID && state[row][col + 3] == activePlayerID) {
                return true;
            }
        }
    }
    for (int row = 0; row < rows - 3; ++row) {
        for (int col = 0; col < cols; ++col) {
            if (state[row][col] == activePlayerID && state[row + 1][col] == activePlayerID &&
                state[row + 2][col] == activePlayerID && state[row + 3][col] == activePlayerID) {
                return true;
            }
        }
    }
    for (int row = 3; row < rows; ++row) {
        for (int col = 0; col < cols - 3; ++col) {
            if (state[row][col] == activePlayerID && state[row - 1][col + 1] == activePlayerID &&
                state[row - 2][col + 2] == activePlayerID && state[row - 3][col + 3] == activePlayerID) {
                return true;
            }
        }
    }
    for (int row = 0; row < rows - 3; ++row) {
        for (int col = 0; col < cols - 3; ++col) {
            if (state[row][col] == activePlayerID && state[row + 1][col + 1] == activePlayerID &&
                state[row + 2][col + 2] == activePlayerID && state[row + 3][col + 3] == activePlayerID) {
                return true;
            }
        }
    }

    return false;
}


int SmartAIPlayer::scorePosition(int countPlayer, int countEmpty, int countOpponent) {
    int score = 0;
    if (countPlayer == 4) {
        score += 5000;
    }
    else if (countPlayer == 3 && countEmpty == 1) {
        score += 500;
    }
    else if (countPlayer == 2 && countEmpty == 2) {
        score += 100;
    }
    else if (countOpponent == 2 && countEmpty == 2) {
        score -= 100;
    }
    if (countOpponent == 3 && countEmpty == 1) {
        score -= 4;
    }
    if (countOpponent == 4) {
        score -= 5000;
    }
    return score;
}

int SmartAIPlayer::evaluateBoard(const std::vector<std::string>&state) {
    int score = 0;
    int rows = (int) (state.size() - 1);
    int cols = (int) (state[0].size());
    char opponentID = playerID == 'X' ? 'O' : 'X';

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols - 3; ++col) {
            int countPlayer = 0, countEmpty = 0, countOpponent = 0;
            for (int k = 0; k < 4; ++k) {
                if (state[row][col + k] == playerID) countPlayer++;
                else if (state[row][col + k] == ' ') countEmpty++;
                else if (state[row][col + k] == opponentID) countOpponent++;
            }
            score += scorePosition(countPlayer, countEmpty, countOpponent);
        }
    }

    for (int row = 0; row < rows - 3; ++row) {
        for (int col = 0; col < cols; ++col) {
            int countPlayer = 0, countEmpty = 0, countOpponent = 0;
            for (int k = 0; k < 4; ++k) {
                if (state[row + k][col] == playerID) countPlayer++;
                else if (state[row + k][col] == ' ') countEmpty++;
                else if (state[row + k][col] == opponentID) countOpponent++;
            }
            score += scorePosition(countPlayer, countEmpty, countOpponent);
        }
    }

    for (int row = 3; row < rows; ++row) {
        for (int col = 0; col < cols - 3; ++col) {
            int countPlayer = 0, countEmpty = 0, countOpponent = 0;
            for (int k = 0; k < 4; ++k) {
                if (state[row - k][col + k] == playerID) countPlayer++;
                else if (state[row - k][col + k] == ' ') countEmpty++;
                else if (state[row - k][col + k] == opponentID) countOpponent++;
            }
            score += scorePosition(countPlayer, countEmpty, countOpponent);
        }
    }

    for (int row = 0; row < rows - 3; ++row) {
        for (int col = 0; col < cols - 3; ++col) {
            int countPlayer = 0, countEmpty = 0, countOpponent = 0;
            for (int k = 0; k < 4; ++k) {
                if (state[row + k][col + k] == playerID) countPlayer++;
                else if (state[row + k][col + k] == ' ') countEmpty++;
                else if (state[row + k][col + k] == opponentID) countOpponent++;
            }
            score += scorePosition(countPlayer, countEmpty, countOpponent);
        }
    }

    return score;
}

std::shared_ptr<Player> SmartAIPlayer::clone() const {
	return std::make_shared<SmartAIPlayer>(*this);
}