#ifndef DATASOURCE2D_HPP
#define DATASOURCE2D_HPP

#include "data/DataSource.hpp"

class DataSource2D : public DataSource {

private:
    string subject2;
    DataSourceType type2;

public:
    DataSource2D(string, string, string, DataSourceType, DataSourceType, const List<Data*>&);

};

#endif
