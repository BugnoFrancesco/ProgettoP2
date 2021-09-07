#include "modifylayout.h"
#include "QPushButton"
//#include "supporto/nievaexception.h"


ModifyLayout::ModifyLayout(QWidget *parent, unsigned int tipo, unsigned int i): InsertLayout(parent,tipo), ind(i),
    modifica(new QPushButton(this))
{
    conferma->hide();
    modifica->setText("Modifica");
    layoutPopUp->addWidget(modifica);

    connect(modifica, SIGNAL(clicked()), parent, SLOT(slotModifyBoat()));
}
void ModifyLayout::setNome(std::string str){
    nome->setText(QString::fromStdString(str));
}
void ModifyLayout::setCantiere(std::string str){
    cantiere->setText(QString::fromStdString(str));
}
void ModifyLayout::setSpeed(unsigned int x){
    speed->setText(QString::number(x));
}
void ModifyLayout::setPeso(unsigned int x){
    peso->setText(QString::number(x));
}

void ModifyLayout::setLunghezza(float x)
{
    lunghezza->setText(QString::number(x));
}

void ModifyLayout::setNumMotori(unsigned int x)
{
    numMotori->setText(QString::number(x));
}

void ModifyLayout::setPotenzaMotore(unsigned int x)
{
    potMotore->setText(QString::number(x));
}

//? da fare
void ModifyLayout::setTipoMotore(std::string str)
{
    if(str=="entrobordo") tipoMotore->setCurrentIndex(0);
    else if(str=="fuoribordo")  tipoMotore->setCurrentIndex(1);
    else if(str=="entrofuoribordo") tipoMotore->setCurrentIndex(2);
}
void ModifyLayout::setTipoCarburante(std::string str)
{
    if(str=="diesel") tipoCarburante->setCurrentIndex(0);
    else if(str=="benzina")  tipoCarburante->setCurrentIndex(1);
}
void ModifyLayout::setTipoBatteria(std::string str)
{
    if(str=="piombo") tipoBatteria->setCurrentIndex(0);
    else if(str=="litio")  tipoBatteria->setCurrentIndex(1);
}
void ModifyLayout::setMotoreAusiliario(bool y)
{
    if(y)   motoreAusi->setCurrentIndex(0);
    else    motoreAusi->setCurrentIndex(1);
}


void ModifyLayout::setConsumoTermico(float x)
{
    consTermico->setText(QString::number(x));
}

void ModifyLayout::setConsumoElettrico(float x)
{
    consElettrico->setText(QString::number(x));
}

void ModifyLayout::setCapSerbatoi(unsigned int x)
{
    capSerbatoi->setText(QString::number(x));
}

void ModifyLayout::setCapBatteria(unsigned int x)
{
    capBatteria->setText(QString::number(x));
}

void ModifyLayout::setNumVele(unsigned int x)
{
    numVele->setText(QString::number(x));
}

void ModifyLayout::setPotenzaMotoreAusiliario(unsigned int x)
{
    potMotAusi->setText(QString::number(x));
}

void ModifyLayout::setTipo(unsigned int x)
{
    tipo = x;
}

unsigned int ModifyLayout::getInd() const{
    return ind;
}








