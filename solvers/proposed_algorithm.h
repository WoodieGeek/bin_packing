#ifndef PROPOSED_ALGORITHM_H
#define PROPOSED_ALGORITHM_H
#include "bin_packing.h"

class TProposed {
public:
    TProposed() = default;
    TAnswer Solve(const TBinPacking &problem) {
        freopen("out", "w", stdin);
        Weights_ = problem.GetWeights();
        C_ = problem.GetC();
        MakeRanges();
        BigRange();
        for (int I = 0; I < 10; I++) {
        size_t i = RANGES / 2;
        do {
            i--;
            while (Ranges_[i].size() >= 2) {
                Add(i, i);
            }
            BigRange();

        } while (i != 0);
        }
        for (size_t i = 0; i < Ranges_.size(); i++) {
            for (size_t j = i + 1; j < Ranges_.size(); j++) {
                if (!Ranges_[i].empty() && !Ranges_[j].empty()) {
                    Add(i, j);
                }
            }
        }
        for (size_t i = 0; i < Ranges_.size(); i++) {
            if (!Ranges_[i].empty()) {
                AddToResult(i);
            }
        }
        Answer_.Length = problem.GetC();
        return Answer_;
    }
    ~TProposed() = default;
private:

    void Add(size_t indexA, size_t indexB) {
        std::vector<int> result;
        const auto& [sA, A] = Ranges_[indexA].back();
        size_t last_B = indexA != indexB ? Ranges_[indexB].size() - 1 : Ranges_[indexB].size() - 2;
        const auto& [sB, B] = Ranges_[indexB][last_B];
        std::copy(A.begin(), A.end(), std::back_inserter(result));
        std::copy(B.begin(), B.end(), std::back_inserter(result));
        auto sum = sA + sB;
        //PRINT();
        std::cout << "Выбираем первый элемент из интервала " << indexA;
        std::cout << " и второй элемент из интервала " << indexB << "\n";
        std::cout << "Создаём новый элемент: \n";
        std::cout << "c = " << sA << " + " << sB <<" = " << sum << " , состоящий из";
        std::cout << " (";
        for (size_t i = 0; i < result.size(); i++) {
            if (i) {
                std::cout << ", ";
            }
            std::cout << result[i];
        }
        std::cout <<")\n";
        std::cout << "И помещем его в " << (int)ToRange(sum) << " интервал\n";
        Ranges_[indexA].pop_back();
        Ranges_[indexB].pop_back();
        Ranges_[ToRange(sum)].push_back({sum, result});
    }

    double ToRange(int weight) {
        if (weight == C_)
            weight--;
        return static_cast<double_t>(weight) / static_cast<double>(C_) * RANGES;;
    }

    void AddToResult(size_t index) {
        std::cout << "Добавляем в итоговый результат следующий план раскроя:\n";
        for (auto e : Ranges_[index].back().second) {
            std::cout << e << " ";
        }
        std::cout << std::endl;
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
                    j--;
                    size_t last_j = i != j ? Ranges_[j].size() - 1 : Ranges_[j].size() - 2;
                    const auto& sB = Ranges_[j][last_j].first;
                    if (i == j) {
                        if (Ranges_[i].size() > 2 && sA + sB <= C_) {
                            Add(i, i);
                            hasAdd = true;
                            break;
                        }
                    }
                    else {
                        if (!Ranges_[j].empty() && sA + sB <= C_) {
                            Add(i, j);
                            hasAdd = true;
                            break;
                        }
                    }
                } while (j != 0);
                if (!hasAdd) {
                    AddToResult(i);
                }
            }
        }
    }

    void PRINT() {
        static int iter = 0;
        iter++;
        std::cout << "\n------------------\n";
        std::cout << "Итерация: " << iter << std::endl;
        for (size_t i = 0; i < Ranges_.size(); i++) {
            std::cout << i + 1 << " интервал: [";
            for (size_t j = 0; j< Ranges_[i].size(); j++) {
                std::cout << "( " << Ranges_[i][j].first << ", ";
                std::cout << "[ ";
                for (size_t k = 0; k < Ranges_[i][j].second.size(); k++) {
                    auto e = Ranges_[i][j].second[k];
                    if (k) std::cout << ", ";
                    std::cout << e;

                }
                std::cout << "]), ";
            }
            std::cout << "]\n";
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
