#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using std::string;
using std::vector;
void tachyon_beam(int &splits, vector<vector<char>> &diagram, int row, int col);

void splitter(int &splits, vector<vector<char>> &diagram, int row, int col) {
    // Summons two beams on the side by recursive function calling
    int rows = diagram.size();
    int cols = rows > 0 ? diagram[0].size() : 0;
    if (col + 1 < cols) {
        tachyon_beam(splits, diagram, row + 1, col + 1);
    }
    if (col - 1 >= 0) {
        tachyon_beam(splits, diagram, row + 1, col - 1);
    }
}

void tachyon_beam(int &splits, vector<vector<char>> &diagram, int row, int col) {
    // Beam starts falling downwards from the (row, col) point given
    int rows = diagram.size();
    int cols = rows > 0 ? diagram[0].size() : 0;

    for (int i = row; i < rows; i++) {
        if (diagram[i][col] == '|') break;
        if (diagram[i][col] == '^') {
            splits++;
            return splitter(splits, diagram, i, col);
        }
        diagram[i][col] = '|';
    }
}

int manifold(vector<vector<char>> &diagram) {
    int rows = diagram.size();
    int cols = rows > 0 ? diagram[0].size() : 0;
    int splits = 0;
    tachyon_beam(splits, diagram, 1, (cols / 2));
    return splits;
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