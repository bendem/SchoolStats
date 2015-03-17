#ifndef STATISTICALSERIE1DFORMATTER
#define STATISTICALSERIE1DFORMATTER

#include "formatters/Data1DListFormatter.hpp"
#include "statistics/StatisticalSerie1D.hpp"
#include "utils/Formatter.hpp"

using namespace std;

class StatisticalSerie1DFormatter : public Formatter {

private:
    StatisticalSerie1D& serie;

public:
    StatisticalSerie1DFormatter(StatisticalSerie1D& serie) : serie(serie) {}

    string format();

};

#endif
