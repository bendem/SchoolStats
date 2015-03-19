#include <iostream>
#include <iomanip>

#include <qapplication.h>

#include "data/DataSource.hpp"
#include "data/Sample.hpp"
#include "formatters/Data1DListFormatter.hpp"
#include "formatters/StatisticalSerie1DFormatter.hpp"
#include "formatters/StatisticalSerie2DFormatter.hpp"
#include "statistics/StatisticalSerie1D.hpp"
#include "statistics/StatisticalSerie2D.hpp"
#include "ui/Application.hpp"
#include "threading/Mutex.hpp"
#include "threading/Log.hpp"

using std::cout;
using std::endl;

unsigned int menu(const string&, const string&);
void* Graph2D(void*);

struct ThreadArgs {
    ThreadArgs(StatisticalSerie2D& serie, Mutex& mutex, int argc, char** argv)
        : serie(serie), mutex(mutex), argc(argc), argv(argv) {}

    StatisticalSerie2D& serie;
    Mutex& mutex;
    int argc;
    char** argv;
};

int main(int argc, char* argv[]) {
    Log::log("main", "Application starting");

    Sample* sample = NULL;
    switch(argc) {
        case 2:
        case 3: {
            cout << "Etude 1D" << endl;
            Log::log("main", "Building 1D sample");
            sample = new Sample(argv[1], argc == 2 ? 1 : StringUtils::stringToUnsigned(argv[2]));

            Log::log("main", "Building StatisticalSerie1D");
            StatisticalSerie1D c1D(sample);
            cout << StatisticalSerie1DFormatter(c1D).format() << endl;
            break;
        }

        case 4: {
            cout << "Etude 2D" << endl;
            Log::log("main", "Buidling 2D sample");
            sample = new Sample(argv[1], StringUtils::stringToUnsigned(argv[2]), StringUtils::stringToUnsigned(argv[3]));
            Log::log("main", "Building StatisticalSerie2D");
            StatisticalSerie2D c2D(sample);
            cout << StatisticalSerie2DFormatter(c2D).format() << endl;

            DataSource2D& dataSource2D(static_cast<DataSource2D&>(sample->getDataSource()));

            Mutex mutex;

            Log::log("main", "Creating thread arguments");
            ThreadArgs args(c2D, mutex, argc, argv);

            Log::log("main", "Thread creation");
            pthread_t threadHandle;
            if(pthread_create(&threadHandle, NULL, Graph2D, (void*) &args)) {
                throw runtime_error("pthread_create error");
            }

            Log::log("main", "Forecast menu thingies");
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

            Log::log("main", "Joining thread");
            if(pthread_join(threadHandle, NULL)) {
                throw runtime_error("pthread_join error");
            }
            break;
        }
        default:
            cout << "Invalid number of arguments" << endl;
    }

    Log::log("main", "Cleaning up");
    delete sample;

    return 0;
}

unsigned int menu(const string& subject1, const string& subject2) {
    string choice;
    unsigned choiceInt = 0;

    cout << endl
        << "  = FORECAST =" << endl
        << "  ============" << endl
        << "    1. Forecast for : " << subject1 << endl
        << "    2. Forecast for : " << subject2 << endl
        << "    3. Exit" << endl << endl;
    while(choiceInt > 3 || choiceInt < 1) {
        cout << "Choice: ";
        choiceInt = StreamUtils::readUnsignedInt();
    }
    return choiceInt;
}

void* Graph2D(void* arguments) {
    Log::log("Graph2D", "We're in the thread \\o/");
    ThreadArgs* args = static_cast<ThreadArgs*>(arguments);

    Log::log("Graph2D", "Creating application");
    QApplication a(args->argc, args->argv);
    Application* app = new Application(args->serie, args->mutex);

    Log::log("Graph2D", "Showing application");
    app->show();
    a.exec();

    Log::log("Graph2D", "Deleting application");
    delete app;

    Log::log("Graph2D", "Thread end");
    return NULL;
}
