#include <iostream>
#include <vector>
#include <memory>

class Player {

protected:
	std::string playerName;
	char playerID;
	bool isActive;
public:
    static const char ID1 = 'X';
    static const char ID2 = 'O';
    


    Player();

    Player(std::string const &name, char const ID);

    virtual std::shared_ptr<Player> clone() const = 0;

    Player& operator=(const Player& other) = default;

    virtual ~Player() = default;

    explicit Player(char const ID);

    std::string getPlayerName();

    char getPlayerID();

    bool checkMove(int length, int choice, std::vector<std::string> state);

    friend std::ostream& operator<< (std::ostream& out, Player const &player);

    virtual int chooseMove(int length, std::vector<std::string> state) = 0;
};