#ifndef INFOLAYOUT_H
#define INFOLAYOUT_H

#include <QWidget>
#include <QDialog>
#include <QLabel>

class InfoLayout: public QDialog
{
    Q_OBJECT

    QLabel* first;
    QLabel* second;
    QLabel* third;
    QLabel* fourth;
    QLabel* fifth;
    QLabel* sixth;
    QLabel* seventh;

public:
    InfoLayout(QWidget * =nullptr, QString ="", QString ="",QString ="",QString ="",QString ="", QString ="", QString ="");
    void setMargin(int margin =20);
    void setDimensioni(int width =100, int height =100);
};

#endif // INFOLAYOUT_H
