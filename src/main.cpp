//This is where the main file is located


#include <iostream>
#include "grid.h"
#include "player.h"
#include "humanplayer.h"
#include "computerplayer.h"
#include "game.h"

using namespace std;


void RunGame(int argc, const char *argv[]);


int main (int argc, const char* argv[]) {

  // If dictionary file is not given
  if (argc <= 1) {
    cout << "Usage: gameexecutable dictionaryFile [setupFile]" << endl;;
    return 0;
  }
  

  RunGame(argc, argv);

  return 0;
}





void RunGame(int argc, const char* argv[]) {

  // Make the game and add the grid and players to it.
  Grid grid;
  Human human;
  Computer computer(argv[1]);
  Game game(grid, human, computer);

  bool test = false;

  if (argc == 3) {
    test = true;
    game.ReadTestDriver(argv[2]);
  }


  while (game.NotDone()) {

    game.GameRound();

    // If this is a test run just play one round.
    if (test) {
      // End game here if it's a test.
      break;
    }
  } 

  // end game here;
  // I had to put this check in here just for the tester
  // Otherwise it would announce the winner at the end of every test
  // I couldn't just put !test then it would never announce a winner!
  if (!game.NotDone()) {
    cout << game.Over();
  }

}








