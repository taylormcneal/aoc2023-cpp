#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main () {

    // create a filestream and pass in its path
    ifstream file("input.txt");

    // variable to store the total of all summed numbers created
    int total = 0;

    // make sure the file was successfully opened
    if (file.is_open()) {
        // string variable to hold each line from the input file
        string fileLine;

        while (file >> fileLine) {

            // array of all digit possibilities
            string const digits = { "123456789" };
            string numString; // string to hold the first and last digit chars of each line

            // append the first and last digit found, respectively
            numString += fileLine[fileLine.find_first_of(digits)];
            numString += fileLine[fileLine.find_last_of(digits)];

            // add this lines calculated number to the running total
            total += stoi(numString);
        }
    }

    // print out the sum of all calculated line numbers
    cout << total << endl;

    return 0;
}