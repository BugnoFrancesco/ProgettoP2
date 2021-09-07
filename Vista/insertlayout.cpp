#include "insertlayout.h"

InsertLayout::InsertLayout(QWidget* p, int tipoT): QDialog(p), layoutPopUp(new QVBoxLayout(this)),
    nomeL(new QLabel(this)), cantiereL(new QLabel(this)), speedL(new QLabel(this)), pesoL(new QLabel(this)), lunghezzaL(new QLabel(this)), numMotoriL(new QLabel(this)), potMotoreL(new QLabel(this)),
    consTermicoL(new QLabel(this)), capSerbatoiL(new QLabel(this)), consElettricoL(new QLabel(this)), capBatteriaL(new QLabel(this)), numVeleL(new QLabel(this)), potMotAusiL(new QLabel(this)),
    nome(new QLineEdit(this)), cantiere(new QLineEdit(this)), speed(new QLineEdit(this)), peso(new QLineEdit(this)), lunghezza(new QLineEdit(this)), numMotori(new QLineEdit(this)), potMotore(new QLineEdit(this)),
    consTermico(new QLineEdit(this)), capSerbatoi(new QLineEdit(this)), consElettrico(new QLineEdit(this)), capBatteria(new QLineEdit(this)), numVele(new QLineEdit(this)), potMotAusi(new QLineEdit(this)),
    tipoMotore(new QComboBox(this)), tipoCarburante(new QComboBox(this)), tipoBatteria(new QComboBox(this)), motoreAusi(new QComboBox(this)), conferma(new QPushButton(this)), annulla(new QPushButton(this)), tipo(tipoT)

{
    conferma->setText("Conferma");
    annulla->setText("Cancella");

    nomeL->setText("Nome modello");
    cantiereL->setText("Cantiere di costruzione");
    pesoL->setText("Peso");
    speedL->setText("Velocità di crociera");
    lunghezzaL->setText("Lunghezza");
    numMotoriL->setText("Numero di motori");
    potMotoreL->setText("Potenza singolo motore");
    consTermicoL->setText("Consumo motore termico");
    consElettricoL->setText("Consumo motore elettrico");
    capSerbatoiL->setText("Capienza serbatoi");
    capBatteriaL->setText("Capienza batteria");
    numVeleL->setText("Numero di vele");
    potMotAusiL->setText("Potenza motore ausiliario");

    nome->setPlaceholderText("Inserisci nome del modello di imbarcazione");
    nome->setValidator(new QRegularExpressionValidator(QRegularExpression("[A-Z0-9a-z ]{0,50}")));
    cantiere->setPlaceholderText("Inserisci cantiere di costruzione");
    cantiere->setValidator(new QRegularExpressionValidator(QRegularExpression("[A-Z0-9a-z]{0,50}")));
    speed->setPlaceholderText("Inserisci velocità di crociera (Nodi)");
    speed->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]{0,5}")));
    peso->setPlaceholderText("Inserisci peso (kg)");
    peso->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]{0,5}")));
    lunghezza->setPlaceholderText("Inserisci lunghezza (m)");
    lunghezza->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9.]{0,5}")));
    numMotori->setPlaceholderText("Inserisci il numero di motori");
    numMotori->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]{0,5}")));
    potMotore->setPlaceholderText("Inserisci la potenza del singolo motore (Cv)");
    potMotore->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]{0,5}")));
    consTermico->setPlaceholderText("Inserisci il consumo del motore termico (L/h)");
    consTermico->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]{0,5}")));
    consElettrico->setPlaceholderText("Inserisci il consumo del motore elettrico (Kw/h)");
    consElettrico->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]{0,5}")));
    capSerbatoi->setPlaceholderText("Inserisci la capienza dei serbatoi (L)");
    capSerbatoi->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]{0,5}")));
    capBatteria->setPlaceholderText("Inserisci la capienza delle batterie (Kw)");
    capBatteria->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]{0,5}")));
    numVele->setPlaceholderText("Inserisci il numero di vele");
    numVele->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]{0,5}")));
    potMotAusi->setPlaceholderText("Inserisci la potenza del motore ausiliario (Cv)");
    potMotAusi->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]{0,5}")));

    tipoMotore->addItem("Entrobordo");
    tipoMotore->addItem("Fuoribordo");
    tipoMotore->addItem("EntroFuoribordo");

    tipoCarburante->addItem("Diesel");
    tipoCarburante->addItem("Benzina");

    tipoBatteria->addItem("Litio");
    tipoBatteria->addItem("Piombo");

    motoreAusi->addItem("Si");
    motoreAusi->addItem("No");

    numMotori->hide();
    potMotore->hide();
    consTermico->hide();
    consElettrico->hide();
    capSerbatoi->hide();
    capBatteria->hide();
    numVele->hide();
    potMotAusi->hide();
    numMotoriL->hide();
    potMotoreL->hide();
    consTermicoL->hide();
    consElettricoL->hide();
    capSerbatoiL->hide();
    capBatteriaL->hide();
    numVeleL->hide();
    potMotAusiL->hide();

    tipoMotore->hide();
    tipoCarburante->hide();
    tipoBatteria->hide();
    motoreAusi->hide();

    layoutPopUp->addWidget(nomeL);
    layoutPopUp->addWidget(nome);
    layoutPopUp->addWidget(cantiereL);
    layoutPopUp->addWidget(cantiere);
    layoutPopUp->addWidget(speedL);
    layoutPopUp->addWidget(speed);
    layoutPopUp->addWidget(pesoL);
    layoutPopUp->addWidget(peso);
    layoutPopUp->addWidget(lunghezzaL);
    layoutPopUp->addWidget(lunghezza);

    switch (tipoT) {
    case 0:
        numMotori->show();
        potMotore->show();
        consTermico->show();
        capSerbatoi->show();
        numMotoriL->show();
        potMotoreL->show();
        consTermicoL->show();
        capSerbatoiL->show();
        tipoMotore->show();
        tipoCarburante->show();

        layoutPopUp->addWidget(tipoMotore);
        layoutPopUp->addWidget(numMotoriL);
        layoutPopUp->addWidget(numMotori);
        layoutPopUp->addWidget(potMotoreL);
        layoutPopUp->addWidget(potMotore);
        layoutPopUp->addWidget(tipoCarburante);
        layoutPopUp->addWidget(consTermicoL);
        layoutPopUp->addWidget(consTermico);
        layoutPopUp->addWidget(capSerbatoiL);
        layoutPopUp->addWidget(capSerbatoi);
        break;
    case 1:
        numMotori->show();
        potMotore->show();
        consElettrico->show();
        capBatteria->show();
        numMotoriL->show();
        potMotoreL->show();
        consElettricoL->show();
        capBatteriaL->show();
        tipoMotore->show();
        tipoBatteria->show();

        layoutPopUp->addWidget(tipoMotore);
        layoutPopUp->addWidget(numMotoriL);
        layoutPopUp->addWidget(numMotori);
        layoutPopUp->addWidget(potMotoreL);
        layoutPopUp->addWidget(potMotore);
        layoutPopUp->addWidget(tipoBatteria);
        layoutPopUp->addWidget(consElettricoL);
        layoutPopUp->addWidget(consElettrico);
        layoutPopUp->addWidget(capBatteriaL);
        layoutPopUp->addWidget(capBatteria);
        break;
    case 2:
        numVele->show();
        potMotAusi->show();
        numVeleL->show();
        potMotAusiL->show();
        motoreAusi->show();

        layoutPopUp->addWidget(numVeleL);
        layoutPopUp->addWidget(numVele);
        layoutPopUp->addWidget(motoreAusi);
        layoutPopUp->addWidget(potMotAusiL);
        layoutPopUp->addWidget(potMotAusi);

    //default:
        //throwa qualcosa
    }
    connect(conferma, SIGNAL(clicked()), p, SLOT(slotInsertBoat()));
    connect(annulla, SIGNAL(clicked()), this, SLOT(close()));
    layoutPopUp->addWidget(annulla);
    layoutPopUp->addWidget(conferma);

    setLayout(layoutPopUp);
}

