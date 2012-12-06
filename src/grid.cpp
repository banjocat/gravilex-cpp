
#include <cctype>
#include <cstring>
#include <sstream>
#include <string>
#include <cassert>
#include <iostream>
// For reversing strings
#include <algorithm>
#include "grid.h"
//#define DEBUG
#include "error.h"

using namespace std;

enum e_att {X = 0, Y = 1, INVALID = -1};


Grid::Grid():xsize(7), ysize(6), blank(' ') {

  for (int x = 0; x < xsize; x++) 
    for (int y = 0; y < xsize; y++)
      thegrid[x][y] = blank;
}

int Grid::MaxX() {return xsize;}

int Grid::MaxY() {return ysize;}



bool Grid::ColFull(int c) {

  if (c < 1 || c > 7) {
    //cerr << "ColFull recieved col out of range." << endl;
    return true;
  }

  debug("Check if Col Full :" << c);
  if (GetGrid((c -1), 0) == blank)  {
    debug("Column is not filled.");
    return false;
  }
  else {
    return true;
  }
}

bool Grid::ValidPos(const int x, const int y) {

  if ( x < xsize && y < ysize && x >= 0 && y >= 0)
      return true;

     
 return false;
}

int Grid::GetEmptyY(int x) {

  int y;

  for (y = (MaxY() - 1); y >= 0; y--) {

    if (GetGrid(x, y) == blank) {
      break;
    }
  }

  return y;
}

// Returns -1 if filled
int Grid::GetEmptyRow(int col) {

  int row;

  for (row = (MaxY() - 1); row >= -1; row--) {
    
    if (GetGrid(col, row) == blank) {
      break;
    }
  }

  return row;
}
  
// Returns Y 
int Grid::FilledY(int x) {

  for (int y = 0; y < MaxY(); y++) {

    if (GetGrid(x,y) != blank) {
      return y;
    }
  }

  return MaxY() - 1;
}

// Last minute fix to not giving correct msg
// To word spelled but not with last word
bool Grid::WordSomeWhereInGrid(string word)  {


  for (int y = 0; y < MaxY(); y++) {
    for (int x = 0; x < MaxX(); x++) {

      lastpostemp[X] = x;
      lastpostemp[Y] = y;

      if (WordInGrid(word, false) > 0) {
	return true;
      }
    }
  }

  return false;
}





      



bool Grid::IsBlank(int x, int y) {

  if (GetGrid(x, y) == blank) {
    return true;
  }
  else {
    return false;
  }
}


// Find Y
int Grid::FindY(const int slope, const int x1, const int y1, const int x2) {

  int y2 = -1;


  if (slope == VERTICAL) {
    y2 = x1;
  }

  else if (slope == HORIZONTAL) {
    y2 = y1;
  }

  else if (slope == DIRECT) {
    y2 = (x1 - x2) + y1;
  }

  else if (slope == INDIRECT) {
    y2 = y1 - (x1 - x2);
  }

  return y2;
}

//Gets a line of words connected to the starting position
string Grid::GetLine(int slope, const int xmove, 
		     const int ymove, int &lpos) {

  string word("");

  bool atmove = false;

  
  // This works for all but Vertical cause it is an undefined slope
  for (int x = 0, y = 0; x <= MaxX(); ++x, ++y) {

    // Vertical not being a real slope gets special issues
    if (VERTICAL == slope) {

      if (y >= MaxY()) {
	break;
      }
      x = xmove;
      //cerr << "******xmove : " << x << endl;
    }
    else {
      y = FindY(slope, xmove, ymove, x);
    }

    if (!ValidPos(x, y))
      continue;

    if (IsBlank(x, y) && !atmove) {
      word = "";
      continue;
    }

    if (IsBlank(x, y) && atmove) {
      break;
    }

    word.push_back(GetGrid(x,y));

    if (x == xmove && y == ymove) {
      lpos = word.length() - 1;
      atmove = true;
    }
  }
      
  debug("Getline -> line: " << word << " slope "<< slope << " lpos " << lpos);
  return word;
}

 
bool Grid::InRightPos(int lengthline, int lengthstring,
		      int lpos, int pos) {


  int end = pos + lengthstring - 1;

  if (end < 0 || end > lengthline) {
    return false;

  }

  if (lpos < pos || lpos > end) {
    return false;
  }

  return true;
}

int Grid::ReversePos(int length, int pos) {

  int middle = length / 2;
  bool even = (length % 2) == 0 ? true : false;

  int rpos = 0;


  if ( pos == middle && !even) {
 
    rpos = pos;
  }

  else if (pos == middle) {

    rpos = pos - 1;
  }

  else {

    rpos = length - pos - 1;
  }

  if (rpos < 0 ) {
    cerr << "Fatal error with reverse Pos have negative number. " << endl;
  }

  return rpos;
}
    

  
 

      

