#include "boatlist.h"
#include <iostream>

BoatListWidget::BoatListWidget(QWidget *parent):QListWidget (parent){
    connect(this,SIGNAL(itemSelectionChanged()),parent->parent(),SLOT(slotShowBoat()));
}
/**
 * @brief getIndex ritorna l'indice della lista selezionato al momento
 * @return int rappresentante l'indice della lista
 */
unsigned int BoatListWidget::getIndex() const {
    return currentRow();
}
/**
 * @brief getItem l'item della lista selezionato al momento
 * @return item della lista
 */
BoatListWidgetItem* BoatListWidget::getItem() const {
    BoatListWidgetItem* item=static_cast<BoatListWidgetItem*>(currentItem());
    return item;
}
/**
 * @brief getItem seleziona il treno estratto dall'item della lista in posizione indicata dal parametro
 * @param x= indice della lista
 * @return campo imbarcazione dell'item in posizione x
 */
Imbarcazione* BoatListWidget::getItemByIndex(unsigned int x) const
{
    BoatListWidgetItem* it=static_cast<BoatListWidgetItem*>(item(x));
    return it->getImbarcazione();
}
/**
 * @brief addBoatList aggiunge un nuovo item alla lista
 * @param boat = imbarcazione da aggiungere
 * @param x = posizione reale nel suo contenitore dell'imbarcazione
 */
void BoatListWidget::addBoatList(Imbarcazione* boat, unsigned int x){
    BoatListWidgetItem* item= new BoatListWidgetItem(boat, x);
    addItem(item);
}
/**
 * @brief clear svuota la lista
 */
void BoatListWidget::clear()
{
    for(int i=0; i<count(); ){
         delete takeItem(0);;
    }
}
/**
 * @brief erase elimina l'item in posizione x
 * @param x = indice della lista
 */
void BoatListWidget::erase(unsigned int x)
{
    delete takeItem(x);
}

BoatListWidgetItem::BoatListWidgetItem(Imbarcazione* t,unsigned int index, QWidget *p ): QListWidgetItem(), t(t), parent(p), realIndex(index){
    setText(QString::fromStdString(t->getNome()));
}
/**
 * @brief getRealIndex ritorna la posizione originale dell'imbarcazione rispetto a tutti gli altri senza considerare i filtri
 * @return intero rappresentante la posizione dell'imbarcazione
 */
unsigned int BoatListWidgetItem::getRealIndex() const{
    return realIndex;
}
Imbarcazione* BoatListWidgetItem::getImbarcazione() const{
    return t;
}
