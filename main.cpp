#include <iostream>
#include <iomanip>

#include <qapplication.h>

#include "data/DataSource.hpp"
#include "data/Sample.hpp"
#include "statistics/StatisticalSerie1D.hpp"
#include "statistics/StatisticalSerie2D.hpp"
#include "ui/Application.hpp"
#include "threading/Mutex.hpp"

using namespace std;

unsigned int menu(const string&, const string&);
void* Graph2D(void*);

struct ThreadArgs {
    ThreadArgs(StatisticalSerie2D& serie2D, Mutex& mutex, int argc, char** argv)
        : serie2D(serie2D), mutex(mutex), argc(argc), argv(argv) {
    }
    StatisticalSerie2D& serie2D;
    Mutex& mutex;
    int argc;
    char** argv;
};

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
                << "\tstd: " << setw(15) << setfill(' ') << c1D.getStandardDeviation() << endl;
            //c1D.displayReport();
            break;
        }
        case 4: {
            cout << "Etude 2D" << endl;
            cerr << "Buidling 2D sample" << endl;
            sample = new Sample(argv[1], StringUtils::stringToUnsigned(argv[2]), StringUtils::stringToUnsigned(argv[3]));
            cerr << "Building StatisticalSerie2D" << endl;
            StatisticalSerie2D c2D(sample);
            DataSource2D dataSource2D(static_cast<DataSource2D&>(sample->getDataSource()));

            Mutex mutex;

            cerr << "Creating thread arguments" << endl;
            ThreadArgs args(c2D, mutex, argc, argv);

            cerr << "Thread creation" << endl;
            pthread_t threadHandle;
            if(pthread_create(&threadHandle, NULL, Graph2D, (void*) &args)) {
                throw runtime_error("pthread_create error");
            }

            cerr << "Forecast menu thingies" << endl;
            unsigned int choice;
            do {
                choice = menu(dataSource2D.getSubject(), dataSource2D.getSubject2());
                mutex.lock();
                switch(choice) {
                    case 1: c2D.forecast1(); break;
                    case 2: c2D.forecast2(); break;
                }
                mutex.unlock();
            } while(choice != 3);

            cerr << "Joining thread" << endl;
            if(pthread_join(threadHandle, NULL)) {
                throw runtime_error("pthread_join error");
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

unsigned int menu(const string& subject1, const string& subject2) {
    string choice;
    unsigned choiceInt = 0;

    cout << "FORECAST" << endl;
    cout << "---------------------------------------------" << endl;
    cout << "\t1. Forecast for : " << subject1 << endl;
    cout << "\t2. Forecast for : " << subject2 << endl;
    cout << "\t3. Exit" << endl;
    cout << endl;
    while(choiceInt > 3 || choiceInt < 1) {
        cout << "Choice: ";
        getline(cin, choice, cin.widen('\n'));
        choiceInt = StringUtils::stringToUnsigned(choice);
    }
    return choiceInt;
}

void* Graph2D(void* arguments) {
    cerr << "[Graph2D] We're in the thread \\o/" << endl;
    ThreadArgs* args = static_cast<ThreadArgs*>(arguments);

    cerr << "[Graph2D] Creating application" << endl;
    QApplication a(args->argc, args->argv);
    Application* app = new Application(args->serie2D, args->mutex);

    cerr << "[Graph2D] Showing application" << endl;
    app->show();
    a.exec();

    cerr << "[Graph2D] Deleting application" << endl;
    delete app;

    cerr << "[Graph2D] Thread end" << endl;
    return NULL;
}
