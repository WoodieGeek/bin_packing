#ifndef PROPOSED_ALGORITHM_H
#define PROPOSED_ALGORITHM_H
#include "bin_packing.h"


class TProposed {
public:
    TProposed() = default;
    TAnswer Solve(const TBinPacking &problem) {
        Weights_ = problem.GetWeights();
        C_ = problem.GetC();
        MakeRanges();
        BigRange();
        size_t i = RANGES / 2;
        do {
            i--;
            while (Ranges_[i].size() >= 2) {
                Add(i, i);
            }
            BigRange();

        } while (i != 0);
        Answer_.Length = problem.GetC();
        return Answer_;
    }
    ~TProposed() = default;
private:

    void Add(size_t indexA, size_t indexB) {
        std::vector<int> result;
        const auto& [sA, A] = Ranges_[indexA].back();
        const auto& [sB, B] = Ranges_[indexB].back();
        std::copy(A.begin(), A.end(), std::back_inserter(result));
        std::copy(B.begin(), B.end(), std::back_inserter(result));
        auto sum = sA + sB;
        Ranges_[ToRange(sum)].push_back({sum, result});
        Ranges_[indexA].pop_back();
        Ranges_[indexB].pop_back();
    }

    double ToRange(int weight) {
        if (weight == C_)
            weight--;
        return static_cast<double_t>(weight) / static_cast<double>(C_) * RANGES;;
    }

    void AddToResult(size_t index) {
        Answer_.Plane.push_back(Ranges_[index].back().second);
        Ranges_[index].pop_back();
    }

    void MakeRanges() {
        Ranges_.resize(RANGES);
        for (const auto& w : Weights_) {
            auto range = ToRange(w);
            Ranges_[static_cast<size_t>(range)].push_back({w, {w}});
        }
    }

    void BigRange() {
        for (size_t i = RANGES / 2; i < RANGES; i++) {
            while (!Ranges_[i].empty()) {
                auto hasAdd = false;
                size_t j = RANGES - i + 1;
                const auto& [sA, A] = Ranges_[i].back();
                do {
                    if (!Ranges_[--j].empty() && sA + Ranges_[j].back().first <= C_) {
                        Add(i, j);
                        hasAdd = true;
                        break;
                    }
                } while (j != 0);
                if (!hasAdd) {
                    AddToResult(i);
                }
            }
        }
    }

private:
    std::vector<int> Weights_;
    int C_;
    using URange = std::pair<int, std::vector<int>>;
    std::vector<std::vector<URange>> Ranges_;
    static constexpr size_t RANGES = 10;
    TAnswer Answer_;
};


#endif // PROPOSED_ALGORITHM_H
