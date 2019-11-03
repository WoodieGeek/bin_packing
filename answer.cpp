#include "answer.h"

TAnswer::TAnswer() {

}

void TAnswer::Draw(int x, int y, QWidget *parent) const {
    int inputX = x;
    double h = static_cast<double>(Height_) / static_cast<double>(Plane.size());
    for (size_t i = 0; i < Plane.size(); i++) {
        int sum = 0;
        for (size_t j = 0; j < Plane[i].size(); j++) {
            DrowRect(x, y, Plane[i][j], Qt::green, parent);
            double w = static_cast<double>(Plane[i][j]) / static_cast<double>(Length) * static_cast<double>(Width_);
            x += w;
            sum += Plane[i][j];
        }
        if (sum != Length) {
            DrowRect(x, y, Length - sum, Qt::red, parent);
        }
        y += h;
        x = inputX;
    }
}

void TAnswer::DrowRect(int x, int y, int length, QColor color, QWidget *parent) const {
    double w = static_cast<double>(length) / static_cast<double>(Length) * static_cast<double>(Width_);
    double h = static_cast<double>(Height_) / static_cast<double>(Plane.size());
    QRectF rect(x, y, w, h);
    auto* painter = new QPainter(parent);
    painter->setBrush(color);
    painter->drawRect(rect);

    rect.setX(x + w / 2.0); // text position
    rect.setY(y + h / 9.0);
    painter->drawText(rect, QString::number(length));
    delete painter;
}

int TAnswer::GetHeight() const {
    return Height_;
}

int TAnswer::GetWidth() const {
    return Width_;
}
