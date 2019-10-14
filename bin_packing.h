#ifndef CUTTINGSTOCKPROBLEM_H
#define CUTTINGSTOCKPROBLEM_H
#include <bits/stdc++.h>
#include "answer.h"

class TBinPacking {
public:
    TBinPacking();
    TBinPacking(int c, const std::vector<int>& weights);
    template <typename Solver>
    TAnswer GetAnswer(Solver& solver) const {
        return solver.Solve(*this);
    }
    void Load(std::fstream& fin);
    void Save(std::fstream& fout);
    int GetC() const;
    const std::vector<int>& GetWeights() const;
private:
    int C_;
    std::vector<int> Weights_;
};

#endif // CUTTINGSTOCKPROBLEM_H
