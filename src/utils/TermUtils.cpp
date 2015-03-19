#include "utils/TermUtils.hpp"

static const string ESCAPE_SEQUENCE = "\033[";

// Manipulators without args
ostream& black(ostream& os)   { return os << ESCAPE_SEQUENCE << "30m"; }
ostream& red(ostream& os)     { return os << ESCAPE_SEQUENCE << "31m"; }
ostream& green(ostream& os)   { return os << ESCAPE_SEQUENCE << "32m"; }
ostream& yellow(ostream& os)  { return os << ESCAPE_SEQUENCE << "33m"; }
ostream& blue(ostream& os)    { return os << ESCAPE_SEQUENCE << "34m"; }
ostream& magenta(ostream& os) { return os << ESCAPE_SEQUENCE << "35m"; }
ostream& cyan(ostream& os)    { return os << ESCAPE_SEQUENCE << "36m"; }
ostream& white(ostream& os)   { return os << ESCAPE_SEQUENCE << "37m"; }
ostream& reset(ostream& os)   { return os << ESCAPE_SEQUENCE << "0m"; }
