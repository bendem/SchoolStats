#ifndef DATA2DITERATOR_HPP
#define DATA2DITERATOR_HPP

#include "data/Data2D.hpp"
#include "data/DataIterator.hpp"

class Data2DIterator : public DataIterator<Data2DIterator> {

public:
    Data2DIterator(List<Data*>& data) : DataIterator<Data2DIterator>(data) {}

    float getX();
    float getY();

};

inline float Data2DIterator::getX() {
    return static_cast<Data2D*>(this->iterator.get())->getValue1();
}

inline float Data2DIterator::getY() {
    return static_cast<Data2D*>(this->iterator.get())->getValue2();
}

#endif
