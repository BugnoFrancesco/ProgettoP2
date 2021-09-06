#include "boatexception.h"

BoatException::BoatException(std::string m, QObject *parent):  QObject(parent), message(QString::fromStdString(m)){}

void BoatException::setMessage(std::string m)
{
    message=QString::fromStdString(m);
}

std::string BoatException::getMessage() const
{
    return message.toStdString();
}

std::string BoatException::print() const
{
    return "- Eccezione:: \n\t"+message.toStdString()+"\n";
}
