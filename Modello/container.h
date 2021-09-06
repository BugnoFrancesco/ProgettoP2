#ifndef CONTAINER_H
#define CONTAINER_H

#include <iostream>
#include <limits.h>
#include <algorithm>

template <class T>
class Container{
public:
    class Iterator;
    class Const_Iterator;
private:
    T* v;
    unsigned int capacity;
    unsigned int size;
    T* copia(unsigned int, unsigned int) const; //v.copia(n,c) restituisce un array a[0..c] tale che a[0..n]==v[0..n]
    static void distruggi(T* v);
    void resize();

public:
    class Iterator{
        friend class Container;
    private:
        T* p;
        Iterator(T* =0);
    public:
        T& operator*() const;
        T& operator[](unsigned int) const;
        T* operator->() const;

        Iterator& operator+=(int);
        Iterator& operator-=(int);
        Iterator& operator++();
        Iterator& operator--();

        bool operator<=(const Const_Iterator &) const;
        bool operator>=(const Const_Iterator &) const;
        bool operator==(const Const_Iterator &) const;
        bool operator!=(const Const_Iterator &) const;
    };

    class Const_Iterator{
        friend class Container;
    private:
        const T* p;
        Const_Iterator(const T* =0);
    public:
        const T& operator*() const;
        const T& operator[](unsigned) const;
        const T* operator->() const;

        Const_Iterator& operator+=(int);
        Const_Iterator& operator-=(int);
        Const_Iterator& operator++();
        Const_Iterator& operator--();

        bool operator<=(const Const_Iterator &) const;
        bool operator>=(const Const_Iterator &) const;
        bool operator==(const Const_Iterator &) const;
        bool operator!=(const Const_Iterator &) const;
    };

    Container(unsigned int=1, unsigned int=0);

    Container(const Container&); //costruttore di copia profondo
    Container& operator=(const Container&); //assegnazione profonda
    ~Container(); //distruzione profonda

    T& operator[](unsigned int);
    const T& operator[](unsigned int) const;

    bool operator==(const Container&) const;
    bool operator<=(const Container&) const;
    bool operator>=(const Container&) const;

    unsigned int getSize() const;
    unsigned int getCapacity() const;

    bool empty() const;
    void clear();
    void push_back(const T&);
    void pop(unsigned int =0);
    void switchItem(const T&, unsigned int =0);
    void erase(T);

    Iterator begin();
    Iterator end();
    Const_Iterator cbegin() const;
    Const_Iterator cend() const;
};

template<class T>
T* Container<T>::copia(unsigned n, unsigned c) const{ //v.copy(n,c) restituisce un array a[0..c] tale che a[0..n]==v[0..n]
    if(n<=c && n<=size){
        T* p= new T[c];
        std::copy(v,v+n,p);
        return p;
    } else return nullptr;
}
template<class T>
void Container<T>::distruggi(T* v){
    if(v) delete[] v;
}
template <class T>
void Container<T>::resize(){
    if(capacity==0) capacity=1;
    else    capacity *=2;
    T* tmp= v;
    v = new T[capacity];
    for(unsigned int i=0; i<size; i++){
        v[i]=tmp[i];
    }
    delete[] tmp;
}

// ITERATOR
template<class T>
Container<T>::Iterator::Iterator(T* point): p(point){}

template<class T>
T& Container<T>::Iterator::operator*() const {
    return *p;
}

template<class T>
T& Container<T>::Iterator::operator[](unsigned int x) const {
    return *(p+x);
}

template<class T>
T* Container<T>::Iterator::operator->() const {
    return &p;
}

template<class T>
typename Container<T>::Iterator& Container<T>::Iterator::operator+=(int x) {
    p+=x;
    return *this;
}

template<class T>
typename Container<T>::Iterator& Container<T>::Iterator::operator-=(int x) {
    p-=x;
    return *this;
}

template<class T>
typename Container<T>::Iterator& Container<T>::Iterator::operator++() {
    p++;
    return *this;
}

template<class T>
typename Container<T>::Iterator& Container<T>::Iterator::operator--() {
    p--;
    return *this;
}

template<class T>
bool Container<T>::Iterator::operator<=(const Const_Iterator& it) const{
    return p<=it.p;
}

template<class T>
bool Container<T>::Iterator::operator>=(const Const_Iterator& it) const{
    return p>=it.p;
}

template<class T>
bool Container<T>::Iterator::operator==(const Const_Iterator& it) const{
    return p==it.p;
}

