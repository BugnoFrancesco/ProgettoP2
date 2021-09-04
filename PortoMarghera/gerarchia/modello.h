#ifndef MODELLO_H
#define MODELLO_H

#include "container.h"
#include "deepptr.h"
#include "imbarcazione.h"

class modello
{
private:
    Container<DeepPtr<Imbarcazione>> list;
public:
    modello() = default;
    ~modello() = default;

    void aggiungi(Imbarcazione*);
    void sostituisci(Imbarcazione* x, unsigned int y);
    void erase(unsigned int =0);

    Imbarcazione* operator[](unsigned int) const;
    Imbarcazione* getImbarcazione(unsigned int) const;

    void print(unsigned int =0) const;
    void print_all() const;
    std::string getImbarcazione_string(unsigned int =0) const;

    unsigned int countNumeroImbarcazioni() const;
    void clear();
    bool isEmpty() const;

    double getConsumi() const;
    double getAutonomia() const;
    bool getPatenteNautica() const;
    std::string getTipoPropulsione() const;

};

#endif // MODELLO_H
