#include <iostream>
#include <iomanip>

#include "data/Sample.hpp"
#include "statistics/StatisticalSerie1D.hpp"
#include "statistics/StatisticalSerie2D.hpp"
#include "utils/StringUtils.hpp"

using namespace std;

unsigned int menu();

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
                << "\tavg: " << setw(15) << setfill(' ') << c1D.getAverage() << endl
                << "\tcov: " << setw(15) << setfill(' ') << c1D.getCoefficientOfVariation() << endl
                << "\tmed: " << setw(15) << setfill(' ') << c1D.getMedian() << endl
                << "\tmod: " << setw(11) << setfill(' ') << c1D.getMode()[0] << ", " << c1D.getMode()[1] << ", " << c1D.getMode()[2] << endl
                << "\tran: " << setw(15) << setfill(' ') << c1D.getRange() << endl
                << "\tstd: " << setw(15) << setfill(' ') << c1D.getStandardDeviation() << endl
                ;
            //c1D.displayReport();
            break;
        }
        case 4: {
            cout << "Etude 2D" << endl;
            cerr << "Buidling 2D sample" << endl;
            sample = new Sample(argv[1], StringUtils::stringToUnsigned(argv[2]), StringUtils::stringToUnsigned(argv[3]));
            cerr << "Building StatisticalSerie2D" << endl;
            StatisticalSerie2D c2D(sample);
            //C2D.display();
            //C2D.forecast();
            unsigned int choice = menu();
            while(choice != 3) {
                if(choice == 1) {
                    c2D.forecast1();
                } else if(choice == 2) {
                    c2D.forecast2();
                }
            }
            break;
        }
        default:
            cout << "Invalid number of arguments" << endl;
    }

    cerr << "Cleaning up" << endl;
    delete sample;

    cerr << "Restoring cerr buffer" << endl;
    cerr.rdbuf(old);
    return 0;
}

unsigned int menu() {
    return 0;
}
