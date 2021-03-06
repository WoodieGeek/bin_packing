#-------------------------------------------------
#
# Project created by QtCreator 2019-10-09T17:03:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = bin_packing
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
CONFIG += c++1z
QMAKE_CXX = g++-7
QMAKE_CC = gcc-7


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    bin_packing.cpp \
    solvers/next_fit.cpp \
    answer.cpp

HEADERS += \
        mainwindow.h \
    bin_packing.h \
    solvers/next_fit.h \
    answer.h \
    solvers/first_fit.h \
    solvers/best_fit.h \
    solvers/proposed_algorithm.h \
    tests_generation.h \
    solvers/genetic_algorithm.h \
    solvers/ffd.h

FORMS += \
        mainwindow.ui
