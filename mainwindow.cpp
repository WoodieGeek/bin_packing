#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

#include "solvers/next_fit.h"
#include "solvers/first_fit.h"
#include "solvers/best_fit.h"
#include "solvers/proposed_algorithm.h"
#include "solvers/genetic_algorithm.h"
#include "solvers/ffd.h"

#include "tests_generation.h"

namespace {

void CreateTests(int testNumber) {
    for (size_t i = 2, test = 0; i < 16; i++, test++) {
        size_t elements = (1 << i);
        auto problem = TTestGeneretion::GenerateProblem(elements);
        std::string fname = "tests/test_" + std::to_string(test);
        std::fstream fout;
        fout.open("tests/test_" + std::to_string(test));
        problem.Save(fout);
        fout.close();
    }
}

}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Table_ = new QTableWidget(this);
    connect(Table_, SIGNAL(cellClicked(int,int)), this, SLOT(TableChanged(int,int)));
    SolveName_ = {"Next-Fit", "First-Fit", "Best-Fit", "FFD", "Genetic"};
    auto solvers = std::tuple<TNextFit, TFirstFit, TBestFit, TFFD, TGenetic>();

    int testNumber = 1;
    //CreateTests(testNumber);
    LoadProblems(testNumber);
    qDebug() << Problems_.size()  << "!";
    for (const auto& problem : Problems_) {
        std::vector<TAnswer> currentAnswers;
        auto add2Answers = [&](auto&& x) {
            currentAnswers.push_back(problem.GetAnswer(x));
        };
        std::apply([&](auto ...x) {
            (..., add2Answers(x));
        }, solvers);
        Answers_.push_back(std::move(currentAnswers));
    }

}

void MainWindow::paintEvent(QPaintEvent *) {
    DrawTable();
    QPainter* painter = new QPainter(this);
    QFont font = painter->font();
    font.setPointSize(15);
    painter->setFont(font);

    int fromLeft = 550;
    int fromTop = 200;
    int interval = 200;

    if (CurrentIndex_ == -1) {
        return;
    }
    const auto& problem = Problems_[CurrentIndex_];
    problem.Draw(fromLeft, 50, this);
    const auto& answers = Answers_[CurrentIndex_];
    for (size_t i = 0; i < SolveName_.size(); i++) {
        painter->drawText(fromLeft, fromTop + interval * i - 5, SolveName_[i]);
    }
    for (size_t i = 0; i < answers.size(); i++) {
        answers[i].Draw(fromLeft, fromTop + interval * i, this);
    }
    delete painter;
}

void MainWindow::LoadProblems(size_t testNumber) {
    Problems_.clear();
    for (size_t i = 0; i < testNumber; ++i) {
        std::fstream fin;
        fin.open("tests/test_" + std::to_string(i));
        if (!fin.is_open()) {
            continue;
        }
        TBinPacking tmpProblem;
        tmpProblem.Load(fin);
        Problems_.push_back(std::move(tmpProblem));
    }
}

void MainWindow::DrawTable() {
    if (Answers_.empty()) {
        return;
    }
    Table_->verticalHeader()->hide();
    Table_->horizontalHeader()->hide();
    Table_->setColumnCount(4);
    const auto& solveNumber = SolveName_.size();
    Table_->setRowCount(Answers_.size() * solveNumber);
    for (size_t i = 0; i < Answers_.size(); ++i) {
        const auto& n = Problems_[i].GetWeights().size();
        for (size_t j = 0; j < Answers_[i].size(); ++j) {
            const auto& time = Answers_[i][j].Time;
            const auto& cnt = Answers_[i][j].Plane.size();
            auto *itemN = new QTableWidgetItem(QString::number(n));
            auto *itemTime = new QTableWidgetItem(QString::number(time));
            auto *itemCnt = new QTableWidgetItem(QString::number(cnt));
            auto *itemName = new QTableWidgetItem(SolveName_[j]);
            if (i & 1) {
                itemName->setBackgroundColor(Qt::lightGray);
            }
            const auto& current = i * solveNumber;
            Table_->setItem(current + j, 0, itemName);
            Table_->setItem(current + j, 1, itemN);
            Table_->setItem(current + j, 2 , itemCnt);
            Table_->setItem(current + j, 3, itemTime);
        }
    }
    Table_->setGeometry(25, 100, 500, 900);
    Table_->show();
}

void MainWindow::TableChanged(int x, int y) {
    CurrentIndex_ = x / SolveName_.size();
    repaint();
}

MainWindow::~MainWindow()
{
    delete ui;
}
