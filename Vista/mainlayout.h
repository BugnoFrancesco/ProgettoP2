#ifndef MAINLAYOUT_H
#define MAINLAYOUT_H

#include <QMainWindow>
#include <QLabel>
//#include "supporto/combotype.h"
//#include "supporto/combofilter.h"
#include <QListWidget>
#include <QTextBrowser>
#include <QPushButton>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QComboBox>
#include "boatlist.h"
#include <string>

class MainLayout: public QWidget
{
    Q_OBJECT

    QLabel* text1;
    QLabel* text2;
    QLabel* text3;
    QLabel* text4;

    //ComboType* selectType;
    //ComboFilter* selectFilter;
    QComboBox* selectType;
    QComboBox* selectFilter;

    BoatListWidget *boatList;

    QTextBrowser* infoBoat;
    QPushButton* flush;
    QPushButton* search;
    QPushButton* annulla;
    QPushButton* modifica;
    QPushButton* elimina;
    QPushButton* inserisci;
    QLineEdit* searchBar;

    QLineEdit* consumiBar;
    QLineEdit* autonomiaBar;
    QLineEdit* timeNavBar;
    QLineEdit* migliaBar;

    QPushButton* consumiButton;
    QPushButton* autonomiaButton;
    QPushButton* timeNavButton;
    QPushButton* migliaButton;

    QPushButton* typeButton;
    QPushButton* patenteButton;

public:
    int estraiBarcaSelezionata() const;
    void stampaDettagliBarca(std::string s) const;
    int getInserimentoBarca() const;
    int getFiltro() const;
    std::string getParametroRicerca() const;

    unsigned int getConsumi() const;
    unsigned int getAutonomia() const;
    float getTempo() const;
    float getMiglia() const;
    bool getPatente() const;
    std::string getType() const;


    void flushList();
    void eliminaBarca(unsigned int);
    MainLayout(QWidget * =nullptr);
    BoatListWidget *getList() const;

};

#endif // MAINLAYOUT_H
