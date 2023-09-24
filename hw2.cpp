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

*person[0] = x-axis
*person[1] = y-axis
*person[2] = number of moves
*person[3] = wall hits
int personA[] = {0, 0, 0, 0};
int personB[] = {userDimension, userDimension, 0, 0};

External files: None
*/

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

// Function prototypes
bool intCheck(string str);
bool dimCheck(int x);
bool moveCheck(int x);
int* rollEight(int person[], int dimension);
bool locCheck(int personA[], int personB[]);
bool maxmoveCheck(int personA[], int personB[], int maxMoves, int totalMovesPersonA, int totalMovesPersonB);

struct Experiment {
  vector<int> values;
};

vector<Experiment> experiments;

bool openFile(const string& filename) {
  string line;
  int lineNumber = 0;

  ifstream inputFile(filename);

  if (!inputFile.is_open()) {
    cerr << "Error: Unable to open file " << filename << endl;
    return false;
  }

  while (getline(inputFile, line)) {
    Experiment experiment;
    stringstream ss(line);
    string token;

    // Read integers and assign them to unique variables, comma delimited
    while (getline(ss, token, ',')) {
      if ( intCheck(token) ) {
        experiment.values.push_back(stoi(token));
      }
      else {
        cerr << "Error: Invalid input on line " << lineNumber + 1 << ": " << endl;
        inputFile.close();
        return false;
      }
    }

    experiments.push_back(experiment);
    lineNumber++;
  }

  inputFile.close();

  return true;
}

//checks input string by char array and returns on first
//encountered non integer character from index 0
bool intCheck(string str) {
  if (str.size()==0)
    return false;

  for (int i=0; i < str.size(); i++) {
    if (!isdigit(str[i]))
      return false;
  }

  return true;
}

/*
rolls a pseudo random dice between 0 and 3

rolls a pseudo random dice between 0 and 7.

N = 0 | S = 1 | E = 2 | W = 3

NE = 4 | NW = 5 | SE= 6 | SW = 7
*/
int* roll(int proto, int person[], int dimension) {
  int originalX = person[0];
  int originalY = person[1];

  while (true) {
    int dir = -1;

    if (proto == 4) {
      dir = rand() % 4;
    }
    else if (proto == 8) {
      dir = rand() % 8;
    }
    else {
      cerr << "Error: Invalid number for protocol, 4 or 8 only!" << endl;
    }

    // y+1
    if (dir == 0) {
      person[1]++;
      person[2]++;
    }
    // y-1
    else if (dir == 1) {
      person[1]--;
      person[2]++;
    }
    // x+1
    else if (dir == 2) {
      person[0]++;
      person[2]++;
    }
    // x-1
    else if (dir == 3) {
      person[0]--;
      person[2]++;
    }
     // x+1 y+1
    else if (dir == 4) {
      person[0]++;
      person[1]++;
      person[2]++;
    }
    // x-1 y+1
    else if (dir == 5) {
      person[0]--;
      person[1]++;
      person[2]++;
    }
    // x+1 y-1
    else if (dir == 6) {
      person[0]++;
      person[1]--;
      person[2]++;
    }
    // x-1 y-1
    else if (dir == 7) {
      person[0]--;
      person[1]--;
      person[2]++;
    }
    else {
      cerr << "Random Number Generator Error" << endl;
      continue;
    }

    if (person[0] < 0 || person[0] > dimension || person[1] < 0 || person[1] > dimension) {
      person[0] = originalX;
      person[1] = originalY;

      if (proto == 4) {
        person[3]++;
      }
      else if (proto == 8) {
        person[2]--;
        person[3]++;
        continue;
      }
    }
    break;
  }
    return person;
}

// Provides error messaging based on invalid, less than, or greater than
// This is the user input Dimension variable error messaging
bool dimCheck(int x) {
  if (x == -1) {
    cout << "\nThis is not a number. Please write a number between 1 to 99.\n" << endl;
  }
  else if (x < 1) {
    cout << "\nThe number has to be larger than 1. Please write a number between 1 to 99.\n" << endl;
    return false;
  }
  else if (x > 99) {
    cout << "\nDimension has to smaller than 100. Please write a number between 1 to 99.\n" << endl;
    return false;
  }
  return true;
}

// Provides error messaging based on invalid, less than, or greater than
// This is the user input maxMoves variable error messaging
bool moveCheck(int x) {
  if(x == -1)
    cout << "\nThis is not a number. Please write a number between 1 to 1000000.\n" << endl;
  else if (x < 1) {
    cout << "\nDimension has to be larger than 1. Please write a number between 1 to 1000000.\n" << endl;
    return false;
  }
  else if (x > 1000000) {
    cout << "\nDimension has to smaller than 1000000. Please write a number between 1 to 1000000.\n" << endl;
    return false;
  }

  return true;
}

