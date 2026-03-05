#include "simulator.h"

#include <unordered_set>
#include <unordered_map>
#include <deque>
#include <list>

int simulateFIFO(int k, const std::vector<int>& req) {
    std::unordered_set<int> cache;
    std::deque<int> q;
    int misses = 0;

    for (int r : req) {
        if (cache.find(r) == cache.end()) {
            misses++;
            if (cache.size() == static_cast<size_t>(k)) {
                // Handle stale entries in the deque by popping until the front is actually in the set
                while (!q.empty() && cache.find(q.front()) == cache.end()) {
                    q.pop_front();
                }
                if (!q.empty()) {
                    cache.erase(q.front());
                    q.pop_front();
                }
            }
            cache.insert(r);
            q.push_back(r);
        }
    }
    return misses;
}

int simulateLRU(int k, const std::vector<int>& req) {
    std::list<int> lru_list;
    std::unordered_map<int, std::list<int>::iterator> cache_map;
    int misses = 0;

    for (int r : req) {
        auto it = cache_map.find(r);
        if (it == cache_map.end()) {
            misses++;
            if (cache_map.size() == static_cast<size_t>(k)) {
                int last = lru_list.back();
                lru_list.pop_back();
                cache_map.erase(last);
            }
            lru_list.push_front(r);
            cache_map.insert({r, lru_list.begin()});
        } else {
            lru_list.erase(it->second);
            lru_list.push_front(r);
            it->second = lru_list.begin();
        }
    }
    return misses;
}

int simulateOPTFF(int k, const std::vector<int>& req) {
    // Stub definition
    return -1;
}
