#include <iostream>
#include <iomanip>

#include "data/Sample.hpp"
#include "statistics/StatisticalSerie1D.hpp"
#include "statistics/StatisticalSerie2D.hpp"
#include "utils/StringUtils.hpp"

using namespace std;

unsigned int menu(const DataSource2D&);

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
            do {
                unsigned int choice = menu(static_cast<const DataSource2D&>(sample->getDataSource()));
                if(choice == 1) {
                    c2D.forecast1();
                } else if(choice == 2) {
                    c2D.forecast2();
                }
            } while(choice != 3)
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

unsigned int menu(const DataSource2D& derp) {
    string choice;
    unsigned choiceInt = 0;

    cout << "FORECAST" << endl;
    cout << "---------------------------------------------" << endl;
    cout << "\t1. Forecast for : " << derp.getSubject() << endl;
    cout << "\t2. Forecast for : " << derp.getSubject2() << endl;
    cout << "\t3. Exit" << endl;
    cout << endl;
    while(choiceInt > 3 || choiceInt < 1) {
        cout << "Choice: ";
        getline(cin, choice, cin.widen('\n'));
        choiceInt = StringUtils::stringToUnsigned(choice);
    }
    return choiceInt;
}
