#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

using std::string;
using std::vector;

unsigned long manifold(vector<vector<char>> &diagram) {
    long rows = diagram.size();
    long cols = rows > 0 ? diagram[0].size() : 0;
    vector<unsigned long> seq(cols);

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (diagram[r][c] == 'S') {
                seq[c] = 1;
                continue;
            }

            if (diagram[r][c] == '^') {
                if (c - 1 >= 0) seq[c - 1] += seq[c];
                if (c + 1 < cols) seq[c + 1] += seq[c];
                seq[c] = 0;
            };
        }
    }
    unsigned long sum = std::accumulate(seq.begin(), seq.end(), 0L);
    return sum;
}

int main() {
    std::ifstream file("dayseven_input.txt");
    if (!file.is_open()) {
        std::cerr << "Error: " << std::strerror(errno) << std::endl;
        return 1;
    }

    string line;
    vector<vector<char>> diagram;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        // Convert the string line into a vector of chars
        // std::vector has a constructor that takes iterators
        vector<char> row(line.begin(), line.end());
        // Add this row to our 2D grid
        diagram.push_back(row);
    }
    std::cout << "Code: " << manifold(diagram) << std::endl;
    return 0;
}