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
