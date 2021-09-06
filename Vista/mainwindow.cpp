#include "mainwindow.h"
//#include "supporto/combotype.h"
#include <QMessageBox>
#include <QString>
//#include "supporto/infolayout.h"
#include <iostream>
#include <QFile>
#include <QFileDialog>
//#include "supporto/nievaexception.h"
using std::string;


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
        layout->getList()->addTrenoList(modello->getImbarcazione(i),i);
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
 * @brief slotAutori mostra in una finestra di dialogo l'autore del programma
 */
void MainWindow::slotAutore()
{
    QMessageBox::information(this,"Marghera Boat","Autore:\nFrancesco Bugno");
}

/**
 * @brief slotRemoveBoat rimuove l'imbarcazione selezionata nella lista delle imbarcazioni
 */
void MainWindow::slotRemoveBoat() try {
    if(layout->estraiTrenoSelezionato()==-1)   throw new BoatException("Seleziona un'imbarcazione esistente da eliminare");
        unsigned int t=layout->estraiTrenoSelezionato();
        unsigned int i=layout->getList()->getItem()->getRealIndex();
        layout->eliminaTreno(t);
        modello->erase(i);
        refreshList();
}catch(NievaException* e){
    QMessageBox::warning(this,"Nieva Trains",QString::fromStdString(e->getMessage()));
}

/**
 * @brief slotShowTreno mostra le caratteristiche del treno selezionato nella lista dei treni nell'apposito spazio
 */
void MainWindow::slotShowTreno(){
    string str="";
    if(layout->estraiTrenoSelezionato()!=-1 && layout->getList()->getItem()){
        str=modello->treno2string(layout->getList()->getItem()->getRealIndex());
    }
    layout->stampaDettagliTreno(str);
}
/**
 * @brief slotFlush svuota la lista dei treni ed il modello
 */
void MainWindow::slotFlush(){
    layout->flushList();
    modello->clear();
}
/**
 * @brief slotShowInserimentoTreno fa comparire la finestra di inserimento treno del tipo selezionato dall'utente
 */
void MainWindow::slotShowInserimentoTreno(){
    int x=layout->getTrenoInserimento();
    layoutAdd=new AggiuntaLayout(this,x);
    layoutAdd->resize(250,350);
    layoutAdd->exec();
}
/**
 * @brief slotInserisciTreno crea un nuovo treno con le informazioni date dall'utente e lo inserisce nel modello
 */
void MainWindow::slotInserisciTreno() try {
    unsigned int x=layoutAdd->getTipo();
    std::string nome=layoutAdd->getNome();
    std::string nome_trimmed=nome;
    nome_trimmed.erase(nome_trimmed.begin(), std::find_if(nome_trimmed.begin(), nome_trimmed.end(),
            std::not1(std::ptr_fun<int, int>(std::isspace))));
    if(nome_trimmed=="") throw new NievaException("Dai un nome al treno");
    std::string costruttore=layoutAdd->getCostruttore();
    unsigned int speed=layoutAdd->getSpeed();
    unsigned int peso=layoutAdd->getPeso();
    if(x==0){
        unsigned int temperaturaS=layoutAdd->getTemperaturaS();
        std::string carburanteS=layoutAdd->getCarburanteS();
        Steam* train=new Steam(nome, costruttore, speed, peso, temperaturaS, carburanteS);
        modello->push_end(train);
    }else if(x==1){
        double efficenzaE=layoutAdd->getEfficenzaE();
        if(efficenzaE<0 || efficenzaE>1){
            QMessageBox::warning(this,"Nieva Trains","Efficenza dev'essere compresa tra 0 e 1.\nVerra' settata a 0.5 e potrà essere modificata");
            efficenzaE=0.5;
        }
        bool trasmissione=layoutAdd->getTrasmissione();
        Electric* train=new Electric(nome, costruttore, peso, speed, trasmissione, efficenzaE);
        modello->push_end(train);
    }else if(x==2){
        std::string motoreIC=layoutAdd->getMotoreIC();
        unsigned int potenzaIC=layoutAdd->getPotenzaIC();
        Internal_Combustion* train= new Internal_Combustion(nome, costruttore, peso, speed, potenzaIC, motoreIC);
        modello->push_end(train);
    }else if(x==3){
        bool tecnologia=layoutAdd->getTecnologia();
        Maglev* train= new Maglev(nome, costruttore, peso, speed, tecnologia);
        modello->push_end(train);
    }else{
        double efficenzaE=layoutAdd->getEfficenzaE();
        if(efficenzaE<0 || efficenzaE>1){
            QMessageBox::warning(this,"Nieva Trains","Efficenza dev'essere compresa tra 0 e 1.\nVerra' settata a 0.5 e potrà essere modificata");
            efficenzaE=0.5;
        }
        bool trasmissione=layoutAdd->getTrasmissione();
        std::string motoreIC=layoutAdd->getMotoreIC();
        unsigned int potenzaIC=layoutAdd->getPotenzaIC();
        bool primario=layoutAdd->getPrimario();
        Bimode* train= new Bimode(nome, costruttore, peso, speed, trasmissione, efficenzaE, potenzaIC, motoreIC, primario);
        modello->push_end(train);
    }
    //prende l'ultimo treno del modello e lo aggiunge alla lista
    layout->getList()->addTrenoList(modello->getTreno(modello->numerotreni()-1),modello->numerotreni()-1);
    layout->getList()->setCurrentRow(modello->numerotreni()-1);
    //aggiornamento lista view
    layoutAdd->close();
    delete layoutAdd;
}catch(NievaException* e){QMessageBox::warning(this,"Nieva Trains",QString::fromStdString(e->getMessage()));}
/**
 * @brief slotShowModificaTreno fa comparire la finestra di modifica del treno selezionato precompilando i valori del treno
 */
