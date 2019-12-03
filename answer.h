#ifndef ANSWER_H
#define ANSWER_H

#include <QLabel>
#include <QPainter>


class TAnswer {
public:
    TAnswer();
    void Draw(int x, int y, QWidget* parent) const;
    size_t Length;
    std::vector<std::vector<int>> Plane;
    time_t Time;
public:
    int GetHeight() const;
    int GetWidth() const;
private:
    void DrowRect(int x, int y, int length, QColor color, QWidget* parent) const;
private:
    const int Height_ = 100;
    const int Width_ = 1000;
};

#endif // ANSWER_H
