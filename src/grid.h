#include <string>


// Direction not used - Orginally I had used this
enum direction_t {N, S, E, W, NE, SE, NW, SW };

// This is used instead!
enum d_direction {HORIZONTAL = 0, VERTICAL = -10, DIRECT = 1, INDIRECT = -1};


/*
Because cols are 1-7
But grid is 0-6
Everytime col is used it SHOULD be 1-7
Everytime x is used it SHOULD be 0-6
I made this decision midway sooo yeah..

Grid is setup as a X and Y axis with
(0,0) being top left.
X positive to the right
Y positive going down

*/


class Grid {

public:
  Grid();

  //Places a letter down a column
  //Returns True if it can, false if not a char or col is filled
  bool DropLetter(char const letter, int x);

  //Checks if grid is filled up
  bool GridFull();

  

  // New version
  // Returns how many times it appears 0 if it does not
  // Not the greatest but better than my old one.
  // The positionmatters = false, works only for the human player.
  // It is not needed for computer.
  int WordInGrid(std::string word, bool positionmatters = true);
  
  // Checks if COl is full
  bool ColFull(int c);

  
  // Checks if Pos is in range of grid
  bool ValidPos(int x, int y);

  

  // Returns char to string
  char GetGrid(int x, int y) const;
  

  // No error checking
  // Used in TestCase
  // I am assuming test file is formatted correctly
  // A real game this function is never used.
  void WriteToGrid(std::string);

  // Changes the grid - Don't think I ever use this
  // Was created just incase.
  void CopyGrid(char **grid);

  //How many points per word length.
  int HowManyPoints(int length);

  // Enter a col and it will return the row that it is empty
  // It will return -1 if filled
  int GetEmptyRow(int col);

  // Returns true if x col is empty
  bool XEmpty(int x);

  // Last position played
  // Used for checking if last letter is in the word to claim
  // X= 0 Y = 1
  int lastpos[2];

  // Gets a line in a specific direction determined by slope
  // lpos is the location of the letter played in that line
  // Slope is vertical, horiztonal, direct or indirect.
  // I did it to be fancy it isn't that great of an algorithm sadly.
  std::string GetLine(int slope, const int xmove,
		      const int ymove, int &lpos);


  //After extracting a line with GetLine
  //The line is compared via position to see if it matches
  //It then reverse the line and sees if it matches again.
  int MatchWord(std::string line, std::string word, 
		int pos, bool posmatters = true);

  int MaxX();

  int MaxY();

  // Returns the next empty y based on x
  int GetEmptyY(int);

  std::string StringGrid();


  // Last minute addition to check if a word
  // is in the grid regardless of position
  // Used just for human player check
  bool WordSomeWhereInGrid(std::string);
private:
  char thegrid[7][6];

  int lastpostemp[2];

  const int xsize;
  const int ysize;
  const char blank;

  bool WordInPos(std::string word, int x, int y, direction_t d);
  std::string Boarder();
  std::string Lines();
  bool IsBlank(int x, int y);
  int FindY(const int slope, const int x1,
	    const int y1, const int x2);

  // Returns the highest filled Y value from an x value
  int FilledY(int);

  // Is letter played in the word named
  bool InRightPos(int, int, int, int);

  // Reverse the position of a character in a string
  // Used in string matching
  int ReversePos(int, int);
 

 
};


