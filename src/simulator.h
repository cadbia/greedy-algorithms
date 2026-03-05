#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <vector>

int simulateFIFO(int k, const std::vector<int>& req);
int simulateLRU(int k, const std::vector<int>& req);
int simulateOPTFF(int k, const std::vector<int>& req);

#endif // SIMULATOR_H
