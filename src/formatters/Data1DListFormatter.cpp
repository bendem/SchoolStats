#include "formatters/Data1DListFormatter.hpp"

string Data1DListFormatter::format() const {
    ostringstream ss;

    ConstData1DIterator it(data);
    while(!it.end()) {
        ss << setw(7) << it.getX() << " | " << setw(7) << it.getY() << endl;
        ++it;
    }

    return ss.str();
}
