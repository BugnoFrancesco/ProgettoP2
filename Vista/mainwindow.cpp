#include "mainwindow.h"
//#include "supporto/combotype.h"
#include <QMessageBox>
#include <QString>
#include "infolayout.h"
#include <iostream>
#include <QFile>
#include <QFileDialog>
#include "boatexception.h"
#include <QMenuBar>
#include <math.h>
using std::string;
using std::cout;

MainWindow::MainWindow(Model* m, QWidget *parent): QWidget(parent), menu(new MenuBar(this)), modello(m), layout(new MainLayout(this)), layoutIns(nullptr), layoutMod(nullptr)
{
    setWindowTitle("Margera Boat");
    QHBoxLayout* mainLayout= new QHBoxLayout(this);
    mainLayout->addWidget(layout);
    mainLayout->setMenuBar(menu);

    setLayout(mainLayout);
}

/**
 * @brief refreshList svuota la lista delle imbarcazioni e la riempie con le imbarcazioni presenti nel modello
 */
void MainWindow::refreshList(){
    layout->getList()->clear();
    for(unsigned int i=0; i<modello->numImbarcazioni(); i++)
        layout->getList()->addImbarcazioneList(modello->getImbarcazione(i),i);
}

/**
 * @brief slotShowInfoGenerali mostra una finestra popup in cui sono presenti delle informazioni riguardanti l'insieme delle imbarcazioni nel sistema
 */
void MainWindow::slotShowInfoGenerali(){
    QString str1= "La quantità di imbarcazioni presenti nel sistema è:  "+QString::number(modello->numImbarcazioni())+" imbarcazioni";
    QString str2= "Il peso medio delle imbarcazioni nel sistema è:  "+QString::number(modello->getPesoMedio())+" kg";
    QString str3= "La velocità media delle imbarcazioni nel sistema è:  "+QString::number(modello->getVelocitaMedia())+" nodi";
    QString str4= "La lunghezza media delle imbarcazioni nel sistema è:  "+QString::number(modello->getLunghezzaMedia())+" m";
    QString str5= "Il peso maggiore registrato è:  "+QString::number(modello->getPesoMax())+" kg";
    QString str6= "La velocità maggiore registrata è:  "+QString::number(modello->getVelocitaMax())+" nodi";
    QString str7= "La lunghezza maggiore registrata è:  "+QString::number(modello->getLunghezzaMax())+" m";

    InfoLayout* info=new InfoLayout(this,str1,str2,str3,str4,str5,str6,str7);
    info->setMargin(8);
    info->exec();
}

/**
 * @brief slotAutore mostra in una finestra di dialogo l'autore del programma
 */
void MainWindow::slotAutore()
{
    QMessageBox::information(this,"Marghera Boat","Autore:\nFrancesco Bugno");
}

/**
 * @brief slotRemoveBoat rimuove l'imbarcazione selezionata nella lista delle imbarcazioni
 */
void MainWindow::slotRemoveBoat() try {
    if(layout->estraiBarcaSelezionata()==-1)   throw new BoatException("Seleziona un'imbarcazione esistente da eliminare");
        unsigned int b=layout->estraiBarcaSelezionata();
        unsigned int i=layout->getList()->getItem()->getRealIndex();
        layout->eliminaBarca(b);
        modello->erase(i);
        refreshList();
}catch(BoatException* e){
    QMessageBox::warning(this,"Marghera Boat",QString::fromStdString(e->getMessage()));
}

/**
 * @brief slotShowBoat mostra le caratteristiche dell'imbarcazione selezionata nella lista delle imbarcazioni
 */
void MainWindow::slotShowBoat(){
    string str="";
    if(layout->estraiBarcaSelezionata()!=-1 && layout->getList()->getItem()){
        str=modello->boat_toString(layout->getList()->getItem()->getRealIndex());
    }
    layout->stampaDettagliBarca(str);
}
/**
 * @brief slotFlush svuota la lista delle imbarcazioni ed il modello
 */
void MainWindow::slotFlush(){
    layout->flushList();
    modello->clear();
}
/**
 * @brief slotShowInsertBoat fa comparire la finestra di inserimento dell'imbarcazione del tipo selezionato dall'utente
 */
