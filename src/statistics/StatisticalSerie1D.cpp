#include "statistics/StatisticalSerie1D.hpp"

StatisticalSerie1D::StatisticalSerie1D(Sample* sample)
        : sample(sample), dataSource(sample->getDataSource()) {
    this->computeMode();
    this->computeAverage();
    this->computeMedian();
    this->computeStandardDeviation();
    this->computeRange();
    this->computeCoefficientOfVariation();
}

void StatisticalSerie1D::computeMode() {
    Data1DIterator it(this->dataSource.getData());
    this->mode.fill(0);
    unsigned highestCount = 0;
    unsigned currentMode = 0;

    while(!it.end()) {
        if(it.getY() > highestCount) {
            this->mode.fill(0);
            this->mode[0] = it.getX();
            highestCount = it.getY();
            currentMode = 1;
        } else if(it.getY() == highestCount && currentMode < this->mode.size()) {
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
    List<Data*>& data(this->dataSource.getData());
    unsigned totalCount = this->dataSource.getTotalCount();
    unsigned middle = totalCount / 2;

    // Discrete stuff
    if(this->dataSource.getType() == DISCRETE) {
        // Rebuild value list
        List<float> values;
        Data1DIterator it(data);
        while(!it.end()) {
            for(unsigned i = 0; i < it.getY(); ++i) {
                values.add(it.getX());
            }
            ++it;
        }

        if(totalCount % 2 == 0) { // Odd
            this->median = (values.get(middle) + values.get(middle + 1)) / 2;
        } else {
            this->median = values.get(middle);
        }
        return;
    }

    // Continous stuff

    // Looking up the interval containing the median
    Data1DIterator it(data);
    unsigned count = 0;
    Data1D* data1D = NULL;
    while(!it.end()) {
        ++it;
        data1D = it.get();
        if(count + data1D->getCount() > middle) {
            break;
        }
        count += data1D->getCount(); // Accumulate counts in intervals
    }

    Sanity::truthness(data1D != NULL, "Middle interval of continous data not found when computing median");

    float interval = static_cast<const ContinousDataSource&>(this->dataSource).getIntervalSizes();
    this->median = data1D->getValue() - interval / 2 // Start of interval
        + interval / data1D->getCount()
        * (data1D->getCount() - (middle - count)); // Position of the middle in the interval
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
    this->range = static_cast<Data1D*>(data.get(data.size() - 1))->getValue()
        - static_cast<Data1D*>(data.get(0))->getValue();
}

void StatisticalSerie1D::computeCoefficientOfVariation() {
    this->coefficientOfVariation = this->standardDeviation / this->average / 100;
}
