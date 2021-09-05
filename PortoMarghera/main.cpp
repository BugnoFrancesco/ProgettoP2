#include "imbarcazione.h"
#include "motore.h"
#include "vela.h"
#include "termico.h"
#include "elettrico.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Vela w;
    Termico t;
    Elettrico e;

    return a.exec();
}
