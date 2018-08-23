#include "mainwindow.h"
#include <QApplication>
#include "minerui.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MinerUI w;
    w.show();

    return a.exec();
}
