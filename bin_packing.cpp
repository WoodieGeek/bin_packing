#include "bin_packing.h"

TBinPacking::TBinPacking() {

}

TBinPacking::TBinPacking(int c, const std::vector<int>& weights)
    : C_(c)
    , Weights_(weights)
{
}

int TBinPacking::GetC() const {
    return C_;
}

const std::vector<int>& TBinPacking::GetWeights() const {
    return Weights_;
}

void TBinPacking::Load(std::fstream& fin) {
    size_t n;
    fin >> C_ >> n;
    Weights_.resize(n);
    for (auto& w : Weights_) {
        fin >> w;
    }
}

void TBinPacking::Save(std::fstream &fout) {
    fout << C_ << Weights_.size() << std::endl;
    for (auto& w : Weights_) {
        fout << w << " ";
    }
    fout << std::endl;
}
