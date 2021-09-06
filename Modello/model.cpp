#include "model.h"
#include <iostream>

using std::cout;
using std::string;

/**
 * @brief print stampa alcuni dati appartenenti all'imbarcazione in posizione i (usata per debugging)
 * @param i = index nel contenitore
 */
void Model::print(unsigned int i) const
{
    cout<<"Dati "<<": \n";
    lista[i]->print();
    cout<<"\n\n\n";
}
/**
 * @brief boat_toString rappresenta le informazioni dell'imbarcazione in posizione i tramite una stringa
 * @param i = index nel contenitore
 * @return stringa contenente la rappresentazione dell'imbarcazione
 */
std::string Model::boat_toString(unsigned int i) const{
    int num=i+1;
    std::string s="IMBARCAZIONE "+ std::to_string(num)+": \n";
    //if(lista[i])
         s.append(lista[i]->boat_toString());
    s.append("\n\n\n");
    return s;
}
/**
 * @brief utilizza print per stampare alcune informazioni di tutte le imbarcazioni all'interno del contenitore
 */
void Model::print_all() const
{
    for(unsigned int i=0; i<lista.getSize();i++) print(i);
}
Imbarcazione* Model::operator[](unsigned int i) const
{
    if(i<lista.getSize())    return lista[i].operator ->();
    else    return 0;
}
Imbarcazione* Model::getImbarcazione(unsigned int i) const{
    return (*this)[i];
}

/**
 * @brief push_end aggiunge un'imbarcazione in coda al contenitore
 * @param b = barca da aggiungere
 */
void Model::push_end(Imbarcazione *b)
{
    if(b)   lista.push_back(DeepPtr<Imbarcazione>(b));
}

/**
 * @brief sostituisce l'imbarcazione in posizione y con una nuova
 * @param x = imbarcazione da sostituire al posto di quella presente nel contenitore
 * @param y = indice dell'imbarcazione da eliminare
 */
void Model::sostituisci(Imbarcazione* x, unsigned int y){
    if(x) lista.switchItem(DeepPtr<Imbarcazione>(x),y);

}

/**
 * @brief erase elimina l'imbarcazione in posizione i
 * @param i = index nel contenitore
 */
void Model::erase(unsigned int i)
{
    lista.pop(i);
}

/**
 * @brief clear elimina tutti le imbarcazione dal contenitore
 */
void Model::clear()
{
    while(lista.getSize()>0) erase(0);
}
/**
 * @brief isEmpty verifica se il contenitore è vuoto o meno
 * @return booleano
 */
bool Model::isEmpty() const
{
    if(lista.getSize()==0)   return 1;
    else    return 0;
}
/**
  * @brief calcola la velocità media tra tutte le imbarcazioni nel contenitore
  * @return double rappresentante la velocità media tra tutte le imbarcazioni
  */
double  Model::getVelocitaMedia() const
{
     unsigned int count=0;
     unsigned int i=0;
     for(;i< lista.getSize(); i++){
       count+=lista[i]->getVelocita();
     }
     if(!count)  return 0;
     else    return count/i;
}
 /**
   * @brief calcola il peso medio tra tutte le imbarcazione nel contenitore
   * @return double rappresentante il peso medio tra tutte le imbarcazioni
   */
double Model::getPesoMedio() const
{
    unsigned int count=0;
    unsigned int i=0;
    for(;i< lista.getSize(); i++){
        count+=lista[i]->getPeso();
    }

    if(!count)  return 0;
    else    return count/i;
}

/**
  * @brief calcola la lunghezza media tra tutte le imbarcazione nel contenitore
  * @return float rappresentante la lunghezza media tra tutte le imbarcazioni
  */
float Model::getLunghezzaMedia() const{
    float count=0;
    unsigned int i=0;
    for(;i< lista.getSize(); i++){
        count+=lista[i]->getLunghezza();
    }

    if(!count)  return 0;
    else    return count/i;
}

/**
 * @brief cerca il peso più alto tra le imbarcazioni del contenitore
 * @return intero rappresentante il peso più alto
 */
unsigned int Model::getPesoMax() const
{
    double peso_max=0;
    unsigned int i=0;
    for(;i< lista.getSize(); i++){
        if(peso_max<lista[i]->getPeso()) peso_max=lista[i]->getPeso();
    }
    return peso_max;
}
/**
 * @brief cerca la velocità più alta tra le imbarcazioni del contenitore
 * @return intero rappresentante la velocità più alta
 */
unsigned int Model::getVelocitaMax() const
{
    double vel_max=0;
    unsigned int i=0;
    for(;i< lista.getSize(); i++){
        if(vel_max<lista[i]->getVelocita()) vel_max=lista[i]->getVelocita();
    }
    return vel_max;
}

/**
 * @brief cerca la lunghezza massima tra le imbarcazioni del contenitore
 * @return float rappresentante la lunghezza massima
 */
float Model::getLunghezzaMax() const{
    double lun_max=0;
    unsigned int i=0;
    for(;i< lista.getSize(); i++){
        if(lun_max<lista[i]->getLunghezza()) lun_max=lista[i]->getLunghezza();
    }
    return lun_max;
}

/**
 * @brief ritorna la quantità di imbarcazioni nel contenitore
 * @return intero rappresentante il numero di imbarcazioni presenti
 */
unsigned int Model::numImbarcazioni() const
{
    return lista.getSize();
}
