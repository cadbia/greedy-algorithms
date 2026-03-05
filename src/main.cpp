#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int simulateFIFO(int k, const std::vector<int>& req) {
    // stub def
    return -1;
}

int simulateLRU(int k, const std::vector<int>& req) {
    // stub def
    return -1;
}

int simulateOPTFF(int k, const std::vector<int>& req) {
    // stub def
    return -1;
}

int main(int argc, char* argv[]) {
    // verify arg count
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_filename>\n";
        std::cerr << "Example: " << argv[0] << " data/example.in\n";
        return 1;
    }

    std::string filename = argv[1];
    std::ifstream infile(filename);

    if (!infile.is_open()) {
        std::cerr << "Error: Could not open file " << filename << "\n";
        return 1;
    }

    // read first line: k and m
    int k, m;
    if (!(infile >> k >> m)) {
        std::cerr << "Error: Invalid file format. Expected k and m.\n";
        return 1;
    }

    if (k < 1) {
        std::cerr << "Error: Cache size k must be >= 1.\n";
        return 1;
    }

    // read exactly m req
    std::vector<int> req(m);
    for (int i = 0; i < m; ++i) {
        if (!(infile >> req[i])) {
            std::cerr << "Error: Expected " << m << " requests but only found " << i << ".\n";
            return 1;
        }
    }

    // run simulators and output strings
    std::cout << "FIFO : " << simulateFIFO(k, req) << "\n";
    std::cout << "LRU : " << simulateLRU(k, req) << "\n";
    std::cout << "OPTFF : " << simulateOPTFF(k, req) << "\n";

    return 0;
}
