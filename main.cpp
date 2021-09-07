
#include "Vista/mainwindow.h"
#include <QApplication>
#include <iostream>
#include "Modello/model.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
        MainWindow w(new Model());
        w.show();
        return a.exec();
}
