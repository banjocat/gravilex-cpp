#include <iostream>
#include <sstream>
#include <fstream>
#include <cassert>
#include <string>
#include <vector>
#include "grid.h"
#include "player.h"
#include "humanplayer.h"
#include "computerplayer.h"
#include "game.h"
//#define DEBUG
#include "error.h"

using namespace std;

Game::Game(Grid &one, Human &two, Computer &three)
  :computer(three), grid(one), human(two) {
}



bool Game::NotDone() {

  if (grid.GridFull())
    return false;

  return true;
}


void Game::ReadTestDriver(const char *filename) {

    ifstream infile;
    string input = "";

    infile.open(filename);

    assert(infile);

    for (int i = 0; i < 6; i++) {
      string line = "";
      getline(infile, line);
      input.append(line);
      input.push_back('\n');
    }

    grid.WriteToGrid(input);

    getline(infile, input);
    human.ReadLetters(input);
    getline(infile, input);
    computer.ReadLetters(input);
    int score = 0;

    infile >> score;
    human.AddScore(score);
    infile >> score;
    computer.AddScore(score);

    infile.close();
}

string Game::Over() {

  stringstream output("");

  output <<  "Game over." << endl;
  
  if (human.GetScore() > computer.GetScore()) {
    output << "You win!" << endl;
  }
  else if (human.GetScore() < computer.GetScore()) {
    output << "I win!" << endl;
  }
  else {
    output << "We have tied!" << endl;
  }

  return output.str();
}

string Game::PointsScored(int points) {

  stringstream output("");

  output << "Points scored on this turn: " << points;
  return output.str();

}

void Game::GameRound() { 

  int cpoints, hpoints = 0;

  hpoints = HumanTurn();

  cout << PointsScored(hpoints) << endl; 

  cpoints = ComputerTurn();
  cout << PointsScored(cpoints) << endl;

  human.AddScore(hpoints);
  computer.AddScore(cpoints);

  ReportScore();
}

int Game::ComputerTurn()  {


  cout << grid.StringGrid() << endl;
  cout << "Letters remaining to me:" << endl;
  computer.ShowLetters();

  computer.MakeAMove(grid);

  char letter = computer.GetLetter();
  int col = computer.GetCol();

  cout << "I will drop the letter " << letter << " in column " << col << endl;
  grid.DropLetter(letter, col);

  // Remove computer's letter they just played.
  computer.RemoveLetter(letter);

  cout << grid.StringGrid() << endl;

  // Get the words the computer will be playing
  vector<string> computerwords = computer.GetWords();

  int length = computerwords.size();

  int points = 0;

  

  for (int i = 0; i < length; i++) {

    if (grid.WordInGrid(computerwords[i]))  {
      
      stringstream msg("");
      points += grid.HowManyPoints(computerwords[i].length());
      msg << "I claim the word: " << computerwords[i];
      cout << msg.str() << endl;
    }
  
  }


  return points;

}



int Game::HumanTurn() {


  // Defensive to avoid infite loop if odd reason grid is filled
  if (grid.GridFull() == true)
    return 0;

  // Report the grid to the player
  cout << grid.StringGrid() << endl;
 
  // Gets a valid letter and col.. then drops it in the grid.
  char letter = human.GetLetter();

  int col =  human.GetCol(grid);

  debug("Got human col " << col);

  grid.DropLetter(letter, col);


  // Does the human want to declare a word?
  // Returns 0 if no points

  int totalpoints = human.DeclareWords(grid, computer);
  

  return totalpoints;
}




void Game::ReportScore() {

  stringstream output;

  output.str("");

  output << "Score so far: You=" << human.GetScore() << " Me=" << computer.GetScore();
  
  cout << output.str() << endl;
}