template<class T>
bool Container<T>::Iterator::operator!=(const Const_Iterator& it) const{
    return p!=it.p;
}

//CONST_ITERATOR
template<class T>
Container<T>::Const_Iterator::Const_Iterator(const T* point): p(point){}

template<class T>
const T& Container<T>::Const_Iterator::operator*() const {
    return *p;
}

template<class T>
const T& Container<T>::Const_Iterator::operator[](unsigned int x) const {
    return *(p+x);
}

template<class T>
const T* Container<T>::Const_Iterator::operator->() const {
    return &p;
}

template<class T>
typename Container<T>::Const_Iterator& Container<T>::Const_Iterator::operator+=(int x) {
    p+=x;
    return*this;
}

template<class T>
typename Container<T>::Const_Iterator& Container<T>::Const_Iterator::operator-=(int x) {
    p-=x;
    return *this;
}

template<class T>
typename Container<T>::Const_Iterator& Container<T>::Const_Iterator::operator++() {
    p++;
    return *this;
}

template<class T>
typename Container<T>::Const_Iterator& Container<T>::Const_Iterator::operator--() {
    p--;
    return *this;
}

template<class T>
bool Container<T>::Const_Iterator::operator<=(const Const_Iterator& it) const{
    return p<=it.p;
}

template<class T>
bool Container<T>::Const_Iterator::operator>=(const Const_Iterator& it) const{
    return p>=it.p;
}

template<class T>
bool Container<T>::Const_Iterator::operator==(const Const_Iterator& it) const{
    return p==it.p;
}

template<class T>
bool Container<T>::Const_Iterator::operator!=(const Const_Iterator& it) const{
    return p!=it.p;
}

//CONTAINER
template <class T>
Container<T>::Container(unsigned int c, unsigned int s): v(new T[c]), capacity(c), size(s){}

template <class T>
Container<T>::Container(const Container<T>& q):v(q.copia(q.size, q.capacity)), size(q.size), capacity(q.capacity){}

template <class T>
Container<T>& Container<T>::operator=(const Container<T>& q){
    if(this!=&q){
        distruggi(v);
        capacity=q.capacity;
        size=q.size;
        v = q.copia(size, capacity);
    }
    return *this;
}

template <class T>
Container<T>::~Container(){ distruggi(v); }

template<class T>
bool Container<T>::operator==(const Container& q) const{
    if(size!=q.size) return false;
    unsigned int i=0;
    for(;i<size && v[i]==q.v[i];++i);
    if(i==size)
        return true;
    return false;
}

template<class T>
bool Container<T>::operator<=(const Container& q) const{
    return *this<q || *this==q;
}

template<class T>
bool Container<T>::operator>=(const Container& q) const{
    return *this>q || *this==q;
}

template <class T>
unsigned int Container<T>::getSize() const{
    return size;
}

template <class T>
unsigned int Container<T>::getCapacity() const{
    return capacity;
}

template <class T>
bool Container<T>::empty() const{
    return getSize()==0;
}

template <class T>
void Container<T>::clear(){
    unsigned int i=size;
        while (i>0) {
            pop(0);
            i--;
        }
}

template <class T>
void Container<T>::push_back(const T& t){
    if(size==capacity)  resize();
        v[size]=t;
        size++;

}

template <class T>
void Container<T>::pop(unsigned int i){
    if(size!=0 && i<size){
            size--;
            for(unsigned int j=i; j<size; j++){
                v[j]=v[j+1];
            }
            v[size]=nullptr;
        }
}

template <class T>
void Container<T>::switchItem(const T& t, unsigned int i){
    //delete v[i]
    distruggi(v);
    v[i]=t;
}

template<class T>
void Container<T>::erase(T t)
{
    unsigned int i=0;
    for(auto it= begin(); it!=end(); ++it){
        if((*it)== t)   return pop(i);
        else    i++;
    }
}

template <class T>
const T& Container<T>::operator[](unsigned int i) const{
    return v[i];
}

template <class T>
T& Container<T>::operator[](unsigned int i){
    return v[i];
}

template <class T>
typename Container<T>::Iterator Container<T>::begin(){
    return Iterator(v);
}

template <class T>
typename Container<T>::Iterator Container<T>::end(){
    return Iterator(v+size);
}

template <class T>
typename Container<T>::Const_Iterator Container<T>::cbegin() const{
    return Const_Iterator(v);
}

template <class T>
typename Container<T>::Const_Iterator Container<T>::cend() const{
    return Const_Iterator(v+size);
}

#endif /* CONTAINER_H */
