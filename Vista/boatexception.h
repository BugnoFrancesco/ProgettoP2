#ifndef BOATEXCEPTION_H
#define BOATEXCEPTION_H

#include <QObject>

class BoatException : public QObject
{
    Q_OBJECT

public:
    explicit BoatException(std::string ="", QObject *parent = nullptr);
    void setMessage(std::string);
    std::string getMessage() const;
    std::string print() const;
private:
    QString message;
};


#endif // BOATEXCEPTION_H
