#include "termico.h"
#include <iostream>

using std::string;
using std::cerr;
using std::cout;

Termico::Termico(const std::string& m, const std::string& c, unsigned int p, unsigned int v, unsigned int l, unsigned int numM, unsigned int potM, std::string tM,
                 std::string tC, float con, unsigned int capS): Motore(m,c,p,v,l,numM,potM,tM), tipoC(tC), consumo(con), capienzaSerbatoi(capS){}

float Termico::getConsumo() const{
    return consumo;
}

unsigned int Termico::getCapienzaSerbatoi() const{
    return capienzaSerbatoi;
}

std::string Termico::getTipoCombustione() const{
    return tipoC;
}

void Termico::setConsumo(float con){
    consumo=con;
}

void Termico::setCapienzaSerbatoi(unsigned int capS){
    capienzaSerbatoi=capS;
}
void Termico::setTipoCombustione(std::string tC){
    tipoC=tC;
}

void Termico::print() const{
    Imbarcazione::print();
    Motore::print();
    cout<<"\nTipo di combustione: "<<getTipoCombustione()<<"\nConsumo: "<<getConsumo()<<" L/h"<<"\nCapienza serbatoi: "<<getCapienzaSerbatoi()<<" L";
}

std::string Termico::boat_toString() const{
    std::string s=Motore::boat_toString();
    std::string cons=std::to_string(getConsumo());
    std::string c_serbatoi=std::to_string(getCapienzaSerbatoi());
    std::string t_combust=getTipoCombustione();
    /*if(getTipoCombustione()==diesel) t_combust="diesel";
    else if(getTipoCombustione()==benzina) t_combust="benzina";*/
    s.append("\nConsumo: "+cons+" L/h"+"\nCapienza Serbatoi: "+c_serbatoi+"\nTipo combustione: "+t_combust);
    return s;
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
