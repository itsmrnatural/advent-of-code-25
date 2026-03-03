#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using std::string;
using std::stringstream;

long quant(std::vector<std::pair<long, long>> &ranges) {
    long total = 0;
    for (const std::pair<long, long> &range : ranges) {
        // std::cout << "(" << range.first << ", " << range.second << ")" << std::endl;
        total += (range.second - range.first + 1);
    }
    return total;
}

void merge(std::vector<std::pair<long, long>> &ranges) {
    if (ranges.empty()) return;
    std::sort(ranges.begin(), ranges.end());

    std::vector<std::pair<long, long>> merged;
    merged.push_back(ranges[0]);
    for (size_t i = 1; i < ranges.size(); ++i) {
        std::pair<long, long> &last = merged.back();
        std::pair<long, long> &current = ranges[i];

        // Check for overlap
        // If the current start is less than or equal to the last end
        if (current.first <= last.second) {
            // Merge them by updating the end point of last
            last.second = std::max(last.second, current.second);
        } else {
            merged.push_back(current);
        }
    }
    ranges = std::move(merged);
}

int main() {
    std::ifstream file("dayfive_input.txt");
    if (!file.is_open()) {
        std::cerr << "Error: " << std::strerror(errno) << std::endl;
        return 1;
    }

    string line;
    std::vector<std::pair<long, long>> freshids;
    long freshitems = 0;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        // Check the line type
        if (line.find('-') != std::string::npos) {
            stringstream ss(line);
            long a, b;
            char dash;
            if (ss >> a >> dash >> b) {
                freshids.push_back({a, b});
            }
        }
    }
    merge(freshids);
    freshitems = quant(freshids);
    std::cout << "Total: " << freshitems << std::endl;
    return 0;
}