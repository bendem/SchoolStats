#ifndef STATSTICALSERIE2D_HPP
#define STATSTICALSERIE2D_HPP

#include "data/Sample.hpp"
#include "data/Data2DIterator.hpp"
#include "utils/StringUtils.hpp"

class StatisticalSerie2D {
private:
    Sample* sample;
    const DataSource& dataSource;
    float averageValue1;
    float averageValue2;
    float coefficientA;
    float coefficientB;
public:
    StatisticalSerie2D(Sample*);

    void forecast1();
    void forecast2();

    void computeAverages();
    void computeCoefficient();

    float getCoefficientA() const;
    float getCoefficientB() const;
    float getAverageValue1() const;
    float getAverageValue2() const;

};


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


#endif
