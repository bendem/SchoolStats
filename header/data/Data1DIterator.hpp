#ifndef DATA1DITERATOR_HPP
#define DATA1DITERATOR_HPP

#include "data/Data1D.hpp"
#include "data/DataIterator.hpp"

class Data1DIterator : public DataIterator<Data1DIterator> {

public:
    Data1DIterator(List<Data*>& data) : DataIterator<Data1DIterator>(data) {}

    Data1D* get();
    float getX();
    unsigned getY();

};

inline Data1D* Data1DIterator::get() {
    return static_cast<Data1D*>(this->iterator.get());
}

inline float Data1DIterator::getX() {
    return static_cast<Data1D*>(this->iterator.get())->getValue();
}

inline unsigned Data1DIterator::getY() {
    return static_cast<Data1D*>(this->iterator.get())->getCount();
}

#endif
