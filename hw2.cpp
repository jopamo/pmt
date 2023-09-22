/*
Programming language: C++
Programmers: Mahabu Matin, Efrata Serbessa, Paul Moses

Date: 08.24.23
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

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

bool openFile(const string& filename) {
  string line;
  ifstream inputFile(filename);

  if (!inputFile.is_open()) {
    cerr << "Error: Unable to open file " << filename << endl;
    return false;
  }

  while (getline(inputFile, line)) {
    cout << line << endl;
  }

  inputFile.close();

  return true;
}

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
rolls a pseudo random dice between 0 and 3

north = 0, south = 1, east = 2, west = 3.
*/
int* rollFour(int person[], int dimension) {
  int originalX = person[1];
  int originalY = person[2];

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

  if (person[1] < 0 || person[1] > dimension || person[2] < 0 || person[2] > dimension) {
      person[1] = originalX;
      person[2] = originalY;
      person[4]++;
    }

  return person;
}

/*
rolls a pseudo random dice between 0 and 7.

N = 0 | S = 1 | E = 2 | W = 3

NE = 4 | NW = 5 | SE= 6 | SW = 7
*/
int* rollEight(int person[], int dimension, int& totalMoves, int& wallHits) {
  while (true) {
    int dir = rand() % 8;

    int originalX = person[1];
    int originalY = person[2];

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
    // x+1 y+1
    else if (dir == 4) {
      person[1]++;
      person[2]++;
      person[3]++;
    }
    // x-1 y+1
    else if (dir == 5) {
      person[1]--;
      person[2]++;
      person[3]++;
    }
    // x+1 y-1
    else if (dir == 6) {
      person[1]++;
      person[2]--;
      person[3]++;
    }
    // x-1 y-1
    else if (dir == 7) {
      person[1]--;
      person[2]--;
      person[3]++;
    }
    else {
      cerr << "Random Number Generator Error" << endl;
      continue;
    }

    if (person[1] < 0 || person[1] > dimension || person[2] < 0 || person[2] > dimension) {
      person[1] = originalX;
      person[2] = originalY;
      person[4]++;
    }

    break;
  }

  return person;
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

// Check if the maximum number of moves has been reached
bool maxmoveCheck(int personA[], int personB[], int maxMoves, int totalMovesPersonA, int totalMovesPersonB) {
  if (personA[3] + personB[3] == maxMoves) {
    cout << "\nYou have reached the maximum number of moves. Try again!" << endl;
    cout << "\tThe people took " << maxMoves << " turns and never met." << endl;
    cout << "\tPersonA ended up at (" << personA[1] << "," << personA[2] << "),";
    cout << " meanwhile, PersonB was at (" << personB[1] << "," << personB[2] << ")" << endl;
    cout << "\tTotal moves for PersonA: " << totalMovesPersonA << endl;
    cout << "\tTotal moves for PersonB: " << totalMovesPersonB << endl;
    return true;
  }

  return false;
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
  int personA[] = {1, 0, 0, 0, 0};
  int personB[] = {2, userDimension, userDimension, 0, 0};

  while (1) {
    rollEight(personA, userDimension, personA[3], personA[4]);
    didTheyMeet = locCheck(personA, personB);
    if (didTheyMeet == 1)
      break;
    maxReached = maxmoveCheck(personA, personB, maxMoves, personA[3], personB[3]);
    if (maxReached == 1)
      break;

    rollEight(personB, userDimension, personB[3], personB[4]);
    didTheyMeet = locCheck(personA, personB);
    if (didTheyMeet == 1)
      break;
    maxReached = maxmoveCheck(personA, personB, maxMoves, personA[3], personB[3]);
    if (maxReached == 1)
      break;
  }

  cout << "Total wall hits for PersonA: " << personA[4] << endl;
  cout << "Total wall hits for PersonB: " << personB[4] << endl;

  cout << "\tTotal moves for PersonA: " << personA[3] << endl;
  cout << "\tTotal moves for PersonB: " << personB[3] << endl;

  string filename = "indata.txt";

  if (openFile(filename)) {
    cout << "success open file" << endl;
  }
  else {
    cerr << "fail open file" << endl;
  }

  return 0;
}
