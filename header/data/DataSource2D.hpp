#ifndef DATASOURCE2D_HPP
#define DATASOURCE2D_HPP

#include "data/Data2DIterator.hpp"
#include "data/DataSource.hpp"

class DataSource2D : public DataSource {

private:
    string subject2;
    DataSourceType type2;
    float minX;
    float minY;
    float maxX;
    float maxY;

public:
    DataSource2D(string, string, string, DataSourceType, DataSourceType, const List<Data*>&);
    string getSubject2() const;

    float getMinX() const;
    float getMinY() const;
    float getMaxX() const;
    float getMaxY() const;

};

inline string DataSource2D::getSubject2() const {
    return this->subject2;
}

inline float DataSource2D::getMinX() const {
    return this->minX;
}

inline float DataSource2D::getMinY() const {
    return this->minY;
}

inline float DataSource2D::getMaxX() const {
    return this->maxX;
}

inline float DataSource2D::getMaxY() const {
    return this->maxY;
}


#endif
