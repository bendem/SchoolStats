#include "data/DataIterator.hpp"

inline bool DataIterator::end() const {
    return iterator.end();
}

DataIterator& DataIterator::operator++() {
    ++this->iterator;
    return *this;
}

DataIterator DataIterator::operator++(int) {
    DataIterator tmp(*this);
    ++this->iterator;
    return tmp;
}
