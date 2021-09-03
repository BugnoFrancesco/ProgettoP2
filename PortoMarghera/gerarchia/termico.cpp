#include "termico.h"
#include <iostream>

using std::string;
using std::cerr;
using std::cout;

Termico::Termico(const std::string& m, const std::string& c, unsigned int p, unsigned int v, unsigned int l, unsigned int numM, unsigned int potM, tipo_motore tM,
                 tipo_combustione tC, float con, unsigned int capS): Motore(m,c,p,v,l,numM,potM,tM), tipoC(tC), consumo(con), capienzaSerbatoi(capS){}

float Termico::getConsumo() const{
    return consumo;
}

unsigned int Termico::getCapienzaSerbatoi() const{
    return capienzaSerbatoi;
}

tipo_combustione Termico::getTipoCombustione() const{
    return tipoC;
}

void Termico::setConsumo(float con){
    consumo=con;
}

void Termico::setCapienzaSerbatoi(unsigned int capS){
    capienzaSerbatoi=capS;
}
void Termico::setTipoCombustione(tipo_combustione tC){
    tipoC=tC;
}

void Termico::print() const{
    Imbarcazione::print();
    Motore::print();
    cout<<"\nTipo di combustione: "<<getTipoCombustione()<<"\nConsumo: "<<getConsumo()<<" L/h"<<"\nCapienza serbatoi: "<<getCapienzaSerbatoi()<<" L";
}

std::string Termico::tipoPropulsione() const {
    return "Motore Termico";
}

float Termico::calcoloConsumi(float tempo) const {
    if((consumo*tempo)<capienzaSerbatoi) return (consumo*tempo);
    else return 0;//throw new BoatException("L'imbarcazione non ha abbastanza carburante");
}

float Termico::calcoloAutonomia(unsigned int carburante_imbarcato) const{
    if(carburante_imbarcato<capienzaSerbatoi) return (carburante_imbarcato/consumo);
    else return 0;//throw new BoatException("La capienza dei serbatoi non permette l'inserimento del carburante selezionato");
}

Termico* Termico::clone() const {
    return new Termico(*this);
}
