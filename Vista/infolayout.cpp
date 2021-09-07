#include "infolayout.h"
#include <QString>
#include <QVBoxLayout>

InfoLayout::InfoLayout(QWidget* p, QString str1, QString str2, QString str3, QString str4, QString str5, QString str6, QString str7): QDialog(p),
    first(new QLabel(this)),
    second(new QLabel(this)),
    third(new QLabel(this)),
    fourth(new QLabel(this)),
    fifth(new QLabel(this)),
    sixth(new QLabel(this)),
    seventh(new QLabel(this))
{
    first->setText(str1);
    second->setText(str2);
    third->setText(str3);
    fourth->setText(str4);
    fifth->setText(str5);
    sixth->setText(str6);
    seventh->setText(str7);

    QVBoxLayout* infolayout(new QVBoxLayout(this));
    setWindowTitle("Informazioni Generali");

    infolayout->addWidget(first);
    infolayout->addWidget(second);
    infolayout->addWidget(third);
    infolayout->addWidget(fourth);
    infolayout->addWidget(fifth);
    infolayout->addWidget(sixth);
    infolayout->addWidget(seventh);

    setLayout(infolayout);
    resize(350,500);
}

void InfoLayout::setMargin(int margin)
{
    first->setMargin(margin);
    second->setMargin(margin);
    third->setMargin(margin);
    fourth->setMargin(margin);
    fifth->setMargin(margin);
    sixth->setMargin(margin);
    seventh->setMargin(margin);
}



