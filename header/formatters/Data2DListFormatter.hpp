#ifndef DATA2DLISTFORMATTER_HPP
#define DATA2DLISTFORMATTER_HPP

#include <string>
#include <sstream>

#include "container/List.hpp"
#include "data/Data.hpp"
#include "data/iterators/Data2DIterator.hpp"
#include "utils/Formatter.hpp"
#include "utils/StringUtils.hpp"

using namespace std;

class Data2DListFormatter : public Formatter {

private:
    List<Data*>& data;
    float maxX;
    float maxY;

public:
    Data2DListFormatter(List<Data*>& data, float maxX, float maxY)
        : data(data), maxX(maxX), maxY(maxY) {}

    string format();

};

#endif
