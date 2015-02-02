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
        result = result * 10  + (str[i] - '0');
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
        result = result * 10  + (str[i] - '0');
        ++i;
    }
    return negate ? -result : result;
}
