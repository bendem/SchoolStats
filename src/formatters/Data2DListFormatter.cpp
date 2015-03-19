#include "formatters/Data2DListFormatter.hpp"

string Data2DListFormatter::format() {
    ostringstream ss;

    unsigned maxXLen = StringUtils::toString(maxX).length();
    unsigned maxYLen = StringUtils::toString(maxY).length();

    Data2DIterator it(data);
    while(!it.end()) {
        ss << ' ' << setw(maxXLen) << it.getX() << blue << " | " << setw(maxYLen) << reset << it.getY() << endl;
        ++it;
    }

    return ss.str();
}
