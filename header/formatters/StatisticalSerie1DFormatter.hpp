#ifndef STATISTICALSERIE1DFORMATTER
#define STATISTICALSERIE1DFORMATTER

#include <statistics/StatisticalSerie1D.hpp>
#include "utils/Formatter.hpp"

using namespace std;

class StatisticalSerie1DFormatter : public Formatter {

private:
    const StatisticalSerie1D& serie;

public:
    StatisticalSerie1DFormatter(const StatisticalSerie1D& serie) : serie(serie) {}

    string format() const;

};

#endif
