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
    unsigned totalCount;
    DataSourceType type;
    List<Data*> data;

public:
    DataSource(string, string, unsigned, DataSourceType, List<Data*>&);
    virtual ~DataSource() = 0;

    List<Data*>& getData();
    unsigned getTotalCount() const;
    DataSourceType getType() const;
    string getSubject() const;
    string getName() const;

    DataSource& operator=(const DataSource&);

};

inline List<Data*>& DataSource::getData() {
    return this->data;
}

inline unsigned DataSource::getTotalCount() const {
    return this->totalCount;
}

inline DataSourceType DataSource::getType() const {
    return this->type;
}

inline string DataSource::getSubject() const {
    return this->subject;
}

inline string DataSource::getName() const {
    return this->name;
}

#endif