void MainWindow::slotShowInsertBoat(){
    int x=layout->getInserimentoBarca();
    layoutIns=new InsertLayout(this,x);
    layoutIns->resize(250,350);
    layoutIns->exec();
}
/**
 * @brief slotInserisciTreno crea un nuovo treno con le informazioni date dall'utente e lo inserisce nel modello
 */
void MainWindow::slotInsertBoat() try {
    unsigned int x=layoutIns->getTipo();
    std::string nome=layoutIns->getNome();
    std::string nome_trimmed=nome;
    nome_trimmed.erase(nome_trimmed.begin(), std::find_if(nome_trimmed.begin(), nome_trimmed.end(),
            std::not1(std::ptr_fun<int, int>(std::isspace))));
    if(nome_trimmed=="") throw new BoatException("Dai il nome del modello di barca");
    std::string cantiere=layoutIns->getCantiere();
    unsigned int speed=layoutIns->getSpeed();
    unsigned int peso=layoutIns->getPeso();
    unsigned int lunghezza=layoutIns->getLunghezza();
    if(x==0){
        unsigned int numMotori=layoutIns->getNumMotori();
        unsigned int potMotore=layoutIns->getPotenzaMotore();
         std::string tipoMotore=layoutIns->getTipoMotore();
        float consumoT=layoutIns->getConsumoTermico();
        unsigned int capSerbatoi=layoutIns->getCapSerbatoi();
         std::string tipoCarb=layoutIns->getTipoCarburante();
        Termico* boat=new Termico(nome, cantiere, peso, speed, lunghezza, numMotori, potMotore, tipoMotore, tipoCarb, consumoT, capSerbatoi);
        modello->push_end(boat);
    }else if(x==1){
        unsigned int numMotori=layoutIns->getNumMotori();
        unsigned int potMotore=layoutIns->getPotenzaMotore();
         std::string tipoMotore=layoutIns->getTipoMotore();
        float consumoE=layoutIns->getConsumoElettrico();
        unsigned int capBatteria=layoutIns->getCapBatteria();
         std::string tipoBatt=layoutIns->getTipoBatteria();
        Elettrico* boat=new Elettrico(nome, cantiere, peso, speed, lunghezza, numMotori, potMotore, tipoMotore, tipoBatt, consumoE, capBatteria);
        modello->push_end(boat);
    }else if(x==2){
        unsigned int numVele=layoutIns->getNumVele();
        unsigned int potMotoreAus=layoutIns->getPotenzaMotoreAusiliario();
        bool motoreAus=layoutIns->getMotoreAusiliario();
        Vela* boat= new Vela(nome, cantiere, peso, speed, lunghezza, motoreAus, potMotoreAus, numVele);
        modello->push_end(boat);
    }
    //prende l'ultima imbarcazione del modello e la aggiunge alla lista
    layout->getList()->addImbarcazioneList(modello->getImbarcazione(modello->numImbarcazioni()-1),modello->numImbarcazioni()-1);
    layout->getList()->setCurrentRow(modello->numImbarcazioni()-1);
    //aggiornamento lista view
    layoutIns->close();
    delete layoutIns;
} catch(BoatException* e){
    QMessageBox::warning(this,"Marghera Boat",QString::fromStdString(e->getMessage()));
}
/**
 * @brief slotShowModifyBoat fa comparire la finestra di modifica dell'imbarcazione selezionata precompilando i valori
 */
