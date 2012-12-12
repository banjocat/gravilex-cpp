#include <string>
#include <vector>

/* This is the base class of the human and computer player.
 * Because they shared a lot this class was created
 */


class Player {

 public:
  int GetScore() const;  //

  int AddScore(int rewards); // 


  // Reads letters from TestFile
  void ReadLetters(std::string line);  

  // SHows the letters computer or human
  void ShowLetters();

  // Remove a letter from avaiable letters
  void RemoveLetter(char c);

  
 protected:
  
  // Checks if a letter is able to be player
  bool FreeLetter(char c); 

  // Counts to see how many of those letters is had
  // Will count any letter not just vowels
  int VowelCount(char c);

  

  // Sets up the letters aka resets them
  void SetUpLetters();

  // Checks if a letter is a vowe.l
  bool IsVowel(char c); 

  // Human or Computer score
  int score;

  // Lowercases an entire word
  void LowerCaseIt(std::string &word); //

  // Use to keep track of words already played
  //bool UsedWord(std::string word); 
  std::vector<std::string> wordsplayed;
  
  

 private:

  // Letters able to be played
  std::vector<char> lettersfree;

  // Checks if the char is the last letter
  // Used to avoid the extra space at the end
  bool LastLetter(char);

  
 
};
