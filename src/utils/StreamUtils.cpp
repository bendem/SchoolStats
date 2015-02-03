#include "utils/StreamUtils.hpp"

List<string> StreamUtils::readLines(istream& is) {
    List<string> lines;
    string line;
    while(is.peek() != EOF) {
        getline(is, line, is.widen('\n'));
        lines.add(line);
    }
    return lines;
}
