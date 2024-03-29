#ifndef STATSTICALSERIE1D_HPP
#define STATSTICALSERIE1D_HPP

#include "container/Array.hpp"
#include "data/iterators/Data1DIterator.hpp"
#include "data/Sample.hpp"
#include "data/DataSource.hpp"

class StatisticalSerie1D {

private:
    Sample* sample;
    DataSource& dataSource;
    Array<float, 3> mode;
    float average;
    float median;
    float standardDeviation; // Écart type
    float range;             // Étendue
    float coefficientOfVariation;

    void computeMode();
    void computeAverage();
    void computeMedian();
    void computeStandardDeviation();
    void computeRange();
    void computeCoefficientOfVariation();

public:
    StatisticalSerie1D(Sample*);

    Array<float, 3> getMode() const;
    float getAverage() const;
    float getMedian() const;
    float getStandardDeviation() const;
    float getRange() const;
    float getCoefficientOfVariation() const;
    DataSource& getDataSource();

};

inline Array<float, 3> StatisticalSerie1D::getMode() const {
    return this->mode;
}

inline float StatisticalSerie1D::getAverage() const {
    return this->average;
}

inline float StatisticalSerie1D::getMedian() const {
    return this->median;
}

inline float StatisticalSerie1D::getStandardDeviation() const {
    return this->standardDeviation;
}

inline float StatisticalSerie1D::getRange() const {
    return this->range;
}

inline float StatisticalSerie1D::getCoefficientOfVariation() const {
    return this->coefficientOfVariation;
}

inline DataSource& StatisticalSerie1D::getDataSource() {
    return this->dataSource;
}

#endif
