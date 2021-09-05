#ifndef IMBARCAZIONE_H
#define IMBARCAZIONE_H
#include <string>

class Imbarcazione
{
private:
    std::string nomeModello;
    std::string cantiere;
    unsigned int peso;
    unsigned int velocita;
    float lunghezza;

public:
    Imbarcazione(const std::string& m= "No Name", const std::string& c= "No Builder", unsigned int p=0, unsigned int v=0, unsigned int l=0);
    virtual ~Imbarcazione() = default;

    std::string getNome() const;
    std::string getCantiere() const;
    unsigned int getPeso() const;
    unsigned int getVelocita() const;
    float getLunghezza() const;

    void setNome(std::string="No Name");
    void setCantiere(std::string="No Builder");
    void setPeso(unsigned int=0);
    void setVelocita(unsigned int=0);
    void setLunghezza(float=0);

    std::string tipoImbarcazione() const;
    double conversioneKMh() const;
    float tempoNavigazione(unsigned int) const;
    float calcoloMiglia(float) const;

    virtual void print() const;
    virtual std::string boat_toString() const;

    virtual std::string tipoPropulsione() const=0;
    virtual bool patenteNautica() const=0;
    virtual float calcoloConsumi(float) const=0;
    virtual float calcoloAutonomia(unsigned int) const=0;
    virtual Imbarcazione* clone() const = 0;

};

#endif // IMBARCAZIONE_H
