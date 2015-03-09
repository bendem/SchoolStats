#include "data/DataSource2D.hpp"

DataSource2D::DataSource2D(string name, string subject1, string subject2,
    DataSourceType type1, DataSourceType type2, const List<Data*>& data)
        : DataSource(name, subject1, data.size(), type1, data) {
    this->subject2 = subject2;
    this->type2 = type2;

    Data2DIterator it(data);
    this->minX = this->maxX = it.getX();
    this->minY = this->maxY = it.getY();
    ++it;
    while(!it.end()) {
        this->minX = min(this->minX, it.getX());
        this->minY = min(this->minY, it.getY());
        this->maxX = max(this->maxX, it.getX());
        this->maxY = max(this->maxY, it.getY());
        ++it;
    }
}
