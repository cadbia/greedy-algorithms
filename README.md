# Cache Simulator

This is a C++ project that simulates cache replacement policies (FIFO, LRU, and soon OPTFF), reporting the total number of cache misses. Note that the OPTFF (Optimal Furthest in Future) implementation is pending.

## Repository Structure
- `src/` : Source code (`main.cpp`, `simulator.h`, `simulator.cpp`).
- `data/` : Directory intended for input data files and request sequences.
- `tests/`: Automated test scripts and assertions (`test_small.cpp`, `run.sh`).

## Build
Compile the main simulator program with a C++17 compliant compiler:
```bash
g++ -std=c++17 -O3 -Wall -Wextra src/main.cpp src/simulator.cpp -o cache_sim
```

## Run
The program expects an input file passed via the command line argument.

**Input Format**:
The first line contains `k` (the cache size) and `m` (the total number of memory requests).

The remaining input contains exactly `m` integers representing the sequence of memory requests (these may be spaced out across multiple whitespace-separated lines).

Example run command:
```bash
./cache_sim data/example.in
```

## Testing
Basic test sequences with known miss counts are defined in `tests/test_small.cpp`. A helper wrapper script handles the testing lifecycle.

To compile and verify tests:
```bash
./tests/run.sh
```

## Output Format
The program directly computes and outputs miss counts exactly matching standard format metrics:
```
FIFO : <misses>
LRU : <misses>
OPTFF : <misses>
```

## Assumptions
- Memory request IDs are purely represented as integers.
- Inputs are strictly separated by whitespace.
- The cache size limit `k` must fulfill `k >= 1`.
- A miss occurs exclusively when a requested integer is not present in the current cache footprint. On a miss, the algorithm automatically inserts it. If the cache is full relative to its limit `k`, space is reclaimed according to the explicit replacement policy (FIFO, LRU).
