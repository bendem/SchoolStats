#ifndef DATA2DITERATOR_HPP
#define DATA2DITERATOR_HPP

#include "data/Data2D.hpp"
#include "data/DataIterator.hpp"

class Data2DIterator : public DataIterator<Data2DIterator> {

public:
    Data2DIterator(const List<Data*>& data) : DataIterator(data) {}

    float getX() const;
    float getY() const;

};

inline float Data2DIterator::getX() const {
    return static_cast<Data2D*>(this->iterator.get())->getValue1();
}

inline float Data2DIterator::getY() const {
    return static_cast<Data2D*>(this->iterator.get())->getValue2();
}

#endif
