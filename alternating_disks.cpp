
// ============================================================
// CPSC 335 - Algorithm Engineering, Project 1
// Algorithm 1: The Alternating Disk Problem
//
// Group members: Chase Hales, Chris Reyes
//
// Description:
//   Starts with 2n disks alternating light and dark (starting
//   with light). Rearranges them so all dark disks are on the
//   left and all light disks are on the right, using only
//   swaps of neighboring disks. Uses left-to-right and
//   right-to-left passes (round trips) until no swaps are made.
//
// Compile: g++ -std=c++17 -o alternating_disks alternating_disks.cpp
// Run:     ./alternating_disks
// ============================================================

#include <iostream>
#include <vector>
#include <string>    // for std::string, std::to_string
#include <utility>   // for std::swap

// ------------------------------------------------------------
// SETTINGS - change these to test different cases
// ------------------------------------------------------------
const int  N              = 4;     // number of light disks (and dark disks)
const char LIGHT          = 'L';   // symbol used for a light disk
const char DARK           = 'D';   // symbol used for a dark disk
const bool SHOW_EACH_PASS = true;  // true = print the row after every pass

// ------------------------------------------------------------
// Prints the current row of disks with a label in front.
// ------------------------------------------------------------
void printDisks(const std::string& label, const std::vector<char>& disks) {
    std::cout << label;
    for (char disk : disks) {
        std::cout << disk << ' ';
    }
    std::cout << '\n';
}

// ------------------------------------------------------------
// Builds the starting row: L D L D ... (2n disks total).
// Even positions are light, odd positions are dark.
// ------------------------------------------------------------
std::vector<char> makeAlternatingDisks(int n) {
    std::vector<char> disks(2 * n);
    for (int i = 0; i < 2 * n; i++) {
        if (i % 2 == 0) {
            disks[i] = LIGHT;
        } else {
            disks[i] = DARK;
        }
    }
    return disks;
}

// ------------------------------------------------------------
// Sorts the disks so all dark disks come before light disks.
// Returns the number of swaps made (m).
// ------------------------------------------------------------
int sortDisks(std::vector<char>& disks) {
    int size    = disks.size();  // total number of disks (2n)
    int m       = 0;             // swap counter
    int pass    = 0;             // pass counter (for printing only)
    bool swapped = true;         // did the last round trip make a swap?

    // Keep doing round trips until a full round trip makes no swaps
    while (swapped) {
        swapped = false;

        // ---- Left-to-right pass ----
        for (int i = 0; i < size - 1; i++) {
            // A light disk before a dark disk is out of order
            if (disks[i] == LIGHT && disks[i + 1] == DARK) {
                std::swap(disks[i], disks[i + 1]);
                m++;
                swapped = true;
            }
        }
        pass++;
        if (SHOW_EACH_PASS) {
            printDisks("Pass " + std::to_string(pass) + " (L->R): ", disks);
        }

        // ---- Right-to-left pass ----
        for (int i = size - 2; i >= 0; i--) {
            if (disks[i] == LIGHT && disks[i + 1] == DARK) {
                std::swap(disks[i], disks[i + 1]);
                m++;
                swapped = true;
            }
        }
        pass++;
        if (SHOW_EACH_PASS) {
            printDisks("Pass " + std::to_string(pass) + " (R->L): ", disks);
        }
    }

    return m;
}

// ------------------------------------------------------------
// Main: builds the row, sorts it, and prints the results.
// ------------------------------------------------------------
int main() {
    std::vector<char> disks = makeAlternatingDisks(N);

    std::cout << "n = " << N << "\n";
    printDisks("Input:  ", disks);
    std::cout << '\n';

    int m = sortDisks(disks);

    std::cout << '\n';
    printDisks("Output: ", disks);
    std::cout << "Number of swaps (m): " << m << '\n';
    std::cout << "Expected n(n+1)/2:   " << N * (N + 1) / 2 << '\n';

    return 0;
}
