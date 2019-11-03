#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPaintEvent>
#include <QTableWidget>

#include <bits/stdc++.h>
#include "bin_packing.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    void LoadProblems(size_t testNumber);
    void DrawTable();
private:
    Ui::MainWindow *ui;
    std::vector<QString> SolveName_;
    std::vector<TBinPacking> Problems_;
    std::vector<std::vector<TAnswer>> Answers_;
    QTableWidget* Table_;
    int CurrentIndex_ = -1;
public slots:
    void paintEvent(QPaintEvent*);
    void TableChanged(int x, int y);
};

#endif // MAINWINDOW_H
