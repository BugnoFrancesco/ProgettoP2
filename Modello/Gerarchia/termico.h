#ifndef TERMICO_H
#define TERMICO_H
#include "motore.h"

class Termico : public Motore
{
private:
    std::string tipoC;
    float consumo;
    unsigned int capienzaSerbatoi;
public:
    Termico(const std::string& m= "No Name", const std::string& c= "No Builder", unsigned int p=0, unsigned int v=0, unsigned int l=0, unsigned int numM=0, unsigned int potM=0,tipo_motore tM=fuoribordo,
            std::string tC="diesel", float con=0, unsigned int capS=0);

    float getConsumo() const;
    unsigned int getCapienzaSerbatoi() const;
    std::string getTipoCombustione() const;

    void setConsumo(float=0);
    void setCapienzaSerbatoi(unsigned int=0);
    void setTipoCombustione(std::string);

    virtual void print() const;
    virtual std::string boat_toString() const;

    virtual std::string tipoPropulsione() const override;
    virtual float calcoloConsumi(float) const override;
    virtual float calcoloAutonomia(unsigned int) const override;
    virtual Termico* clone() const override;
};

#endif // TERMICO_H
