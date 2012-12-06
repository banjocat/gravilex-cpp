#include <iostream>
#include <vector>
#include <string>
#include <cassert>
//For checking types
#include <cctype>
#include <fstream>
//For rand()
#include <cstdlib>
#include "player.h"
#include "computerplayer.h"
#include "grid.h"
//#define DEBUG
#include "error.h"

using namespace std;


enum e_const{INVALID = -1, DIRECTIONS = 4};

Computer::Computer(const char *filename) {
  
  score = 0;

  dictionary = filename;

  wordsplayed.clear();
  SetUpLetters();

 
  ClearChoice();

  ReadInWords();

}



bool Computer::ComputerKnowsWord(string word) {

  int length = words.size();

  for (int i = 0; i < length; i++) {
   
    if (word.length() > words[i].length() ) {
      continue;
    }

    if (word.compare(words[i]) == 0 && word.length() <= words[i].length()) {
      return true;
    }

  }

  return false;
}

  


// Is the word acceptable?
// If it is also make it lowerccase
bool Computer::WordAcceptable(string &word) {

  int length = word.length();
  

  // Lower cas all the letters
  // Also check to make sure they are all characters
  for (int i = 0; i < length; i++) {

    char c = word[i];

    if ( (c > 'z' && c < 'a') ) {
      return false;
    }
    

  }

  return true;
}

// Debugging only
// Used to make sure words were being read in right
void Computer::ReportWords() {

  for (int i = 0; i < words.size(); i++)
    cerr << words[i] << endl;
}

void Computer::ReadInWords() {

  assert(dictionary != NULL);

  ifstream infile;
  string word = "";

  infile.open(dictionary);

  if (!infile) {
    cerr << "Could not open file." << endl;
    assert(infile);
  }

  while (infile >> word) {

      if (WordAcceptable(word)) {
	words.push_back(word);
      }

  }

  // Debugging only
  //ReportWords();

  infile.close();

  

  //ReportWords(); 
}
  

int Computer::GetCol() {return (choice.col + 1);}

char Computer::GetLetter() {return choice.letter;}



// Very long function should be made shorter
// But it is mostly function calls.
void Computer::TryLetter(Grid Realgrid, int x, char c) {

  Grid grid(Realgrid);
  
  int col = x + 1;

  debug("Trying letter: " << c);

  bool go = grid.DropLetter(c, col );

  if (!go)
    return;

  int length = words.size();

  Choice possible;
  possible.points = 0;
  possible.letter = c;
  possible.words.clear();

  const int xmove = grid.lastpos[0];
  const int ymove = grid.lastpos[1];

  int hpos = 0, vpos = 0, dpos = 0, ipos = 0;

  string horizontal = grid.GetLine(HORIZONTAL, xmove, ymove, hpos);
  string vertical = grid.GetLine(VERTICAL, xmove, ymove, vpos);
  string direct = grid.GetLine(DIRECT, xmove, ymove, dpos);
  string indirect = grid.GetLine(INDIRECT, xmove, ymove, ipos);

  for (int i = 0; i < length; i++) {

    string word = words[i];

    debug("Computer trying word: " << words[i]);

    int wlength = words[i].length();

    if (wlength < 3 || wlength > 7) {
      debug("Word is not right size");
      continue;
    }

    // If the letter isn't in the word no point in continuing
    if (word.find(c) == string::npos) {
      debug("Word does not have letter : " << c);
      continue;
    }

    // Source of all pain
    int wordcount = 0;
    wordcount += grid.MatchWord(horizontal, word, hpos);
    wordcount += grid.MatchWord(vertical, word, vpos);
    wordcount += grid.MatchWord(direct, word, dpos);
    wordcount += grid.MatchWord(indirect, word, ipos);

    if (wordcount == 0) {
      debug("No points for word.");
    }

    for (int i = 0; i < wordcount; i++) {
      
      possible.words.push_back(word); 
      possible.points += grid.HowManyPoints(word.length());
      possible.col = x;
    }
  }

  if (possible.points > 0)
    possibles.push_back(possible);
}

void Computer::ClearChoice() {

  choice.col = INVALID;
  choice.letter = INVALID;
  choice.points = 0;
  choice.words.clear();
  possibles.clear();
}
  

