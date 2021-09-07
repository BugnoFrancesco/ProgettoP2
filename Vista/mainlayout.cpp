#include "mainlayout.h"
#include "menubar.h"
#include "Modello/model.h"
#include <iostream>
#include <QRegularExpressionValidator>

MainLayout::MainLayout(QWidget* p): QWidget(p),
    text1(new QLabel(this)),
    text2(new QLabel(this)),
    text3(new QLabel(this)),
    text4(new QLabel(this)),
    selectType(new QComboBox(this)),
    selectFilter(new QComboBox(this)),
    infoBoat(new QTextBrowser(this)),
    flush(new QPushButton(this)),
    search(new QPushButton(this)),
    annulla(new QPushButton(this)),
    modifica(new QPushButton(this)),
    elimina(new QPushButton(this)),
    inserisci(new QPushButton(this)),
    searchBar(new QLineEdit(this)),
    consumiBar(new QLineEdit(this)),
    autonomiaBar(new QLineEdit(this)),
    timeNavBar(new QLineEdit(this)),
    migliaBar(new QLineEdit(this)),
    consumiButton(new QPushButton(this)),
    autonomiaButton(new QPushButton(this)),
    timeNavButton(new QPushButton(this)),
    migliaButton(new QPushButton(this)),
    typeButton(new QPushButton(this)),
    patenteButton(new QPushButton(this))

{
    boatList=new BoatListWidget(this);
    boatList->setSelectionMode(QAbstractItemView::SingleSelection);
    setWindowTitle("Marghera Boat");
    text1->setText("Imbarcazioni nel sistema");
    text2->setText("Informazioni specifiche");
    text3->setText("Inserisci Imbarcazione");
    text4->setText("Cerca");

    flush->setText("Svuota");
    search->setText("Cerca");
    annulla->setText("Annulla");
    modifica->setText("Modifica");
    elimina->setText("Elimina");
    inserisci->setText("Inserisci");
    consumiButton->setText("Calcola Consumi");
    autonomiaButton->setText("Calcola Autonomia");
    timeNavButton->setText("Calcola Tempo Navigazione");
    migliaButton->setText("Calcola Miglia");
    typeButton->setText("Tipo Imbarcazione");
    patenteButton->setText("Verifica Richiesta Patente");
    consumiBar->setPlaceholderText("Inserisci il tempo di navigazione");
    autonomiaBar->setPlaceholderText("Inserisci il carburante disponibile");
    timeNavBar->setPlaceholderText("Inserisci le miglia da percorrere");
    migliaBar->setPlaceholderText("Inserisci il tempo di navigazione");

    QHBoxLayout* layout=new QHBoxLayout(this);
    QVBoxLayout* left=new QVBoxLayout();
    QVBoxLayout* right=new QVBoxLayout();
    QHBoxLayout* searchField=new QHBoxLayout();
    QHBoxLayout* bts2=new QHBoxLayout();
    QHBoxLayout* bts3=new QHBoxLayout();
    QHBoxLayout* bts4=new QHBoxLayout();
    QHBoxLayout* cons=new QHBoxLayout();
    QHBoxLayout* aut=new QHBoxLayout();
    QHBoxLayout* temp=new QHBoxLayout();
    QHBoxLayout* migl=new QHBoxLayout();


    left->addWidget(text1);
    left->addWidget(boatList);
    left->addWidget(flush);
    searchBar->setPlaceholderText("Cerca");
    searchBar->setValidator(new QRegularExpressionValidator(QRegularExpression("[A-Z0-9a-z<>=, ]{0,50}/i")));
    consumiBar->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]{0,50}/i")));
    autonomiaBar->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]{0,50}/i")));
    timeNavBar->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]{0,50}/i")));
    migliaBar->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]{0,50}/i")));
    searchField->addWidget(searchBar);
    searchField->addWidget(selectFilter);
    searchField->addWidget(search);
    searchField->addWidget(annulla);

    selectType->addItem("Motore Termico");
    selectType->addItem("Motore Elettrico");
    selectType->addItem("Vela");

    bts2->addWidget(modifica);
    bts2->addWidget(elimina);
    bts3->addWidget(selectType);
    bts3->addWidget(inserisci);
    bts4->addWidget(typeButton);
    bts4->addWidget(patenteButton);
    cons->addWidget(consumiBar);
    cons->addWidget(consumiButton);
    aut->addWidget(autonomiaBar);
    aut->addWidget(autonomiaButton);
    temp->addWidget(timeNavBar);
    temp->addWidget(timeNavButton);
    migl->addWidget(migliaBar);
    migl->addWidget(migliaButton);
    right->addWidget(text4);
    right->addLayout(searchField);
    right->addWidget(text2);
    right->addWidget(infoBoat);
    right->addLayout(bts2);
    right->addLayout(cons);
    right->addLayout(aut);
    right->addLayout(temp);
    right->addLayout(migl);
    right->addLayout(bts4);
    right->addWidget(text3);
    right->addLayout(bts3);
    layout->addLayout(left, 35);
    layout->addLayout(right, 65);
    setLayout(layout);


    connect(flush, SIGNAL(clicked()),p,SLOT(slotFlush()));
    connect(elimina, SIGNAL(clicked()),p,SLOT(slotRemoveBoat()));
    connect(inserisci, SIGNAL(clicked()),p,SLOT(slotShowInsertBoat()));
    connect(modifica, SIGNAL(clicked()),p,SLOT(slotShowModifyBoat()));
    connect(search, SIGNAL(clicked()), p, SLOT(slotCerca()));
    connect(annulla, SIGNAL(clicked()), p, SLOT(slotResetSearch()));
    connect(consumiButton, SIGNAL(clicked()), p, SLOT(slotConsumi()));
    connect(autonomiaButton, SIGNAL(clicked()), p, SLOT(slotAutonomia()));
    connect(timeNavButton, SIGNAL(clicked()), p, SLOT(slotTempoNavigazione()));
    connect(migliaButton, SIGNAL(clicked()), p, SLOT(slotMiglia()));
    connect(typeButton, SIGNAL(clicked()), p, SLOT(slotType()));
    connect(patenteButton, SIGNAL(clicked()), p, SLOT(slotPatente()));

}
/**
 * @brief estraiBarcaSelezionata ritorna l'indice del treno selezionato nella lista dei treni
 * @return intero rappresentante un indice
 */
