/* 
CPSC 335 - Algorithm Engineering, Project 1
Algorithm 1: The Alternating Disk Problem

Group members: Chase Hales, Chris Reyes, Alexavier Lualhati, Darren Ngo

Compile: g++ -std=c++17 -o alternating_disks alternating_disks.cpp
Run: ./alternating_disks
*/

#include <iostream>
#include <vector>
#include <string>
#include <utility>

const int  num_disks = 4;
const char light = 'L';
const char dark = 'D';

// Creates the row of alternating disks
std::vector<char> make_alternating_disks(int n) {
    std::vector<char> disks(2 * n);
    for (int i = 0; i < 2 * n; i++) {
        if (i % 2 == 0) {
            disks[i] = dark; // interchangeable with light
        } else {
            disks[i] = light; // interchangeable with dark
        }
    }
    return disks;
}

// Prints the row of disks
void print_disks(const std::string& label, const std::vector<char>& disks) {
    std::cout << label;
    for (char disk : disks)
        std::cout << disk << ' ';
    std::cout << '\n';
}

// Sorts the disks so that all dark disks are on the left hand side all light disks are on the right
int sort_disks(std::vector<char>& disks) {
    int size = disks.size();
    int swaps = 0;
    int passes = 0;
    bool swapped = true;

    // Keep passing through the row swapping disks until all disks are sorted on one side and no more swaps are done
    while (swapped) {
        swapped = false;

        // Left-to-right pass
        for (int i = 0; i < size - 1; i++) {
            // A light disk before a dark disk is out of order
            if (disks[i] == light && disks[i + 1] == dark) {
                std::swap(disks[i], disks[i + 1]);
                swaps++;
                swapped = true;
            }
        }
        passes++;
        print_disks("Pass " + std::to_string(passes) + " (L->R): ", disks);

        // Right-to-left pass
        for (int i = size - 2; i >= 0; i--) {
            if (disks[i] == light && disks[i + 1] == dark) {
                std::swap(disks[i], disks[i + 1]);
                swaps++;
                swapped = true;
            }
        }
        passes++;
        print_disks("Pass " + std::to_string(passes) + " (R->L): ", disks);
    }

    return passes;
}

int main() {
    std::vector<char> disks = make_alternating_disks(num_disks);

    std::cout << "n = " << num_disks << "\n";
    print_disks("Input:  ", disks);
    std::cout << '\n';

    int sorted_disks = sort_disks(disks);

    std::cout << '\n';
    print_disks("Output: ", disks);
    std::cout << "Number of swaps (m): " << sorted_disks << '\n';
    std::cout << "Expected n(n+1)/2:   " << num_disks * (num_disks + 1) / 2 << '\n';

    return 0;
}