void Computer::ThisChoice(Choice i) {

  choice.col = i.col;
  choice.points = i.points;
  choice.words = i.words;
  choice.letter = i.letter;
}

void Computer::ReportPossibles() {

  int length = possibles.size();

  for (int i = 0; i < length; i++) {

    debug("Possible : " << i);
    debug("Col : " << possibles[i].col);
    debug("Points : " << possibles[i].points);
    debug("Letter : " << possibles[i].letter);
    debug(possibles[i].words.size());
    debug("Words list");

    for (int j = 0; j < possibles[i].words.size(); j++) {
      debug(possibles[i].words[j] << " ");
    }

  }

}


void Computer::MakeChoice() {

  ReportPossibles();
  int length = possibles.size();

  for (int i = 0; i < length; i++) {

    // If no choice has been selected
    if (choice.col == INVALID) {
      ThisChoice(possibles[i]);
    }

    else if (possibles[i]. points > choice.points) {
      ThisChoice(possibles[i]);
    }

    // If it is a tie
    else if (possibles[i].points == choice.points) {

      // If it is not a vowel and top points is a vowel
      if (!IsVowel(possibles[i].letter) && IsVowel(choice.letter)) {
	ThisChoice(possibles[i]);
      }

      // Don't do anything if we have a constant top letter already
      else if (IsVowel(possibles[i].letter) && !IsVowel(choice.letter)) {
	continue;
      }

      // Pick abc order if both are vowels or both or constants
      else if (possibles[i].letter < choice.letter) {
	ThisChoice(possibles[i]);
      }

      else if (possibles[i].letter == choice.letter
	       && choice.col > possibles[i].col) {
	ThisChoice(possibles[i]);
      }
    }
  }

  

}

vector<string> Computer::GetWords() {

  return choice.words;
}

bool Computer::HasAdjacentLetters(Grid grid, int x) {
 
  
  int y = grid.GetEmptyY(x);

  assert(!grid.GridFull());

  debug("Check for AdjacentLetters x:" << x << " y:" << y);

  if (x == (grid.MaxX() - 1) ) {
    return true;
  }

  if (y < (grid.MaxY() - 1)) {
    debug("Y column has words in it");
    return true;
  }

  if (x < grid.MaxX() && !grid.XEmpty(x + 1) ) {
    debug("The Y column next to it has letters."); 
    return true;
  }

  debug("The Y column next to it has no letters!");

  return false;
}


    
char Computer::AbcPreference() {    
 
  if (OnlyVowels()) {
    
    const char vowels[5] = {'a', 'e', 'i', 'o', 'u'};

    for (int i = 0; i < 5; i++) {

      if (FreeLetter(vowels[i]))
	return vowels[i];

    }
    cerr << "Failure in AbcPreference." << endl;
    return 'x';
  }
  else {


    for (char c = 'a'; c <= 'z'; c++) {

      if (!IsVowel(c) && FreeLetter(c))
	return c;
    }

  }

  cerr << "Severe Error in AbcPreference." << endl;
  return 'x';

}

bool Computer::OnlyVowels() {

  for (char c = 'a'; c <= 'z'; c++) {

    if (!IsVowel(c) && FreeLetter(c))
      return false;
  }

  return true;
}
	
void Computer::NoWord(Grid grid) {

  int x = 0;
  char letter = 0;

  // If the grid is filled bad news!
  assert(!grid.GridFull());

  
  // Try each row find one that is next to a letter
  for (x = 0; x < grid.MaxX(); x++) {
  
    if (!grid.ColFull(x + 1) && HasAdjacentLetters(grid, x)) {
      break;
    }
  }

  letter = AbcPreference();
  
  choice.col = x;
  choice.letter = letter;
  choice.words.clear();
}

  
  
void Computer::MakeAMove(Grid grid) {

  ClearChoice();

  for (int x = 0; x < grid.MaxX(); x++)
    for (char c = 'a'; c <= 'z'; c++)
      if (FreeLetter(c))
	TryLetter(grid, x, c);

  
  MakeChoice();

  // If no letter is best
  if (choice.letter == INVALID)
    NoWord(grid);
   
}