int MainLayout::estraiBarcaSelezionata() const{
    return boatList->getIndex();
}
BoatListWidget* MainLayout::getList() const{
    return boatList;
}
/**
 * @brief stampaDettagliBarca stampa nell'apposito spazio la stringa che gli viene passata (che rappresenterà una barca in questo formato)
 * @param s= barca in formato stringa
 */
void MainLayout::stampaDettagliBarca(std::string s) const{
    infoBoat->clear();
    infoBoat->setText(QString::fromStdString(s));
}
/**
 * @brief flushList svuota la lista
 */
void MainLayout::flushList(){
    infoBoat->clear();
    boatList->clear();
}
void MainLayout::eliminaBarca(unsigned int t)
{
    boatList->erase(t);
}
int MainLayout::getInserimentoBarca() const{
    return selectType->currentIndex();
}
int MainLayout::getFiltro() const{
    return selectFilter->currentIndex();
}
std::string MainLayout::getParametroRicerca() const{
    return searchBar->text().toStdString();
}
unsigned int MainLayout::getAutonomia() const{
    return autonomiaBar->text().toUInt();
}
unsigned int MainLayout::getConsumi() const{
    return consumiBar->text().toUInt();
}
float MainLayout::getTempo() const{
    return timeNavBar->text().toUInt();
}
float MainLayout::getMiglia() const{
    return migliaBar->text().toUInt();
}