void MainWindow::slotShowModifyBoat() try{
    if(layout->estraiBarcaSelezionata()==-1)   throw new BoatException("Seleziona un'imbarcazione esistente da modificare");
    unsigned int index=layout->getList()->getItem()->getRealIndex();
    Imbarcazione* BarcaDaModificare=modello->getImbarcazione(index);
    std::string tipo=BarcaDaModificare->tipoPropulsione();
    /*
     * Vengono usati i dynamic cast dove è necessario poichè non c'è altro modo per estrarre i campi di tipi derivati senza andare a modificare la gerarchia con
     * metodi ad hoc (si usano per questo i normali get)
     */
    if(tipo=="Motore Termico"){
        layoutMod=new ModifyLayout(this,0,index);
        Termico* tmp=dynamic_cast<Termico*>(BarcaDaModificare);
        layoutMod->setNumMotori(tmp->getNumMotori());
        layoutMod->setPotenzaMotore(tmp->getPotenzaMotore());
        layoutMod->setTipoMotore(tmp->getTipoMotore());
        layoutMod->setConsumoTermico(tmp->getConsumo());
        layoutMod->setCapSerbatoi(tmp->getCapienzaSerbatoi());
        layoutMod->setTipoCarburante(tmp->getTipoCombustione());
    }
    else if(tipo=="Motore Elettrico"){
        layoutMod=new ModifyLayout(this,1,index);
        Elettrico* tmp=dynamic_cast<Elettrico*>(BarcaDaModificare);
        layoutMod->setNumMotori(tmp->getNumMotori());
        layoutMod->setPotenzaMotore(tmp->getPotenzaMotore());
        layoutMod->setTipoMotore(tmp->getTipoMotore());
        layoutMod->setConsumoElettrico(tmp->getConsumo());
        layoutMod->setCapBatteria(tmp->getCapienzaBatteria());
        layoutMod->setTipoCarburante(tmp->getTipoBatteria());
    }
    else if(tipo=="Vela"){
        layoutMod=new ModifyLayout(this,2,index);
        Vela* tmp=dynamic_cast<Vela*>(BarcaDaModificare);
        layoutMod->setNumVele(tmp->getNumVele());
        layoutMod->setMotoreAusiliario(tmp->getMotoreAusiliario());
        layoutMod->setPotenzaMotoreAusiliario(tmp->getPotenzaMotoreAusiliario());
    }
    else{
        throw new BoatException("Tipo di propulsione sbagliato");
    }
    layoutMod->setNome(BarcaDaModificare->getNome());
    layoutMod->setCantiere(BarcaDaModificare->getCantiere());
    layoutMod->setPeso(BarcaDaModificare->getPeso());
    layoutMod->setSpeed(BarcaDaModificare->getVelocita());
    layoutMod->resize(250,350);
    layoutMod->exec();
}catch(BoatException* e){
    QMessageBox::warning(this,"Marghera Boat",QString::fromStdString(e->getMessage()));
}
/**
 * @brief slotModifyBoat crea una nuova imbarcazione con le informazioni date dall'utente e la inserisce nel modello al posto della precedente
 */
void MainWindow::slotModifyBoat(){
    unsigned int x=layoutMod->getInd(); //è l'indice reale
    unsigned int tip=layoutMod->getTipo();
    //in base al tipo identificato da tip creo una nuova imbarcazione e la inserisco nel modello
    std::string nomeNew=layoutMod->getNome();
    std::string cantiereNew=layoutMod->getCantiere();
    unsigned int speedNew=layoutMod->getSpeed();
    unsigned int pesoNew=layoutMod->getPeso();
    float lunghezzaNew=layoutMod->getLunghezza();
    if(tip==0){
        unsigned int numMotoriNew=layoutMod->getNumMotori();
        unsigned int potMotoreNew=layoutMod->getPotenzaMotore();
         std::string tipoMotoreNew=layoutMod->getTipoMotore();
        float consumoTNew=layoutMod->getConsumoTermico();
        unsigned int capSerbatoiNew=layoutMod->getCapSerbatoi();
         std::string tipoCarbNew=layoutMod->getTipoCarburante();
        Termico* barcaDaSostituire=new Termico(nomeNew, cantiereNew, pesoNew, speedNew, lunghezzaNew, numMotoriNew, potMotoreNew, tipoMotoreNew, tipoCarbNew, consumoTNew, capSerbatoiNew);
        modello->erase(x);
        modello->push_end(barcaDaSostituire);
    }else if(tip==1){
        unsigned int numMotoriNew=layoutMod->getNumMotori();
        unsigned int potMotoreNew=layoutMod->getPotenzaMotore();
         std::string tipoMotoreNew=layoutMod->getTipoMotore();
        float consumoENew=layoutMod->getConsumoElettrico();
        unsigned int capBatteriaNew=layoutMod->getCapBatteria();
         std::string tipoBattNew=layoutMod->getTipoBatteria();
        Elettrico* barcaDaSostituire=new Elettrico(nomeNew, cantiereNew, pesoNew, speedNew, lunghezzaNew, numMotoriNew, potMotoreNew, tipoMotoreNew, tipoBattNew, consumoENew, capBatteriaNew);
        modello->erase(x);
        modello->push_end(barcaDaSostituire);
    }else if(tip==2){
        unsigned int numVeleNew=layoutMod->getNumMotori();
        unsigned int potMotoreAusNew=layoutMod->getPotenzaMotoreAusiliario();
        bool motoreAusNew=layoutMod->getMotoreAusiliario();
        Vela* barcaDaSostituire=new Vela(nomeNew, cantiereNew, pesoNew, speedNew, lunghezzaNew, motoreAusNew, potMotoreAusNew, numVeleNew);
        modello->erase(x);
        modello->push_end(barcaDaSostituire);

    }
    //refresh lista
    refreshList();
    layout->getList()->setCurrentRow(x);
    layoutMod->close();
    delete layoutMod;
}
/**
 * @brief slotCerca filtra la lista delle imbarcazioni a seconda del parametro scelto dall'utente
 */
