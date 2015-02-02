#ifndef SAMPLE_HPP
#define SAMPLE_HPP

#include <string>

#include "data/DataSource.hpp"

using namespace std;

class Sample {
private:
    DataSource* dataSource;

public:
    Sample(string filename, unsigned column);
    Sample(string filename, unsigned column1, unsigned column2);

    void display() const;

};

#endif
