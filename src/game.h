
#include <string>

class Grid;
class Human;
class Computer;



class Game {

public:
  // Reads testdriver - skips if not provided
  void ReadTestDriver(const char *filename);

  // Starts the game
 Game(Grid&, Human&, Computer&);

 // Play one round of the game
 void GameRound();

 bool NotDone();

 std::string Over();

 
private:
 Human human;
 Computer computer;
 Grid grid;

 int WordKnown(std::string);

 // Turns based on type of player
 int HumanTurn();
 int ComputerTurn();

 void ReportScore();

 std::string PointsScored(int);
};
