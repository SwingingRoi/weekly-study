QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FloatingBall
TEMPLATE = app

SOURCES += main.cpp \
           FloatingBallWidget.cpp

HEADERS  += FloatingBallWidget.h

# 添加所需的模块
QT += network