void MainWindow::slotCerca(){
    try{
    unsigned int filtro=layout->getFiltro();
    std::string parametro=layout->getParametroRicerca();
    switch(filtro){
    case 0:
        searchNome(parametro);
        break;
    case 1:
        searchCantiere(parametro);
        break;
    case 2:
        searchPeso(std::stoi(parametro));
        break;
    case 3:
        searchVelocita(std::stoi(parametro));
        break;
    case 4:
        searchLunghezza(std::stoi(parametro));
        break;

    }
    }
    catch(BoatException* e){
        if(e->getMessage()=="ricerca sbagliata"){
            for(int i=0;i<layout->getList()->count();)   layout->getList()->erase(i);
        }
    }
    catch(...){
        QMessageBox::warning(this,"Marghera Boat","Qualcosa è andato storto, controlla i parametri di ricerca e riprova");
    }

}
/**
 * @brief slotResetSearch annulla il filtraggio applicato alla lista delle imbarcazioni se presente
 */
void MainWindow::slotResetSearch(){
    refreshList();
}

/**
 * @brief searchNome filtra la lista delle imbarcazioni mantenendo solo le barche aventi il nome simile al parametro inserito dall'utente
 * @param n = stringa inserita dall'utente
 */
void MainWindow::searchNome(std::string n)
{
    unsigned int lun=layout->getList()->count();
    for(unsigned int i=0; i<lun; ++i){
        std::string nome=layout->getList()->getItemByIndex(i)->getNome();
        transform(nome.begin(), nome.end(), nome.begin(),
            [](unsigned char c){ return toupper(c); });
        transform(n.begin(), n.end(), n.begin(),
            [](unsigned char c){ return toupper(c); });
        if(n!=nome){
            if(nome.find(n)==std::string::npos){
                layout->getList()->erase(i);
                --i; --lun;
            }
        }
    }
}
/**
 * @brief searchCantiere filtra la lista delle imbarcazioni mantenendo solo le barche aventi il cantiere di costruzione simile al parametro inserito dall'utente
 * @param n = stringa inserita dall'utente
 */
void MainWindow::searchCantiere(std::string n)
{
    unsigned int lun=layout->getList()->count();
    for(unsigned int i=0; i<lun; ++i){
        std::string costruttore=layout->getList()->getItemByIndex(i)->getCantiere();
        transform(costruttore.begin(), costruttore.end(), costruttore.begin(),
            [](unsigned char c){ return toupper(c); });
        transform(n.begin(), n.end(), n.begin(),
            [](unsigned char c){ return toupper(c); });
        if(n!=layout->getList()->getItemByIndex(i)->getCantiere()){
            if(costruttore.find(n)==std::string::npos){
                layout->getList()->erase(i);
                --i; --lun;
            }
        }
    }
}

