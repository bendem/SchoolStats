#include "formatters/StatisticalSerie2DFormatter.hpp"

string StatisticalSerie2DFormatter::format() {
    ostringstream ss;

    DataSource2D& bob(serie.getDataSource());
    Data2DIterator it(bob.getData());

    int x = max(bob.getSubject().length(), DataSource::getTypeName(bob.getType()).length());

    ss << endl << "  = REPORT =" << endl
        << "  ==========" << endl
        << " Name: " << bob.getName() << endl
        << " Subjects of the study: " << setw(x) << bob.getSubject() << " | " << bob.getSubject2() << endl
        << " Data type:             " << setw(x) << DataSource::getTypeName(bob.getType()) << " | "
        << DataSource::getTypeName(bob.getType2()) << endl << endl
        << "  = DATA =" << endl
        << "  ========" << endl
        << Data2DListFormatter(bob.getData(), bob.getMaxX(), bob.getMaxY()).format() << endl
        << " Total count: " << bob.getTotalCount() << endl << endl << endl
        << " Average value1: " << serie.getAverageValue1() << endl
        << " Average value2: " << serie.getAverageValue2() << endl << endl

        << " Correlation:" << endl
        << " Coefficient a :" << serie.getCoefficientA() << endl
        << " Coefficient b :" << serie.getCoefficientB() << endl << endl;
    return ss.str();
}
