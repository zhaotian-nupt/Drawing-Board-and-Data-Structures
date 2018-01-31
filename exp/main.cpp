#include "mainwindow.h"
#include <QApplication>
#include "data.h"

extern Data graph_data;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setFixedSize(1000,800);
    w.show();
    return a.exec();
}
