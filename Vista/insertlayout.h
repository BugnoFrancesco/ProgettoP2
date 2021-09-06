#ifndef INSERTLAYOUT_H
#define INSERTLAYOUT_H

#include <QWidget>
#include <QDialog>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QStringList>
#include <QPushButton>
#include <QLabel>
#include <string>
//#include "supporto/comboboxmotoreprimario.h"
//#include "supporto/comboboxtech.h"
//#include "supporto/comboboxtrasmissione.h"


class InsertLayout: public QDialog
{
    Q_OBJECT
protected:
    QVBoxLayout* layoutPopUp;
    QLabel *nomeL, *costruttoreL, *temperaturaSL, *efficenzaEL, *potenzaICL, *speedL, *pesoL, *carburanteSL, *motoreICL;
    QLineEdit *nome, *costruttore, *temperaturaS, *efficenzaE, *potenzaIC, *speed, *peso, *carburanteS, *motoreIC;
    ComboBoxTech *tecnologia;
    ComboBoxMotorePrimario *primario;
    ComboBoxTrasmissione *trasmissione;
    QPushButton *conferma, *annulla;
    unsigned int tipo;
public:
    std::string getNome() const;
    std::string getCostruttore()const;
    unsigned int getTemperaturaS()const;
    double getEfficenzaE()const;
    unsigned int getPotenzaIC()const;
    unsigned int getSpeed() const;
    unsigned int getPeso()const;
    std::string getCarburanteS()const;
    std::string getMotoreIC()const;
    bool getTecnologia()const;
    bool getPrimario()const;
    bool getTrasmissione()const;
    unsigned int getTipo()const;
    AggiuntaLayout(QWidget * =nullptr, int tipoT=0);
};

#endif // INSERTLAYOUT_H
