#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int dimCheck(string str) {
    bool check;
    double dimension = 0;
    check = (atof(str.c_str()) != 0 || str.compare("0") == 0);
        if(check == 0) {
            cout << "This is not a number. Please write a number between 1 to 99." << endl;
            return dimension;
        }
        else {
            istringstream(str) >> dimension;
            if((dimension - (int) dimension) == 0) {
                if(dimension < 1) {
                    cout << "Dimension has to be larger than 1. Please write a number between 1 to 99." << endl;
                    dimension = 0;
                    return dimension;
                }
                else if(dimension > 100) {
                    cout << "Dimension has to smaller than 100. Please write a number between 1 to 99." << endl;
                    dimension = 0;
                    return dimension;
                }
                else {
                    return dimension;
                }
            }
            else {
                cout << "This is not a integer. Please write a number between 1 to 99." << endl;
                dimension = 0;
                return dimension;
            }
        }
    
}

int moveCheck(string str) {
    bool check;
    double maxMoves = 0;
    check = (atof(str.c_str()) != 0 || str.compare("0") == 0);
        if(check == 0) {
            cout << "This is not a number. Please write a number between 1 to 1000000." << endl;
            return maxMoves;
        }
        else {
            istringstream(str) >> maxMoves;
            if((maxMoves - (int) maxMoves) == 0) {
                if(maxMoves < 1) {
                    cout << "Dimension has to be larger than 1. Please write a number between 1 to 1000000." << endl;
                    maxMoves = 0;
                    return maxMoves;
                }
                else if(maxMoves > 100) {
                    cout << "Dimension has to smaller than 100. Please write a number between 1 to 1000000." << endl;
                    maxMoves = 0;
                    return maxMoves;
                }
                else {
                    return maxMoves;
                }
            }
            else {
                cout << "This is not a integer. Please write a number between 1 to 1000000." << endl;
                maxMoves = 0;
                return maxMoves;
            }
        }
    
}

int main() {
    string userString;
    int dimension = 0;
    int maxMoves = 0;

    /* Ask the user to enter a dimension*/
    if(dimension == 0){
        while(dimension == 0) {
            cout << "Enter a number between 1 to 99 for dimension: ";
            cin >> userString;
            dimension = dimCheck(userString); 
        }
    }

    /* Ask the user to enter a maxMoves*/
    if(maxMoves == 0){
        while(maxMoves == 0) {
            cout << "Enter a number between 1 to 1000000 for maximum movements: ";
            cin >> userString;
            maxMoves = moveCheck(userString); 
        }
    }

    return 0;

}