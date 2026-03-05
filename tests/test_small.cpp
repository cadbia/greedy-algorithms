#include <iostream>
#include <vector>
#include <cassert>

#include "../src/simulator.h"

int main() {
    // Test 1: Simple monotonic sequence
    // cache size > req size
    std::vector<int> req1 = {1, 2, 3};
    assert(simulateFIFO(5, req1) == 3);
    assert(simulateLRU(5, req1) == 3);

    // Test 2: Repeating sequence
    // cache size 2
    std::vector<int> req2 = {1, 2, 1, 2, 1, 2};
    assert(simulateFIFO(2, req2) == 2);
    assert(simulateLRU(2, req2) == 2);

    // Test 3: Standard eviction examples
    std::vector<int> req3 = {1, 2, 3, 1, 4, 1};
    // FIFO(3): 
    // 1 (miss), 2 (miss), 3 (miss) -> [1, 2, 3]
    // 1 (hit)
    // 4 (miss), evict 1 -> [2, 3, 4]
    // 1 (miss), evict 2 -> [3, 4, 1]
    // misses = 3 + 0 + 1 + 1 = 5
    assert(simulateFIFO(3, req3) == 5);

    // LRU(3):
    // 1 (miss), 2 (miss), 3 (miss) -> [3, 2, 1]
    // 1 (hit) -> [1, 3, 2]
    // 4 (miss), evict 2 -> [4, 1, 3]
    // 1 (hit) -> [1, 4, 3]
    // misses = 3 + 0 + 1 + 0 = 4
    assert(simulateLRU(3, req3) == 4);

    std::cout << "All small tests passed!\n";
    return 0;
}
