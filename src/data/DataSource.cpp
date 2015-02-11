#include "data/DataSource.hpp"

DataSource::DataSource(string name, string subject, unsigned totalCount,
        DataSourceType type, const List<Data*>& data) {
    this->name = name;
    this->subject = subject;
    this->totalCount = totalCount;
    this->type = type;
    this->data = data;
}

DataSource::DataSource(const DataSource& p) {
    this->name = p.name;
    this->subject = p.subject;
    this->totalCount = p.totalCount;
}

DataSource::~DataSource() {}

inline const List<Data*>& DataSource::getData() const {
    return this->data;
}

inline unsigned DataSource::getTotalCount() const {
    return this->totalCount;
}

DataSource& DataSource::operator=(const DataSource& p) {
    this->name = p.name;
    this->subject = p.subject;
    this->totalCount = p.totalCount;
    return *this;
}
