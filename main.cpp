#include <iostream>

#include "data/Sample.hpp"
#include "statistics/StatisticalSerie1D.hpp"
#include "statistics/StatisticalSerie2D.hpp"
#include "utils/StringUtils.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    fstream x("application.log", ios::out | ios::trunc);
    streambuf* old = cerr.rdbuf(x.rdbuf());
    cerr << "Application starting" << endl;

    Sample* sample = NULL;
    switch(argc) {
        case 2:
        case 3: {
            cout << "Etude 1D" << endl;
            cerr << "Building 1D sample" << endl;
            sample = new Sample(argv[1], argc == 2 ? 1 : StringUtils::stringToUnsigned(argv[2]));
            sample->display();
            cerr << "Building StatisticalSerie1D" << endl;
            StatisticalSerie1D c1D(sample);
            cout
                << "avg: " << c1D.getAverage() << endl
                << "cov: " << c1D.getCoefficientOfVariation() << endl
                << "med: " << c1D.getMedian() << endl
                << "mod: " << c1D.getMode()[0] << ", " << c1D.getMode()[1] << ", " << c1D.getMode()[2] << endl
                << "ran: " << c1D.getRange() << endl
                << "std: " << c1D.getStandardDeviation() << endl
                ;
            //c1D.displayReport();
            break;
        }
        case 4: {
            cout << "Etude 2D" << endl;
            cerr << "Buidling 2D sample" << endl;
            sample = new Sample(argv[1], StringUtils::stringToUnsigned(argv[2]), StringUtils::stringToUnsigned(argv[3]));
            cerr << "Building StatisticalSerie2D" << endl;
            //StatisticalSerie2D C2D(E1);
            //C2D.display();
            //C2D.forecast();
            break;
        }
    }

    cerr << "Cleaning up" << endl;
    delete sample;

    cerr << "Restoring cerr buffer" << endl;
    cerr.rdbuf(old);
    return 0;
}
