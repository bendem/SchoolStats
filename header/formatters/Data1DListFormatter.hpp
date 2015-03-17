#ifndef DATA1DLISTFORMATTER_HPP
#define DATA1DLISTFORMATTER_HPP

#include <sstream>

#include "container/List.hpp"
#include "data/Data.hpp"
#include "data/DataSource.hpp"
#include "data/iterators/ConstData1DIterator.hpp"
#include "utils/Formatter.hpp"
#include "utils/StringUtils.hpp"

using namespace std;

class Data1DListFormatter : public Formatter {

private:
    List<Data*>& data;
    DataSourceType type;
    float interval;

    string formatInterval(float);

public:
    Data1DListFormatter(List<Data*>& data, DataSourceType type, float interval)
        : data(data), type(type), interval(interval) {}

    string format();

};

#endif
