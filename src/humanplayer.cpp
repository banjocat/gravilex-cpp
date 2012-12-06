#include <iostream>
#include <cctype>
#include <vector>
#include <cstdio>
#include <cassert>
#include <sstream>
#include <cstdlib>
#include "player.h"
#include "grid.h"
#include "humanplayer.h"
#include "computerplayer.h"
//#define DEBUG
#include "error.h"


using namespace std;



Human::Human() {

  SetUpLetters();

  score = 0;
  wordsplayed.clear();
}

void Human::ReachedEOF() {

  cout << "End of Input Detected" << endl;
  exit(1);
  
}


string Human::FirstWord(string word) {

  string fword("");

  int length = word.length();

  int found = false;

  for (int i = 0; i < length; i++) {

    if (!isspace(word[i])) {
      fword.push_back(word[i]);
      found = true;
    }
    else if (found) {
      break;
    }

  }

  return fword;
}

    

string Human::GetWord() {

  string word("");

  cout << "Enter a word that you would like to claim (empty line to end): " << flush;




  if(!getline(cin, word) ) {
    ReachedEOF();
  }
      
  word = FirstWord(word);

  debug("Got word from human -> " << word);

  LowerCaseIt(word);

  

 return word;
}







char Human::GetLetter() {

  char c;
 

  bool found = false;

  while (!found) {
    
    cout << "Letters remaining to you:" << endl;
    ShowLetters();
    cout << "What letter would you like to drop? " << flush;


    IgnoreSpaces();

    if (!(cin >> c)) {
      ReachedEOF();
    }

    if (isalpha(c)) {
      c = tolower(c);

      if (!FreeLetter(c)) {
       	continue;

      }
      else   {// All good escape the loop!

	RemoveLetter(c);
	found = true;
      }
    }

  }

 
  wordsplayed.clear();

  return c;
}



// Removes all spaces from the input stream.
void Human::IgnoreSpaces() {


  while (isspace(cin.peek())) {
    cin.ignore(1);
  }

  return;
}

// This returns actual col 1-7
int Human::GetCol(Grid grid) {

 
  int col = 0;

  bool found = false;

  while (!found) {
    
    col = 0;
   
    cout << "What column would you like to drop that in? (1-7) " << flush;


    IgnoreSpaces();
    
    // I read in an integer
    // But if a character is put in it will cause problems.
    if (isalpha(cin.peek())) {
      cin.ignore(1);
    }
    else {
      
      if (!(cin >> col)) {
	ReachedEOF();
      }
    }


    if (col > 7 || col < 1) {
      continue;
    }
    else if (!grid.ColFull(col)) { 
      found = true;
    }

  }
  
  cin.ignore(100, '\n');
  if (cin.eof()) {
    ReachedEOF();
  }
  return col;
}

int Human::DeclareWords(Grid grid, Computer computer) {

  string word = "";
  int totalpoints = 0;

  cout << grid.StringGrid() << endl;
  do  {

    word = GetWord();
    debug("Got word from human:-> " << word);
    if (word == "") {
      debug("No word put in");
      // human decided not to put in a word.
    }
    // Is the word in the Grid and was it part of last letter played?
    else if (grid.WordInGrid(word) > 0) {

      debug("Found Word" << word);
      totalpoints += WordKnown(word, grid,  computer);
      
    }

    else if (grid.WordSomeWhereInGrid(word)) {
      debug("Found word in Grid but not last letter: " << word);
      cout << "Sorry, you cannot claim that word." << endl;
    }
    
    else {
      cout << "Sorry, I cannot find that word." << endl;
    }

  }  while (word != "");

  return totalpoints;
}


// Talks to the computer to see if they know the word.
int Human::WordKnown(string word, Grid grid, Computer computer) {

  debug("Found a word");
  bool known = computer.ComputerKnowsWord(word);
      
  if (!known) {
    debug("Computer does not know word");
    cout << "I don't know that word. Are you sure you spelled it correctly? (y/n) " << flush;
    char c;


    
    if (!(cin >> c)) {
      ReachedEOF();
    }

    cin.ignore(100, '\n');
    if (c == 'y' || c == 'Y') {
      known = true;
    }
  }

  if (known)
    return grid.HowManyPoints(word.length());
  else
    return 0;

}
