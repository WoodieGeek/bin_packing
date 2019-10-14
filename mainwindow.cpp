#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "solvers/next_fit.h"
#include "solvers/first_fit.h"
#include "solvers/best_fit.h"
#include "solvers/proposed_algorithm.h"

#include "tests_generation.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    for (size_t i = 4, test = 0; i < 16; i++, test++) {
        size_t elements = (1 << i);
        auto problem = TTestGeneretion::GenerateProblem(elements);
        std::string fname = "tests/test_" + std::to_string(test);
        std::fstream fout;
        fout.open("tests/test_" + std::to_string(test));
        problem.Save(fout);
        fout.close();
    }
    ui->setupUi(this);
    TBinPacking problem;
    std::fstream fin;
    fin.open("input");
    problem.Load(fin);

    SolveName_ = {"Next-Fit", "First-Fit", "Best-Fit", "Proposed"};
    auto solvers = std::tuple<TNextFit, TFirstFit, TBestFit, TProposed>();
    auto add2Answers = [&](auto&& x) {
        Answers_.push_back(problem.GetAnswer(x));
    };
    std::apply([&](auto ...x) {
        (..., add2Answers(x));
    }, solvers);
}

void MainWindow::paintEvent(QPaintEvent *) {
    QPainter* painter =  new QPainter(this);
    QFont font = painter->font();
    font.setPointSize(15);
    painter->setFont(font);
    for (size_t i = 0; i < SolveName_.size(); i++) {
        painter->drawText(100, 100 + 200 * i - 5, SolveName_[i]);
    }
    for (size_t i = 0; i < Answers_.size(); i++) {
        Answers_[i].Draw(100, 100 + 200 * i, this);
    }
    delete painter;
}

MainWindow::~MainWindow()
{
    delete ui;
}
