#include "threading/Mutex.hpp"

Mutex::Mutex() {
    if(pthread_mutex_init(&mutex, NULL)) {
        fail("init");
    }
}

Mutex::~Mutex() {
    if(pthread_mutex_destroy(&mutex)) {
        fail("destroy");
    }
}

void Mutex::lock() {
    if(pthread_mutex_lock(&mutex)) {
        fail("lock");
    }
}

void Mutex::unlock() {
    if(pthread_mutex_unlock(&mutex)) {
        fail("unlock");
    }
}

void Mutex::fail(string action) {
    throw runtime_error("Mutex" + action + " failed");
}
