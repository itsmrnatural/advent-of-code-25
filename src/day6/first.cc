#include <cstddef>
#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

using std::size_t;
using std::string;

int main() {
    std::ifstream file("daysix_input.txt");
    if (!file.is_open()) {
        std::cerr << "Error: " << std::strerror(errno) << std::endl;
        return 1;
    }

    // --- --- Reading the last line --- ---
    file.seekg(0, std::ios::end);
    std::streampos size = file.tellg();

    for (long i = 2; i <= size; ++i) {
        file.seekg(-i, std::ios::end);
        if (file.peek() == '\n') {  // peek doesn't move the pointer
            file.get();             // move past the newline so getline gets the actual text
            break;
        }
        if (i == size) file.seekg(0);  // reached beginning of file
    }

    string line;
    std::vector<bool> coltype;  // True when column type is multiplication
    if (std::getline(file, line)) {
        std::stringstream ss(line);
        char ch;
        while (ss >> ch) {
            if (ch == '+') {
                coltype.push_back(false);
            } else {
                coltype.push_back(true);
            }
        }
    }
    file.clear();
    file.seekg(0, std::ios::beg);

    std::vector<long> answers(coltype.size());
    for (int i = 0; i < coltype.size(); i++) {
        if (coltype[i] == false) {
            answers[i] = 0;
        } else {
            answers[i] = 1;
        }
    }
    for (int i = 0; i < 4; i++) {
        if (std::getline(file, line)) {
            std::stringstream ss(line);
            int col;
            for (int i = 0; i < coltype.size(); i++) {
                if (!(ss >> col)) break;
                if (coltype[i] == false) {
                    answers[i] += (col);
                } else {
                    answers[i] *= (col);
                }
            }
        }
    }

    long sum = std::accumulate(answers.begin(), answers.end(), 0L);
    std::cout << "Code: " << sum << std::endl;
    return 0;
}