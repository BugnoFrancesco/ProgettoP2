#include "menubar.h"

MenuBar::MenuBar(QWidget* p):
    parent(p),
    infoGenerali(new QAction("Info Generali",this)),
    autore(new QAction("Autore",this))
{

    addAction(infoGenerali);
    addAction(autore);

    connect(infoGenerali,SIGNAL(triggered()),parent,SLOT(slotShowInfoGenerali()));
    connect(autore,SIGNAL(triggered()),parent,SLOT(slotAutore()));
}
