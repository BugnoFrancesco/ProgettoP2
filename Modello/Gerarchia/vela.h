#ifndef VELA_H
#define VELA_H
#include "imbarcazione.h"

class Vela : public Imbarcazione
{
private:
    bool motore_ausiliario;
    unsigned int potenza_motoreA;
    unsigned int num_vele;
public:
    Vela(const std::string& m= "No Name", const std::string& c= "No Builder", unsigned int p=0, unsigned int v=0, unsigned int l=0, bool motore=false, unsigned int potenza_motoreA=0, unsigned int n_vele=1);

    bool getMotoreAusiliario() const;
    unsigned int getPotenzaMotoreAusiliario() const;
    unsigned int getNumVele() const;

    void setMotoreAusiliario(bool=false);
    void setPotenzaMotoreAusiliario(unsigned int=0);
    void setNumVele(unsigned int=1);

    virtual void print() const;
    virtual std::string boat_toString() const;

    virtual std::string tipoPropulsione() const final override;
    virtual bool patenteNautica() const final override;
    virtual float calcoloConsumi(float) const override;
    virtual float calcoloAutonomia(unsigned int) const override;
    virtual Vela* clone() const override;
};
#endif // VELA_H
