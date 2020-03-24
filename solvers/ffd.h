#ifndef FFD_H
#define FFD_H
#include "bin_packing.h"

class TFFD {
public:
    TAnswer Solve(const TBinPacking& problem) {
        TAnswer result;
        auto weights = problem.GetWeights();
        std::sort(weights.begin(), weights.end());
        std::reverse(weights.begin(), weights.end());
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

#endif // FFD_H
