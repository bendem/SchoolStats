#include "statistics/StatisticalSerie1D.hpp"

StatisticalSerie1D::StatisticalSerie1D(Sample* sample)
    : sample(sample), dataSource(sample->getDataSource()) {}

void StatisticalSerie1D::computeMode() {
    Data1DIterator it(this->dataSource.getData());
    fill(this->mode, this->mode + 3, 0);
    unsigned highestCount = 0;
    unsigned currentMode = 0;

    while(!it.end()) {
        if(it.getY() > highestCount) {
            for(unsigned j = 0; j < 3; ++j) {
                this->mode[j] = 0;
            }
            this->mode[0] = it.getX();
            highestCount = it.getY();
            currentMode = 1;
        } else if(it.getY() == highestCount){
            this->mode[currentMode++] = it.getX();
        }
        ++it;
    }
}

void StatisticalSerie1D::computeAverage() {
    Data1DIterator it(this->dataSource.getData());
    float sum = 0;

    while(!it.end()){
        sum += it.getX() * it.getY();
        ++it;
    }

    this->average = sum / this->dataSource.getTotalCount();
}

void StatisticalSerie1D::computeMedian() {
    const List<Data*>& data(this->dataSource.getData());

    // Discrete stuff is easy
    if(this->dataSource.getType() == DISCRETE) {
        if(this->dataSource.getTotalCount() % 2 == 0) {
            this->median = static_cast<Data1D*>(data.get(data.size() / 2 + 1))->getValue();
        } else {
            this->median = (
                static_cast<Data1D*>(data.get(data.size() / 2))->getValue() +
                    static_cast<Data1D*>(data.get(data.size() / 2 + 1))->getValue()
            ) / 2;
        }
        return;
    }

    // Continous stuff is less easy
    // TODO Write less easy stuff
}

void StatisticalSerie1D::computeStandardDeviation() {
    Data1DIterator it(this->dataSource.getData());
    float sum = 0;

    while(!it.end()) {
        sum += (it.getX() - this->average) * (it.getX() - this->average) * it.getY();
        ++it;
    }

    this->standardDeviation = sqrt(sum / this->dataSource.getTotalCount());
}

void StatisticalSerie1D::computeRange() {
    const List<Data*>& data(this->dataSource.getData());
    this->range = data.get(data.size() - 1) - data.get(0);
}

void StatisticalSerie1D::computeCoefficientOfVariation() {
    this->coefficientOfVariation = this->standardDeviation / this->average / 100;
}

void StatisticalSerie1D::displayReport() {
}
