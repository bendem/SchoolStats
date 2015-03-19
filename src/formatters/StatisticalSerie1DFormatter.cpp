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
        << yellow << "  avg: " << reset << setw(15) << setfill(' ') << serie.getAverage() << endl
        << yellow << "  cov: " << reset << setw(15) << setfill(' ') << serie.getCoefficientOfVariation() << endl
        << yellow << "  med: " << reset << setw(15) << setfill(' ') << serie.getMedian() << endl
        << yellow << "  mod: " << reset << setw(11) << setfill(' ') << serie.getMode()[0] << ", " << serie.getMode()[1] << ", " << serie.getMode()[2] << endl
        << yellow << "  ran: " << reset << setw(15) << setfill(' ') << serie.getRange() << endl
        << yellow << "  std: " << reset << setw(15) << setfill(' ') << serie.getStandardDeviation() << endl;
    return ss.str();
}
