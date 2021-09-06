#include "modifylayout.h"
//#include "supporto/nievaexception.h"


ModifyLayout::ModifyLayout(QWidget *parent, unsigned int tipo, unsigned int i): AggiuntaLayout(parent,tipo), ind(i), modifica(new QPushButton(this))
{
    conferma->hide();
    modifica->setText("Modifica");
    layoutPopUp->addWidget(modifica);

    connect(modifica, SIGNAL(clicked()), parent, SLOT(slotModificaTreno()));
}
void ModifyLayout::setNome(std::string str){
    nome->setText(QString::fromStdString(str));
}
void ModifyLayout::setCantiere(std::string str){
    costruttore->setText(QString::fromStdString(str));
}
void ModifyLayout::setSpeed(unsigned int x){
    speed->setText(QString::number(x));
}
void ModifyLayout::setPeso(unsigned int x){
     peso->setText(QString::number(x));
}
void ModifyLayout::setPotenzaIC(unsigned int x){
    potenzaIC->setText(QString::number(x));
}
void ModifyLayout::setTemperaturaS(unsigned int x){
    temperaturaS->setText(QString::number(x));
}
void ModifyLayout::setEfficenzaE(double x){
     efficenzaE->setText(QString::number(x));
}
void ModifyLayout::setCarburanteS(std::string str){
    carburanteS->setText(QString::fromStdString(str));
}
void ModifyLayout::setMotoreIC(std::string str){
    motoreIC->setText(QString::fromStdString(str));
}
void ModifyLayout::setPrimario(bool x){
    if(x==false) primario->setCurrentIndex(0);
    else primario->setCurrentIndex(1);
}
void ModifyLayout::setTrasmissione(bool x){
    if(x==false) trasmissione->setCurrentIndex(0);
    else trasmissione->setCurrentIndex(1);//
}
void ModifyLayout::setTecnologia(bool x){
    if(x==false) tecnologia->setCurrentIndex(0);
    else tecnologia->setCurrentIndex(1);
}
unsigned int ModifyLayout::getInd() const{
    return ind;
}








