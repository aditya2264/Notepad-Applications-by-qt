#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("NotePad by Aditya Raj Sinha");
    w.show();
    return a.exec();
}
