#include "data/DataSource.hpp"

DataSource::DataSource(string name, string subject, unsigned totalEffective) {
    this->name = name;
    this->subject = subject;
    this->totalEffective = totalEffective;
}

DataSource::DataSource(const DataSource& p) {
    this->name = p.name;
    this->subject = p.subject;
    this->totalEffective = p.totalEffective;
}

DataSource::~DataSource() {}

DataSource& DataSource::operator=(const DataSource& p) {
    this->name = p.name;
    this->subject = p.subject;
    this->totalEffective = p.totalEffective;
}
