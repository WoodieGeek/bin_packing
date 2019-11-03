#ifndef TESTS_GENERATION_H
#define TESTS_GENERATION_H
#include "bin_packing.h"

class TTestGeneretion {
public:
    static TBinPacking GenerateProblem(size_t countElements) {
        size_t length = rand() % 100 + 10;
        std::vector<int> weights(countElements);
        for (auto& w : weights) {
            w = rand() % length;
            if (!w) {
                w = 1;
            }
        }
        return {length, std::move(weights)};
    }
};

#endif // TESTS_GENERATION_H
