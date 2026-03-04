#include <cmath>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

using std::size_t;
using std::vector;
bool is_odd(long n) {
    return (n % 2 != 0);
}

bool is_invalid(long id) {
    std::string strid = std::to_string(id);
    size_t size = strid.size();
    if (size == 1) return false;
    // if (is_odd(size)) return false;

    bool break_flag = false;
    size_t halfsize = ceil((double) size / 2);
    for (long i = 1; i <= halfsize; i++) {
        break_flag = false;
        size_t limit = size - i;
        for (size_t j = 0; j < limit; j++) {
            if (strid[j] != strid[j + i]) {
                break_flag = true;
                break;
            }
        }
        if (!break_flag) {
            if (i != 1 && size % i != 0) break;  // Size is not perfectly divisible by i, id size(3) can't be made of substrings of size(2)
            return true;
        };
    }
    return false;
}

void validIds(vector<long> &ids, long lower, long upper) {
    size_t sizelower = (lower == 0) ? 1 : floor(log10(abs(lower))) + 1;
    size_t sizeupper = (upper == 0) ? 1 : floor(log10(abs(upper))) + 1;
    // if (is_odd(sizelower)) {
    //     lower = pow(10, sizelower);
    //     if (lower >= upper) return;
    // }

    size_t halfsize = sizelower / 2;
    for (long i = lower; i <= upper; i++) {
        if (is_invalid(i)) {
            ids.push_back(i);
        }
    }
}

int main() {
    std::ifstream file("daytwo_input.txt");
    if (!file.is_open()) {
        std::cerr << "Error: " << std::strerror(errno) << std::endl;
        return 1;
    }

    std::vector<long> ids;
    std::string segment;
    while (std::getline(file, segment, ',')) {  // Split by comma
        if (segment.empty()) continue;

        // Converting string recieved to stream for >> operators
        std::stringstream ss(segment);
        long lower, upper;
        char dash, comma;
        if (ss >> lower >> dash >> upper) {
            validIds(ids, lower, upper);
        }
    }

    // Finding the sum of all values in vector, idiomatic way :D
    long sum = std::accumulate(ids.begin(), ids.end(), 0L);
    std::cout << "Code: " << sum << std::endl;
    for (const long &a : ids) {
        std::cout << a << ",";
    }
    std::cout << std::endl;
    return 0;
}