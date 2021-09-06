#ifndef MODEL_H
#define MODEL_H

#include "container.h"
#include "deepptr.h"
#include "Gerarchia/elettrico.h"
#include "Gerarchia/termico.h"
#include "Gerarchia/vela.h"

class Model
{
private:
    Container<DeepPtr<Imbarcazione>> lista;
public:
    Model() = default;
    ~Model() = default;
    void push_end(Imbarcazione*); //aggiunge un'imbarcazione in coda
    void erase(unsigned int =0); //elimina l'imbarcazione in una data posizione
    void clear(); //elimina tutte le imbarcazioni presenti
    bool isEmpty() const; //verifica se il contenitore è vuoto
    void print(unsigned int =0) const;
    std::string boat_toString(unsigned int =0) const; //rappresenta le informazioni dell'imbarcazione in una data posizione
    void print_all() const;
    Imbarcazione* operator[] (unsigned int) const; //l[i] restituisce un puntatore all'imbarcazione di indice i
    Imbarcazione* getImbarcazione(unsigned int) const; //l.getImbarcazione(i) restituisce un puntatore all'imbarcazione di indice i

    double getVelocitaMedia() const;
    double getPesoMedio() const;
    float getLunghezzaMedia() const;
    unsigned int getVelocitaMax() const;
    unsigned int getPesoMax() const;
    float getLunghezzaMax() const;
    unsigned int numImbarcazioni() const;

};

#endif // MODEL_H


