#include "insertlayout.h"

InsertLayout::InsertLayout(QWidget* p, int tipoT): QDialog(p), layoutPopUp(new QVBoxLayout(this)),
    nomeL(new QLabel(this)), costruttoreL(new QLabel(this)), temperaturaSL(new QLabel(this)), efficenzaEL(new QLabel(this)), potenzaICL(new QLabel(this)), speedL(new QLabel(this)), pesoL(new QLabel(this)), carburanteSL(new QLabel(this)), motoreICL(new QLabel(this)),
    nome(new QLineEdit(this)), costruttore(new QLineEdit(this)), temperaturaS(new QLineEdit(this)), efficenzaE(new QLineEdit(this)), potenzaIC(new QLineEdit(this)), speed(new QLineEdit(this)),
    peso(new QLineEdit(this)), carburanteS(new QLineEdit(this)),motoreIC(new QLineEdit(this)),
    tecnologia(new ComboBoxTech(this)),primario(new ComboBoxMotorePrimario(this)), trasmissione(new ComboBoxTrasmissione(this)), conferma(new QPushButton(this)), annulla(new QPushButton(this)), tipo(tipoT)

{
    conferma->setText("Conferma");
    annulla->setText("Cancella");
    nomeL->setText("Nome");
    pesoL->setText("Peso");
    speedL->setText("Velocità massima");
    costruttoreL->setText("Costruttore");
    temperaturaSL->setText("Temperatura operativa motore a vapore");
    efficenzaEL->setText("Effcienza motore elettrico");
    potenzaICL->setText("Potenza motore Diesel");
    carburanteSL->setText("Carburante motore a vapore");
    motoreICL->setText("Nome motore Diesel");

    nome->setPlaceholderText("Inserisci nome treno");
    nome->setValidator(new QRegExpValidator(QRegExp("[A-Z0-9a-z ]{0,50}")));
    costruttore->setPlaceholderText("Inserisci costruttore treno");
    costruttore->setValidator(new QRegExpValidator(QRegExp("[A-Z0-9a-z]{0,50}")));
    efficenzaE->setPlaceholderText("Inserisci efficenza motore elettrico");
    efficenzaE->setValidator(new QRegExpValidator(QRegExp("[0-9.]{0,5}")));
    temperaturaS->setPlaceholderText("Inserisci temperatura operativa del motore a vapore");
    temperaturaS->setValidator(new QRegExpValidator(QRegExp("[0-9]{0,5}")));
    potenzaIC->setPlaceholderText("Inserisci la potenza motore a combustione interna");
    potenzaIC->setValidator(new QRegExpValidator(QRegExp("[0-9]{0,5}")));
    speed->setPlaceholderText("Inserisci velocità massima");
    speed->setValidator(new QRegExpValidator(QRegExp("[0-9]{0,5}")));
    peso->setPlaceholderText("Inserisci peso");
    peso->setValidator(new QRegExpValidator(QRegExp("[0-9]{0,5}")));
    carburanteS->setPlaceholderText("Inserisci carburante steam");
    carburanteS->setValidator(new QRegExpValidator(QRegExp("[A-Z0-9a-z]{0,50}")));
    motoreIC->setPlaceholderText("Inserisci nome e marca motore a combustione interna");
    motoreIC->setValidator(new QRegExpValidator(QRegExp("[A-Z0-9a-z]{0,50}")));

    motoreIC->hide();
    efficenzaE->hide();
    trasmissione->hide();
    primario->hide();
    tecnologia->hide();
    potenzaIC->hide();
    temperaturaS->hide();
    carburanteS->hide();
    temperaturaSL->hide();
    efficenzaEL->hide();
    potenzaICL->hide();
    motoreICL->hide();
    carburanteSL->hide();

    layoutPopUp->addWidget(nomeL);
    layoutPopUp->addWidget(nome);
    layoutPopUp->addWidget(costruttoreL);
    layoutPopUp->addWidget(costruttore);
    layoutPopUp->addWidget(speedL);
    layoutPopUp->addWidget(speed);
    layoutPopUp->addWidget(pesoL);
    layoutPopUp->addWidget(peso);
    switch (tipoT) {
    case 0:
        temperaturaS->show();
        carburanteS->show();
        temperaturaSL->show();
        carburanteSL->show();
        layoutPopUp->addWidget(temperaturaSL);
        layoutPopUp->addWidget(temperaturaS);
        layoutPopUp->addWidget(carburanteSL);
        layoutPopUp->addWidget(carburanteS);
        break;
    case 1:
        efficenzaE->show();
        trasmissione->show();
        efficenzaEL->show();
        layoutPopUp->addWidget(efficenzaEL);
        layoutPopUp->addWidget(efficenzaE);
        layoutPopUp->addWidget(trasmissione);
        break;
    case 2:
        potenzaIC->show();
        potenzaICL->show();
        motoreIC->show();
        motoreICL->show();
        layoutPopUp->addWidget(potenzaICL);
        layoutPopUp->addWidget(potenzaIC);
        layoutPopUp->addWidget(motoreICL);
        layoutPopUp->addWidget(motoreIC);
        break;
    case 3:
        tecnologia->show();
        layoutPopUp->addWidget(tecnologia);
        break;
    case 4:
        efficenzaE->show();
        potenzaIC->show();
        motoreIC->show();
        efficenzaEL->show();
        potenzaICL->show();
        motoreICL->show();
        trasmissione->show();
        primario->show();
        layoutPopUp->addWidget(efficenzaEL);
        layoutPopUp->addWidget(efficenzaE);
        layoutPopUp->addWidget(potenzaICL);
        layoutPopUp->addWidget(potenzaIC);
        layoutPopUp->addWidget(motoreICL);
        layoutPopUp->addWidget(motoreIC);
        layoutPopUp->addWidget(trasmissione);
        layoutPopUp->addWidget(primario);
        break;
    //default:
        //throwa qualcosa
    }
    connect(conferma, SIGNAL(clicked()), p, SLOT(slotInserisciTreno()));
    connect(annulla, SIGNAL(clicked()), this, SLOT(close()));
    layoutPopUp->addWidget(annulla);
    layoutPopUp->addWidget(conferma);

    setLayout(layoutPopUp);
}
std::string AggiuntaLayout::getNome() const{
    return nome->text().toStdString();
}
std::string AggiuntaLayout::getCostruttore()const{
    return costruttore->text().toStdString();
}

unsigned int AggiuntaLayout::getTemperaturaS()const{
    return temperaturaS->text().toInt();
}

double AggiuntaLayout::getEfficenzaE()const{
    return efficenzaE->text().toDouble();
}
unsigned int AggiuntaLayout::getPotenzaIC()const{
    return potenzaIC->text().toInt();
}
unsigned int AggiuntaLayout::getSpeed() const{
    return speed->text().toInt();
}
unsigned int AggiuntaLayout::getPeso()const{
    return peso->text().toInt();
}
std::string AggiuntaLayout::getCarburanteS()const{
    return carburanteS->text().toStdString();
}
std::string AggiuntaLayout::getMotoreIC()const{
    return motoreIC->text().toStdString();
}
bool AggiuntaLayout::getTecnologia()const{
    return tecnologia->currentIndex();
}
bool AggiuntaLayout::getPrimario()const{
    return primario->currentIndex();
}
bool AggiuntaLayout::getTrasmissione()const{
    return trasmissione->currentIndex();
}
unsigned int AggiuntaLayout::getTipo()const{
    return tipo;
}
