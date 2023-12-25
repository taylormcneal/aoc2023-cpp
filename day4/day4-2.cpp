#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

void add_count(vector<int>&, size_t, int);

int main () {
    // create file stream and pass in the input file path
    ifstream file("input.txt");

    string fileLine; // string to hold the last read file line

    int total = 0; // cumulative total for all scratch card winnings
    size_t count = 0; // count for the current card being processed

    vector<int> cardCopies;

    // read in each file line into the fileLine variable
    while (getline(file, fileLine)) {
        add_count(cardCopies, count, 1);

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


        int winCount = 0;
        for (int number : cardNumbers) {
            // if the current number is found on the card's winning numbers, double the winnings
                // if the winnings are still at 0, initialize the winnings to 1
            if (find(winningNumbers.begin(), winningNumbers.end(), number) != winningNumbers.end()) {
                winCount++;
            }
        }

        // for each win found on the card, add the amount of copies of the current card to the appropriate cards
        for (int i = 0; i < winCount; i++) {
            add_count(cardCopies, count + i + 1, cardCopies[count]);
        }

        count++;
    }

    // for all cards within bounds, add the number of copies to the cumulative total
    for (size_t i = 0; i < count; i++) {
        total += cardCopies[i];
    }

    // print the cumulative total to the console
    cout << total << endl;

    return 0;
}

// function to add a value to an index of the card copies vector
// if the index is out of the current bounds, push the value to the end of the vector
    // this only works because the only indexes referenced out of bounds will be one out of bounds
void add_count (vector<int> &cardCopies, size_t index, int value) {
    if (index >= cardCopies.size()) {
        cardCopies.push_back(value);
    } else {
        cardCopies[index] += value;
    }
}