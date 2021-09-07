#ifndef MODIFYLAYOUT_H
#define MODIFYLAYOUT_H

#include "insertlayout.h"


class ModifyLayout: public InsertLayout {
    unsigned int ind;
    QPushButton* modifica;
public:
    ModifyLayout(QWidget *parent = nullptr, unsigned int tipo=0, unsigned int ind=0);

    void setNome(std::string);
    void setCantiere(std::string);
    void setSpeed(unsigned int);
    void setPeso(unsigned int);
    void setLunghezza(float);
    void setNumMotori(unsigned int);
    void setPotenzaMotore(unsigned int);
    void setTipoMotore(std::string);
    void setTipoCarburante(std::string);
    void setTipoBatteria(std::string);
    void setConsumoTermico(float);
    void setConsumoElettrico(float);
    void setCapSerbatoi(unsigned int);
    void setCapBatteria(unsigned int);
    void setNumVele(unsigned int);
    void setMotoreAusiliario(bool);
    void setPotenzaMotoreAusiliario(unsigned int);
    void setTipo(unsigned int);
    unsigned int getInd() const;

};

#endif // MODIFYLAYOUT_H
