#ifndef DATA1DITERATOR_HPP
#define DATA1DITERATOR_HPP

#include "data/Data1D.hpp"
#include "data/DataIterator.hpp"

class Data1DIterator : public DataIterator {

public:
    Data1DIterator(const List<Data*>& data) : DataIterator(data) {}

    float getX() const;
    unsigned getY() const;

};

#endif
