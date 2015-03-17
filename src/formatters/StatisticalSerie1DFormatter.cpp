#include "formatters/StatisticalSerie1DFormatter.hpp"

string StatisticalSerie1DFormatter::format() const {
    ostringstream ss;
    ss
        << "\tavg: " << setw(15) << setfill(' ') << serie.getAverage() << endl
        << "\tcov: " << setw(15) << setfill(' ') << serie.getCoefficientOfVariation() << endl
        << "\tmed: " << setw(15) << setfill(' ') << serie.getMedian() << endl
        << "\tmod: " << setw(11) << setfill(' ') << serie.getMode()[0] << ", " << serie.getMode()[1] << ", " << serie.getMode()[2] << endl
        << "\tran: " << setw(15) << setfill(' ') << serie.getRange() << endl
        << "\tstd: " << setw(15) << setfill(' ') << serie.getStandardDeviation() << endl;
    return ss.str();
}
