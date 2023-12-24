#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

// function prototpes
void is_part(vector<string>&, int&, size_t&, map<size_t, vector<int>>&);
void check_gear(vector<string>, size_t, size_t, size_t, size_t, map<size_t, vector<int>>&);

int main () {
    
    // create a file stream and pass in the input file path
    ifstream file("input.txt");

    // vector to hold the file lines currently being checked
    vector<string> fileLines;

    map<size_t, vector<int>> gearPartAdj;

    int total = 0; // running total for all engine part ids
    size_t currentRow = 0;

    // make sure the file was successfully opened
    if (file.is_open()) {
        string fileLine; // string to hold the last read file line
        while (file >> fileLine) {
            // push the last read line into the vector of lines being searched for parts
            fileLines.push_back(fileLine);
            is_part(fileLines, total, currentRow, gearPartAdj);
        }

        // the above while loop leaves a singular line which needs to be checked for parts
        is_part(fileLines, total, currentRow, gearPartAdj);

        // iterate through the map of gears and if the gear is next to exactly two parts,
            // add their gear ratio to the cumulative total
        for (auto const &[key, val] : gearPartAdj) {
            int gearRatio = 1;
            if (val.size() == 2) {
                for (int x : val) {
                    gearRatio *= x;
                }

                total += gearRatio;
            }
        }

        // print the cumulative total of gear ratios to the console
        cout << total << endl;
    }

    return 0;
}

// this function was created to check the current vector of strings for parts
// for part 2, this function is modified to also add in gears to a map to track how many parts they are adjacent to
void is_part (vector<string> &field, int &total, size_t &currentRow, map<size_t, vector<int>> &gearPartAdj) {
    // if the field has a singular string, return
    if (field.size() < 2)
        return;

    string const digits = { "0123456789" }; // const string to hold all numeric possibilities for parts

    // if current row isn't the first, the search needs to happen on the second row
    size_t searchRow = !(currentRow == 0);

    // search for a string of consecutive numeric values
    // if one is found, check the surrounding characters to see if a special character can be found
    size_t index = 0;
    while ((index = field.at(searchRow).find_first_of(digits, index)) != string::npos) {
        size_t len = field.at(searchRow).find_first_not_of(digits, index) - index;

        check_gear(field, searchRow, index, len, currentRow, gearPartAdj);

        index += len;
    }

    // only 3 strings need to be kept for a search of any given "parts" surrounding characters
    // if we're already at 3, erase the first element to make room for the next
    if (field.size() == 3)
        field.erase(field.begin());

    // iterate the current row being searched
    currentRow++;
}

// this function iterates over the field of strings searching for gears '*'
// once found, a unique index is calculated for the gear and a count variable is created to track how many partss are adjacent
void check_gear (vector<string> field, size_t searchRow, size_t index, size_t len, size_t currentRow, map<size_t, vector<int>> &gearPartAdj) {
    for (size_t i = 0; i < field.size(); i++) {
        for (size_t j = (index == 0) ? 0 : index - 1; j <= min(field.at(searchRow).length() - 1, index + len); j++) {
            if (field.at(i)[j] == '*') {
                // calculate a gear index using the gear's position in the string field
                size_t gearIndex = (currentRow + i - !(currentRow == 0)) * field.at(searchRow).length() + j;
                int num = stoi(field.at(searchRow).substr(index, len));
                gearPartAdj[gearIndex].push_back(num);
            }
        }
    }
}