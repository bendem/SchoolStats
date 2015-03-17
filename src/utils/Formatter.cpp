#include "utils/Formatter.hpp"

ostream& operator<<(ostream& os, const Formatter& f) {
    return os << f.format();
}
