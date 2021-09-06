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
    void searchCarburanteVapore(std::string);
    void searchTemperaturaVapore(unsigned int, bool);
    void searchEfficenzaElettrico(double,bool);
    void searchPotenzaIC(unsigned int,bool);
    void searchTrasmissioneElettrico(std::string);
    void searchMotoreIC(std::string);
    void searchMotorePrimario(std::string);
    void searchTecnologiaMaglev(std::string);

public:
    MainWindow(Model* m,QWidget *parent = nullptr);
    ~MainWindow();
    void refreshList();

public slots:
    void slotShowInfoGenerali();
    void slotConversioneKMh();
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
