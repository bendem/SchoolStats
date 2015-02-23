#ifndef STRINGUTILS_HPP
#define STRINGUTILS_HPP

#include <cmath>
#include <stdexcept>
#include <string>
#include <sstream>

#include "container/List.hpp"

using namespace std;

class StringUtils {

public:
    static unsigned stringToUnsigned(string);
    static int stringToInt(string);
    static float stringToFloat(string);
    static List<string> split(string, char);

    template<class T>
    static string toString(const T& p) {
        ostringstream is;
        is << p;
        return is.str();
    }

};

#endif
