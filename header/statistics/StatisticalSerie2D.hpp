#ifndef STATSTICALSERIE2D_HPP
#define STATSTICALSERIE2D_HPP

#include "data/Sample.hpp"
#include "data/DataSource2D.hpp"
#include "data/iterators/Data2DIterator.hpp"
#include "utils/StringUtils.hpp"

class StatisticalSerie2D {
private:
    Sample* sample;
    DataSource& dataSource;
    float averageValue1;
    float averageValue2;
    float coefficientA;
    float coefficientB;
public:
    StatisticalSerie2D(Sample*);

    void forecast1();
    void forecast2();

    void computeAverages();
    void computeCoefficients();

    DataSource2D& getData();

    float getCoefficientA() const;
    float getCoefficientB() const;
    float getAverageValue1() const;
    float getAverageValue2() const;
    DataSource2D& getDataSource();

};

inline DataSource2D& StatisticalSerie2D::getData() {
    return static_cast<DataSource2D&>(this->dataSource);
}

inline float StatisticalSerie2D::getCoefficientA() const {
    return this->coefficientA;
}

inline float StatisticalSerie2D::getCoefficientB() const {
    return this->coefficientB;
}

inline float StatisticalSerie2D::getAverageValue1() const {
    return this->averageValue1;
}

inline float StatisticalSerie2D::getAverageValue2() const {
    return this->averageValue2;
}

inline DataSource2D& StatisticalSerie2D::getDataSource() {
    return static_cast<DataSource2D&>(this->dataSource);
}

#endif
