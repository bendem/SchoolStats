#ifndef DATA1DLISTFORMATTER_HPP
#define DATA1DLISTFORMATTER_HPP

#include <sstream>

#include "container/List.hpp"
#include "data/Data.hpp"
#include "data/iterators/ConstData1DIterator.hpp"
#include "utils/Formatter.hpp"

using namespace std;

class Data1DListFormatter : public Formatter {

private:
    const List<Data*>& data;

public:
    Data1DListFormatter(const List<Data*>& data) : data(data) {}

    string format() const;

};

#endif