std::string InsertLayout::getNome() const{
    return nome->text().toStdString();
}

std::string InsertLayout::getCantiere() const{
    return cantiere->text().toStdString();
}

unsigned int InsertLayout::getSpeed() const{
    return speed->text().toInt();
}

unsigned int InsertLayout::getPeso() const{
    return peso->text().toInt();
}

float InsertLayout::getLunghezza() const{
    return lunghezza->text().toFloat();
}

unsigned int InsertLayout::getNumMotori() const{
    return numMotori->text().toInt();
}

unsigned int InsertLayout::getPotenzaMotore() const{
    return potMotore->text().toInt();
}

std::string InsertLayout::getTipoMotore() const{
    return QString::number(tipoMotore->currentIndex()).toStdString();

}
std::string InsertLayout::getTipoCarburante() const{
    return QString::number(tipoCarburante->currentIndex()).toStdString();
}

std::string InsertLayout::getTipoBatteria() const{
    return QString::number(tipoBatteria->currentIndex()).toStdString();
}

float InsertLayout::getConsumoElettrico() const{
    return consElettrico->text().toFloat();
}

float InsertLayout::getConsumoTermico() const{
    return consTermico->text().toFloat();
}

unsigned int InsertLayout::getCapSerbatoi() const{
    return capSerbatoi->text().toInt();
}

unsigned int InsertLayout::getCapBatteria() const{
    return capBatteria->text().toUInt();
}

unsigned int InsertLayout::getNumVele() const{
    return numVele->text().toInt();
}

bool InsertLayout::getMotoreAusiliario() const{
    return motoreAusi->currentIndex();
}

unsigned int InsertLayout::getPotenzaMotoreAusiliario() const{
    return potMotAusi->text().toInt();
}

unsigned int InsertLayout::getTipo() const{
    return tipo;
}
