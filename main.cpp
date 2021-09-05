#include "Modello/Gerarchia/imbarcazione.h"
#include "Modello/Gerarchia/motore.h"
#include "Modello/Gerarchia/vela.h"
#include "Modello/Gerarchia/termico.h"
#include "Modello/Gerarchia/elettrico.h"
#include "Modello/model.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Model s;
    std::cout<<s.numImbarcazioni();
    s.push_end(new Vela());
    std::cout<<s.numImbarcazioni();
    return 0;
}