void MainWindow::slotShowModificaTreno() try{
    if(layout->estraiTrenoSelezionato()==-1)   throw new NievaException("Seleziona un treno esistente da modificare");
    unsigned int indecs=layout->getList()->getItem()->getRealIndex();
    Treno* TrenoDaModificare=modello->getTreno(indecs);
    std::string tipo=TrenoDaModificare->type();
    /*
     * Vengono usati i dynamic cast dove è necessario poichè non c'è altro modo per estrarre i campi di tipi derivati senza andare a modificare la gerarchia con
     * metodi ad hoc (si usano per questo i normali get)
     */
    if(tipo=="Electric"){
        layoutMod=new ModificaLayout(this,1,indecs);
        Electric*tmp=dynamic_cast<Electric*>(TrenoDaModificare);
        layoutMod->setEfficenzaE(tmp->getEfficenzaElettrico());
        layoutMod->setTrasmissione(tmp->getTrasmissioneElettrico());
    }
    else if(tipo=="Bimode"){
        layoutMod=new ModificaLayout(this,4,indecs);
        Bimode*tmp=dynamic_cast<Bimode*>(TrenoDaModificare);
        layoutMod->setPrimario(tmp->getMotorePrimario());
        layoutMod->setPotenzaIC(tmp->getPotenzaIC());
        layoutMod->setMotoreIC(tmp->getMotoreIC());
        layoutMod->setEfficenzaE(tmp->getEfficenzaElettrico());
        layoutMod->setTrasmissione(tmp->getTrasmissioneElettrico());
    }
    else if(tipo=="Steam"){
        layoutMod=new ModificaLayout(this,0,indecs);
        Steam*tmp=static_cast<Steam*>(TrenoDaModificare);
        layoutMod->setTemperaturaS(tmp->getTemperaturaOperativa());
        layoutMod->setCarburanteS(tmp->getCarburanteSteam());
    }
    else if (tipo=="Internal_Combustion"){
        layoutMod=new ModificaLayout(this,2,indecs);
        Internal_Combustion*tmp=dynamic_cast<Internal_Combustion*>(TrenoDaModificare);
        layoutMod->setPotenzaIC(tmp->getPotenzaIC());
        layoutMod->setMotoreIC(tmp->getMotoreIC());
    }
    else if (tipo=="Maglev"){
        layoutMod=new ModificaLayout(this,3,indecs);
        Maglev*tmp=static_cast<Maglev*>(TrenoDaModificare);
        layoutMod->setTecnologia(tmp->getTecnologia());
    }
    else{
        throw new NievaException("Tipo del treno sbagliato");
    }
    layoutMod->setNome(TrenoDaModificare->getNome());
    layoutMod->setCostruttore(TrenoDaModificare->getCostruttore());
    layoutMod->setPeso(TrenoDaModificare->getPeso());
    layoutMod->setSpeed(TrenoDaModificare->getSpeed());
    layoutMod->resize(250,350);
    layoutMod->exec();
}catch(NievaException* e){
    QMessageBox::warning(this,"Nieva Trains",QString::fromStdString(e->getMessage()));
}
/**
 * @brief slotModificaTreno crea un nuovo treno con le informazioni date dall'utente e lo inserisce nel modello al posto del precedente
 */
