#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using std::string;
using std::stringstream;

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
        } else {
            long id = std::stoll(line);
            for (const std::pair<long, long> &range : freshids) {
                if (id >= range.first && id <= range.second) {
                    freshitems++;
                    break;
                }
            }
        }
    }
    std::cout << "Total: " << freshitems << std::endl;
    return 0;
}