//check if personA and personB meet
bool locCheck(int personA[], int personB[]) {
  int total = personA[2] + personB[2];

  if(personA[0] == personB[0] && personA[1] == personB[1]) {
    cout << "\nPersonA and PersonB met at the same location. The game is over." << endl;
    cout << "\tThey met at: (" << personA[0] << "," <<personA[1] << ")" << endl;
    cout << "\tIt took " << total << " turns for them to meet." << endl;
    return 1;
  }

  return 0;
}

// Check if the maximum number of moves has been reached
bool maxmoveCheck(int personA[], int personB[], int maxMoves, int totalMovesPersonA, int totalMovesPersonB) {
  if (personA[2] + personB[2] == maxMoves) {
    cout << "\nYou have reached the maximum number of moves. Try again!" << endl;
    cout << "\tThe people took " << maxMoves << " turns and never met." << endl;
    cout << "\tPersonA ended up at (" << personA[0] << "," << personA[1] << "),";
    cout << " meanwhile, PersonB was at (" << personB[0] << "," << personB[1] << ")" << endl;
    cout << "\tTotal moves for PersonA: " << totalMovesPersonA << endl;
    cout << "\tTotal moves for PersonB: " << totalMovesPersonB << endl;
    return true;
  }

  return false;
}

void intro() {
  cout << "This program automatically moves 2 people across a gameboard, the\n";
  cout << "board is a classic (x,y) Cartesian coordinate system. PersonA will start in\n";
  cout << "the bottom left hand side and PersonB will start at top right of the board. You\n";
  cout << "will be prompted to choose how big the board will be and how many moves the\n";
  cout << "computer will try before giving up. Have Fun.\n\n";
}

int main() {
  intro();

  srand (time(NULL));

  string userString;

  bool maxReached = 0;
  bool didTheyMeet = 0;

  //this is Dimension and maxMoves as referenced in the documentation
  int userDimension = -1;
  int maxMoves = -1;

  string filename = "indata.txt";

  if (openFile(filename)) {
    userDimension = experiments[0].values[0];
    maxMoves = experiments[1].values[1];

    cout << "success open file" << endl;

    for (int i = 0; i < experiments.size(); ++i) {
      cout << "Line " << i + 1 << " - Values: ";
      for (int j = 0; j < experiments[i].values.size(); ++j) {
        cout << "Value" << j << ": " << experiments[i].values[j] << " ";
      }
      cout << endl;
    }

    /*
    cout << endl;
    cout << experiments[0].values[0] << endl;
    cout << experiments[0].values[1] << endl;
    cout << experiments[0].values[2] << endl;
    */
  }
  else {
    cerr << "fail open file" << endl;
  }

  /* //incomplete not working
  if ( dimCheck(dim) ) {
    //valid input
  }

  if ( moveCheck(moves) ) {
    //valid input
  }*/

  cout <<"\nPersonA start point: (0,0)"<< endl;
  cout <<"PersonB start point: (" << userDimension << "," << userDimension << ")" << endl;
  cout <<"\nLet's go!" << endl;

  int personA[] = {0, 0, 0, 0};
  int personB[] = {userDimension, userDimension, 0, 0};

  while (1) {
    roll(8, personA, userDimension);
    didTheyMeet = locCheck(personA, personB);
    if (didTheyMeet == 1)
      break;
    maxReached = maxmoveCheck(personA, personB, maxMoves, personA[2], personB[2]);
    if (maxReached == 1)
      break;

    roll(8, personB, userDimension);
    didTheyMeet = locCheck(personA, personB);
    if (didTheyMeet == 1)
      break;
    maxReached = maxmoveCheck(personA, personB, maxMoves, personA[2], personB[2]);
    if (maxReached == 1)
      break;
  }

  cout << "Total wall hits for PersonA: " << personA[3] << endl;
  cout << "Total wall hits for PersonB: " << personB[3] << endl;

  cout << "\tTotal moves for PersonA: " << personA[2] << endl;
  cout << "\tTotal moves for PersonB: " << personB[2] << endl;

  //First two lines of the file data
  int d0 = experiments[0].values[0];
  int d1 = experiments[0].values[1];
  int d2 = experiments[0].values[2];
  int d3 = experiments[0].values[3];
  int d4 = experiments[0].values[4];

  int p = experiments[1].values[0];
  int m = experiments[1].values[1];
  int r = experiments[1].values[2];

  return 0;
}
