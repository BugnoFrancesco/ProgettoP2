#include "elettrico.h"
#include <iostream>

using std::string;
using std::cerr;
using std::cout;

Elettrico::Elettrico(const std::string& m, const std::string& c, unsigned int p, unsigned int v, unsigned int l, unsigned int numM, unsigned int potM, tipo_motore tM,
                 tipo_batteria tB, float con, unsigned int capB): Motore(m,c,p,v,l,numM,potM,tM), tipoB(tB), consumo(con), capienzaBatteria(capB){}

float Elettrico::getConsumo() const{
    return consumo;
}

unsigned int Elettrico::getCapienzaBatteria() const{
    return capienzaBatteria;
}

tipo_batteria Elettrico::getTipoBatteria() const{
    return tipoB;
}

void Elettrico::setConsumo(float con){
    consumo=con;
}
void Elettrico::setCapienzaBatteria(unsigned int capB){
    capienzaBatteria=capB;
}
void Elettrico::setTipoBatteria(tipo_batteria tB){
    tipoB=tB;
}

void Elettrico::print() const{
    Imbarcazione::print();
    Motore::print();
    cout<<"\nTipo di batteria: "<<getTipoBatteria()<<"\nConsumo: "<<getConsumo()<<" KW/h"<<"\nCapienza batteria: "<<getCapienzaBatteria()<<" KW";
}

std::string Elettrico::boat_toString() const{
    std::string s=Motore::boat_toString();
    std::string cons=std::to_string(getConsumo());
    std::string c_batteria=std::to_string(getCapienzaBatteria());
    std::string t_batteria="";
    if(getTipoBatteria()==litio) t_batteria="litio";
    else if(getTipoBatteria()==piombo) t_batteria="piombo";
    s.append("\nConsumo: "+cons+" L/h"+"\nCapienza Serbatoi: "+c_batteria+"\nTipo combustione: "+t_batteria);
    return s;
}

std::string Elettrico::tipoPropulsione() const {
    return "Motore Elettrico";
}

float Elettrico::calcoloConsumi(float tempo) const {
    if((consumo*tempo)<capienzaBatteria) return (consumo*tempo);
    else return 0; //throw new BoatException("L'imbarcazione non ha abbastanza carica nelle batterie");
}

float Elettrico::calcoloAutonomia(unsigned int carica_batterie) const{
    if(carica_batterie<capienzaBatteria) return (carica_batterie/consumo);
    else return 0; //throw new BoatException("La batteria non permette l'inserimento della carica selezionata");
}

Elettrico* Elettrico::clone() const {
    return new Elettrico(*this);
}
