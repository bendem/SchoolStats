#include "data/DataSource.hpp"

DataSource::DataSource(string name, string subject, unsigned totalCount,
        DataSourceType type, const List<Data*>& data) : data(data) {
    this->name = name;
    this->subject = subject;
    this->totalCount = totalCount;
    this->type = type;
}

DataSource::DataSource(const DataSource& p) {
    this->name = p.name;
    this->subject = p.subject;
    this->totalCount = p.totalCount;
}

DataSource::~DataSource() {}

DataSource& DataSource::operator=(const DataSource& p) {
    this->name = p.name;
    this->subject = p.subject;
    this->totalCount = p.totalCount;
    return *this;
}
