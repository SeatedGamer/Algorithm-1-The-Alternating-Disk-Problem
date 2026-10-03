/*
CPSC 335 - Algorithm Engineering, Project 1
Algorithm 2: Connecting Pairs of Persons

Group members: Chase Hales, Chris Reyes, Alexavier Lualhati, Darren Ngo

Description:
    Given a row of ints, where each int represents a persons ID present in the ith seat,
    we designed an algorithm using a greedy approach to look over the inputted row and check 
    whether each person is seated next to their partner and if not, will have their seats 
    swapped with another person so that all people in the row are sitting next to their partner

Compile: g++ -std=c++17 -o couples couples.cpp
Run:     ./couples
*/

#include <iostream>
#include <vector>
#include <string>
#include <utility>

// Inpput of rows to be tested
const std::vector<std::vector<int>> test_data = {
    {0, 2, 1, 3},
    {3, 2, 0, 1},
    {0, 3, 2, 5, 4, 1},
    {5, 4, 2, 6, 3, 1, 0, 7}
};

const bool SHOW_EACH_SWAP = true; // Prints the row after every swap

// Prints a row of IDs with each ID being the person sitting in the ith seat
void printRow(const std::string& label, const std::vector<int>& row) {
    std::cout << label << "[";
    for (size_t i = 0; i < row.size(); i++) {
        std::cout << row[i];
        if (i < row.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]\n";
}

// Returns the ID of a persons partner
int getPartner(int person) {
    if (person % 2 == 0) {
        return person + 1;
    } else {
        return person - 1;
    }
}

// Swaps each person counting the number of swaps done so that all couples are sitting together with their partner
int minSwapsCouples(std::vector<int> row) {
    int size = row.size();   // number of seats (2n)

    // Persons seat, position in the row
    std::vector<int> pos(size);
    for (int i = 0; i < size; i++) {
        pos[row[i]] = i;
    }

    int swaps = 0;

    // Checks seats in pairs
    for (int i = 0; i < size - 1; i += 2) {
        int first   = row[i];
        int partner = getPartner(first);

        // Swaps persons seat next to partner if not seated together
        if (row[i + 1] != partner) {
            int partnerSeat = pos[partner];   // partners position
            int displaced   = row[i + 1];     // person swapping seats

            std::swap(row[i + 1], row[partnerSeat]);

            // Update the lookup table for the two people who moved
            pos[partner]   = i + 1;
            pos[displaced] = partnerSeat;

            swaps++;

            if (SHOW_EACH_SWAP) {
                printRow("  Swap " + std::to_string(swaps) + ": ", row);
            }
        }
    }

    return swaps;
}

/*Executes the program
    Given an input of rows assuming each integer is an ID of a person,
    the row is print with printRow(), and then minSwapsCouples() goes through each row 
    sorting every persons seat using getPartner() to match their partners so that the row 
    consists of every couple sitting next to their partner */
int main() {
    for (size_t t = 0; t < test_data.size(); t++) {
        std::cout << "Test " << t + 1 << "\n";
        printRow("  Input:  ", test_data[t]);

        int result = minSwapsCouples(test_data[t]);

        std::cout << "  Output: " << result << "\n\n";
    }

    return 0;
}
