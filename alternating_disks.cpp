/* 
CPSC 335 - Algorithm Engineering, Project 1
Algorithm 1: The Alternating Disk Problem

Group members: Chase Hales, Chris Reyes, Alexavier Lualhati, Darren Ngo

Description:
    Using a sorting algorithm, this program will rearrange a row of 2n disks,
    alternating between two colors, light and dark, so that the left hand side
    of the row will contain all dark disks and the right hand side all white disks.

Compile: g++ -std=c++17 -o alternating_disks alternating_disks.cpp
Run:     ./alternating_disks
*/

#include <iostream>
#include <vector>
#include <string>
#include <utility>

const int  N              = 4;     // number of each colored disk
const char LIGHT          = 'L';   // Light disk
const char DARK           = 'D';   // Dark disk
const bool SHOW_EACH_PASS = true;  // prints the row after every pass

// Creates the row of alternating disks
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

// Prints the row of disks
void printDisks(const std::string& label, const std::vector<char>& disks) {
    std::cout << label;
    for (char disk : disks) {
        std::cout << disk << ' ';
    }
    std::cout << '\n';
}

/* Sorts the disks so that all dark disks are on the left hand side 
all light disks are on the right */
int sortDisks(std::vector<char>& disks) {
    int size    = disks.size();  // number of disks (2n)
    int m       = 0;             // swap counter
    int pass    = 0;             // pass counter
    bool swapped = true;         // the disks in the row swapped places

    // Keep passing through the row swapping disks until all disks are sorted on one side and no more swaps are done
    while (swapped) {
        swapped = false;

        // Left-to-right pass
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

        // Right-to-left pass
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

/* Executes the program
    Creates the disks via makeAlternateDisks(), prints them with printDisks(),
    then sorts them using sortDisks() until finally printing out a sorted row of the 
    created disks with printDisk() */
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
