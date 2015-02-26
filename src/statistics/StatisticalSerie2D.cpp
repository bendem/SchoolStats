#include "statistics/StatisticalSerie2D.hpp"

StatisticalSerie2D::StatisticalSerie2D(Sample* sample)
        : sample(sample), dataSource(sample->getDataSource()) {
    this->computeAverages();
    this->computeCoefficient();
}

void StatisticalSerie2D::forecast1() {

}

void StatisticalSerie2D::forecast2() {

}

void StatisticalSerie2D::computeAverages() {
    Data2DIterator it(this->dataSource.getData());
    float sumValue1 = 0;
    float sumValue2 = 0;

    while(!it.end()){
        sumValue1 += it.getX();
        sumValue2 += it.getY();
        ++it;
    }

    this->averageValue1 = sumValue1 / this->dataSource.getTotalCount();
    this->averageValue2 = sumValue2 / this->dataSource.getTotalCount();
}

void StatisticalSerie2D::computeCoefficient() {
    Data2DIterator it(this->dataSource.getData());
    float sumX=0;
    float sumXX=0;
    float sumY=0;
    float sumXY=0;

    while(!it.end()){
        sumX += it.getX();
        sumXX += it.getX()*it.getX();
        sumY += it.getY();
        sumXY += it.getX()*it.getY();
        ++it;
    }

    this->coefficientA = (sumXY - (sumX * sumY) / this->dataSource.getTotalCount())
        / (sumXX - (sumX * sumX) / this->dataSource.getTotalCount());
    this->coefficientB = this->averageValue2 - this->coefficientA * this->averageValue1;
}
