#include "data/Data1DIterator.hpp"

inline float Data1DIterator::getX() const {
    return static_cast<Data1D*>(this->iterator.get())->getValue();
}

inline float Data1DIterator::getY() const {
    return static_cast<Data1D*>(this->iterator.get())->getCount();
}
