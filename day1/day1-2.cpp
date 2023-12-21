#include <iostream>
#include <fstream>
#include <string>
#include <ctype.h>
#include <map>

using namespace std;

int main () {

    // create a filestream and pass in its path
    ifstream file("input.txt");

    // string constant to hold all digit characters
    string const digits = { "123456789" };
    // map to store spelled digits and their numeric counterpart
    map<string, int> digitMap = {
        {"one", 1}, {"two", 2}, {"three", 3}, {"four", 4}, {"five", 5},
        {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}
    };

    // variable to store the total of all summed numbers created
    int total = 0;

    // make sure the file was successfully opened
    if (file.is_open()) {
        // string variable to hold each line from the input file
        string fileLine;

        while (file >> fileLine) {

            // storage variables for the current first and last digit
            int firstDigit, lastDigit;
            // initialize the indicies of the first and last index at their respective ends of the string
                // checks will be done against these to see if a new value should take our current digits place
            size_t firstDigitIndex = fileLine.length() + 1;
            size_t lastDigitIndex;
            
            // check for the first numeric digit in the string and set it as our current first digit
            size_t firstIndex = fileLine.find_first_of(digits);
            if (firstIndex != string::npos) {
                firstDigitIndex = firstIndex;
                firstDigit = fileLine[firstDigitIndex] - '0';
            }

            // iterate through the spelled digits map and check our string for its first occurence
            // if the substring appears before our current first digit, replace it
            for (auto i : digitMap) {
                size_t index;
                if ((index = fileLine.find(i.first)) != string::npos) {
                    if (index < firstDigitIndex) {
                        firstDigitIndex = index;
                        firstDigit = i.second;
                    }
                }
            }

            // check for the last numeric digit in the string and set it as our current last digit
            size_t lastIndex = fileLine.find_last_of(digits);
            if (lastIndex != string::npos) {
                lastDigitIndex = lastIndex;
                lastDigit = fileLine[lastDigitIndex] - '0';
            }

            // iterate through the spelled digits map and check our string for its last occurence
            // if the substring appears after our current last digit, replace it
            for (auto i : digitMap) {
                size_t index;
                if ((index = fileLine.rfind(i.first)) != string::npos) {
                    if (index >= lastDigitIndex) {
                        lastDigitIndex = index;
                        lastDigit = i.second;
                    }
                }
            }

            // use our two stored digits to add the equivalent two digit value to our running total
            total += 10 * firstDigit + lastDigit;

        }
    }

    // print out our resulting total to console
    cout << total << endl;

    return 0;
}