#include "imbarcazione.h"
#include <iostream>
#include <algorithm>
#include <cctype>

/* #include "model/gerarchia/termico.h"
 * #include "model/gerarchia/elettrico.h"
 * #include "model/gerarchia/vela.h"
 * #include "view/supporto/BoatException.h"
 */

using std::string;
using std::cerr;
using std::cout;

Imbarcazione::Imbarcazione(const string& m, const string& c, unsigned int p, unsigned int v, unsigned int l):
    nomeModello(m),cantiere(c),peso(p),velocita(v),lunghezza(l){}

string Imbarcazione::getNome() const{
    return nomeModello;
}

string Imbarcazione::getCantiere() const{
    return cantiere;
}

unsigned int Imbarcazione::getPeso() const{
    return peso;
}

unsigned int Imbarcazione::getVelocita() const{
    return velocita;
}

float Imbarcazione::getLunghezza() const{
    return lunghezza;
}

void Imbarcazione::setNome(string m){
    nomeModello=m;
}
void Imbarcazione::setCantiere(string c){
    cantiere=c;
}
void Imbarcazione::setPeso(unsigned int p){
    peso=p;
}
void Imbarcazione::setVelocita(unsigned int v){
    velocita=v;
}
void Imbarcazione::setLunghezza(float l){
    lunghezza=l;
}

double Imbarcazione::conversioneKMh() const{
    return (getVelocita()*1.85);
}

/*
 * @brief restituisce la nomenclatura dell'imbarcazione in base alla sua lunghezza
*/
string Imbarcazione::tipoImbarcazione() const{
    if(lunghezza<10) return "Natante";
    else if(lunghezza<24) return "Barca";
    else return "Nave";
}

/*
 * @brief stampa alcune info sull'imbarcazione
*/
void Imbarcazione::print() const{
    string s=tipoImbarcazione();
    transform(s.begin(), s.end(), s.begin(),[](unsigned char c){return toupper(c);});
    cout<<"\nTipo: "<<s<<"\nModello: "<<getNome()<<"\nCantiere: "<<getCantiere()<<"\nVelocità: "<<getVelocita()<<" nodi"<<"\nLunghezza: "<<getLunghezza()<<" m"<<"\nPeso: "<<getPeso()<<" kg";
}

/*
 * @brief utilizzata per rappresentazre in forma di stringa un'imbarcazione
 * @return stringa contentente le informazioni riguardanti l'imbarcazione
*/
std::string Imbarcazione::boat_toString() const{
    string b=tipoImbarcazione();
    transform(b.begin(), b.end(), b.begin(), [](unsigned char c){ return toupper(c); });
    std::string s="\nTipo: "+b+"\nNome: "+getNome()+"\nCantiere: "+getCantiere()+"\nVelocita': "+std::to_string(getVelocita())+" nodi"+"\nLunghezza: "+std::to_string(getLunghezza())+" m"+"\nPeso: "+std::to_string(getPeso())+" kg";
    return s;
}

/*
 * @brief restituisce il tempo di navigazione possibile in base alla velocità di crociera dell'imbarcazione
 * @param miglia nautiche
*/
float Imbarcazione::tempoNavigazione(unsigned int miglia) const{
    return (miglia/velocita);
}
float Imbarcazione::calcoloMiglia(float tempo) const {
    return (tempo*velocita);
}

