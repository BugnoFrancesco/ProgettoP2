#include "vela.h"
#include <iostream>

using std::string;
using std::cerr;
using std::cout;

Vela::Vela(const std::string& m, const std::string& c, unsigned int p, unsigned int v, unsigned int l, bool motA, unsigned int pot_motA, unsigned int n_vele):
    Imbarcazione(m,c,p,v,l), motore_ausiliario(motA), potenza_motoreA(pot_motA), num_vele(n_vele){}

bool Vela::getMotoreAusiliario() const{
    return motore_ausiliario;
}

unsigned int Vela::getPotenzaMotoreAusiliario() const{
    return potenza_motoreA;
}

unsigned int Vela::getNumVele() const{
    return num_vele;
}

void Vela::setMotoreAusiliario(bool motA){
    motore_ausiliario=motA;
}
void Vela::setPotenzaMotoreAusiliario(unsigned int pot_motA){
    potenza_motoreA=pot_motA;
}
void Vela::setNumVele(unsigned int n_vele){
    num_vele=n_vele;
}

bool Vela::patenteNautica() const {
    if(Imbarcazione::tipoImbarcazione()=="Nave" || Imbarcazione::tipoImbarcazione()=="Barca") return true;
    else if(Imbarcazione::tipoImbarcazione()=="Natante" && motore_ausiliario==true && potenza_motoreA>=40) return true;
    else return false;
}

void Vela::print() const{
    Imbarcazione::print();
    cout<<"\nMotore Ausiliario: "<<getMotoreAusiliario()<<"\nPotenza motore: "<<getPotenzaMotoreAusiliario()<<"\nNumero di vele: "<<getNumVele();
}

std::string Vela::tipoPropulsione() const {
    return "Vela";
}

float Vela::calcoloConsumi(float tempo) const {
    return tempo;
    //throw new BoatException("Impossibile dare una stima dei consumi");
 }
float Vela::calcoloAutonomia(unsigned int carburante_imbarcato) const{
    return carburante_imbarcato;
    //throw new BoatException("La capienza dei serbatoi non permette l'inserimento del carburante selezionato");
}

Vela* Vela::clone() const {
    return new Vela(*this);
}
