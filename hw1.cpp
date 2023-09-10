/*
Programming language: C++
Programmers: Suhyun Lee, Paul Moses
Date: 08.09.23
Name of class: CS4500-001

This program automatically moves 2 people across a gameboard, the
board is a classic (x,y) Cartesian coordinate system. PersonA will start in
the bottom left hand side and PersonB will start at top right of the board. You
will be prompted to choose how big the board will be and how many moves the
computer will try before giving up. Have Fun.

*person[0] = distinguish between personA and personB
*person[1] = x-axis
*person[2] = y-axis
*person[3] = number of moves
int personA[] = {1, 0, 0, 0};
int personB[] = {2, userDimension, userDimension, 0};

External files: None
*/

#include <iostream>

using namespace std;

void wallCheck(int*, int);
void curLocation(int*);

//checks input string by char array and returns on first
//encountered non integer character from index 0
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

/*
rolls a pseudo random dice between 0 and 4.

north = 0, south = 1, east = 2, west = 3.
*/
int* roll(int person[], int dimension) {
  int dir = rand() % 4;

  // y+1
  if (dir == 0) {
    person[2]++;
    person[3]++;
  }
  // y-1
  else if (dir == 1) {
    person[2]--;
    person[3]++;
  }
  // x+1
  else if (dir == 2) {
    person[1]++;
    person[3]++;
  }
  // x-1
  else if (dir == 3) {
    person[1]--;
    person[3]++;
  }
  else
    cerr << "Random Number Generator Error" << endl;

  wallCheck(person, dimension);

  return person;
}

//prevents roll() from going out of bounds
void wallCheck(int person[], int dimension) {
  if (person[1] < 0)
    person[1] = 0;
  else if (person[1] > dimension)
    person[1] = dimension;
  else if (person[2] < 0)
    person[2] = 0;
  else if (person[2] > dimension)
    person[2] = dimension;
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

  if (x == -1) {
    cout << "\nThis is not a number. Please write a number between 1 to 99.\n" << endl;
  }
  else if (x < 1) {
    cout << "\nThe number has to be larger than 1. Please write a number between 1 to 99.\n" << endl;
    return -1;
  }
  else if (x > 99) {
    cout << "\nDimension has to smaller than 100. Please write a number between 1 to 99.\n" << endl;
    return -1;
  }
  return x;
}

// Provides error messaging based on invalid, less than, or greater than
// This is the user input maxMoves variable error messaging
int moveCheck(string str) {
  int x = str2int(str);

  if(x == -1)
    cout << "\nThis is not a number. Please write a number between 1 to 1000000.\n" << endl;
  else if (x < 1) {
    cout << "\nDimension has to be larger than 1. Please write a number between 1 to 1000000.\n" << endl;
    return -1;
  }
  else if (x > 1000000) {
    cout << "\nDimension has to smaller than 1000000. Please write a number between 1 to 1000000.\n" << endl;
    return -1;
  }

  return x;
}

//check if personA and personB meet
bool locCheck(int personA[], int personB[]) {
  int total = personA[3] + personB[3];

  if(personA[1] == personB[1] && personA[2] == personB[2]) {
    cout << "\nPersonA and PersonB met at the same location. The game is over." << endl;
    cout << "\tThey met at: (" << personA[1] << "," <<personA[2] << ")" << endl;
    cout << "\tIt took " << total << " turns for them to meet." << endl;
    return 1;
  }

  return 0;
}

//check if person exceed the maxMoves
bool maxmoveCheck(int personA[], int personB[], int maxMoves) {
  if(personA[3] + personB[3] == maxMoves) {
    cout << "\nYou have reached the maximum number of moves. Try again!" << endl;
    cout << "\tThe people took " << maxMoves << " turns and never met." << endl;
    cout << "\tPersonA ended up at (" << personA[1] << "," <<personA[2] << "),";
    cout << " meanwhile, PersonB was at (" << personB[1] << "," <<personB[2] << ")" << endl;
    return 1;
  }

  return 0;
}

int main() {
  srand (time(NULL));

  string userString;

  bool maxReached = 0;
  bool didTheyMeet = 0;

  //this is Dimension and maxMoves as referenced in the documentation
  int userDimension = -1;
  int maxMoves = -1;

  cout << "This program automatically moves 2 people across a gameboard, the\n";
  cout << "board is a classic (x,y) Cartesian coordinate system. PersonA will start in\n";
  cout << "the bottom left hand side and PersonB will start at top right of the board. You\n";
  cout << "will be prompted to choose how big the board will be and how many moves the\n";
  cout << "computer will try before giving up. Have Fun.\n\n";

  /* Ask the user to enter dimension*/
  while (userDimension == -1) {
    cout << "For the maximum coordinate of the square grid," << endl;
    cout << "Enter a number between 1 to 99: ";
    cin >> userString;
    userDimension = dimCheck(userString);
  }

  /* Ask the user to enter maxMoves*/
  while (maxMoves == -1) {
    cout << "\nFor the maximum number of turns," << endl;
    cout << "Enter a number between 1 to 1000000: ";
    cin >> userString;
    maxMoves = moveCheck(userString);
  }

  cout <<"\nPersonA start point: (0,0)"<< endl;
  cout <<"PersonB start point: (" << userDimension << "," << userDimension << ")" << endl;
  cout <<"\nLet's go!" << endl;

  /*
  person[0] = distinguish between personA and personB
  person[1] = x-axis
  person[2] = y-axis
  person[3] = number of moves
  */
  int personA[] = {1, 0, 0, 0};
  int personB[] = {2, userDimension, userDimension, 0};

  while (1) {
    roll(personA, userDimension);
    didTheyMeet = locCheck(personA, personB);
    if ( didTheyMeet == 1 )
      break;
    maxReached = maxmoveCheck(personA, personB, maxMoves);
    if ( maxReached == 1 )
      break;

    roll(personB, userDimension);
    didTheyMeet = locCheck(personA, personB);
    if ( didTheyMeet == 1 )
      break;
    maxReached = maxmoveCheck(personA, personB, maxMoves);
    if ( maxReached == 1 )
      break;
  }

  return 0;
}
