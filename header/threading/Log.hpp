#ifndef LOG_HPP
#define LOG_HPP

#include <fstream>

#include "threading/Mutex.hpp"

using namespace std;

class Log {

public:
    static void log(const string&, const string&);

private:
    Log(); // Prevent multiple instances

    Mutex mutex;
    ofstream os;

    static Log l;

};

#endif
