#ifndef DATASOURCE_HPP
#define DATASOURCE_HPP

#include <string>

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

public:


};

#endif
