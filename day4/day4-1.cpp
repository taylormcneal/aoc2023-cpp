#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

int main () {
    // create file stream and pass in the input file path
    ifstream file("input.txt");

    string fileLine; // string to hold the last read file line

    int total = 0; // cumulative total for all scratch card winnings

    // read in each file line into the fileLine variable
    while (getline(file, fileLine)) {

        // vectors to hold the winning numbers for each card and the card's playable numbers
        vector<int> winningNumbers;
        vector<int> cardNumbers;

        bool dividerPassed = false; // flag used to tell if we're reading in winning or playable numbers

        // erase the string up until the winning numbers
        fileLine.erase(0, fileLine.find(':') + 1);

        // pass the line into a string stream so it can be parsed word by word
        stringstream lineStream(fileLine);
        string word; // string variable to hold each word

        // parse the line stream for each word
        while (lineStream >> word) {
            // check to see if the current word being read is the divider
            if (word == "|") {
                dividerPassed = true;
                continue;
            }

            // if we're before the divider, push the number into the winning number vector
                // if it's after, push the number into the card numbers
            if (dividerPassed)
                winningNumbers.push_back(stoi(word));
            else
                cardNumbers.push_back(stoi(word));
        }

        int winnings = 0; // initialize the cards winnings at 0
        for (int number : cardNumbers) {
            // if the current number is found on the card's winning numbers, double the winnings
                // if the winnings are still at 0, initialize the winnings to 1
            if (find(winningNumbers.begin(), winningNumbers.end(), number) != winningNumbers.end()) {
                winnings = (winnings == 0) ? 1 : winnings * 2;
            }
        }

        // add the cards winnings to the running cumulative total
        total += winnings;
    }

    // print the cumulative total to the console
    cout << total << endl;

    return 0;
}