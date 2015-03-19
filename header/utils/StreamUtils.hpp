#ifndef STREAMUTILS_HPP
#define STREAMUTILS_HPP

// import EOF
#include <cstdio>

#include <iostream>
#include <string>

#include "container/List.hpp"
#include "utils/StringUtils.hpp"

using namespace std;

class StreamUtils {

private:
    static string read();

public:
    static List<string> readLines(istream&);
    static float readFloat();
    static unsigned readUnsignedInt();

};

#endif
