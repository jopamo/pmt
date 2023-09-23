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

using namespace std;

struct Experiment {
    int protocol;
    int maxMovesBeforeGivingUp;
    int repetitions;
    int d0, d1, d2, d3, d4;
    
};

Experiment readingExpData(ifstream& inputFile){
    Experiment experiment;
    string line;
    char comma;
    
    //first line (dimensions)
    if (getline(inputFile, line)) {
        istringstream iss(line);
        if (!(iss >> experiment.d0 >> comma >> experiment.d1 >> comma >> experiment.d2
        >> comma >> experiment.d3 >> comma >> experiment.d4)) {
            cerr << "Error reading first line!" << endl;
        }
    } else {
        cerr << "Empty file!" << endl;
    }
    
    //second line
    getline(inputFile, line);
    istringstream iss(line);
    if (!(iss >> experiment.protocol >> comma >> experiment.maxMovesBeforeGivingUp
    >> comma >> experiment.repetitions)){
        cerr << "Error reading second line!" << endl;
    }
    

    return experiment;
}

/*
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

*/

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
  int originalX = person[0];
  int originalY = person[1];

  int dir = rand() % 4;

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
  else
    cerr << "Random Number Generator Error" << endl;

  if (person[0] < 0 || person[0] > dimension || person[1] < 0 || person[1] > dimension) {
    person[0] = originalX;
    person[1] = originalY;
    person[3]++;
  }

  return person;
}

/*
rolls a pseudo random dice between 0 and 7.

N = 0 | S = 1 | E = 2 | W = 3

NE = 4 | NW = 5 | SE= 6 | SW = 7
*/
int* rollEight(int person[], int dimension) {
  while (true) {
    int dir = rand() % 8;

    int originalX = person[0];
    int originalY = person[1];

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
      person[2]--;
      person[3]++;
      continue;
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

  int personA[] = {0, 0, 0, 0};
  int personB[] = {userDimension, userDimension, 0, 0};

  while (1) {
    //rollFour(personA, userDimension);
    rollEight(personA, userDimension);
    didTheyMeet = locCheck(personA, personB);
    if (didTheyMeet == 1)
      break;
    maxReached = maxmoveCheck(personA, personB, maxMoves, personA[2], personB[2]);
    if (maxReached == 1)
      break;

    //rollFour(personB, userDimension);
    rollEight(personB, userDimension);
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
  
 
  //if file can't open
  string filename = "indata.txt";
  /*
  if (!openFile(filename)) {
    cout << "fail open file" << endl;
  }
  
  */
  ifstream inputFile(filename);
  if (!inputFile.is_open()){
      cerr << "unable to open file." << endl;
  }
  
  /*
  inputFile >> comma;
  
  Experiment* experiments = new Experiment[numOfExperiments];
  int* results = new int[numOfExperiments * 3];
  
  for (int i = 0; i < numOfExperiments; i++){
      experiments[i] = readingExpData(inputFile);
  }
  inputFile.close();
  */
  
  Experiment experiment = readingExpData(inputFile);
  
  
  cout << experiment.d0 << endl;
  cout << experiment.d1 << endl;
  cout << experiment.d2 << endl;
  cout << experiment.d3 << endl;
  cout << experiment.d4 << endl;
  cout << experiment.protocol << endl;
  cout << experiment.maxMovesBeforeGivingUp << endl;
  cout << experiment.repetitions << endl;
  cout << endl;
  

  return 0;
}
