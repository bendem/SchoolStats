#ifndef MUTEX_HPP
#define MUTEX_HPP

#include <stdexcept>

using namespace std;

class Mutex {

public:
    Mutex();
    ~Mutex();

    void lock();
    void unlock();

private:
    pthread_mutex_t mutex;

    void fail(string);

};

#endif
