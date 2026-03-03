#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using std::size_t;
using std::string;
using std::vector;
int forklift(vector<vector<char>> &diagram) {
    int rows = diagram.size();
    int cols = rows > 0 ? diagram[0].size() : 0;
    int liftable = 0, delta;

    int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    do {
        delta = 0;
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (diagram[r][c] != '@') continue;

                int neighbors = 0;
                for (int i = 0; i < 8; ++i) {
                    int nr = r + dx[i];
                    int nc = c + dy[i];

                    if (nr >= 0 && nr < rows && nc >= 0 && nc < cols) {
                        if (diagram[nr][nc] == '@') neighbors++;
                    }
                }
                if (neighbors < 4) {
                    diagram[r][c] = 'X';
                    delta++;
                }
            }
        }
        liftable += delta;
    } while (delta > 0);
    return liftable;
}

int main() {
    std::ifstream file("dayfour_input.txt");
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
    std::cout << "Code: " << forklift(diagram) << std::endl;
    return 0;
}