void MainWindow::slotModificaTreno(){
    unsigned int x=layoutMod->getInd(); //è l'indice reale
    unsigned int tip=layoutMod->getTipo();
    //in base al tipo identificato da tip creo un nuovo treno e lo inserisco nel modello
    std::string nomeNew=layoutMod->getNome();
    std::string costruttoreNew=layoutMod->getCostruttore();
    unsigned int speedNew=layoutMod->getSpeed();
    unsigned int pesoNew=layoutMod->getPeso();
    if(tip==0){
        unsigned int temperaturaSNew=layoutMod->getTemperaturaS();
        std::string carburanteSNew=layoutMod->getCarburanteS();
        Steam* trenoDaSostituire=new Steam(nomeNew, costruttoreNew, speedNew, pesoNew, temperaturaSNew, carburanteSNew);
        modello->sostituisci(trenoDaSostituire, x);
    }else if(tip==1){
        double efficenzaENew=layoutMod->getEfficenzaE();
        if(efficenzaENew<0 || efficenzaENew>1)    {
            QMessageBox::warning(this,"Nieva Trains","Efficenza dev'essere compresa tra 0 e 1.\nVerra' settata a 0.5 e potrà essere modificata");
            efficenzaENew=0.5;
        }
        bool trasmissioneNew=layoutMod->getTrasmissione();
        Electric* trenoDaSostituire=new Electric(nomeNew, costruttoreNew, speedNew, pesoNew, trasmissioneNew, efficenzaENew);
        modello->sostituisci(trenoDaSostituire, x);
    }else if(tip==2){
        std::string motoreICNew=layoutMod->getMotoreIC();
        unsigned int potenzaICNew=layoutMod->getPotenzaIC();
        Internal_Combustion* trenoDaSostituire=new Internal_Combustion(nomeNew, costruttoreNew, speedNew, pesoNew, potenzaICNew, motoreICNew);
        modello->sostituisci(trenoDaSostituire, x);
    }else if(tip==3){
        bool tecnologiaNew=layoutMod->getTecnologia();
        Maglev* trenoDaSostituire=new Maglev(nomeNew, costruttoreNew, speedNew, pesoNew, tecnologiaNew);
        modello->sostituisci(trenoDaSostituire, x);
    }else if(tip==4){
        std::string motoreICNew=layoutMod->getMotoreIC();
        unsigned int potenzaICNew=layoutMod->getPotenzaIC();
        double efficenzaENew=layoutMod->getEfficenzaE();
        if(efficenzaENew<0 || efficenzaENew>1){
            QMessageBox::warning(this,"Nieva Trains","Efficenza dev'essere compresa tra 0 e 1.\nVerra' settata a 0.5 e potrà essere modificata");
            efficenzaENew=0.5;
        }
        bool trasmissioneNew=layoutMod->getTrasmissione();
        bool primarioNew=layoutMod->getPrimario();
        Bimode* trenoDaSostituire=new Bimode(nomeNew, costruttoreNew, speedNew, pesoNew, trasmissioneNew, efficenzaENew, potenzaICNew, motoreICNew, primarioNew);
        modello->sostituisci(trenoDaSostituire, x);
    }
    //refresh lista
    refreshList();
    layout->getList()->setCurrentRow(x);
    layoutMod->close();
    delete layoutMod;
}
/**
 * @brief slotCerca filtra la lista dei treni a seconda del parametro e dell'ambito scelti dall'utente
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
        searchCostruttore(parametro);
        break;
    case 2:
    if(parametro.substr(0,1)=="<")
        searchPeso(std::stoi(parametro.substr(1)), false);
    else if(parametro.substr(0,1)==">")
        searchPeso(std::stoi(parametro=parametro.substr(1)), true);
    else
        searchPeso(std::stoi(parametro), false);
    break;
    case 3:
    if(parametro.substr(0,1)=="<")
        searchVelocita(std::stoi(parametro.substr(1)), true);
    else if(parametro.substr(0,1)==">")
        searchVelocita(std::stoi(parametro=parametro.substr(1)), false);
    else
        searchVelocita(std::stoi(parametro), false);
    break;
    case 4:
        searchMotoreIC(parametro);
        break;
    case 5:
           if(parametro.substr(0,1)=="<")
               searchPotenzaIC(std::atof(parametro.substr(1).c_str()), true);
           else if(parametro.substr(0,1)==">")
               searchPotenzaIC(std::atof(parametro.substr(1).c_str()), false);
           else
               searchPotenzaIC(std::atof(parametro.substr(0).c_str()), false);
           break;
    case 6:
        searchTrasmissioneElettrico(parametro);
        break;
    case 7:
           if(parametro.substr(0,1)=="<")
               searchEfficenzaElettrico(std::atof(parametro.substr(1).c_str()), true);
           else if(parametro.substr(0,1)==">")
               searchEfficenzaElettrico(std::atof(parametro.substr(1).c_str()), false);
           else
               searchEfficenzaElettrico(std::atof(parametro.substr(0).c_str()), false);
           break;
    case 8:
           if(parametro.substr(0,1)=="<")
               searchTemperaturaVapore(std::atof(parametro.substr(1).c_str()), true);
           else if(parametro.substr(0,1)==">")
               searchTemperaturaVapore(std::atof(parametro.substr(1).c_str()), false);
           else{
               searchTemperaturaVapore(std::atof(parametro.substr(0).c_str()), false);}
           break;
    case 9:
        searchCarburanteVapore(parametro);
        break;
    case 10:
        searchTecnologiaMaglev(parametro);
        break;
    case 11:
        searchMotorePrimario(parametro);
        break;

    }
    }
    catch(NievaException* e){
        if(e->getMessage()=="ricerca sbagliata"){
            for(int i=0;i<layout->getList()->count();)   layout->getList()->erase(i);
        }
    }
    catch(...){
        QMessageBox::warning(this,"Nieva Trains","Qualcosa è andato storto, controlla i parametri di ricerca e riprova");
    }

}
/**
 * @brief slotResetSearch annulla il filtraggio applicato alla lista dei treni se presente
 */
