#ifndef DATASOURCE2D_HPP
#define DATASOURCE2D_HPP

#include "data/DataSource.hpp"

class DataSource2D : public DataSource {

private:
    string subject2;
    DataSourceType type2;

public:
    DataSource2D(string, string, string, DataSourceType, DataSourceType, const List<Data*>&);
    string getSubject2() const;
    DataSourceType getType2() const;
};

inline string DataSource2D::getSubject2() const {
    return this->subject2;
}

inline DataSourceType DataSource2D::getType2() const {
	return this->type2;	
}

#endif
