#include <iostream>

using namespace std;

//checks input string by char array and returns on first encountered non integer character from index 0
bool intCheck(string input) {
  if (input.size()==0)
    return false;

  for (int i=0; i < input.size(); i++) {
    if (!isdigit(input[i]))
        return false;
  }

  return true;
}

//if intCheck returns true, give stoi the first 8 digits only
int str2int(string input) {
  bool isInt = intCheck(input);

  if (isInt) {
    //don't give stoi() anything beyond 8 char wide
    input.resize(8);
    return stoi(input);
  }

  return -1;
}

//rolls a pseudo random dice with supplied start/end values
int roll(int min, int max) {
  int roll = rand() % max + min;

  return roll;
}

// Provides error messaging based on invalid, less than, or greater than
// This is the user input Dimension variable error messaging
int dimCheck(string str) {
  int x = str2int(str);

  if (x == -1)
    cout << "This is not a number. Please write a number between 1 to 99." << endl;
  else if (x < 1) {
    cout << "x has to be larger than 1. Please write a number between 1 to 99." << endl;
    return -1;
  }
  else if (x > 99) {
    cout << "Dimension has to smaller than 100. Please write a number between 1 to 99." << endl;
    return -1;
  }

  return x;
}

// Provides error messaging based on invalid, less than, or greater than
// This is the user input maxMoves variable error messaging
int moveCheck(string str) {
  int x = str2int(str);

  if(x == -1)
    cout << "This is not a number. Please write a number between 1 to 1000000." << endl;
  else if (x < 1) {
    cout << "Dimension has to be larger than 1. Please write a number between 1 to 1000000." << endl;
    return -1;
  }
  else if (x > 1000000) {
    cout << "Dimension has to smaller than 1000000. Please write a number between 1 to 1000000." << endl;
    return -1;
  }

  return x;
}

int main() {
  srand (time(NULL));

  string userString;

  int randFour = roll(1, 4);

  //this is Dimension and maxMoves as referenced in the documentation
  int userDimension = -1;
  int maxMoves = -1;

  //this can probably be removed later
  int maxPositions = -1;

  /* Ask the user to enter a dimension*/
  while (userDimension == -1) {
    cout << "Enter a number between 1 to 99 for dimension: ";
    cin >> userString;
    userDimension = dimCheck(userString);
  }

  //this can probably be removed later
  maxPositions = userDimension * userDimension;

  /* Ask the user to enter a maxMoves*/
  while (maxMoves == -1) {
    cout << "Enter a number between 1 to 1000000 for maximum movements: ";
    cin >> userString;
    maxMoves = moveCheck(userString);
  }

  cout << "\nDEBUG Output:\n";
  cout << "\nHere's a random number between 1 and 4: ";
  cout << randFour << endl;

  cout << "\nHere's the dimensions, it's a square...\n";
  cout << "\tLength/Width: ";
  cout << userDimension << endl;
  cout << "\tTotal Squares: ";
  cout << maxPositions << endl;

  return 0;
}
