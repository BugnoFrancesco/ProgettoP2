#ifndef ELETTRICO_H
#define ELETTRICO_H
#include "motore.h"

enum tipo_batteria {litio, piombo};

class Elettrico : public Motore
{
private:
    tipo_batteria tipoB;
    float consumo;
    unsigned int capienzaBatteria;
public:
    Elettrico(const std::string& m= "No Name", const std::string& c= "No Builder", unsigned int p=0, unsigned int v=0, unsigned int l=0, unsigned int numM=0, unsigned int potM=0,tipo_motore tM=fuoribordo,
            tipo_batteria tB=litio, float con=0, unsigned int capB=0);

    float getConsumo() const;
    unsigned int getCapienzaBatteria() const;
    tipo_batteria getTipoBatteria() const;

    void setConsumo(float=0);
    void setCapienzaBatteria(unsigned int=0);
    void setTipoBatteria(tipo_batteria=litio);

    virtual void print() const;
    virtual std::string boat_toString() const;

    virtual std::string tipoPropulsione() const override;
    virtual float calcoloConsumi(float) const override;
    virtual float calcoloAutonomia(unsigned int) const override;
    virtual Elettrico* clone() const override;

};

#endif // ELETTRICO_H
