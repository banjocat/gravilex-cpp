#include <vector>

// The human class deals with all things of the human player
// Getting characters and cols
// It is here it will check for actual logic to 
// make sure the right data is given.
// It inherits the player class

class Grid;
class Computer;

class Human: public Player {

 public:

  Human();
  // Gets the letter to play
  char GetLetter();

  // Get the col to play
  int GetCol(Grid grid);

  // Get word that player is saying points.
  std::string GetWord();

  // Reached the EOF so display msg and exit
  void ReachedEOF();


  // Gets words human is to declare for points.
  // Returns the amount of points scored.
  int DeclareWords(Grid grid, Computer computer);
  
 private:
  // If the word is acceptable for points.
  bool WordAcceptable(std::string word);

  // Extracts the first word of a line
  std::string FirstWord(std::string);

  // Removes all spaces including '\n' from the input stream
  void IgnoreSpaces();

  // Talks to computer
  // Sees if the computer knows the word to be played.
  int WordKnown(std::string, Grid grid, Computer computer);

 
};