/**
 * @brief searchPeso filtra la lista delle imbarcazioni mantenendo solo quelle aventi il peso maggiore o minore del parametro inserito dall'utente
 * @param n = peso inserito dall'utente
 * @param b = scelta se selezionare solo i maggiori o solo i minori
 */
void MainWindow::searchPeso(unsigned int n){
    unsigned int lun=layout->getList()->count();
    for(unsigned int i=0; i<lun; ++i){
        if(layout->getList()->getItemByIndex(i)->getPeso()<n){
            layout->getList()->erase(i);
            --i; --lun;
        }
    }
}
/**
 * @brief searchVelocita filtra la lista dlle imbarcazioni mantenendo solo quelle aventi la velocità maggiore o minore del parametro inserito dall'utente
 * @param n = velocita inserito dall'utente
 * @param b = scelta se selezionare solo i maggiori o solo i minori
 */
void MainWindow::searchVelocita(unsigned int n){
    unsigned int lun=layout->getList()->count();
    for(unsigned int i=0; i<lun; ++i){
        if( layout->getList()->getItemByIndex(i)->getVelocita()<n){
            layout->getList()->erase(i);
            --i; --lun;
        }

    }
}
/**
 * @brief searchLunghezza filtra la lista dlle imbarcazioni mantenendo solo quelle aventi la lunghezza maggiore o minore del parametro inserito dall'utente
 * @param n = lunghezza inserita dall'utente
 * @param b = scelta se selezionare solo i maggiori o solo i minori
 */
void MainWindow::searchLunghezza(float n){
    unsigned int lun=layout->getList()->count();
    for(unsigned int i=0; i<lun; ++i){
        if(layout->getList()->getItemByIndex(i)->getLunghezza()<n){
            layout->getList()->erase(i);
            --i; --lun;
        }

    }
}


/**
 * @brief slotConsumi mostra una finestra pop up contenente i litri necessari per l'imbarcazione selezionata nella lista  per navigare il tempo indicato nell'apposita barra dall'utente.
 * Nel caso un'imbarcazione non utilizzi i motori per navigare ma solamente per attraccare al porto come per esempio le barche a vela, sarà bloccato a 0
 */
void MainWindow::slotConsumi() {
    if(layout->getList()->getItem()){
        if(layout->getList()->getItem()->getImbarcazione()->tipoPropulsione()=="Motore Termico"){
        unsigned int mostra=layout->getList()->getItem()->getImbarcazione()->calcoloConsumi(layout->getConsumi());
        std::string str="I Litri necessari per navigare "+std::to_string(layout->getConsumi())+" ore sono: "+std::to_string(mostra)+" L";
        QMessageBox::information(this,"Marghera Boat",QString::fromStdString(str));
        }
        else if(layout->getList()->getItem()->getImbarcazione()->tipoPropulsione()=="Motore Elettrico"){
            unsigned int mostra=layout->getList()->getItem()->getImbarcazione()->calcoloConsumi(layout->getConsumi());
            std::string str="I KW necessari per navigare "+std::to_string(layout->getConsumi())+" ore sono: "+std::to_string(mostra)+" KW";
            QMessageBox::information(this,"Marghera Boat",QString::fromStdString(str));
        }
        else if(layout->getList()->getItem()->getImbarcazione()->tipoPropulsione()=="Vela"){
            try{
                unsigned int mostra;
                mostra=layout->getList()->getItem()->getImbarcazione()->calcoloAutonomia(layout->getAutonomia());
            }catch(BoatException* e){
                QMessageBox::information(this,"Marghera Boat","Questa operazione non puo' essere eseguita con le barche a vela");
            }
            catch(...){}
        }
    }
}
/**
 * @brief slotAutonomia mostra una finestra pop up contenente il tempo di navigazione dell'imbarcazione selezionata nella lista dati i litri di carburante imbarcati indicati nell'apposita barra dall'utente.
 * Nel caso un'imbarcazione non utilizzi i motori per navigare ma solamente per attraccare al porto come per esempio le barche a vela, sarà bloccato a 0
 */
