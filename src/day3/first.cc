#include <cstddef>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using std::size_t;
using std::string;
void bridge(int &joltage, const string &bank) {
    size_t len = bank.length();

    char fst = bank[0];
    char snd = bank[1];
    for (size_t i = 1; i < len; i++) {
        if (i < len - 1 && bank[i] > fst) {
            fst = bank[i];
            snd = bank[i + 1];
        } else if (bank[i] > snd) {
            snd = bank[i];
        }
    }
    string jolt = {fst, snd};
    joltage += std::stoi(jolt);
}

int main() {
    std::ifstream file("daythree_input.txt");
    if (!file.is_open()) {
        std::cerr << "Error: " << std::strerror(errno) << std::endl;
        return 1;
    }

    int joltage = 0;
    string segment;
    while (std::getline(file, segment)) {
        if (segment.empty()) continue;

        // Converting string recieved to stream for >> operators
        std::stringstream ss(segment);
        string bank;
        if (ss >> bank) {
            bridge(joltage, bank);
        }
    }
    std::cout << "Code: " << joltage << std::endl;
    return 0;
}