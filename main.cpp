#include <iostream>
#include <iomanip>

#include "data/Sample.hpp"
#include "data/DataSource.hpp"
#include "data/DataSource2D.hpp"
#include "statistics/StatisticalSerie1D.hpp"
#include "statistics/StatisticalSerie2D.hpp"
#include "utils/StringUtils.hpp"

using namespace std;

unsigned int menu(const DataSource2D&);
void displayReport1D(StatisticalSerie1D&);
void displayReport2D(StatisticalSerie2D&);

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
            /*cout
                << "\tavg: " << setw(15) << setfill(' ') << c1D.getAverage() << endl
                << "\tcov: " << setw(15) << setfill(' ') << c1D.getCoefficientOfVariation() << endl
                << "\tmed: " << setw(15) << setfill(' ') << c1D.getMedian() << endl
                << "\tmod: " << setw(11) << setfill(' ') << c1D.getMode()[0] << ", " << c1D.getMode()[1] << ", " << c1D.getMode()[2] << endl
                << "\tran: " << setw(15) << setfill(' ') << c1D.getRange() << endl
                << "\tstd: " << setw(15) << setfill(' ') << c1D.getStandardDeviation() << endl
                ;*/
            displayReport1D(c1D);
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
            unsigned int choice;
            do {
                choice = menu(static_cast<const DataSource2D&>(sample->getDataSource()));
                if(choice == 1) {
                    c2D.forecast1();
                } else if(choice == 2) {
                    c2D.forecast2();
                }
            } while (choice != 3);
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

void displayReport1D(StatisticalSerie1D& stat) {
    DataSource& bob(stat.getDataSource());
    Data1DIterator it(bob.getData());

    cout << "REPORT" << endl;
    cout << "---------------------------------------------" << endl;
    cout << "Name: " << bob.getName() << endl;
    cout << "Subject of the study: " << bob.getSubject() << endl;
    cout << "Data type: ";
    if(bob.getType() == CONTINOUS) {
        cout << "Continous" << endl;
    } else {
        cout << "Discrete" << endl;
    }
    cout << endl;
    cout << "DONNEES" << endl;
    cout << "---------------------------------------------" << endl;

    while(!it.end()) {
        cout << "\t" << it.getX() << "\t" << it.getY() << endl;
        ++it;
    }

    cout << "Total count: " << bob.getTotalCount() << endl << endl;

    cout << endl;
    cout << "STATS" << endl;
    cout << "---------------------------------------------" << endl;
    cout << "Moyenne: " << stat.getAverage()<< endl;
    cout << "Mediane: " << stat.getMedian()<< endl;
    cout << "Mode: " << stat.getMode()[0] << ", " << stat.getMode()[1] << ", " << stat.getMode()[2] << endl;
    cout << "Standard Deviation: " << stat.getStandardDeviation() << endl;
    cout << "Coefficient of variation: " << stat.getCoefficientOfVariation()<< endl;
}

void displayReport2D(StatisticalSerie2D& stat) {
    DataSource2D& bob(stat.getDataSource());
    Data2DIterator it(bob.getData());

    cout << "REPORT" << endl;
    cout << "---------------------------------------------" << endl;
    cout << "Name: " << bob.getName() << endl;
    cout << "Subjects of the study: " << bob.getSubject() << "|" << bob.getSubject2() << endl;
    cout << "Data type: ";
    if(bob.getType() == CONTINOUS) {
        cout << "Continous | ";
    } else {
        cout << "Discrete | ";
    }
    if(bob.getType2() == CONTINOUS) {
        cout << "Continous" << endl;
    } else {
        cout << "Discrete" << endl;
    }
    cout << endl;
    cout << "DATA" << endl;
    cout << "---------------------------------------------" << endl;

    while(!it.end()) {
        cout << "\t" << it.getX() << "\t" << it.getY() << endl;
        ++it;
    }

    cout << "Total count: " << bob.getTotalCount() << endl << endl;
    cout << endl;

    cout << "Average value1: " << stat.getAverageValue1() << endl;
    cout << "Average value2: " << stat.getAverageValue2() << endl;

    cout << endl;

    cout << "Correlation:" << endl;
    cout << "Coefficient a :" << stat.getCoefficientA() << endl;
    cout << "Coefficient b :" << stat.getCoefficientB() << endl;
    cout << endl;
}
