#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// function prototypes
int verify_part (vector<string>, size_t, size_t, size_t);
void is_part (vector<string>&, int&);

int main () {
    
    // create a file stream and pass in the input file path
    ifstream file("input.txt");

    // vector to hold the file lines currently being checked
    vector<string> fileLines;

    // running total for all engine part ids
    // starting at -1 to have a flag for the first pass
    int total = -1;

    // make sure the file was successfully opened
    if (file.is_open()) {
        string fileLine; // string to hold the last read file line
        while (file >> fileLine) {
            fileLines.push_back(fileLine);
            is_part(fileLines, total);
        }

        is_part(fileLines, total);

        cout << total << endl;
    }

    return 0;
}

void is_part (vector<string> &field, int &total) {
    // if the field of strings only has a singular entry, return
    if (field.size() < 2)
        return;

    string const digits = { "0123456789" }; // constant string of numeric digits

    // check if this is the first pass and reset the total accordingly
    size_t searchRow = !(total == -1);
    if (total == -1)
        total = 0;

    // search for a string of consecutive numeric values
    size_t index = 0;
    while ((index = field.at(searchRow).find_first_of(digits, index)) != string::npos) {
        size_t len = field.at(searchRow).find_first_not_of(digits, index) - index;

        // for each part found, send the substring data to the verify part function
        total += verify_part(field, searchRow, index, len);

        // adjust the index to continue looking for part substrings
        index += len;
    }

    // only 3 strings need to be kept for a search of any given "parts" surrounding characters
    // if we're already at 3, erase the first element to make room for the next
    if (field.size() == 3)
        field.erase(field.begin());
}

// this function takes in data about the substring representing a part
// if the substring has a special character surrounding it, return the value of the part
int verify_part (vector<string> field, size_t searchRow, size_t index, size_t len) {
    string const nonSpecial = { "0123456789." }; // const string containing all nonspecial character values

    // search the box of characters around the part substring
    for (size_t i = 0; i < field.size(); i++) {
        for (size_t j = (index == 0) ? 0 : index - 1; j <= min(field.at(searchRow).length() - 1, index + len); j++) {
            if (nonSpecial.find(field.at(i)[j]) == string::npos) {
                return stoi(field.at(searchRow).substr(index, len));
            }
        }
    }

    return 0;
}