void MainWindow::slotResetSearch(){
    refreshList();
}
using std::cout;
/**
 * @brief searchNome filtra la lista dei treni mantenendo solo i treni aventi il nome simile al parametro inserito dall'utente
 * @param n= stringa inserita dall'utente
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
 * @brief searchCostruttore filtra la lista dei treni mantenendo solo i treni aventi il costruttore simile al parametro inserito dall'utente
 * @param n= stringa inserita dall'utente
 */
void MainWindow::searchCostruttore(std::string n)
{
    unsigned int lun=layout->getList()->count();
    for(unsigned int i=0; i<lun; ++i){
        std::string costruttore=layout->getList()->getItemByIndex(i)->getCostruttore();
        transform(costruttore.begin(), costruttore.end(), costruttore.begin(),
            [](unsigned char c){ return toupper(c); });
        transform(n.begin(), n.end(), n.begin(),
            [](unsigned char c){ return toupper(c); });
        if(n!=layout->getList()->getItemByIndex(i)->getCostruttore()){
            if(costruttore.find(n)==std::string::npos){
                layout->getList()->erase(i);
                --i; --lun;
            }
        }
    }
}
/**
 * @brief searchMotoreIC filtra la lista dei treni mantenendo solo i treni a combustione interna aventi il nome del motore simile al parametro inserito dall'utente
 * @param n= stringa inserita dall'utente
 */
