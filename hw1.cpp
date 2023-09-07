#include <iostream>

using namespace std;

bool intCheck(string input) {
  if (input.size()==0)
    return false;

  for (int i=0; i < input.size(); i++) {
    if (!isdigit(input[i]))
      return false;
  }

  return true;
}

int str2int(string input) {
  bool isInt = intCheck(input);

  if (isInt) {
    //don't give stoi() anything big, 8 char wide is beyond spec
    input.resize(8);
    return stoi(input);
  }

  return -1;
}

int roll(int min, int max) {
  int roll = rand() % max + min;

  return roll;
}

int dimCheck(string str) {
  int dimension = str2int(str);

  if (dimension == -1)
    cout << "This is not a number. Please write a number between 1 to 99." << endl;
  else if (dimension < 1) {
    cout << "Dimension has to be larger than 1. Please write a number between 1 to 99." << endl;
    return -1;
  }
  else if (dimension > 99) {
    cout << "Dimension has to smaller than 100. Please write a number between 1 to 99." << endl;
    return -1;
  }

  return dimension;
}

int moveCheck(string str) {
  int maxMoves = str2int(str);

  if(maxMoves == -1)
    cout << "This is not a number. Please write a number between 1 to 1000000." << endl;
  else if (maxMoves < 1) {
    cout << "Dimension has to be larger than 1. Please write a number between 1 to 1000000." << endl;
    return -1;
  }
  else if (maxMoves > 1000000) {
    cout << "Dimension has to smaller than 1000000. Please write a number between 1 to 1000000." << endl;
    return -1;
  }

  return maxMoves;
}

int main() {
  string userString;
  int dimension = -1;
  int maxMoves = -1;

  /* Ask the user to enter a dimension*/
  while (dimension == -1) {
    cout << "Enter a number between 1 to 99 for dimension: ";
    cin >> userString;
    dimension = dimCheck(userString);
  }

  /* Ask the user to enter a maxMoves*/
  while (maxMoves == -1) {
    cout << "Enter a number between 1 to 1000000 for maximum movements: ";
    cin >> userString;
    maxMoves = moveCheck(userString);
  }

  return 0;
}
