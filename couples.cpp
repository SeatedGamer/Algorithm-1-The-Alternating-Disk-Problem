// ============================================================
// CPSC 335 - Algorithm Engineering, Project 1
// Algorithm 2: Connecting Pairs of Persons
//
// Group members: [add names here]
//
// Description:
//   n couples sit in 2n seats in a row. row[i] is the ID of the
//   person in seat i. Couples are (0,1), (2,3), ..., (2n-2, 2n-1).
//   Finds the minimum number of swaps (any two people trade seats)
//   so that every couple sits side by side.
//
//   Uses a greedy approach: check seats in pairs, and if a person's
//   partner is not next to them, swap the partner into that seat.
//   A lookup table (pos) stores each person's seat so partners are
//   found in constant time.
//
// Compile: g++ -std=c++17 -o couples couples.cpp
// Run:     ./couples
// ============================================================

#include <iostream>
#include <vector>
#include <string>
#include <utility>   // for std::swap

// ------------------------------------------------------------
// SETTINGS - change these to test different cases
// ------------------------------------------------------------

// Each inner list is one test row. Add, remove, or edit rows freely.
// Rules: even length, unique IDs from 0 to (length - 1).
const std::vector<std::vector<int>> TEST_ROWS = {
    {0, 2, 1, 3},             // Sample 1 from the handout (expected 1)
    {3, 2, 0, 1},             // Sample 2 from the handout (expected 0)
    {0, 3, 2, 5, 4, 1},       // extra test (expected 2)
    {5, 4, 2, 6, 3, 1, 0, 7}  // extra test (expected 2)
};

const bool SHOW_EACH_SWAP = true;  // true = print the row after every swap

// ------------------------------------------------------------
// Prints a row of IDs with a label in front, like: [0, 2, 1, 3]
// ------------------------------------------------------------
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

// ------------------------------------------------------------
// Returns the partner of a person.
// Even IDs pair with the next ID (0 -> 1), odd with the previous (1 -> 0).
// ------------------------------------------------------------
int getPartner(int person) {
    if (person % 2 == 0) {
        return person + 1;
    } else {
        return person - 1;
    }
}

// ------------------------------------------------------------
// Returns the minimum number of swaps so every couple sits together.
// The row is copied so the original test row is not changed.
// ------------------------------------------------------------
int minSwapsCouples(std::vector<int> row) {
    int size = row.size();   // total number of seats (2n)

    // Lookup table: pos[person] = seat that person is sitting in
    std::vector<int> pos(size);
    for (int i = 0; i < size; i++) {
        pos[row[i]] = i;
    }

    int swaps = 0;

    // Check seats in pairs: (0,1), (2,3), (4,5), ...
    for (int i = 0; i < size - 1; i += 2) {
        int first   = row[i];
        int partner = getPartner(first);

        // If the partner is not in the next seat, swap them into it
        if (row[i + 1] != partner) {
            int partnerSeat = pos[partner];   // where the partner is now
            int displaced   = row[i + 1];     // person being moved out

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

// ------------------------------------------------------------
// Main: runs every test row and prints the results.
// ------------------------------------------------------------
int main() {
    for (size_t t = 0; t < TEST_ROWS.size(); t++) {
        std::cout << "Test " << t + 1 << "\n";
        printRow("  Input:  ", TEST_ROWS[t]);

        int result = minSwapsCouples(TEST_ROWS[t]);

        std::cout << "  Output: " << result << "\n\n";
    }

    return 0;
}
