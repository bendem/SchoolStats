#include "statistics/StatisticalSerie2D.hpp"

StatisticalSerie2D::StatisticalSerie2D(Sample* sample)
        : sample(sample), dataSource(sample->getDataSource()) {
    this->computeAverages();
    this->computeCoefficients();
}

void StatisticalSerie2D::forecast1() {
    float valueFloat, result;
    
    cout << endl << "    Enter a value for " << dataSource.getSubject() << ": ";
    valueFloat = StreamUtils::readFloat();
    result = coefficientA * valueFloat + coefficientB;
    cout << "    > Forecasted value = " << result << endl << endl;
}

void StatisticalSerie2D::forecast2() {
    float valueFloat, result;
    
    cout << "\tEnter a value for " << static_cast<DataSource2D&>(dataSource).getSubject2() << ": ";
    valueFloat = StreamUtils::readFloat();
    result = (valueFloat - coefficientB) / coefficientA;
    cout << "\tForecasted value = " << result << endl;
}

void StatisticalSerie2D::computeAverages() {
    Data2DIterator it(this->dataSource.getData());
    float sumValue1 = 0;
    float sumValue2 = 0;

    while(!it.end()) {
        sumValue1 += it.getX();
        sumValue2 += it.getY();
        ++it;
    }

    this->averageValue1 = sumValue1 / this->dataSource.getTotalCount();
    this->averageValue2 = sumValue2 / this->dataSource.getTotalCount();
}

void StatisticalSerie2D::computeCoefficients() {
    this->computeAverages();

    float sumX = 0;
    float sumXX = 0;
    float sumY = 0;
    float sumXY = 0;

    Data2DIterator it(this->dataSource.getData());
    while(!it.end()) {
        sumX += it.getX();
        sumXX += it.getX() * it.getX();
        sumY += it.getY();
        sumXY += it.getX() * it.getY();
        ++it;
    }

    this->coefficientA = (sumXY - (sumX * sumY) / this->dataSource.getTotalCount())
        / (sumXX - (sumX * sumX) / this->dataSource.getTotalCount());
    this->coefficientB = this->averageValue2 - this->coefficientA * this->averageValue1;
}
