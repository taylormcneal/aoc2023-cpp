#include <iostream>
#include <fstream>
#include <string>
#include <ctype.h>

using namespace std;

int main () {
    ifstream file ("input.txt");
    string fileLine;

    int total = 0;

    if (file.is_open()) {
        while (file >> fileLine) {
            char numStr[2];

            for (int i = 0; i < fileLine.length(); i++) {
                if (isdigit(fileLine[i])) {
                    numStr[0] = fileLine[i];
                    break;
                }
            }

            for (int i = fileLine.length() - 1; i >= 0; i--) {
                if (isdigit(fileLine[i])) {
                    numStr[1] = fileLine[i];
                    break;
                }
            }

            total += stoi(numStr);
        }
    }

    cout << total;

    return 0;
}