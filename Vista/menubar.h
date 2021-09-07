#ifndef MENUBAR_H
#define MENUBAR_H

#include <qmenubar.h>

class MenuBar : public QMenuBar
{
    Q_OBJECT

    QWidget* parent;

    QAction* infoGenerali;
    QAction* autore;


public:
    MenuBar(QWidget* = nullptr);

};


#endif // MENUBAR_H
