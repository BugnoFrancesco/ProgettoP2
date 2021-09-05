#ifndef TERMICO_H
#define TERMICO_H
#include "motore.h"

enum tipo_combustione {diesel, benzina};

class Termico : public Motore
{
private:
    tipo_combustione tipoC;
    float consumo;
    unsigned int capienzaSerbatoi;
public:
    Termico(const std::string& m= "No Name", const std::string& c= "No Builder", unsigned int p=0, unsigned int v=0, unsigned int l=0, unsigned int numM=0, unsigned int potM=0,tipo_motore tM=fuoribordo,
            tipo_combustione tC=diesel, float con=0, unsigned int capS=0);

    float getConsumo() const;
    unsigned int getCapienzaSerbatoi() const;
    tipo_combustione getTipoCombustione() const;

    void setConsumo(float=0);
    void setCapienzaSerbatoi(unsigned int=0);
    void setTipoCombustione(tipo_combustione=diesel);

    virtual void print() const;
    virtual std::string boat_toString() const;

    virtual std::string tipoPropulsione() const override;
    virtual float calcoloConsumi(float) const override;
    virtual float calcoloAutonomia(unsigned int) const override;
    virtual Termico* clone() const override;
};

#endif // TERMICO_H
