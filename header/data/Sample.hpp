#ifndef SAMPLE_HPP
#define SAMPLE_HPP

#include <fstream>
#include <string>

#include "container/List.hpp"
#include "container/SortedList.hpp"
#include "data/Data1D.hpp"
#include "data/Data2D.hpp"
#include "data/DataSource.hpp"
#include "ContinousDataSource.hpp"
#include "data/DataSource2D.hpp"
#include "utils/StreamUtils.hpp"
#include "utils/StringUtils.hpp"

using namespace std;

class Sample {
private:
    DataSource* dataSource;

public:
    Sample(string filename, unsigned column);
    Sample(string filename, unsigned column1, unsigned column2);
    Sample(const Sample&);
    ~Sample();

    const DataSource& getDataSource() const;
    void display() const;

    Sample& operator=(Sample);

};

#endif
