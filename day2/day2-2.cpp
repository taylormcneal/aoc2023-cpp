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

    // mapping to hold each iterations minimum requirements
    map<string, int> colorCount;

    // create a file stream and pass in the input text file name
    ifstream file ("input.txt");
    string fileLine; // string variable to hold each file line

    // initialize a running total for powers
    int total = 0;
    
    // check that the file was successfully opened
    if (file.is_open()) {

        // if a new line has been successfully read into fileLine, continue
        while (getline(file, fileLine)) {

            // reset all color counts to zero
            colorCount["red"] = 0;
            colorCount["green"] = 0;
            colorCount["blue"] = 0;

            // remove the game text and game number
            fileLine.erase(0, fileLine.find(':') + 2);

            string const delims = { " ,;" }; // string constant to hold character delimiters
            int countCheck; // count check variable to hold last read number from file
            size_t pos = 0; // initialize a position varaible to the start of the file line

            // find the first substring which contains no delimiters
            // if the substring is a number, store it in the count check variable
            // if the substring is a string, compare the count check to the current color count map value
                // if the value is greater, replace it
            while ((pos = fileLine.find_first_not_of(delims)) != string::npos) {
                size_t len = fileLine.find_first_of(delims, pos) - pos;
                string token = fileLine.substr(pos, len);
                fileLine.erase(0, pos + len);

                if (is_number(token)) {
                    countCheck = stoi(token);
                } else {
                    if (countCheck > colorCount[token]) {
                        colorCount[token] = countCheck;
                    }
                }
            }

            // calculate the "power" of each color count and add it to the running total
            total += colorCount["red"] * colorCount["green"] * colorCount["blue"];
        }
    }

    // print out the running total to console
    cout << total << endl;

    return 0;
}