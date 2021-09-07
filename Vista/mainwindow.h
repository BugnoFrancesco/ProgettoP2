#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QLabel>
#include <QListWidget>
#include <QTextBrowser>
#include <QPushButton>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QVBoxLayout>
#include <QLineEdit>


#include "Modello/model.h"
#include "Vista/menubar.h"
#include "Vista/mainlayout.h"
#include "Vista/insertlayout.h"
#include "Vista/modifylayout.h"
#include "boatlist.h"


class MainWindow : public QWidget
{
    Q_OBJECT
private:
    MenuBar* menu;
    Model* modello;
    MainLayout* layout;
    InsertLayout *layoutIns;
    ModifyLayout *layoutMod;

    //filtri
    void searchNome(std::string);
    void searchCantiere(std::string);
    void searchPeso(unsigned int,bool);
    void searchVelocita(unsigned int,bool);
    void searchLunghezza(float,bool);
    void searchNumMotori(unsigned int,bool);
    void searchPotenzaMotori(unsigned int, bool);
    void searchConsumoTermico(unsigned int,bool);
    void searchConsumoElettrico(unsigned int,bool);
    void searchCapienzaSerbatoi(unsigned int,bool);
    void searchCapienzaBatteria(unsigned int,bool);
    void searchTipoMotore(std::string);
    void searchTipoCarburante(std::string);
    void searchTipoBatteria(std::string);
    void searchNumVele(unsigned int,bool);
    void searchMotoreAusi(std::string);
    void searchPotenzaMotoreAusi(unsigned int,bool);

public:
    MainWindow(Model* m,QWidget *parent = nullptr);
    ~MainWindow();
    void refreshList();

public slots:
    void slotShowInfoGenerali();
    void slotConversioneKMh();
    void slotAutore();
    void slotShowBoat();
    void slotFlush();
    void slotRemoveBoat();
    void slotShowInsertBoat();
    void slotInsertBoat();
    void slotShowModifyBoat();
    void slotModifyBoat();
    void slotCerca();
    void slotResetSearch();
    void slotConsumi();
    void slotAutonomia();
    void slotTempoNavigazione();
    void slotMiglia();
    void slotType();
    void slotPatente();
};

#endif // MAINWINDOW_H
