#ifndef DISCRETEDATASOURCE_HPP
#define DISCRETEDATASOURCE_HPP

#include "container/List.hpp"
#include "data/DataSource.hpp"
#include "data/Data.hpp"

class DiscreteDataSource : public DataSource {

public:
    DiscreteDataSource(string, string, unsigned, List<Data*>&);

};

#endif
