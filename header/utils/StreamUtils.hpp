#ifndef STREAMUTILS_HPP
#define STREAMUTILS_HPP

// import EOF
#include <cstdio>

#include <iostream>
#include <string>


#include "container/List.hpp"

using namespace std;

class StreamUtils {

public:
    static List<string> readLines(istream&);

};

#endif
