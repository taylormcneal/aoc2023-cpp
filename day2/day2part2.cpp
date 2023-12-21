#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <ctype.h>
#include <algorithm>

using namespace std;

bool is_number (string& str) {
    return !str.empty() && find_if(str.begin(), str.end(), [](unsigned char c) { return !isdigit(c); }) == str.end();
}

int main () {

    map<string, int> colorCount;

    // create a file stream and pass in the input text file name
    ifstream file ("input.txt");
    string fileLine; // string variable to hold each file line

    int total = 0;
    
    // check that the file was successfully opened
    if (file.is_open()) {

        // if a new line has been successfully read into fileLine, continue
        while (getline(file, fileLine)) {

            colorCount["red"] = 0;
            colorCount["green"] = 0;
            colorCount["blue"] = 0;

            fileLine.erase(0, fileLine.find(':') + 2);

            string const delims = { " ,;" };
            int countCheck;
            size_t pos = 0;
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

            total += colorCount["red"] * colorCount["green"] * colorCount["blue"];
        }
    }

    std::cout << total << endl;

    return 0;
}