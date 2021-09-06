#ifndef BOATLIST_H
#define BOATLIST_H

#include <QListWidgetItem>
#include <QListWidget>
#include "Modello/Gerarchia/imbarcazione.h"
#include "Modello/container.h"


class BoatListWidgetItem : public QListWidgetItem
{
    Imbarcazione* t;
    QWidget* parent;
    unsigned int realIndex;

public:
    BoatListWidgetItem(Imbarcazione* t, unsigned int=0, QWidget * p=nullptr);
    unsigned int getRealIndex() const;
    Imbarcazione* getImbarcazione() const;

};

class BoatListWidget : public QListWidget
{
    Q_OBJECT

public:
    BoatListWidget(QWidget * =nullptr);

    unsigned int getIndex() const;
    BoatListWidgetItem* getItem() const;
    Imbarcazione* getItemByIndex(unsigned int x) const;
    void addImbarcazioneList(Imbarcazione* , unsigned int=0);
    void clear();
    void erase(unsigned int);
};

#endif // BOATLIST_H
