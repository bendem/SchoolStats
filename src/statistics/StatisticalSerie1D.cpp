#include "statistics/StatisticalSerie1D.hpp"
#include "data/Data1DIterator.hpp"


StatisticalSerie1D::StatisticalSerie1D(Sample* sample) : sample(sample) {

}

void StatisticalSerie1D::computeMode() {
    float tempMode[3]={0,0,0};
    unsigned highEff=0;
    int k=0;

    Data1DIterator it = new Data1DIterator(this->sample->getDataSource().getData());

    while(!it.end()){
        if(it.getY() > highEff){
            for(int j=0; j<3; j++){
                tempMode[j]=0;
            }
            k=0;
            tempMode[k] = it.getX();
            highEff = it.getY();
            k++;
        }
        else{
            if(it.getY() == highEff){
                tempMode[k] = it.getX();
                k++;
            }
        }
        ++it;
    }
    for(int l=0;l<3;l++){
        mode[l] = tempMode[l];
    }
}

void StatisticalSerie1D::computeAverage() {
    float sum=0;

    Data1DIterator it = new Data1DIterator(this->sample->getDataSource().getData());

    while(!it.end()){
        sum = sum + (it.getX() * it.getY());
        ++it;
    }
    this->average = (float)sum * (1f/this->sample->getDataSource().getData().getTotalCount());
}

void StatisticalSerie1D::computeMedian() {

}


void StatisticalSerie1D::computeStandardDeviation() {
    float sum=0;

    Data1DIterator it = new Data1DIterator(this->sample->getDataSource().getData());

    while(!it.end()){
        sum = sum + (((it.getX() - this->average)*(it.getX() - this->average)) * it.getY());
        ++it;
    }

    standardDeviation = sqrt(sum / this->sample->getDataSource().getData().getTotalCount());
}

void StatisticalSerie1D::computeRange() {
    this->range = this->sample->getDataSource.getData().get(this->sample->getDataSource.getData().size() - 1) - this->sample->getDataSource.getData().get(0);
}

void StatisticalSerie1D::computeCoefficientOfVariation() {
    coefficientOfVariation = (standardDeviation / average) / 100;
}

void StatisticalSerie1D::displayReport() {

}
