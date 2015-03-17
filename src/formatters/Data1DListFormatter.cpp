#include "formatters/Data1DListFormatter.hpp"

string Data1DListFormatter::format() {
    ostringstream ss;

    ConstData1DIterator it(data);
    ss << endl
        << "  = DATA =" << endl
        << "  ========" << endl;
    while(!it.end()) {
        ss << ' ' << formatInterval(it.getX()) << " | " << it.getY() << endl;
        ++it;
    }

    return ss.str();
}

string Data1DListFormatter::formatInterval(float d) {
    if(type == DISCRETE) {
        return StringUtils::toString(d);
    }
    return '[' + StringUtils::toString(d - interval / 2) + ';' + StringUtils::toString(d + interval / 2) + '[';
}
