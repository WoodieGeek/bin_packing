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
    fout << C_ << " " << Weights_.size() << std::endl;
    for (auto& w : Weights_) {
        fout << w << " ";
    }
    fout << std::endl;
}

void TBinPacking::Draw(int x, int y, QWidget* parent) const {
    auto* painter = new QPainter(parent);
    QFont font = painter->font();
    font.setPointSize(15);
    painter->setFont(font);


    int h = 25;
    int w = 50;
    QRectF row1(x, y, w, h);
    painter->drawText(row1, QString::number(C_));

    QString weightsString;
    for (size_t i = 0; i < Weights_.size(); i++) {
        weightsString += QString::number(Weights_[i]) + "  ";
    }

    QRectF row2(x, y + h, w * Weights_.size(), h);
    painter->drawText(row2, weightsString);
}
