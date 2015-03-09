#ifndef DATA1DITERATOR_HPP
#define DATA1DITERATOR_HPP

#include "data/Data1D.hpp"
#include "data/DataIterator.hpp"

class Data1DIterator : public DataIterator<Data1DIterator> {

public:
    Data1DIterator(const List<Data*>& data) : DataIterator<Data1DIterator>(data) {}

    const Data1D* get() const;
    float getX() const;
    unsigned getY() const;

};

inline const Data1D* Data1DIterator::get() const {
    return static_cast<Data1D*>(this->iterator.get());
}

inline float Data1DIterator::getX() const {
    return static_cast<Data1D*>(this->iterator.get())->getValue();
}

inline unsigned Data1DIterator::getY() const {
    return static_cast<Data1D*>(this->iterator.get())->getCount();
}

#endif
