#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <ctype.h>
#include <algorithm>

using namespace std;

// check the string to see if it contains any non digit values and return a bool value accordingly
bool is_number (string& str) {
    return !str.empty() && find_if(str.begin(), str.end(), [](unsigned char c) { return !isdigit(c); }) == str.end();
}

int main () {

    // mapping to hold the string value of cube colors and their respective count
    map<string, int> colorCount {{"red", 12}, {"green", 13}, {"blue", 14}};

    // create a file stream and pass in the input text file name
    ifstream file ("input.txt");
    string fileLine; // string variable to hold each file line

    // running total of the possible games initialized to 0
    int total = 0;
    
    // check that the file was successfully opened
    if (file.is_open()) {

        // keep track of the current game number being parsed
        int gameNum = 1;

        // if a new line has been successfully read into fileLine, continue
        while (getline(file, fileLine)) {
            fileLine.erase(0, fileLine.find(':') + 2);

            // preemptively add the game number, it will be removed if the game is decided to be impossible
            total += gameNum;

            // string constant storing the delimiters for the file lines
            string const delims = { " ,;" };
            int countCheck; // variable to hold the last read count from a game
            size_t pos = 0; // initialize a position variable for the start of a file line

            // find the first substring which contains no delimiters
            // if the substring is a number, store it in the count check variable
            // if the substring is a string, compare the count check to the number of cubes available
                // if the value in color count is greater than the cubes available, the game is impossible
                // subtract the game number from the total and break from the loop
            while ((pos = fileLine.find_first_not_of(delims)) != string::npos) {
                size_t len = fileLine.find_first_of(delims, pos) - pos;
                string token = fileLine.substr(pos, len);
                fileLine.erase(0, pos + len);

                if (is_number(token)) {
                    countCheck = stoi(token);
                } else {
                    if (countCheck > colorCount[token]) {
                        total -= gameNum;
                        break;
                    }
                }
            }

            gameNum++; // iterate the game number and continue the loop
        }
    }

    // print out the cumulative total to the console
    cout << total << endl;

    return 0;
}