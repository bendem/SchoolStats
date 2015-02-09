#ifndef DATASOURCE_HPP
#define DATASOURCE_HPP

#include <string>
#include <container/List.hpp>
#include "Data.hpp"

using namespace std;

enum DataSourceType {
    CONTINOUS,
    DISCRETE
};

class DataSource {

protected:
    string name;
    string subject;
    unsigned totalEffective;
    DataSourceType type;
    List<Data*> data;

public:
    DataSource(string, string, unsigned, DataSourceType, const List<Data*>&);
    DataSource(const DataSource&);
    virtual ~DataSource() = 0;

    DataSource& operator=(const DataSource&);

};

#endif
