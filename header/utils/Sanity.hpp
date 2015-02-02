#ifndef SANITY_HPP
#define SANITY_HPP

#include <iostream>
#include <stdexcept>

using namespace std;

/**
 * Class Providing code checking facilities.
 */
class Sanity {

public:

    /**
     * Throws an AssertionException with the provided error message if the provided condition is false.
     */
    static void truthness(bool cond, const string&);

    /**
     * Throws an AssertionException with the provided error message if the provided pointer is null.
     */
    static void nullness(const void* cond, const string&);

};

#endif
