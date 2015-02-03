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
    static void truthness(bool, const string&);

    /**
     * Throws an AssertionException with the provided error message if the provided pointer is null.
     */
    static void nullness(const void*, const string&); // Should be template instead of void*

    static void streamness(const istream&, const string&);
    static void streamness(const ostream&, const string&);

};

#endif