void MainWindow::slotAutonomia() {
    if(layout->getList()->getItem()){
        if(layout->getList()->getItem()->getImbarcazione()->tipoPropulsione()=="Motore Termico"){
            unsigned int mostra=layout->getList()->getItem()->getImbarcazione()->calcoloAutonomia(layout->getAutonomia());
            std::string str="Il tempo di autonomia della barca con "+std::to_string(layout->getAutonomia())+"L di carburante imbarcato e': "+std::to_string(mostra);
            QMessageBox::information(this,"Nieva Trains",QString::fromStdString(str));
        }
        else if(layout->getList()->getItem()->getImbarcazione()->tipoPropulsione()=="Motore Elettrico"){
            unsigned int mostra=layout->getList()->getItem()->getImbarcazione()->calcoloAutonomia(layout->getAutonomia());
            std::string str="Il tempo di autonomia della barca con "+std::to_string(layout->getAutonomia())+"KW di carica batterie e': "+std::to_string(mostra);
            QMessageBox::information(this,"Nieva Trains",QString::fromStdString(str));
        }
        else if(layout->getList()->getItem()->getImbarcazione()->tipoPropulsione()=="Vela"){
            try{
                unsigned int mostra;
                mostra=layout->getList()->getItem()->getImbarcazione()->calcoloAutonomia(layout->getAutonomia());
            }catch(BoatException* e){
                QMessageBox::information(this,"Marghera Boat","Questa operazione non puo' essere eseguita con le barche a vela");
            }
            catch(...){}
        }

    }

}


/**
 * @brief slotTempoNavigazione mostra una finestra pop up contenente il tempo di navigazione dell'imbarcazione selezionata nella lista per navigare le miglia indicate nell'apposita barra dall'utente.
 */
void MainWindow::slotTempoNavigazione() try{
    if(layout->getList()->getItem()){
        float mostra=layout->getList()->getItem()->getImbarcazione()->tempoNavigazione(layout->getTempo());
        std::string str="Il tempo di navigazione per fare "+std::to_string(layout->getTempo())+" miglia e': "+std::to_string(mostra)+" h";
        QMessageBox::information(this,"Marghera Boat",QString::fromStdString(str));
    }
} catch(...){}

/**
 * @brief slotMiglia mostra una finestra pop up contenente le miglia percorse dell'imbarcazione selezionata nella lista per navigare il tempo indicate nell'apposita barra dall'utente.
 */
void MainWindow::slotMiglia() try{
    if(layout->getList()->getItem()){
        float mostra=layout->getList()->getItem()->getImbarcazione()->calcoloMiglia(layout->getMiglia());
        std::string str="Le miglia percorse navigando "+std::to_string(layout->getMiglia())+" h sono: "+std::to_string(mostra)+" miglia";
        QMessageBox::information(this,"Marghera Boat",QString::fromStdString(str));
    }
} catch(...){}

/**
 * @brief slotType mostra una finestra pop up contenente il tipo dell'imbarcazione selezionata nella lista.
 */
void MainWindow::slotType() try{
    if(layout->getList()->getItem()){
        std::string mostra=layout->getList()->getItem()->getImbarcazione()->tipoImbarcazione();
        std::string str="Per il codice della navigazione da diporto questa imbarcazione è classificata come: "+mostra;
        QMessageBox::information(this,"Marghera Boat",QString::fromStdString(str));
    }
} catch(...){}

/**
 * @brief slotPatente mostra una finestra pop up contente la verifica della patente nautica con risposta Si o No.
 */
void MainWindow::slotPatente() try{
    if(layout->getList()->getItem()){
        bool mostra=layout->getList()->getItem()->getImbarcazione()->patenteNautica();
        std::string str;
        if(mostra)  str="Si, è richiesta la patente nautica per questa imbarcazione";
        else    str="No, questa imbarcazione non necessita di patente nautica";
        QMessageBox::information(this,"Marghera Boat",QString::fromStdString(str));
    }
} catch(...){}

void MainWindow::slotEnableMotAusi(int i)
{
    layoutIns->support_enableMotoreAusiliario(i);
}

MainWindow::~MainWindow()
{
    delete modello;
}



























