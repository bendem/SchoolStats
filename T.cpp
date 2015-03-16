#include <iostream>
#include <iomanip>

#include <errno.h>

#include <qapplication.h>

#include "data/DataSource.hpp"
#include "data/Sample.hpp"
#include "statistics/StatisticalSerie1D.hpp"
#include "statistics/StatisticalSerie2D.hpp"
#include "ui/Application.hpp"

using namespace std;

void* Graph2D(void*);

unsigned int menu(DataSource2D&);

int again = 1;

pthread_t threadHandle;
pthread_cond_t cond;
pthread_mutex_t mutex;

int Argc;
char** Argv;

int main(int argc, char* argv[]) {
    fstream x("application.log", ios::out | ios::trunc);
    streambuf* old = cerr.rdbuf(x.rdbuf());
    cerr << "Application starting" << endl;

    Argc = argc;
    Argv = argv;

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

            cerr << "Thread creation" << endl;
            if(pthread_create(&threadHandle, NULL, Graph2D, (void*) &c2D)) {
                throw runtime_error("pthread_create error");
            }

            cerr << "Forecast menu thingies" << endl;
            unsigned int choice;
            do {
                choice = menu(static_cast<DataSource2D&>(sample->getDataSource()));
                pthread_mutex_lock(&mutex);
                switch(choice) {
                    case 1: c2D.forecast1(); break;
                    case 2: c2D.forecast2(); break;
                }
                pthread_mutex_unlock(&mutex);
            } while(choice != 3);

            cerr << "Joining thread" << endl;
            if(pthread_join(threadHandle, NULL)) {
                throw runtime_error("pthread_join error");
            }
            cerr << "Unlocking mutex" << endl;
            if(pthread_mutex_unlock(&mutex)) {
                throw runtime_error("pthread_mutex_lock error");
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

unsigned int menu(DataSource2D& derp) {
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

void* Graph2D(void* serie) {
    cerr << "[Graph2D] We're in the thread \\o/" << endl;
    StatisticalSerie2D* serie2D = static_cast<StatisticalSerie2D*>(serie);

    cerr << "[Graph2D] Creating application" << endl;
    QApplication a(Argc, Argv);
    Application* app = new Application(serie2D);

    cerr << "[Graph2D] Showing application" << endl;
    app->show();
    a.exec();

    cerr << "[Graph2D] Deleting application" << endl;
    delete app;

    cerr << "[Graph2D] Thread end" << endl;
    return NULL;
}
