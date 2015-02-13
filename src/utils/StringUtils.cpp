#include "utils/StringUtils.hpp"

unsigned StringUtils::stringToUnsigned(string str) {
    if(str.empty()) {
        throw invalid_argument("empty string");
    }

    unsigned i = 0;
    if(str[0] == '+') {
        ++i;
    }
    if(i == str.length()) {
        throw invalid_argument("invalid integer, sign character only");
    }

    unsigned result = 0;
    while(i < str.length()) {
        if(str[i] < '0' || str[i] > '9') {
            throw invalid_argument("the string is not an integer");
        }
        result = result * 10 + (str[i] - '0');
        ++i;
    }
    return result;
}

int StringUtils::stringToInt(string str) {
    if(str.empty()) {
        throw invalid_argument("empty string");
    }

    bool negate = str[0] == '-';
    unsigned i = 0;
    if(str[0] == '+' || str[0] == '-') {
        ++i;
    }
    if(i == str.length()) {
        throw invalid_argument("invalid integer, sign character only");
    }

    int result = 0;
    while(i < str.length()) {
        if(str[i] < '0' || str[i] > '9') {
            throw invalid_argument("the string is not an integer");
        }
        result = result * 10 + (str[i] - '0');
        ++i;
    }
    return negate ? -result : result;
}

float StringUtils::stringToFloat(string str) {
    if(str.empty()) {
        throw invalid_argument("empty String");
    }

    float result = 0;
    bool dec = false;
    int decCount = 0;
    bool niggative = str[0] == '-';
    unsigned i = 0;

    if(str[0] == '+' || str[0] == '-') {
        ++i;
    }

    if(i == str.length()) {
        throw invalid_argument("not a valid float, sign character only");
    }

    while(i < str.length()) {
        if(str[i] == '.' || str[i] == ',') {
            if(dec) {
                throw invalid_argument("not a valid float, multiple points found");
            }
            dec = true;
            ++i;
            continue;
        }

        if(str[i] < '0' || str[i] > '9') {
            throw invalid_argument("not a valid float, found non decimal characters");
        }

        if(dec) {
            ++decCount;
        }
        result = result * 10 + (str[i] - '0');
        ++i;
    }

    if(niggative) {
        result = -result;
    }

    if(decCount == 0) {
        return result;
    }

    return result / pow(10.0f, decCount);
}

List<string> StringUtils::split(string str, char delim) {
    List<string> elems;
    istringstream ss(str);
    string item;
    while(getline(ss, item, delim)) {
        elems.add(item);
    }
    return elems;
}
