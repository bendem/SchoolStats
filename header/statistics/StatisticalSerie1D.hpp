#ifndef STATSTICALSERIE1D_HPP
#define STATSTICALSERIE1D_HPP

#include "data/Sample.hpp"

class StatisticalSerie1D {

private:
    Sample* sample;
    float mode[3];
    float average;
    float median;
    float standardDeviation; // Écart type
    float range;             // Étendue
    float coefficientOfVariation;

public:
    StatisticalSerie1D(Sample*);

};

#endif