void MainWindow::searchMotoreIC(std::string n){
    unsigned int lun=layout->getList()->count();
    for(unsigned int i=0; i<lun; ++i){
        if(dynamic_cast<Internal_Combustion*>(layout->getList()->getItemByIndex(i))){
            Internal_Combustion* t=dynamic_cast<Internal_Combustion*>(layout->getList()->getItemByIndex(i));
            std::string motore=t->getMotoreIC();
            transform(motore.begin(), motore.end(), motore.begin(),
                [](unsigned char c){ return toupper(c); });
            transform(n.begin(), n.end(), n.begin(),
                [](unsigned char c){ return toupper(c); });
            if(n!=motore){
                if(motore.find(n)==std::string::npos){
                    layout->getList()->erase(i);
                    --i; --lun;
                }
            }
        }else{
                layout->getList()->erase(i);
                --i; --lun;
        }
    }
}
/**
 * @brief searchCarburanteVapore filtra la lista dei treni mantenendo solo i treni a vapore aventi il carburante simile al parametro inserito dall'utente
 * @param n= stringa inserita dall'utente
 */
void MainWindow::searchCarburanteVapore(std::string n){
    unsigned int lun=layout->getList()->count();
    for(unsigned int i=0; i<lun; ++i){
        if(layout->getList()->getItemByIndex(i)->type()=="Steam"){
            Steam* t=static_cast<Steam*>(layout->getList()->getItemByIndex(i));
            std::string fuel=t->getCarburanteSteam();
            transform(fuel.begin(), fuel.end(), fuel.begin(),
                [](unsigned char c){ return toupper(c); });
            transform(n.begin(), n.end(), n.begin(),
                [](unsigned char c){ return toupper(c); });
            if(n!=fuel){
                if(fuel.find(n)==std::string::npos){
                    layout->getList()->erase(i);
                    --i; --lun;
                };
            }
        }
        else{
            layout->getList()->erase(i);
            --i; --lun;
        }
    }
}
/**
 * @brief searchPeso filtra la lista dei treni mantenendo solo i treni aventi il peso maggiore o minore del parametro inserito dall'utente
 * @param n= peso inserito dall'utente
 * @param b= scelta se selezionare solo i maggiori o solo i minori
 */
void MainWindow::searchPeso(unsigned int n, bool b){
    unsigned int lun=layout->getList()->count();
    for(unsigned int i=0; i<lun; ++i){
        if(b && layout->getList()->getItemByIndex(i)->getPeso()<n){
            //maggiore
            layout->getList()->erase(i);
            --i; --lun;
        }else if(!b && layout->getList()->getItemByIndex(i)->getPeso()>=n){
            //minore
            layout->getList()->erase(i);
            --i; --lun;
        }
    }
}
/**
 * @brief searchVelocita filtra la lista dei treni mantenendo solo i treni aventi la velocità maggiore o minore del parametro inserito dall'utente
 * @param n= velocita inserito dall'utente
 * @param b= scelta se selezionare solo i maggiori o solo i minori
 */
void MainWindow::searchVelocita(unsigned int n, bool b){
    unsigned int lun=layout->getList()->count();
    for(unsigned int i=0; i<lun; ++i){
        if(b && layout->getList()->getItemByIndex(i)->getSpeed()>=n){
            //maggiore
            layout->getList()->erase(i);
            --i; --lun;
        }else if(!b && layout->getList()->getItemByIndex(i)->getSpeed()<n){
            //minore
            layout->getList()->erase(i);
            --i; --lun;
        }
    }
}
/**
 * @brief searchPotenzaIC filtra la lista dei treni mantenendo sol i treni a combustione interna aventi la potenza specifica del motore diesel maggiore o minore del parametro inserito dall'utente
 * @param n= potenza specifica inserita dall'utente
 * @param b= scelta se selezionare solo i maggiori o solo i minori
 */
