#include <cstddef>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#define SUBSEQ_MAX 12

using std::size_t;
using std::string;
void bridge(long &joltage, const string &bank) {
    size_t len = bank.length();
    std::vector<int> subseq;
    subseq.push_back(bank[0] - '0');
    for (size_t i = 1; i < len; i++) {
        while (subseq.size() >= 1 && subseq.back() + '0' < bank[i] && subseq.size() + (len - i) > SUBSEQ_MAX) {
            subseq.pop_back();
        }
        if (subseq.size() < SUBSEQ_MAX) {
            subseq.push_back(bank[i] - '0');
        }
    }

    long jolt = 0;
    for (int digit : subseq) {
        jolt = (jolt * 10) + digit;
    }
    joltage += jolt;
}

int main() {
    std::ifstream file("daythree_input.txt");
    if (!file.is_open()) {
        std::cerr << "Error: " << std::strerror(errno) << std::endl;
        return 1;
    }

    long joltage = 0;
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