int Grid::MatchWord(string line, string word, int lpos, bool posmatters) {


  int count = 0;


  debug("MatchWord - word: "<< word << " line: " << line);
  if (line == "" || word == "") {
    debug("Word or line is blank");
    return count;
  }
 
  
  int llength = line.length();
  int wlength = word.length();

  if (wlength > llength) {
    return count;
  }
 
  for (int pos = 0; pos < llength; pos++) {

    if (line.find(word, pos) == pos) {
      
      if (posmatters == false
	  || InRightPos(llength, wlength, lpos, pos)) {

	debug("Found it! llength=" << llength
	      << " wlength=" << wlength << " lpos= " << lpos
	      << " pos=" << pos);
	count++;
      }
    }
  }

  reverse(line.begin(), line.end());
  
  int rpos = ReversePos(llength, lpos);

  for (int pos = 0; pos < llength; pos++) {

    if (line.find(word, pos) == pos) {

      if (posmatters == false
	  || InRightPos(llength, wlength, rpos, pos)) {

	debug("Found it! llength=" << llength
	      << " wlength=" << wlength << " rpos= " << rpos
	      << " pos=" << pos);

	count++;
      }
    }
  }

  return count;
}
      
  
  
bool Grid::XEmpty(int x) {

  for (int i = 0; i < MaxY(); i++) {

    if (GetGrid(x, i) != blank)
      return false;
  }

  return true;
}

int Grid::WordInGrid(string word, bool positionmatters) {

  // This is the last move made

  int xmove, ymove;

  if (positionmatters == true) {
    xmove = lastpos[X];
    ymove = lastpos[Y];
  }
  else {
    xmove = lastpostemp[X];
    ymove = lastpostemp[Y];
  }

  int count = 0;
  int pos = 0;

  string horizontal = GetLine(HORIZONTAL, xmove, ymove, pos);
  count += MatchWord(horizontal, word, pos, positionmatters);

  string vertical = GetLine(VERTICAL, xmove, ymove, pos);
  count += MatchWord(vertical, word, pos, positionmatters);

  string direct = GetLine(DIRECT, xmove, ymove, pos);
  count += MatchWord(direct, word, pos, positionmatters);

  string indirect = GetLine(INDIRECT, xmove, ymove, pos);
  count += MatchWord(indirect, word, pos, positionmatters);

  return count;
}

    
  

// Added that 0 points is awarded
int Grid::HowManyPoints(int length) {

  assert(length >= 0);

  switch (length) {
  case 3:return 1;
  case 4:return 2;
  case 5:return 4;
  case 6:return 8;
  case 7:return 16;
  default:return 0;
  }
  std::cerr << "Error in HowManyPoints.\n";
  return 0;
}

  
  
	   
	

// This accepts the col not that actual array position
bool Grid::DropLetter(char letter, int x) {

  // Compensate for col number being put in.
  x--;


  // Check if out of bounds just incase;
  if (x >= xsize && x < 0)
    return false;

  letter = tolower(letter);

  if (!isalpha(letter) )
    return false;

  for (int y = (ysize - 1); y >= 0; y--){
    
    assert(thegrid[x][y]);

    if (thegrid[x][y] == blank) {
      thegrid[x][y] = letter;
      lastpos[X] = x;
      lastpos[Y] = y;
      return true;
    }

  }
  return false;
}

bool Grid::GridFull() {

  for (int x = 0; x < xsize; x++) {

    if (thegrid[x][0] == blank)
      return false;

  }
  return true;
}
std::string Grid::Boarder() {

  std::stringstream output;

  output.str("");
  for (int i = 1; i <= xsize; i++) {
    
    output << i;
 
  }


  return output.str();
}


std::string Grid::StringGrid() {

  std::stringstream output;

  output.str("");
 

  for (int y = 0; y < ysize; y++) {

    for (int x = 0; x < xsize; x++) {

      if (thegrid[x][y] == blank) {
	output << ".";
      }
      else {
	output << thegrid[x][y];
      }
   
    }
    
    output << std::endl;
  }

  output << Boarder();

  return output.str();
}

char Grid::GetGrid(int x, int y) const {

  assert(x >= 0 && x < 7 && y >= 0 && y < 6);

  return thegrid[x][y];
}

// Only to be used  with test driver
void Grid::WriteToGrid(std::string txt) {

  int i = 0;

  for (int y = 0; y < ysize; y++) 
    for (int x = 0; x < xsize; x++) {

      if (txt[i] == '.')
	thegrid[x][y] = blank;
      
      else if (isalpha(txt[i])) 
	thegrid[x][y] = tolower(txt[i]);

      else if (txt[i] == '\n')
	x--;

      i++;
    }
   

}
	

    