void MainWindow::searchPotenzaIC(unsigned int n, bool b){
    unsigned int lun=layout->getList()->count();
    for(unsigned int i=0; i<lun; ++i){
        if(layout->getList()->getItemByIndex(i)->type()=="Internal_Combustion" || layout->getList()->getItemByIndex(i)->type()=="Bimode"){
            if(Internal_Combustion* t=dynamic_cast<Internal_Combustion*>(layout->getList()->getItemByIndex(i))){
                if(b && n<t->getPotenzaIC()){
                    layout->getList()->erase(i);
                    --i; --lun;
                }else if(!b && n>=t->getPotenzaIC()){
                    layout->getList()->erase(i);
                    --i; --lun;
                }
            }else{
                layout->getList()->erase(i);
                --i; --lun;
            }
        }else{
            layout->getList()->erase(i);
            --i; --lun;
        }
    }
}
/**
 * @brief searchTemperaturaVapore filtra la lista dei treni mantenendo sol i treni a vapore aventi la temperatura operativa del motore a vapore maggiore o minore del parametro inserito dall'utente
 * @param n= temperatura in celsius inserita dall'utente
 * @param b= scelta se selezionare solo i maggiori o solo i minori
 */
void MainWindow::searchTemperaturaVapore(unsigned int n, bool b){
    unsigned int lun=layout->getList()->count();
    for(unsigned int i=0; i<lun; ++i){
        if(layout->getList()->getItemByIndex(i)->type()=="Steam"){
            if(Steam* t=static_cast<Steam*>(layout->getList()->getItemByIndex(i))){
                if(b && n<t->getTemperaturaOperativa()){
                    layout->getList()->erase(i);
                    --i; --lun;
                }else if(!b && n>=t->getTemperaturaOperativa()){
                    layout->getList()->erase(i);
                    --i; --lun;
                }
            }else{
                layout->getList()->erase(i);
                --i; --lun;
            }
        }else{
            layout->getList()->erase(i);
            --i; --lun;
        }
    }
}
/**
 * @brief searchEfficenzaElettrico filtra la lista dei treni mantenendo sol i treni elettrici aventi l'efficenza del motore elettrico maggiore o minore del parametro inserito dall'utente
 * @param n= efficenza inserita dall'utente
 * @param b= scelta se selezionare solo i maggiori o solo i minori
 */
void MainWindow::searchEfficenzaElettrico(double n, bool b){
    unsigned int lun=layout->getList()->count();
    for(unsigned int i=0; i<lun; ++i){
        if(layout->getList()->getItemByIndex(i)->type()=="Electric" || layout->getList()->getItemByIndex(i)->type()=="Bimode"){
            if(Electric* t=dynamic_cast<Electric*>(layout->getList()->getItemByIndex(i))){
                if(b && n<t->getEfficenzaElettrico()){
                    layout->getList()->erase(i);
                    --i; --lun;
                }else if(!b && n>=t->getEfficenzaElettrico()){
                    layout->getList()->erase(i);
                    --i; --lun;
                }
            }else{
                layout->getList()->erase(i);
                --i; --lun;
            }
        }
        else{
            layout->getList()->erase(i);
            --i; --lun;
        }
    }
}



/**
 * @brief searchTrasmissioneElettrico filtra la lista dei treni mantenendo sol i treni elettrici aventi il tipo di trasmissione uguale al parametro inserito dall'utente
 * @param n= stringa inserita dall'utente
 */
void MainWindow::searchTrasmissioneElettrico(std::string n){
    unsigned int lun=layout->getList()->count();
    for(unsigned int i=0; i<lun; ++i){
        if(layout->getList()->getItemByIndex(i)->type()=="Electric" || layout->getList()->getItemByIndex(i)->type()=="Bimode"){
            if(Electric* t=dynamic_cast<Electric*>(layout->getList()->getItemByIndex(i))){
                bool  test=true;
                transform(n.begin(), n.end(), n.begin(),
                    [](unsigned char c){ return tolower(c); });
                if(n=="third rail") test=true;
                else if(n=="overhead line")    test=false;
                //eccezione ?
                else throw new NievaException("ricerca sbagliata");
                if(test!=t->getTrasmissioneElettrico()){
                        layout->getList()->erase(i);
                        --i; --lun;
                }
            }                else{
                layout->getList()->erase(i);
                --i; --lun;
            }
        }else{
            layout->getList()->erase(i);
            --i; --lun;
        }
    }
}
/**
 * @brief searchMotorePrimario filtra la lista dei treni mantenendo sol i treni Bimode aventi il motore primario uguale al parametro inserito dall'utente
 * @param n= stringa inserita dall'utente
 */
