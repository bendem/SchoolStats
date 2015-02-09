#ifndef DATAITERATOR_HPP
#define DATAITERATOR_HPP

#include "container/ConstIterator.hpp"
#include "data/Data.hpp"

class DataIterator {

protected:
    ConstIterator<Data*> iterator;

public:
    DataIterator(const List<Data*>& data) : iterator(data) {}
    DataIterator(const DataIterator& p) : iterator(p.iterator) {}

    bool end() const;
    DataIterator& operator++();
    DataIterator operator++(int);

};

#endif
