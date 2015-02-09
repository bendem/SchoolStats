#include "data/DataSource2D.hpp"

DataSource2D::DataSource2D(string name, string subject1, string subject2,
    DataSourceType type1, DataSourceType type2, const List<Data*>& data)
        : DataSource(name, subject1, data.size(), type1, data) {
    this->subject2 = subject2;
    this->type2 = type2;

}
