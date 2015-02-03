#ifndef SAMPLE_HPP
#define SAMPLE_HPP

#include <fstream>
#include <string>

#include "container/List.hpp"
#include "data/DataSource.hpp"
#include "utils/StreamUtils.hpp"
#include "utils/StringUtils.hpp"


using namespace std;

class Sample {
private:
    DataSource* dataSource;

public:
    Sample(string filename, unsigned column1, unsigned column2 = -1);

    void display() const;

};

#endif
