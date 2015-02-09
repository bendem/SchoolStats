#ifndef DATA2DITERATOR_HPP
#define DATA2DITERATOR_HPP

#include "data/Data2D.hpp"
#include "data/DataIterator.hpp"

class Data2DIterator : public DataIterator {

public:
    Data2DIterator(const List<Data*>& data) : DataIterator(data) {}

    float getX() const;
    float getY() const;

};

#endif
