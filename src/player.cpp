#include <string>
#include <vector>
#include <cctype>
#include <iostream>
#include "player.h"

using namespace std;

void Player::LowerCaseIt(string &word) {

  int length = word.length();

  for (int i = 0; i < length; i++)
    word[i] = tolower(word[i]);

  return;
}


void Player::ShowLetters() {

  
  for (char c = 'a'; c <= 'z'; c++) {

    if (FreeLetter(c)) {
      cout << c;

      int amount = VowelCount(c);
      if ( amount > 1 ) {
	cout << "(" << amount << ")";
      }
      if (!LastLetter(c) ){
	  cout << " ";
      }
    }
  }
  cout << endl;
}


bool Player::IsVowel(char c) {

  if (c == 'a' || c == 'e' || c == 'i' || c == 'u' || c == 'o')
    return true;

  return false;
}

int Player::GetScore() const{
  return score;
}

int Player::AddScore(int rewards){
  score += rewards;
  return score;
}

bool Player::FreeLetter(char c) {

  int length = lettersfree.size();

  for (int i = 0; i < length; i++)
    if (lettersfree[i] == c)
      return true;

  return false;
}

void Player::RemoveLetter(char c) {

  int length = lettersfree.size();

  for (int i = 0; i < length; i++) {

    if (c == lettersfree[i]) {
      lettersfree.erase(lettersfree.begin() + i);
      return;
    }
  }
  return;
}
  


void Player::SetUpLetters() {

  lettersfree.clear();

  for (char c = 'a'; c <= 'z'; c++) {
    lettersfree.push_back(c);
    // Vowels get put on twice
    if (IsVowel(c))
      lettersfree.push_back(c);
  }
}

int Player::VowelCount(char c) {

  int length = lettersfree.size();

  int count = 0;

  for (int i = 0; i < length; i++) {

    if (lettersfree[i] == c)
      count++;

  }

  return count;
}

//I added * to it, if you want the player to have all their letters
void Player::ReadLetters(string line) {

  LowerCaseIt(line);

  if (line[0] == '*') {
    SetUpLetters();
    return;
  }

  lettersfree.clear();

  int length = line.length();

  for (int i = 0; i < length; i++) {

    if (line[i] >= 'a' && line[i] <= 'z') {
      lettersfree.push_back(line[i]);
    }
  }

  return;
}

// Checks if it is the last letter
bool Player::LastLetter(char c) {

 

  for (char check = (c + 1) ; check <= 'z'; check++) {

    if (FreeLetter(check)) {
      return false;
    }
  }

  return true;
}
