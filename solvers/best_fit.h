#ifndef BEST_FIT_H
#define BEST_FIT_H
#include "bin_packing.h"


class TBestFit {
public:
    TAnswer Solve(const TBinPacking &problem) {
        TAnswer result;
        const auto& weights = problem.GetWeights();
        const auto& c = problem.GetC();
        std::vector<int> sums;
        for (const auto& item : weights) {
            int mn = std::numeric_limits<int>::max();
            size_t mnIndex = -1;
            for (size_t i = 0; i < sums.size(); i++) {
                if (sums[i] + item <= c && c - (item + sums[i]) < mn) {
                    mn = c - (item + sums[i]);
                    mnIndex = i;
                }
            }
            if (mnIndex != -1) {
                sums[mnIndex] += item;
                result.Plane[mnIndex].push_back(item);
            } else {
                sums.push_back(item);
                result.Plane.push_back({item});
            }
        }
        result.Length = problem.GetC();
        return result;
    }
};

#endif // BEST_FIT_H
