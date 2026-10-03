/*
CPSC 335 - Algorithm Engineering, Project 1
Algorithm 2: Connecting Pairs of Persons

Group members: Chase Hales, Chris Reyes, Alexavier Lualhati, Darren Ngo
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

// Prints a row of IDs with each ID being the person sitting in the ith seat
void print_row(const std::string& label, const std::vector<int>& row) {
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
int get_partner(int person) {
    if (person % 2 == 0) {
        return person + 1;
    } else {
        return person - 1;
    }
}

// Swaps each person counting the number of swaps done so that all couples are sitting together with their partner
int min_swaps(std::vector<int> row) {
    int size = row.size();

    // Persons seat, position in the row
    std::vector<int> pos(size);
    for (int i = 0; i < size; i++) {
        pos[row[i]] = i;
    }

    int swaps = 0;

    // Checks seats in pairs
    for (int i = 0; i < size - 1; i += 2) {
        int first   = row[i];
        int partner = get_partner(first);

        // Swaps persons seat next to partner if not seated together
        if (row[i + 1] != partner) {
            int partnerSeat = pos[partner];
            int displaced = row[i + 1];

            std::swap(row[i + 1], row[partnerSeat]);

            // Update the lookup table for the two people who moved
            pos[partner]   = i + 1;
            pos[displaced] = partnerSeat;

            swaps++;

            print_row("  Swap " + std::to_string(swaps) + ": ", row);
        }
    }

    return swaps;
}

int main() {
    for (size_t t = 0; t < test_data.size(); t++) {
        std::cout << "Test " << t + 1 << "\n";
        print_row("  Input:  ", test_data[t]);

        int result = min_swaps(test_data[t]);

        std::cout << "  Output: " << result << "\n\n";
    }

    return 0;
}
