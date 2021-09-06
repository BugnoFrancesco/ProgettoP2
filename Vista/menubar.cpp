#include "menubar.h"

MenuBar::MenuBar(QWidget* p):
    parent(p),
    infoGenerali(new QAction("Info Generali",this)),
    conversioniUtili(new QMenu("Conversioni Utili", this)),
    conversioneKMh(new QAction("Nodi => Km/h",conversioniUtili)),
    conversioneKM(new QAction("Miglia => Km",conversioniUtili)),
    autore(new QAction("Autore",this))
{
    conversioniUtili->addAction(conversioneKMh);
    conversioniUtili->addAction(conversioneKM);
    addAction(infoGenerali);
    addMenu(conversioniUtili);
    addAction(autore);

    connect(infoGenerali,SIGNAL(triggered()),parent,SLOT(slotShowInfoGenerali()));
    connect(conversioneKMh,SIGNAL(triggered()),parent,SLOT(slotConversioneKMh()));
    connect(conversioneKM,SIGNAL(triggered()),parent,SLOT(slotConversioneKM()));
    connect(autore,SIGNAL(triggered()),parent,SLOT(slotAutore()));
}
