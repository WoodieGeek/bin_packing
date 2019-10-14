#ifndef NEXT_FIT_H
#define NEXT_FIT_H
#include "bin_packing.h"


class TNextFit {
public:
    TNextFit();
    TAnswer Solve(const TBinPacking &problem) {
        TAnswer result;
        const auto& weights = problem.GetWeights();
        const auto& c = problem.GetC();
        int current = 0;
        for (size_t i = 0; i < weights.size(); i++) {
            if (weights[i] + current > c || result.Plane.empty()) {
                current = weights[i];
                std::vector<int> tmp{weights[i]};
                result.Plane.emplace_back(std::move(tmp));
            }
            else {
                current += weights[i];
                result.Plane.back().push_back(weights[i]);
            }
        }
        result.Length = problem.GetC();
        return result;
    }
    ~TNextFit() = default;
};

#endif // NEXT_FIT_H
