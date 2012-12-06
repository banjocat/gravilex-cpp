#include <vector>
#include <string>

class Grid;

class Computer: public Player {

 public:

  // Constructors
  Computer(const char *filename);


  // Computer starts its move
  // When it is done it will place it's move
  // In col and letter variables
  // Then the grid can ask for them.
  // It will also place all the words it will play
  // In a vector.
  void MakeAMove(Grid grid);

  // Get Col of computer move
  int GetCol();

  // Get letter computer will play
  char GetLetter();

  // List of words computer will claim
  std::vector<std::string> GetWords();

  // If the computer knows the word
  // The computer accusing player
  // Of playing a word not known in dictionary file
  bool ComputerKnowsWord(std::string);
   
 private:
  // Filename for word list
  char const *dictionary;

  // List of words read from dictionary
  std::vector<std::string> words;

  // Read words from dictionary file and set them to words
  void ReadInWords();

  // If the word is acceptable fix it if it can be
  bool WordAcceptable(std::string &);

  //debugging only
  // Outputs all the words the computer knows
  void ReportWords();

  // Does the computer only have vowels?
  // Used to for when no words are going to be spelled.
  // Checks for if comp going to have to play a vowel.
  bool OnlyVowels();

  // Choose a letter based on the preference of ABC order
  // Used if no word can be spelled
  char AbcPreference();

  // Remove structure vector of choices
  void ClearChoice();

  // Now that we have a list of possible moves which is better?
  void MakeChoice();

  // Is there an adjacent letter to this move?
  bool HasAdjacentLetters(Grid grid, int x);

  // Try a letter and see how many points from it
  void TryLetter(Grid Realgrid, int x, const char c);

  // No word was spelled so find a letter that best plays
  void NoWord(Grid grid);
  
  // Debug only
  void ReportPossibles();
  
  // This is where the best move is stored for each turn.
  // The already defined choice is the computers final decision.
  // It will be -1 in values if no choice can be discovered.
  // -1 only happens when no words can be spelled.
  struct Choice {
    int col;
    char letter;
    int points;
    // The words the computer will claim points for
    std::vector<std::string> words;
  } choice;

  // Sets letter choice as best
  // Structure copy really
  void ThisChoice(Choice i);

  // This is where all the possible moves are stored.
  // Only point scoring moves are put here.
  // MakeChoice() is what is used to decide what is best play.
  std::vector<Choice> possibles;

};

