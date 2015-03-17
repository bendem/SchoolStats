#include "formatters/StatisticalSerie1DFormatter.hpp"

string StatisticalSerie1DFormatter::format() {
    float interval = 0;
    if(serie.getDataSource().getType() == CONTINOUS) {
        interval = static_cast<ContinousDataSource&>(serie.getDataSource()).getIntervalSizes();
    }

    ostringstream ss;
    ss
        << Data1DListFormatter(
               serie.getDataSource().getData(),
               serie.getDataSource().getType(),
               interval
           ).format() << endl
        << "\tavg: " << setw(15) << setfill(' ') << serie.getAverage() << endl
        << "\tcov: " << setw(15) << setfill(' ') << serie.getCoefficientOfVariation() << endl
        << "\tmed: " << setw(15) << setfill(' ') << serie.getMedian() << endl
        << "\tmod: " << setw(11) << setfill(' ') << serie.getMode()[0] << ", " << serie.getMode()[1] << ", " << serie.getMode()[2] << endl
        << "\tran: " << setw(15) << setfill(' ') << serie.getRange() << endl
        << "\tstd: " << setw(15) << setfill(' ') << serie.getStandardDeviation() << endl;
    return ss.str();
}
