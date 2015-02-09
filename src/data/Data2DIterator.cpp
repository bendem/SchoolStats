#include "data/Data2DIterator.hpp"

inline float Data2DIterator::getX() const {
    return static_cast<Data2D*>(this->iterator.get())->getValue1();
}

inline float Data2DIterator::getY() const {
    return static_cast<Data2D*>(this->iterator.get())->getValue2();
}
