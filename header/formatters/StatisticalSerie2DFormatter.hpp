#ifndef STATISTICALSERIE2DFORMATTER
#define STATISTICALSERIE2DFORMATTER

#include "formatters/Data2DListFormatter.hpp"
#include "statistics/StatisticalSerie2D.hpp"
#include "utils/Formatter.hpp"

using namespace std;

class StatisticalSerie2DFormatter : public Formatter {

private:
    StatisticalSerie2D& serie;

public:
    StatisticalSerie2DFormatter(StatisticalSerie2D& serie) : serie(serie) {}

    string format();

};

#endif
