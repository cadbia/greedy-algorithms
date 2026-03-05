#!/bin/bash
set -e

# Build the test executable
echo "Compiling tests/test_small.cpp..."
g++ -O3 -Wall -Wextra tests/test_small.cpp src/simulator.cpp -o tests/test_small_bin

# Run the test
echo "Running tests..."
./tests/test_small_bin

echo "Tests completed successfully."