void MainWindow::searchMotorePrimario(std::string n){
    unsigned int lun=layout->getList()->count();
    for(unsigned int i=0; i<lun; ++i){
        if(layout->getList()->getItemByIndex(i)->type()=="Bimode"){
            Bimode* t=dynamic_cast<Bimode*>(layout->getList()->getItemByIndex(i));
            if(t){
                transform(n.begin(), n.end(), n.begin(),
                    [](unsigned char c){ return tolower(c); });
                bool test=true;
                if(n=="internal combustion") test=false;
                else if(n=="electric")    test=true;
                //eccezione ?
                else throw new NievaException("ricerca sbagliata");
                if(test!=t->getMotorePrimario()){
                    layout->getList()->erase(i);
                    --i; --lun;
                }
            }else{
                layout->getList()->erase(i);
                --i; --lun;
            }
        }
        else{
            layout->getList()->erase(i);
            --i; --lun;
        }
    }
}
/**
 * @brief searchTecnologiaMaglev filtra la lista dei treni mantenendo sol i treni Maglev utilizzanti la tecnologia uguale al parametro inserito dall'utente
 * @param n= stringa inserita dall'utente
 */
void MainWindow::searchTecnologiaMaglev(std::string n){
    unsigned int lun=layout->getList()->count();
    for(unsigned int i=0; i<lun; ++i){
        if(layout->getList()->getItemByIndex(i)->type()=="Maglev"){
            Maglev* t=static_cast<Maglev*>(layout->getList()->getItemByIndex(i));
            if(t){
                transform(n.begin(), n.end(), n.begin(),
                    [](unsigned char c){ return toupper(c); });
                bool test=true;
                if(n=="EDS") test=true;
                else if(n=="EMS")    test=false;
                //eccezione ?
                else throw new NievaException("ricerca sbagliata");
                if(test!=t->getTecnologia()){
                    layout->getList()->erase(i);
                    --i; --lun;
                }
            }else{
                layout->getList()->erase(i);
                --i; --lun;
            }
        }
        else{
            layout->getList()->erase(i);
            --i; --lun;
        }
    }
}
/**
 * @brief slotKmPercorribili mostra una finestra pop up contenente i km percorribili dal treno selezionato nella lista dei treni con le unità di carburante indicate nell'apposita barra dall'utente.
 * Nel caso un treno non utilizzi carburante come per esempio i Maglev, sarà bloccato a 0
 */
void MainWindow::slotKmPercorribili() try{
    if(layout->getList()->getItem()){
        unsigned int mostra=layout->getList()->getItem()->getTreno()->kmPercorribili(layout->getKm());
        std::string str="I km percorribili dal treno selezionato con "+std::to_string(layout->getKm())+" unità di carburante sono: "+std::to_string(mostra)+"km.";
        QMessageBox::information(this,"Nieva Trains",QString::fromStdString(str));
    }
}
catch(NievaException* e){
    if(e->getMessage()=="Maglev")   QMessageBox::information(this,"Nieva Trains","Questa operazione non puo' essere eseguita con il treno Maglev");
}
catch(...){}

/**
 * @brief slotCarburanteNecessario mostra una finestra pop up contenente il carburante necessario per il treno selezionato nella lista dei treni per percorrere i km indicati nell'apposita barra dall'utente.
 * Nel caso un treno non utilizzi carburante come per esempio i Maglev, sarà bloccato a 0
 */
void MainWindow::slotCarburanteNecessario()
    try{
    if(layout->getList()->getItem()){
        unsigned int mostra=layout->getList()->getItem()->getTreno()->carburanteNecessario(layout->getCarb());
        std::string str="Le unità di carburante necessarie dal treno selezionato per percorrere "+std::to_string(layout->getCarb())+"km sono: "+std::to_string(mostra);
        QMessageBox::information(this,"Nieva Trains",QString::fromStdString(str));
    }
    }
    catch(NievaException* e){
        if(e->getMessage()=="Maglev")   QMessageBox::information(this,"Nieva Trains","Questa operazione non puo' essere eseguita con il treno Maglev");
    }
    catch(...){}

MainWindow::~MainWindow()
{
    delete modello;
}



























