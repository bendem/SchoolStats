#ifndef DATAITERATOR_HPP
#define DATAITERATOR_HPP

#include "container/Iterator.hpp"
#include "data/Data.hpp"

template<class T>
class DataIterator {

protected:
    Iterator<Data*> iterator;

public:
    DataIterator(List<Data*>& data) : iterator(data) {}
    DataIterator(const DataIterator& p) : iterator(p.iterator) {}

    Data* remove();

    bool end() const;
    T& operator++();
    T operator++(int);

};

template<class T>
inline Data* DataIterator<T>::remove() {
    return iterator.remove();
}

template<class T>
inline bool DataIterator<T>::end() const {
    return iterator.end();
}

template<class T>
T& DataIterator<T>::operator++() {
    ++this->iterator;
    return static_cast<T&>(*this);
}

template<class T>
T DataIterator<T>::operator++(int) {
    T tmp(static_cast<T&>(*this));
    ++this->iterator;
    return tmp;
}

#endif
