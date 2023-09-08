#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>

using namespace std;

int* wallCheck(int*, int);
void curLocation(int*);

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
int* roll(int person[], int dimension) {
  int dir = rand() % 4;
  // north = 0, south = 1, east = 2, west = 3
  if (dir == 0) {
    person[2] += 1;
    person[3] += 1;
    cout << "Move to North!" << endl;
    wallCheck(person, dimension);
    curLocation(person);
  }
  else if (dir == 1) {
    person[2] -= 1;
    person[3] += 1;
    cout << "Move to South!" << endl;
    wallCheck(person, dimension);
    curLocation(person);
  }
  else if (dir == 2) {
    person[1] += 1;
    person[3] += 1;
    cout << "Move to East!" << endl;
    wallCheck(person, dimension);
    curLocation(person);
  }
  else if (dir == 3) {
    person[1] -= 1;
    person[3] += 1;
    cout << "Move to West!" << endl;
    wallCheck(person, dimension);
    curLocation(person);
  }
  else {
    cout << "random generator error" << endl;
  }

  return person;
}

int* wallCheck(int person[], int dimension) {
  if (person[1] < 0) {
    person[1] += 1;
    cout << "You have exceeded your allowable range." << endl;
    cout << "Please wait until next people move" << endl;
    return person;
  }
  else if (person[1] > dimension) {
    person[1] -= 1;
    cout << "You have exceeded your allowable range." << endl;
    cout << "Please wait until next people move" << endl;
    return person;
  }
  else if (person[2] < 0) {
    person[2] += 1;
    cout << "You have exceeded your allowable range." << endl;
    cout << "Please wait until next people move" << endl;
    return person;
  }
  else if (person[2] > dimension) {
    person[2] -= 1;
    cout << "You have exceeded your allowable range." << endl;
    cout << "Please wait until next people move" << endl;
    return person;
  }
  else {
    return person;
  }
}

//print current location of person
void curLocation(int person[]) {
  //personA
  if(person[0] == 1) {
    cout << "PersonA: (" << person[1] << "," <<person[2] << ")" << endl;
  }
  //personB
  else {
    cout << "PersonB: (" << person[1] << "," <<person[2] << ")" << endl;
  }
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

//check if personA and personB meet
int locCheck(int personA[], int personB[]) {
  if(personA[1] == personB[1] && personA[2] == personB[2]) {
    cout << "PersonA and PersonB met at the same location. The game is over." << endl;
    return 1;
  }
  else {
    return 0;
  }
}

//check if person exceed the maxMoves
int maxmoveCheck(int person[], int userDimension) {
  if(person[3] == userDimension) {
    cout << "You exceed the movement times. The game is over." << endl;
    return 1;
  }
  else {
    return 0;
  }
}

int main() {
  srand (time(NULL));

  string userString;

  //this is Dimension and maxMoves as referenced in the documentation
  int userDimension = -1;
  int maxMoves = -1;

  /* Ask the user to enter a dimension*/
  while (userDimension == -1) {
    cout << "Enter a number between 1 to 99 for dimension: ";
    cin >> userString;
    userDimension = dimCheck(userString);
  }

  /* Ask the user to enter a maxMoves*/
  while (maxMoves == -1) {
    cout << "Enter a number between 1 to 1000000 for maximum movements: ";
    cin >> userString;
    maxMoves = moveCheck(userString);
  }

  cout <<"PersonA start point: (0,0)"<< endl;
  cout <<"PersonB start point: (" << userDimension << "," << userDimension << ")" << endl;
  cout <<"Let's start the game!" << endl;

  //person[0] = distinguish between personA and personB
  //person[1] = x-axis
  //person[2] = y-axis
  //person[3] = number of moves
  int personA[] = {1, 0, 0, 0};
  int personB[] = {2, userDimension, userDimension, 0};

  while (1) {
    roll(personA, userDimension);
    int end = locCheck(personA, personB);
    int moveA = maxmoveCheck(personA, userDimension);
    if(end == 1 || moveA ==1) {
      break;
    }
    roll(personB, userDimension);
    end;
    int moveB = maxmoveCheck(personA, userDimension);
    if(end == 1 || moveB ==1) {
      break;
    }
  }

  return 0;
}
