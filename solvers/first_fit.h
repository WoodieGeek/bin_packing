#ifndef FIRST_FIT_H
#define FIRST_FIT_H
#include "bin_packing.h"

class TFirstFit {
public:
    TAnswer Solve(const TBinPacking& problem) {
        TAnswer result;
        const auto& weights = problem.GetWeights();
        const auto& c = problem.GetC();
        std::vector<int> sums;
        for (const auto& item : weights) {
            bool wasInserted = false;
            for (size_t i = 0; i < sums.size(); i++) {
                if (sums[i] + item <= c) {
                    sums[i] += item;
                    result.Plane[i].push_back(item);
                    wasInserted = true;
                    break;
                }
            }
            if (!wasInserted) {
                sums.push_back(item);
                result.Plane.push_back({item});
            }
        }
        result.Length = c;
        return result;
    }
};

#endif // FIRST_FIT_H
