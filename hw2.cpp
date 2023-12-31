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
int dimCheck(int x);
int moveCheck(int x);
int* roll(int proto, int person[], int dimension);
bool locCheck(int personA[], int personB[]);
bool maxmoveCheck(int personA[], int personB[], int maxMoves, int totalMovesPersonA, int totalMovesPersonB);

struct Experiment {
  vector<int> values;
};

vector<Experiment> experiments;

int tryStoi(string str) {
  try {
    int x = std::stoi(str);
    return x;
  } catch (std::out_of_range  &e) {
      cout << "out of range: invalid." << endl;
      return 0;
  }
}

// Function to ignore invisible characters other than *nix newline characters
string ignoreInvisible(const string& text) {
  string visible_text;
  for (char c : text) {
    if (c == '\n' || (c >= 32 && c <= 126)) {
      visible_text += c;
    }
  }

  return visible_text;
}

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
        stringstream ss(ignoreInvisible(line)); // Ignore invisible characters
        string token;

        // Read integers and assign them to unique variables, comma delimited
        while (getline(ss, token, ',')) {
            if (intCheck(token)) {
                // DO NOT overflow stoi
                token.resize(9);
                experiment.values.push_back(tryStoi(token));
            } else {
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
rolls a pseudo random dice representing either 4 directions or 8
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
int dimCheck(int x) {
  if (x < 1) {
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
int moveCheck(int x) {
  if (x < 1) {
    cout << "\nMax moves has to be 1 or larger. Please write a number between 1 to 1000000.\n" << endl;
    return -1;
  }
  else if (x > 1000000) {
    cout << "\nMax moves has to smaller than 1000000. Please write a number between 1 to 1000000.\n" << endl;
    return -1;
  }

  return x;
}

//check if personA and personB meet
bool locCheck(int personA[], int personB[]) {
  int total = personA[2] + personB[2];

  if(personA[0] == personB[0] && personA[1] == personB[1]) {
    /*cout << "\nPersonA and PersonB met at the same location. The game is over." << endl;
    cout << "\tThey met at: (" << personA[0] << "," <<personA[1] << ")" << endl;
    cout << "\tIt took " << total << " turns for them to meet." << endl;*/
    return 1;
  }

  return 0;
}

// Check if the maximum number of moves has been reached
bool maxmoveCheck(int personA[], int personB[], int maxMoves, int totalMovesPersonA, int totalMovesPersonB) {
  if (personA[2] + personB[2] == maxMoves) {
    /*cout << "\nYou have reached the maximum number of moves. Try again!" << endl;
    cout << "\tThe people took " << maxMoves << " turns and never met." << endl;
    cout << "\tPersonA ended up at (" << personA[0] << "," << personA[1] << "),";
    cout << " meanwhile, PersonB was at (" << personB[0] << "," << personB[1] << ")" << endl;
    cout << "\tTotal moves for PersonA: " << totalMovesPersonA << endl;
    cout << "\tTotal moves for PersonB: " << totalMovesPersonB << endl; */
    return true;
  }

  return false;
}

void intro() {
  cout << "This program automatically moves 2 people across a gameboard, the\n";
  cout << "board is a classic (x,y) Cartesian coordinate system. PersonA will start in\n";
  cout << "the bottom left hand side and PersonB will start at top right of the board. It\n";
  cout << "uses the indata.txt input file to run play this game repeatedly using different values\n";
  cout << "and provides some resulting statistical data. Have Fun.\n\n";
}

int simulate(int proto, int personA[],int personB[], int dimension, int moves) {
  int userDimension = dimCheck(dimension);
  int maxMoves = moveCheck(moves);
  int total = -1;

  if ( userDimension == -1 || maxMoves == -1 ) {
    return -1;
  }

  bool didTheyMeet;
  int maxReached;

  personA[0] = 0;
  personA[1] = 0;
  personA[2] = 0;
  personA[3] = 0;

  personB[0] = userDimension;
  personB[1] = userDimension;
  personB[2] = 0;
  personB[3] = 0;

  while (1) {
    roll(proto, personA, userDimension);
    didTheyMeet = locCheck(personA, personB);
    if (didTheyMeet == 1)
      break;
    maxReached = maxmoveCheck(personA, personB, maxMoves, personA[2], personB[2]);
    if (maxReached == 1)
      break;

    roll(proto, personB, userDimension);
    didTheyMeet = locCheck(personA, personB);
    if (didTheyMeet == 1)
      break;
    maxReached = maxmoveCheck(personA, personB, maxMoves, personA[2], personB[2]);
    if (maxReached == 1)
      break;
  }

  total = personA[2] + personB[2];

  if (total == -1) {
    cerr << "fail open file" << endl;
    return -1;
  }

  return total;
}

int main() {
  intro();

  srand (time(NULL));

  ofstream outputFile;

  string userString;

  bool maxReached = 0;
  bool didTheyMeet = 0;

  //this is Dimension and maxMoves as referenced in the documentation
  int userDimension = -1;
  int maxMoves = -1;
  int repeats = -1;
  int prot = -1;

  bool empty = true;
  int min, max, avg;

  long long int sum;

  int personA[] = {0, 0, 0, 0};
  int personB[] = {userDimension, userDimension, 0, 0};

  int simulation = -1;

  string filename = "indata.txt";
  outputFile.open("outdata.txt");

  // Check if the file was successfully opened
  if (!outputFile) {
    cerr << "Error opening the file." << endl;
    return 1; // Exit with an error code
  }

  if (openFile(filename)) {
    //Experiment 1 start
    maxMoves = experiments[1].values[1];
    repeats = experiments[1].values[2];
    prot = experiments[1].values[0];

    outputFile << "Experiment #1 changes the dimensions of the grid.\n";
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < repeats; j++) {
        userDimension = experiments[0].values[i];
        simulation = simulate(prot, personA, personB, userDimension, maxMoves);

        if ( simulation == -1 )
          return -1;


        if (empty) {
          empty = false;
          sum = 0;
          min = simulation;
          max = simulation;
        }
        if ( max < simulation || max == -1 ) {
          max = simulation;
        }
        if (simulation < min || min == -1) {
          min = simulation;
        }

        sum += simulation;
      }

       avg = sum / repeats;

       outputFile << "D" << i << ": " << experiments[0].values[i] << "\t";
       outputFile << "maxMoves: " << maxMoves << "   ";
       outputFile << "Repeats: " << repeats << "\t";
       outputFile << "Protocol: " << prot << "   ";
       outputFile << "low: " << min << "    \t";
       outputFile << "high:  " << max << "   \t";
       outputFile << "avg: " << avg << "\n";

       empty = true;
     }
     outputFile << endl;

    //Experiment 2 start
    maxMoves = experiments[3].values[2];
    prot = experiments[3].values[1];
    userDimension = experiments[3].values[0];

    outputFile << "Experiment #2 changes the number of repeats for each row.\n";
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < experiments[2].values[i]; j++) {
        simulation = simulate(prot, personA, personB, userDimension, maxMoves);

        if ( simulation == -1 )
          return -1;

        if (empty) {
          empty = false;
          sum = 0;
          min = simulation;
          max = simulation;
        }
        if ( max < simulation || max == -1 ) {
          max = simulation;
        }
        if (simulation < min || min == -1) {
          min = simulation;
        }

        sum += simulation;
      }

       avg = sum / experiments[2].values[i];

       outputFile << "R" << i << ": " << experiments[2].values[i] << "         \t";
       outputFile << "D: " << userDimension << "   \t";
       outputFile << "maxMoves: " << maxMoves << "   ";
       outputFile << "Protocol: " << prot << "   ";
       outputFile << "low: " << min << "    \t";
       outputFile << "high:  " << max << "   \t";
       outputFile << "avg: " << avg << "\n";

       empty = true;
    }
    outputFile << endl;

    //Experiment 3 start
    maxMoves = experiments[5].values[1];
    repeats = experiments[5].values[2];
    userDimension = experiments[5].values[0];

    outputFile << "Experiment #3 changes the protocols\n";
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < repeats; j++) {
        prot = experiments[4].values[i];
        simulation = simulate(prot, personA, personB, userDimension, maxMoves);

        if ( simulation == -1 )
          return -1;

        if (empty) {
          empty = false;
          sum = 0;
          min = simulation;
          max = simulation;
        }
        if ( max < simulation || max == -1 ) {
          max = simulation;
        }
        if (simulation < min || min == -1) {
          min = simulation;
        }

        sum += simulation;
      }

       avg = sum / repeats;

       outputFile << "P" << i << ": " << experiments[4].values[i] << "\t";
       outputFile << "D: " << userDimension << "   \t";
       outputFile << "maxMoves: " << maxMoves << "   ";
       outputFile << "Repeats: " << repeats << "\t";
       outputFile << "low: " << min << "    \t";
       outputFile << "high:  " << max << "   \t";
       outputFile << "avg: " << avg << "\n";

       empty = true;
   }
   outputFile << endl;

  }
  outputFile.close();

  return 0;
}
