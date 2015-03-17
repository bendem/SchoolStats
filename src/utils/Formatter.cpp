#include "utils/Formatter.hpp"

ostream& operator<<(ostream& os, Formatter& f) {
    return os << f.format();
}
