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
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

void curLocation(int*);

// Check if personA and personB meet
bool locCheck(int personA[], int personB[]) {
  int total = personA[3] + personB[3];

  if (personA[1] == personB[1] && personA[2] == personB[2]) {
    cout << "\nPersonA and PersonB met at the same location. The game is over." << endl;
    cout << "\tThey met at: (" << personA[1] << "," << personA[2] << ")" << endl;
    cout << "\tIt took " << total << " turns for them to meet." << endl;
    return true;
  }

  return false;
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

bool intCheck(string input) {
  if (input.size() == 0)
    return false;

  for (int i = 0; i < input.size(); i++) {
    if (!isdigit(input[i]))
      return false;
  }

  return true;
}

int str2int(string input) {
  bool isInt = intCheck(input);

  if (isInt) {
    input.resize(8); // Limit to 8 characters
    return stoi(input);
  }

  return -1;
}

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

    if (!(person[1] >= 0 && person[1] <= dimension && person[2] >= 0 && person[2] <= dimension)) {
      person[1] = originalX;
      person[2] = originalY;
      person[3]--;
      person[4]++;
      continue;
    }

    break;
  }

  return person;
}

void curLocation(int person[]) {
  if (person[0] == 1) {
    cout << "PersonA: (" << person[1] << "," << person[2] << ")" << endl;
  }
  else {
    cout << "PersonB: (" << person[1] << "," << person[2] << ")" << endl;
  }
}

int main() {
  srand(time(NULL));

  string userString;

  bool maxReached = 0;
  bool didTheyMeet = 0;

  int userDimension = -1;
  int maxMoves = -1;

  cout << "This program automatically moves 2 people across a gameboard, the\n";
  cout << "board is a classic (x,y) Cartesian coordinate system. PersonA will start in\n";
  cout << "the bottom left-hand side and PersonB will start at the top right of the board. You\n";
  cout << "will be prompted to choose how big the board will be and how many moves the\n";
  cout << "computer will try before giving up. Have Fun.\n\n";

  while (userDimension == -1) {
    cout << "For the maximum coordinate of the square grid," << endl;
    cout << "Enter a number between 1 to 99: ";
    cin >> userString;
    userDimension = str2int(userString);
    if (userDimension == -1) {
      cout << "\nInvalid input. Please enter a number between 1 to 99.\n" << endl;
    }
  }

  while (maxMoves == -1) {
    cout << "\nFor the maximum number of turns," << endl;
    cout << "Enter a number between 1 to 1000000: ";
    cin >> userString;
    maxMoves = str2int(userString);
    if (maxMoves == -1) {
      cout << "\nInvalid input. Please enter a number between 1 to 1000000.\n" << endl;
    }
  }

  cout << "\nPersonA start point: (0,0)" << endl;
  cout << "PersonB start point: (" << userDimension << "," << userDimension << ")" << endl;
  cout << "\nLet's go!" << endl;

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

  return 0;
}
