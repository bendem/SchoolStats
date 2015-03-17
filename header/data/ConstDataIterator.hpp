#ifndef CONSTDATAITERATOR_HPP
#define CONSTDATAITERATOR_HPP

#include "container/ConstIterator.hpp"
#include "data/Data.hpp"

template<class T>
class ConstDataIterator {

protected:
    ConstIterator<Data*> iterator;

public:
    ConstDataIterator(const List<Data*>& data) : iterator(data) {}
    ConstDataIterator(const ConstDataIterator<T>& p) : iterator(p.iterator) {}

    bool end() const;
    T& operator++();
    T operator++(int);

};

template<class T>
inline bool ConstDataIterator<T>::end() const {
    return iterator.end();
}

template<class T>
T& ConstDataIterator<T>::operator++() {
    ++this->iterator;
    return static_cast<T&>(*this);
}

template<class T>
T ConstDataIterator<T>::operator++(int) {
    T tmp(static_cast<T&>(*this));
    ++this->iterator;
    return tmp;
}

#endif
