#include "formatters/Data1DListFormatter.hpp"

string Data1DListFormatter::format() {
    ostringstream ss;

    ConstData1DIterator it(data);
    ss << endl
        << yellow << "  = DATA =" << endl
        << "  ========" << reset << endl;
    while(!it.end()) {
        ss << ' ' << formatInterval(it.getX()) << blue << " | " << reset << it.getY() << endl;
        ++it;
    }

    return ss.str();
}

string Data1DListFormatter::formatInterval(float d) {
    ostringstream ss;

    if(type == DISCRETE) {
        return StringUtils::toString(d);
    }
    ss << green << '[' << reset << StringUtils::toString(d - interval / 2) << ';' << StringUtils::toString(d + interval / 2) << green << '[' << reset;

    return ss.str();
}
