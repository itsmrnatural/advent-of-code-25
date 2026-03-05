# Advent of code 2025

This repository contains solutions of advent of code days that I solved during free time. This exists here for reference purposes for myself and other who might want to look at it.

## Usage

Each day's solution is located in the `src/` directory, organized by day. Input files (`dayone_input.txt`, etc.) are expected to be in the root directory.

### Prerequisites

- A C/C++ compiler (GCC or Clang)

### Compilation and Execution

1. Create a build directory if it doesn't exist:
   ```bash
   mkdir -p build
   ```

2. Compile the source file (replace `dayX` and source file as needed):
   
   For C files (e.g., Day 1):
   ```bash
   gcc src/day1/second.c -o build/dayone
   ```

   For C++ files (e.g., Day 2):
   ```bash
   g++ -std=c++17 src/day2/first.cc -o build/daytwo
   ```

3. Run the executable:
   ```bash
   ./build/dayone
   ```

# License
All of this code is licensed under the [MIT license](/LICENSE.md).