#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPaintEvent>

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
    Ui::MainWindow *ui;
    std::vector<TAnswer> Answers_;
    std::vector<QString> SolveName_;
public slots:
    void paintEvent(QPaintEvent*);
};

#endif // MAINWINDOW_H
