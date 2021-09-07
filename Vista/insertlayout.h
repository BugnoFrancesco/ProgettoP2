#ifndef INSERTLAYOUT_H
#define INSERTLAYOUT_H

#include <QWidget>
#include <QDialog>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QStringList>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <string>

class InsertLayout: public QDialog
{
    Q_OBJECT

protected:
    QVBoxLayout* layoutPopUp;
    QLabel *nomeL, *cantiereL, *speedL, *pesoL, *lunghezzaL, *numMotoriL, *potMotoreL, *consTermicoL, *capSerbatoiL, *consElettricoL, *capBatteriaL, *numVeleL, *potMotAusiL;
    QLineEdit *nome, *cantiere, *speed, *peso, *lunghezza, *numMotori, *potMotore, *consTermico, *capSerbatoi, *consElettrico, *capBatteria, *numVele, *potMotAusi;
    QComboBox *tipoMotore, *tipoCarburante, *tipoBatteria, *motoreAusi;
    QPushButton *conferma, *annulla;
    unsigned int tipo;
public:
    std::string getNome() const;
    std::string getCantiere()const;
    unsigned int getSpeed() const;
    unsigned int getPeso()const;
    float getLunghezza() const;
    unsigned int getNumMotori()const;
    unsigned int getPotenzaMotore()const;
     std::string getTipoMotore()const;
     std::string  getTipoCarburante()const;
     std::string  getTipoBatteria()const;
    float getConsumoTermico()const;
    float getConsumoElettrico()const;
    unsigned int getCapSerbatoi()const;
    unsigned int getCapBatteria()const;
    unsigned int getNumVele()const;
    bool getMotoreAusiliario()const;
    unsigned int getPotenzaMotoreAusiliario()const;
    unsigned int getTipo()const;
    InsertLayout(QWidget * =nullptr, int tipoT=0);
};

#endif // INSERTLAYOUT_H
