#include "motore.h"
#include <iostream>

using std::string;
using std::cerr;
using std::cout;

Motore::Motore(const std::string& m, const std::string& c, unsigned int p, unsigned int v, unsigned int l, unsigned int numM, unsigned int potM, std::string tM):
    Imbarcazione(m,c,p,v,l), num_motori(numM), potenza_motore(potM), tipoM(tM){}

unsigned int Motore::getNumMotori() const{
    return num_motori;
}

unsigned int Motore::getPotenzaMotore() const{
    return potenza_motore;
}

std::string Motore::getTipoMotore() const{
    return tipoM;
}

void Motore::setNumMotori(unsigned int numM){
    num_motori=numM;
}
void Motore::setPotenzaMotore(unsigned int potM){
    potenza_motore=potM;
}
void Motore::setTipoMotore(std::string tM){
    tipoM=tM;
}

unsigned int Motore::calcoloPotenzaTot() const{
    return (num_motori*potenza_motore);
}
bool Motore::patenteNautica() const {
    if(Imbarcazione::tipoImbarcazione()=="Nave" || Imbarcazione::tipoImbarcazione()=="Barca") return true;
    else if(Imbarcazione::tipoImbarcazione()=="Natante" && calcoloPotenzaTot()>=40) return true;
    else return false;
}

void Motore::print() const{
    Imbarcazione::print();
    cout<<"\nNumero di motori: "<<getNumMotori()<<"\nPotenza singolo motore: "<<getPotenzaMotore()<<" cv"<<"\nTipo di motore: "<<getTipoMotore();
}

std::string Motore::boat_toString() const{
    std::string s=Imbarcazione::boat_toString();
    std::string n_motori=std::to_string(getNumMotori());
    std::string p_motore=std::to_string(getPotenzaMotore());
    std::string t_motore=getTipoMotore();
    /*if(getTipoMotore()==fuoribordo) t_motore="fuoribordo";
    else if(getTipoMotore()==entrobordo) t_motore="entrobordo";
    else if(getTipoMotore()==entrofuoribordo) t_motore="entrofuoribordo";*/
    s.append("\nNumero motori: "+n_motori+"\nPotenza singolo motore: "+p_motore+"\nTipo motore: "+t_motore);
    return s;
}
