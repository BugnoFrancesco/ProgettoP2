#ifndef MOTORE_H
#define MOTORE_H
#include "imbarcazione.h"

class Motore: public Imbarcazione
{
private:
    unsigned int num_motori;
    unsigned int potenza_motore;
    std::string tipoM;
public:
    Motore(const std::string& m= "No Name", const std::string& c= "No Builder", unsigned int p=0, unsigned int v=0, unsigned int l=0, unsigned int numM=0, unsigned int potM=0, std::string tM="fuoribordo");

    unsigned int getNumMotori() const;
    unsigned int getPotenzaMotore() const;
    std::string getTipoMotore() const;

    void setNumMotori(unsigned int=0);
    void setPotenzaMotore(unsigned int=0);
    void setTipoMotore(std::string);

    unsigned int calcoloPotenzaTot() const;

    virtual std::string boat_toString() const;
    virtual void print() const;
    virtual bool patenteNautica() const;

};

#endif // MOTORE_H
