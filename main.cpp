#include <QApplication>
#include "FloatingBallWidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FloatingBallWidget w;
    w.show();
    return a.exec();
}

