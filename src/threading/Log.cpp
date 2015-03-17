#include "threading/Log.hpp"

Log Log::l;

Log::Log() : os("application.log", ios::out | ios::trunc) {
}

void Log::log(const string& name, const string& msg) {
    l.mutex.lock();
    l.os << '[' << name << "] " << msg << endl;
    l.mutex.unlock();
}
