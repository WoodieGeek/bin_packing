#ifndef CUTTINGSTOCKPROBLEM_H
#define CUTTINGSTOCKPROBLEM_H
#include <bits/stdc++.h>
#include <chrono>
#include "answer.h"

class TBinPacking {
public:
    TBinPacking();
    TBinPacking(int c, const std::vector<int>& weights);
    template <typename Solver>
    TAnswer GetAnswer(Solver& solver) const {
        auto start = std::chrono::system_clock::now();
        auto result = solver.Solve(*this);
        auto end = std::chrono::system_clock::now();
        result.Time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        return std::move(result);
    }
    void Load(std::fstream& fin);
    void Save(std::fstream& fout);
    int GetC() const;
    const std::vector<int>& GetWeights() const;
    void Draw(int x, int y, QWidget* parent) const;
private:
    int C_;
    std::vector<int> Weights_;
};

#endif // CUTTINGSTOCKPROBLEM_H
