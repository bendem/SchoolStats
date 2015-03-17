#ifndef CONSTDATA1DITERATOR_HPP
#define CONSTDATA1DITERATOR_HPP

#include "data/Data1D.hpp"
#include "data/iterators/ConstDataIterator.hpp"

class ConstData1DIterator : public ConstDataIterator<ConstData1DIterator> {

public:
    ConstData1DIterator(const List<Data*>& data) : ConstDataIterator<ConstData1DIterator>(data) {}

    Data1D* get();
    float getX();
    unsigned getY();

};

inline Data1D* ConstData1DIterator::get() {
    return static_cast<Data1D*>(this->iterator.get());
}

inline float ConstData1DIterator::getX() {
    return static_cast<Data1D*>(this->iterator.get())->getValue();
}

inline unsigned ConstData1DIterator::getY() {
    return static_cast<Data1D*>(this->iterator.get())->getCount();
}

#endif
