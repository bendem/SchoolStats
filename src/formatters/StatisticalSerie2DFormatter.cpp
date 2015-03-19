#include "formatters/StatisticalSerie2DFormatter.hpp"

string StatisticalSerie2DFormatter::format() {
    ostringstream ss;

    DataSource2D& bob(serie.getDataSource());
    Data2DIterator it(bob.getData());

    int x = max(bob.getSubject().length(), DataSource::getTypeName(bob.getType()).length());

    ss << endl << yellow << "  = REPORT =" << endl
        << "  ==========" << reset << endl
        << " Name: " << bob.getName() << endl
        << " Subjects of the study: " << setw(x) << bob.getSubject() << blue << " | " << reset << bob.getSubject2() << endl
        << " Data type:             " << setw(x) << DataSource::getTypeName(bob.getType()) << blue << " | " << reset
        << DataSource::getTypeName(bob.getType2()) << endl << endl
        << yellow << "  = DATA =" << endl
        << "  ========" << reset << endl
        << Data2DListFormatter(bob.getData(), bob.getMaxX(), bob.getMaxY()).format() << endl
        << yellow << " Total count: " << reset << bob.getTotalCount() << endl << endl << endl
        << yellow << " Average value1: " << reset << serie.getAverageValue1() << endl
        << yellow << " Average value2: " << reset << serie.getAverageValue2() << endl << endl

        << yellow << " Correlation:" << reset << endl
        << yellow << " Coefficient a :" << reset << serie.getCoefficientA() << endl
        << yellow << " Coefficient b :" << reset << serie.getCoefficientB() << endl << endl;
    return ss.str();
}
