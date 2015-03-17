#ifndef FORMATTER_HPP
#define FORMATTER_HPP

#include <iomanip>
#include <sstream>

using namespace std;

class Formatter {

public:
    virtual string format() const = 0;

};

ostream& operator<<(ostream&, const Formatter&);

#endif
