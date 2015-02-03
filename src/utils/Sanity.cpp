#include "utils/Sanity.hpp"

void Sanity::truthness(bool cond, const string& error) {
    if(!cond) {
        throw invalid_argument(error);
    }
}

void Sanity::nullness(const void* ptr, const string& error) {
    if(ptr == NULL) {
        throw invalid_argument(error);
    }
}

void Sanity::streamness(const istream& stream, const string& error) {
    if(stream.fail()) {
        throw runtime_error(error);
    }
}

void Sanity::streamness(const ostream& stream, const string& error) {
    if(stream.fail()) {
        throw runtime_error(error);
    }
}
